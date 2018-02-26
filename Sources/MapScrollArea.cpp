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
	Size<u16> mapSize = dim->get_size();

	this->setSceneSize(QSize(mapSize.width*32, mapSize.height*32));

	this->timer = new QTimer(this);
	this->timer->setTimerType(Qt::PreciseTimer);
	connect(this->timer, SIGNAL(timeout()), this, SLOT(tick()));
	this->timer->start(12);
	
	this->setMouseTracking(true);
}

void MapScrollArea::centerOn(QPoint point) {
	CHKSectionDIM *dim = this->map->get_chk()->get_section<CHKSectionDIM>();
	Size<u16> mapSize = dim->get_size();
	QRect viewport = this->getViewportRect();
	int maxX = mapSize.width*32 - viewport.width();
	int x = point.x() - viewport.width()/2;
	x = max(0,min(maxX,x));
	int maxY = mapSize.height*32 - viewport.height();
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
	painter.fillRect(rect, Qt::black);
	for (int layer = MapLayer::Terrain; layer < MapLayer::COUNT; layer++) {
		painter.save();
		this->mapControllers.mapLayers[layer]->update(this->map, painter, rect);
		painter.restore();
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

void MapScrollArea::mousePressEvent(QMouseEvent *event) {
	QPoint pos = event->pos() + this->getViewportRect().topLeft();
	this->mapControllers.editModes[this->map->get_editMode()]->click(this->map, pos);
}
