//
//  LocationsEditMode.h
//  SCMap
//
//  Created by Zach Zahos on 2016-01-25.
//
//

#pragma once

#include "EditMode.h"

#include <QString>

class LocationsEditMode : public EditMode {
public:
	LocationsEditMode()
		: EditMode() {}
	
	QString name()
		{ return "Locations"; }
	
	void update(Map *map, QPainter &painter, QRect rect);
	void click(Map *map, QPoint point);
};
