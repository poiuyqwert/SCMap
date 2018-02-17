//
//  EditGroup.h
//  SCMap
//
//  Created by Zach Zahos on 2016-01-23.
//
//

#pragma once

class Map;
class QString;
class QPainter;
class QRect;
class QPoint;

class EditMode {
public:
	enum Mode {
		Terrain,
		Locations,
		Units,
		
		COUNT
	};
	
	EditMode() {}
	
	virtual QString name() = 0;
	
	virtual void update(Map *map, QPainter &painter, QRect rect) = 0;
	virtual void click(Map *map, QPoint point) = 0;
};
