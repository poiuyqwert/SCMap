//
//  DataManager.h
//  SCMap
//
//  Created by Zach Zahos on 2018-02-14.
//

#pragma once

#include "Properties.h"

#include <vector>

#include <libSCMS/Types.h>

#include <SFmpqapi.h>

struct UnitsDAT;
class PCX;
class TBL;
struct Tileset;


class DataManager {
	std::vector<MPQHANDLE> mpqs;
	
	GETTER(UnitsDAT*, unitsDat);
	GETTER(PCX*, tminimap);
	GETTER(TBL*, stat_txt);
	
	DataManager() {}
	
	DataManager(DataManager const&);    // Don't Implement
	void operator=(DataManager const&); // Don't implement
	
	u8* read_file(const char *path, int &size);
public:
	static DataManager& getInstance() {
		static DataManager instance;
		return instance;
	}
	
	void load_data();
	
	Tileset get_tileset(u16 tileset);
};
