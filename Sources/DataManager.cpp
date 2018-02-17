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


void DataManager::load_data() {
	this->unitsDat = new UnitsDAT("units.dat");
	this->tminimap = new PCX("tminimap.pcx");
	this->stat_txt = new TBL("stat_txt.tbl");
}
