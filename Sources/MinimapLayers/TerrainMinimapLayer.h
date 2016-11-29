//
//  TerrainMinimapLayer.h
//  SCMap
//
//  Created by Zach Zahos on 2016-01-22.
//
//

#pragma once

#include "MinimapLayer.h"

class TerrainMinimapLayer : public MinimapLayer {
public:
	TerrainMinimapLayer() {}
	
	void update(Map *map, QPainter &painter, QRect rect, float hScale, float vScale);
};
