//
//  PainterScrollArea.cpp
//  SCMap
//
//  Created by Zach Zahos on 2016-01-20.
//
//

#include "PainterScrollArea.h"

#include <QPaintEvent>
#include <QScrollBar>

void PainterScrollArea::setSceneSize(QSize sceneSize) {
	this->sceneSize = sceneSize;
	this->updateScrollbars();
}

void PainterScrollArea::updateScrollbars() {
	QSize areaSize = this->viewport()->size();
	this->horizontalScrollBar()->setPageStep(this->sceneSize.width());
	this->verticalScrollBar()->setPageStep(this->sceneSize.height());
	this->horizontalScrollBar()->setRange(0, this->sceneSize.width() - areaSize.width());
	this->verticalScrollBar()->setRange(0, this->sceneSize.height() - areaSize.height());
}

void PainterScrollArea::resizeEvent(QResizeEvent *) {
	this->updateScrollbars();
}

QRect PainterScrollArea::getViewportRect() {
	return QRect(
				 this->horizontalScrollBar()->value(),
				 this->verticalScrollBar()->value(),
				 this->viewport()->size().width(),
				 this->viewport()->size().height()
				 );
}

void PainterScrollArea::paintEvent(QPaintEvent *) {
	QPainter painter(this->viewport());
	this->paint(painter, this->getViewportRect());
}

void PainterScrollArea::paint(QPainter&, QRect) {}
