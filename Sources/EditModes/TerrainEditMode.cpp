//
//  TerrainEditMode.cpp
//  SCMap
//
//  Created by Zach Zahos on 2016-01-23.
//
//

#include "TerrainEditMode.h"
#include "Map.h"

#include <QPainter>
#include <QRect>
#include <QMouseEvent>

void TerrainEditMode::update(Map *map, QPainter &painter, QRect rect) {
	QPoint pos = map->get_mouse() + rect.topLeft();
	if (rect.contains(pos)) {
		int x = (int)(pos.x() / 32.0) * 32;
		x -= rect.x();
		int y = (int)(pos.y() / 32.0) * 32;
		y -= rect.y();
		painter.setPen(Qt::red);
		painter.drawRect(x, y, 32, 32);
	}
}
