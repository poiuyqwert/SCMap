//
//  Map.cpp
//  SCMap
//
//  Created by Zach Zahos on 2016-01-10.
//
//

#include "Map.h"
#include "DataManager.h"

#include <libSCMS/CHK.h>
#include <libSCMS/CHKSections.h>
#include <libSCMS/Palette.h>

#include <SFmpqapi.h>


Map* Map::fromCHK(QString path, CHK *chk, MPQHANDLE mpq) {
	CHKSectionERA *era = chk->get_section<CHKSectionERA>();
	if (era == nullptr) {
		return nullptr;
	}

	Tileset tileset = DataManager::getInstance().get_tileset(era->get_tileset());
	
	return new Map(path, chk, tileset, mpq);
}

Map* Map::loadMap(QString qpath) {
	CHK *chk = nullptr;
	
	const char *path = qpath.toLatin1().data();
	MPQHANDLE mpq = MpqOpenArchiveForUpdate(path, MOAU_OPEN_EXISTING | MOAU_READ_ONLY, 1024);
	
	if (mpq) {
		MPQHANDLE file;
		if (SFileOpenFileEx(mpq, "staredit\\scenario.chk", SFILE_SEARCH_CURRENT_ONLY, &file) && file) {
			DWORD size = SFileGetFileSize(file, nullptr);
			DWORD totalread = 0, read = 0;
			u8 buffer[size];
			while (read < size && SFileReadFile(file, buffer+totalread, size-totalread, &read, nullptr)) {
				totalread += read;
			}
			SFileCloseFile(file);
			chk = new CHK();
			try {
				chk->open_data(buffer, size);
			} catch (...) {
				MpqCloseUpdatedArchive(mpq, 0);
				throw;
			}
		} else {
			DWORD err = GetLastError();
			printf("%d", err);
		}
	} else {
		chk = new CHK();
		chk->open_file(path);
	}
	
	if (!chk) {
		return nullptr;
	}
	
	Map *map = Map::fromCHK(qpath, chk);
	if (!map) {
		delete chk;
	}
	return map;
}

Map* Map::newMap(Size<u16> size) {
	CHK *chk = new CHK();
	
	CHKSectionVER *ver = new CHKSectionVER(chk);
	ver->set_version(CHKSectionVER::BroodWar);
	chk->set_section(ver);
	
	CHKSectionERA *era = new CHKSectionERA(chk);
	era->set_tileset(CHKSectionERA::Badlands);
	chk->set_section(era);
	
	CHKSectionDIM *dim = new CHKSectionDIM(chk);
	dim->set_size(size);
	chk->set_section(dim);
	
	CHKSectionMRGN *mrgn = new CHKSectionMRGN(chk);
	chk->set_section(mrgn);
	
	CHKSectionUNIT *unit = new CHKSectionUNIT(chk);
	chk->set_section(unit);
	
	CHKSectionMTXM *mtxm = new CHKSectionMTXM(chk);
	CHKTile *tiles = new CHKTile[size.area()];
	for (int y = 0; y < size.height; y++) {
		for (int x = 0; x < size.width; x++) {
			u16 megatileGroup = 1 + (y / 32) * (size.width / 32) + (x / 32);
			tiles[y*size.width+x] = {1,megatileGroup};
		}
	}
	mtxm->set_tiles(tiles);
	chk->set_section(mtxm);
	
	Map *map = Map::fromCHK("Untitled", chk);
	if (!map) {
		delete chk;
	}
	return map;
}

Pixels Map::get_megatile(CHKTile tile) {
	CV5Group group = this->tileset.cv5->get_group(tile.megatileGroup);
	Pixels megatile;
	if (this->megatiles.count(group.megatiles[tile.megatile])) {
		megatile = this->megatiles[group.megatiles[tile.megatile]];
	} else {
		megatile = tileset.get_megatile(group.megatiles[tile.megatile]);
		this->megatiles[group.megatiles[tile.megatile]] = megatile;
	}
	return megatile;
}

void Map::set_editMode(EditMode::Mode editMode) {
	this->editMode = editMode;
	emit editModeChanged(editMode);
}
