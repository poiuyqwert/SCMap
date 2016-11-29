//
//  MapScrollArea.cpp
//  SCMap
//
//  Created by Zach Zahos on 2016-01-20.
//
//

#include "MapScrollArea.h"

#include "Map.h"

#include <libSCMS/CHK.h>
#include <libSCMS/CHKSectionDIM.h>

#include <QTimer>
#include <QScrollBar>
#include <QMouseEvent>

MapScrollArea::MapScrollArea(Map *map, MapControllers controllers, QWidget *parent)
	: PainterScrollArea(parent), map(map), mapControllers(controllers), scrollbarHeld(false)
{
	connect(this->horizontalScrollBar(), SIGNAL(sliderPressed()), this, SLOT(scrollPressed()));
	connect(this->horizontalScrollBar(), SIGNAL(sliderReleased()), this, SLOT(scrollReleased()));
	connect(this->horizontalScrollBar(), SIGNAL(actionTriggered(int)), this, SLOT(horizontalScrollAction(int)));
	connect(this->verticalScrollBar(), SIGNAL(sliderPressed()), this, SLOT(scrollPressed()));
	connect(this->verticalScrollBar(), SIGNAL(sliderReleased()), this, SLOT(scrollReleased()));
	connect(this->verticalScrollBar(), SIGNAL(actionTriggered(int)), this, SLOT(verticalScrollAction(int)));

	CHK *chk = map->get_chk();
	CHKSectionDIM *dim = chk->get_section<CHKSectionDIM>();
	
	this->setSceneSize(QSize(dim->get_width()*32, dim->get_height()*32));

	this->timer = new QTimer(this);
	this->timer->setTimerType(Qt::PreciseTimer);
	connect(this->timer, SIGNAL(timeout()), this, SLOT(tick()));
	this->timer->start(12);
	
	this->setMouseTracking(true);
}

void MapScrollArea::centerOn(QPoint point) {
	CHKSectionDIM *dim = this->map->get_chk()->get_section<CHKSectionDIM>();
	QRect viewport = this->getViewportRect();
	int maxX = dim->get_width()*32 - viewport.width();
	int x = point.x() - viewport.width()/2;
	x = max(0,min(maxX,x));
	int maxY = dim->get_height()*32 - viewport.height();
	int y = point.y() - viewport.height()/2;
	y = max(0,min(maxY,y));
	this->horizontalScrollBar()->setValue(x);
	this->verticalScrollBar()->setValue(y);
	emit viewportChanged(this->getViewportRect());
}

void MapScrollArea::scrollPressed() {
	this->scrollbarHeld = true;
}
void MapScrollArea::scrollReleased() {
	this->scrollbarHeld = false;
}

void scrollAction(QScrollBar *scrollBar, int action, int max) {
	int position = scrollBar->value();
	switch (action) {
		case QAbstractSlider::SliderSingleStepAdd:
//			printf("SliderSingleStepAdd\n");
			position += 32;
			break;
		case QAbstractSlider::SliderSingleStepSub:
//			printf("SliderSingleStepSub\n");
			position -= 32;
			break;
		case QAbstractSlider::SliderPageStepAdd:
//			printf("SliderPageStepAdd\n");
			position += 320;
			break;
		case QAbstractSlider::SliderPageStepSub:
//			printf("SliderPageStepSub\n");
			position -= 320;
			break;
		case QAbstractSlider::SliderToMinimum:
//			printf("SliderToMinimum\n");
			position = 0;
			break;
		case QAbstractSlider::SliderToMaximum:
//			printf("SliderToMaximum\n");
			position = max;
			break;
		case QAbstractSlider::SliderMove:
//			printf("SliderMove\n");
			position += (scrollBar->sliderPosition() - position) * 32;
			break;
		default:
			break;
	}
	scrollBar->setSliderPosition(position);
	printf("%d / %d\n", position, max);
}

void MapScrollArea::horizontalScrollAction(int action) {
	if (!this->scrollbarHeld) {
		scrollAction(this->horizontalScrollBar(), action, this->getSceneSize().width());
		emit viewportChanged(this->getViewportRect());
	}
}

void MapScrollArea::verticalScrollAction(int action) {
	if (!this->scrollbarHeld) {
		scrollAction(this->verticalScrollBar(), action, this->getSceneSize().height());
		emit viewportChanged(this->getViewportRect());
	}
}

void MapScrollArea::tick() {
	this->viewport()->update();
}

void MapScrollArea::paint(QPainter &painter, QRect rect) {
	for (int layer = MapLayer::Terrain; layer < MapLayer::COUNT; layer++) {
		this->mapControllers.mapLayers[layer]->update(this->map, painter, rect);
	}
	this->mapControllers.editModes[this->map->get_editMode()]->update(this->map, painter, rect);
}

void MapScrollArea::resizeEvent(QResizeEvent *event) {
	PainterScrollArea::resizeEvent(event);
	emit viewportChanged(this->getViewportRect());
}

void MapScrollArea::mouseMoveEvent(QMouseEvent *event) {
	this->map->set_mouse(event->pos());
}
