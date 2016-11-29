//
//  MapScrollArea.h
//  SCMap
//
//  Created by Zach Zahos on 2016-01-20.
//
//

#pragma once

#include "PainterScrollArea.h"
#include "MapControllers.h"

#include <vector>

class Map;
class QMouseEvent;

class MapScrollArea : public PainterScrollArea {
	Q_OBJECT
	Map *map;
	MapControllers mapControllers;
	
	QTimer *timer;
	bool scrollbarHeld;
public:
	MapScrollArea(Map *map, MapControllers controllers, QWidget *parent=0);
	
	Map* get_map()
		{ return this->map; }
	
	void centerOn(QPoint point);
private slots:
	void scrollPressed();
	void scrollReleased();
	void horizontalScrollAction(int action);
	void verticalScrollAction(int action);
	void tick();
signals:
	void viewportChanged(QRect rect);
private:
	void paint(QPainter &painter, QRect rect);
protected:
	void resizeEvent(QResizeEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
};

