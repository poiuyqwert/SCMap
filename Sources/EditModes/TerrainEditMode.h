//
//  TerrainEditMode.h
//  SCMap
//
//  Created by Zach Zahos on 2016-01-23.
//
//

#pragma once

#include "EditMode.h"

#include <QString>

class TerrainEditMode : public EditMode {
public:
	TerrainEditMode()
		: EditMode() {}
	
	QString name()
		{ return "Terrain"; }
	
	void update(Map *map, QPainter &painter, QRect rect);
	void click(Map *map, QPoint point);
};
