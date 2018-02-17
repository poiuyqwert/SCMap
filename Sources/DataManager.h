//
//  DataManager.h
//  SCMap
//
//  Created by Zach Zahos on 2018-02-14.
//

#pragma once

#include "Properties.h"

struct UnitsDAT;
class PCX;
class TBL;

class DataManager {
	DataManager() {}
	
	DataManager(DataManager const&);    // Don't Implement
	void operator=(DataManager const&); // Don't implement
	
	GETTER(UnitsDAT*, unitsDat);
	GETTER(PCX*, tminimap);
	GETTER(TBL*, stat_txt);
public:
	static DataManager& getInstance() {
		static DataManager instance;
		return instance;
	}
	
	void load_data();
};
