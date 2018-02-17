//
//  UnitsEditMode.h
//  SCMap
//
//  Created by Zach Zahos on 2018-02-16.
//

#pragma once

#include "EditMode.h"

#include <QString>

class UnitsEditMode : public EditMode {
public:
	UnitsEditMode()
		: EditMode() {}
	
	QString name()
		{ return "Units"; }
	
	void update(Map *map, QPainter &painter, QRect rect);
	void click(Map *map, QPoint point);
};
