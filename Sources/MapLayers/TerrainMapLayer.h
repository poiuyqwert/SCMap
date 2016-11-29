//
//  TerrainMapLayer.h
//  SCMap
//
//  Created by Zach Zahos on 2016-01-13.
//
//

#pragma once

#include "MapLayer.h"

#include <libSCMS/Types.h>
#include <libSCMS/Images.h>

#include <map>

class QPainter;
class QRect;

class TerrainMapLayer : public MapLayer {
	std::map<u16, Pixels> pixels;
	int colorShift, ticks;
public:
	TerrainMapLayer();
	
	void update(Map *map, QPainter &painter, QRect rect);
};
