//
//  MapWindow.h
//  SCMap
//
//  Created by Zach Zahos on 2016-01-11.
//
//

#pragma once

#include "MapScrollArea.h"
#include "MapControllers.h"
#include "EditMode.h"

#include <vector>

#include <QMdiSubWindow>
#include <QTime>

class Map;
class QTime;
class QTimer;


class MapSubWindow : public QMdiSubWindow {
	Q_OBJECT
	MapScrollArea *scrollArea;
public:
	MapSubWindow(Map *map, MapControllers controllers);
	
	Map* get_map()
		{ return this->scrollArea->get_map(); }
	
	QRect get_viewport()
		{ return this->scrollArea->getViewportRect(); }
	void centerOn(QPoint point);
signals:
	void viewportChanged(QRect rect);
private slots:
	void viewportUpdate(QRect rect);
};
