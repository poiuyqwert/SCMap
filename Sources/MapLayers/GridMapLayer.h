//
//  GridMapLayer.h
//  SCMap
//
//  Created by Zach Zahos on 2018-02-05.
//

#pragma once

#include "MapLayer.h"

#include <map>

#include <QPoint>
#include <QSize>
#include <QColor>

class QPainter;
class QRect;

struct GridSettings {
	QPoint offset;
	QSize size;
	QColor color;
	
	GridSettings(QPoint offset, QSize size, QColor color)
		: offset(offset), size(size), color(color) {}
};

class GridMapLayer : public MapLayer {
	GridSettings settings;
public:
	GridMapLayer()
		: settings(GridSettings({0,0},{32,32},Qt::black)) {}
	
	void update(Map *map, QPainter &painter, QRect rect);
};

