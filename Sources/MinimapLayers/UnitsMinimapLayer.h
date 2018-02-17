//
//  UnitsMinimapLayer.hpp
//  SCMap
//
//  Created by Zach Zahos on 2018-02-11.
//

#pragma once

#include "MinimapLayer.h"

class UnitsMinimapLayer : public MinimapLayer {
public:
	UnitsMinimapLayer() {}
	
	void update(Map *map, QPainter &painter, QRect rect);
};

