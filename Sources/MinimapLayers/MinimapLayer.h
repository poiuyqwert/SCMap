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
class QRect;

class MinimapLayer {
public:
	enum {
		Terrain,
		Units,
		
		COUNT
	};
	
	MinimapLayer() {}
	
	virtual void update(Map *map, QPainter &painter, QRect rect) = 0;
};
