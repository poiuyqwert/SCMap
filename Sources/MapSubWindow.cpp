//
//  MapWindow.cpp
//  SCMap
//
//  Created by Zach Zahos on 2016-01-11.
//
//

#include "MapSubWindow.h"
#include "MapScrollArea.h"



MapSubWindow::MapSubWindow(Map *map, MapControllers controllers) {
	this->setAttribute(Qt::WA_DeleteOnClose);
	
	this->scrollArea = new MapScrollArea(map, controllers, this);
	this->scrollArea->setSceneSize(QSize(32*64,32*64));
	this->setWidget(this->scrollArea);
	
	connect(this->scrollArea, SIGNAL(viewportChanged(QRect)), this, SLOT(viewportUpdate(QRect)));
}

void MapSubWindow::viewportUpdate(QRect rect) {
	emit viewportChanged(rect);
}

void MapSubWindow::centerOn(QPoint point) {
	this->scrollArea->centerOn(point);
}