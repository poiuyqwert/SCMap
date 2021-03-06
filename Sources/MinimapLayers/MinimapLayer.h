//
//  MinimapLayer.h
//  SCMap
//
//  Created by Zach Zahos on 2016-01-22.
//
//

#pragma once

class Map;
class QPainter;
class QSize;

class MinimapLayer {
public:
	enum {
		Terrain,
		Units,
		
		COUNT
	};
	
	MinimapLayer() {}
	
	virtual void update(Map *map, QPainter &painter, QSize minimapSize) = 0;
};
