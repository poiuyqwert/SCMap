//
//  Map.cpp
//  SCMap
//
//  Created by Zach Zahos on 2016-01-10.
//
//

#include "Map.h"

#include <libSCMS/CHK.h>
#include <libSCMS/CHKSections.h>
#include <libSCMS/Palette.h>

#include <SFmpqapi.h>


Map* Map::fromCHK(CHK *chk) {
	CHKSectionERA *era = chk->get_section<CHKSectionERA>();
	if (era == nullptr) {
		return nullptr;
	}
	
	const char *tilesetFilename = CHKSectionERA::TilesetFilenames[era->get_tileset()];
	char file[256] = {0};
	sprintf(file, "%s.cv5", tilesetFilename);
	CV5 *cv5 = new CV5(file);
	sprintf(file, "%s.vf4", tilesetFilename);
	VF4 *vf4 = new VF4(file);
	sprintf(file, "%s.vx4", tilesetFilename);
	VX4 *vx4 = new VX4(file);
	sprintf(file, "%s.vr4", tilesetFilename);
	VR4 *vr4 = new VR4(file);
	sprintf(file, "dddata.bin");
	DDData *dddata = new DDData(file);
	sprintf(file, "%s.wpe", tilesetFilename);
	Palette *wpe = new Palette(file);
	
	Tileset tileset(cv5, vf4, vx4, vr4, dddata, wpe);
	
	return new Map(chk, tileset);
}

Map* Map::loadMap(QString filename) {
	CHK *chk = nullptr;
	
	const char *path = filename.toLatin1().data();
	MPQHANDLE handle = MpqOpenArchiveForUpdate(path, MOAU_OPEN_EXISTING | MOAU_READ_ONLY, 1024);
	
	if (handle) {
		MPQHANDLE file;
		if (SFileOpenFileEx(handle, "staredit\\scenario.chk", SFILE_SEARCH_CURRENT_ONLY, &file) && file) {
			DWORD size = SFileGetFileSize(file, nullptr);
			DWORD totalread = 0, read = 0;
			u8 buffer[size];
			while (read < size && SFileReadFile(file, buffer+totalread, size-totalread, &read, nullptr)) {
				totalread += read;
			}
			chk = new CHK();
			chk->open_data(buffer, size);
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
	
	Map *map = Map::fromCHK(chk);
	if (!map) {
		delete chk;
	}
	return map;
}

Map* Map::newMap() {
	CHK *chk = new CHK();
	
	CHKSectionVER *ver = new CHKSectionVER(chk);
	ver->set_version(CHKSectionVER::BroodWar);
	chk->set_section(ver);
	
	CHKSectionERA *era = new CHKSectionERA(chk);
	era->set_tileset(CHKSectionERA::Badlands);
	chk->set_section(era);
	
	Size<u16> mapSize = {64,128};
	CHKSectionDIM *dim = new CHKSectionDIM(chk);
	dim->set_size(mapSize);
	chk->set_section(dim);
	
	CHKSectionMRGN *mrgn = new CHKSectionMRGN(chk);
	chk->set_section(mrgn);
	
	CHKSectionUNIT *unit = new CHKSectionUNIT(chk);
	chk->set_section(unit);
	
	CHKSectionMTXM *mtxm = new CHKSectionMTXM(chk);
	CHKTile *tiles = new CHKTile[mapSize.area()];
	for (int y = 0; y < mapSize.height; y++) {
		for (int x = 0; x < mapSize.width; x++) {
			u16 megatileGroup = 1 + (y / 32) * (mapSize.width / 32) + (x / 32);
			tiles[y*mapSize.width+x] = {1,megatileGroup};
		}
	}
	mtxm->set_tiles(tiles);
	chk->set_section(mtxm);
	
	Map *map = Map::fromCHK(chk);
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
