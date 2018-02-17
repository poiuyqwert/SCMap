//
//  LocationsMapLayer.h
//  SCMap
//
//  Created by Zach Zahos on 2018-02-03.
//

#pragma once

#include "MapLayer.h"

#include <map>

class QPainter;
class QRect;

class LocationsMapLayer : public MapLayer {
	
public:
	LocationsMapLayer() {}
	
	void update(Map *map, QPainter &painter, QRect rect);
};

