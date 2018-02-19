//
//  DataManager.cpp
//  SCMap
//
//  Created by Zach Zahos on 2018-02-14.
//

#include "DataManager.h"

#include <libSCMS/UnitsDAT.h>
#include <libSCMS/PCX.h>
#include <libSCMS/TBL.h>
#include <libSCMS/Tileset.h>
#include <libSCMS/CHKSectionERA.h>
#include <libSCMS/Palette.h>

u8* DataManager::read_file(const char *path, int &size) {
	size = 0;
	for (int i = 0; i < (int)this->mpqs.size(); i++) {
		MPQHANDLE mpq = this->mpqs[i];
		MPQHANDLE file;
		if (SFileOpenFileEx(mpq, path, SFILE_SEARCH_CURRENT_ONLY, &file) && file) {
			DWORD filesize = SFileGetFileSize(file, nullptr);
			DWORD totalread = 0, read = 0;
			u8 *buffer = new u8[filesize];
			while (read < filesize && SFileReadFile(file, buffer+totalread, filesize-totalread, &read, nullptr)) {
				totalread += read;
			}
			SFileCloseFile(file);
			if (totalread != filesize) {
				delete[] buffer;
				continue;
			}
			size = filesize;
			return buffer;
		}
	}
	return nullptr;
}

void DataManager::load_data() {
	char const * paths[3] = {
		"patch_rt.mpq",
		"broodat.mpq",
		"stardat.mpq"
	};
	for (int i = 0; i < 3; i++) {
		MPQHANDLE handle = MpqOpenArchiveForUpdate(paths[i], MOAU_OPEN_EXISTING | MOAU_READ_ONLY, 1024);
		if (handle) {
			this->mpqs.push_back(handle);
		}
	}
	
	int size = 0;
	u8 *data = this->read_file("arr\\units.dat", size);
	this->unitsDat = new UnitsDAT();
	this->unitsDat->open_data(data, size);
	data = this->read_file("game\\tminimap.pcx", size);
	this->tminimap = new PCX();
	this->tminimap->open_data(data, size);
	data = this->read_file("rez\\stat_txt.tbl", size);
	this->stat_txt = new TBL();
	this->stat_txt->open_data(data, size);
}

Tileset DataManager::get_tileset(u16 tileset) {
	const char *tilesetFilename = CHKSectionERA::TilesetFilenames[tileset];
	char file[256] = {0};
	sprintf(file, "tileset\\%s.cv5", tilesetFilename);
	int size = 0;
	u8 *data = this->read_file(file, size);
	CV5 *cv5 = new CV5();
	cv5->open_data(data, size);
	sprintf(file, "tileset\\%s.vf4", tilesetFilename);
	data = this->read_file(file, size);
	VF4 *vf4 = new VF4();
	vf4->open_data(data, size);
	sprintf(file, "tileset\\%s.vx4", tilesetFilename);
	data = this->read_file(file, size);
	VX4 *vx4 = new VX4();
	vx4->open_data(data, size);
	sprintf(file, "tileset\\%s.vr4", tilesetFilename);
	data = this->read_file(file, size);
	VR4 *vr4 = new VR4();
	vr4->open_data(data, size);
	sprintf(file, "tileset\\%s\\dddata.bin", tilesetFilename);
	data = this->read_file(file, size);
	DDData *dddata = new DDData();
	dddata->open_data(data, size);
	sprintf(file, "tileset\\%s.wpe", tilesetFilename);
	data = this->read_file(file, size);
	Palette *wpe = new Palette();
	wpe->open_data(data, size);
	
	return Tileset(cv5, vf4, vx4, vr4, dddata, wpe);
}
