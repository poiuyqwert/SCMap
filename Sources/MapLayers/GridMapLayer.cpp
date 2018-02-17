//
//  GridMapLayer.cpp
//  SCMap
//
//  Created by Zach Zahos on 2018-02-05.
//

#include "GridMapLayer.h"
#include "Map.h"

#include <libSCMS/Tileset.h>
#include <libSCMS/CHK.h>

#include <math.h>

#include <QPainter>
#include <QPoint>
#include <QSize>


void GridMapLayer::update(Map *, QPainter &painter, QRect rect) {
	painter.setPen(settings.color);
	
	int offsetX = rect.x() - settings.offset.x();
	int offsetY = rect.y() - settings.offset.y();
	int width = settings.size.width();
	int height = settings.size.height();
	
	int startX = (int)ceil(offsetX / float(width)) * width - offsetX;
	int startY = (int)ceil(offsetY / float(height)) * height - offsetY;
	int endX = ((rect.right() - settings.offset.x()) / width * width) - offsetX;
	int endY = ((rect.bottom() - settings.offset.y()) / height * height) - offsetY;
	
	for (int x = startX; x <= endX; x += width) {
		painter.drawLine(x, 0, x, rect.height());
	}
	for (int y = startY; y <= endY; y += height) {
		painter.drawLine(0, y, rect.width(), y);
	}
}
