//
//  PainterScrollArea.h
//  SCMap
//
//  Created by Zach Zahos on 2016-01-20.
//
//

#pragma once

#include <QAbstractScrollArea>
#include <QPainter>

class PainterScrollArea : public QAbstractScrollArea {
	Q_OBJECT
	QSize sceneSize;
public:
	explicit PainterScrollArea(QWidget* parent=0)
		: QAbstractScrollArea(parent) {}
	
	void setSceneSize(QSize sceneSize);
	QSize getSceneSize()
		{ return this->sceneSize; }
	
	QRect getViewportRect();
protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);
private:
	void updateScrollbars();
	virtual void paint(QPainter &painter, QRect rect);
};
