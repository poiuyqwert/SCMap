//
//  MapLayer.h
//  SCMap
//
//  Created by Zach Zahos on 2016-01-13.
//
//

#pragma once

class Map;
class QPainter;
class QRect;

class MapLayer {
public:
	enum {
		Terrain,
		
		COUNT
	};
	
	MapLayer() {}
	
	virtual void update(Map *map, QPainter &painter, QRect rect) = 0;
};
