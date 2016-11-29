//
//  MinimapWidget.h
//  SCMap
//
//  Created by Zach Zahos on 2016-01-22.
//
//

#pragma once

#include "MapControllers.h"

#include <vector>

#include <QWidget>

class Map;
class QTimer;

class MinimapWidget : public QWidget {
	Q_OBJECT
	Map *map;
	QRect viewport;
	MapControllers mapControllers;
	
	float hScale,vScale;
	QTimer *timer;
public:
	MinimapWidget(MapControllers controllers, QWidget *parent=0);
	
	void set_map(Map *map);
public slots:
	void viewportChanged(QRect rect);
signals:
	void centerOn(QPoint center);
protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
};
