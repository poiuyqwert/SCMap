//
//  TerrainMapLayer.h
//  SCMap
//
//  Created by Zach Zahos on 2016-01-13.
//
//

#pragma once

#include "MapLayer.h"

#include <map>

class QPainter;
class QRect;

class TerrainMapLayer : public MapLayer {
	int colorShift, ticks;
public:
	TerrainMapLayer()
		: MapLayer(), colorShift(0), ticks(0) {}
	
	void update(Map *map, QPainter &painter, QRect rect);
};
