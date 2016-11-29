//
//  MinimapWidget.cpp
//  SCMap
//
//  Created by Zach Zahos on 2016-01-22.
//
//

#include "MinimapWidget.h"
#include "TerrainMinimapLayer.h"
#include "Map.h"

#include <libSCMS/CHK.h>
#include <libSCMS/CHKSectionDIM.h>

#include <QPainter>
#include <QMouseEvent>

MinimapWidget::MinimapWidget(MapControllers controllers, QWidget *parent)
	: QWidget(parent), map(nullptr), viewport(QRect()), mapControllers(controllers)
{
	this->setMinimumWidth(128);
	this->setMinimumHeight(128);
	this->setMaximumWidth(128);
	this->setMaximumHeight(128);
}

void MinimapWidget::set_map(Map *map) {
	this->map = map;
	CHKSectionDIM *dim = map->get_chk()->get_section<CHKSectionDIM>();
	u16 width = dim->get_width();
	if (width > 128) {
		this->hScale = 0.5;
	} else if (width <= 64) {
		this->hScale = 2;
	}
	width *= this->hScale;
	u16 height = dim->get_height();
	if (height > 128) {
		this->vScale = 0.5;
	} else if (height <= 64) {
		this->vScale = 2;
	}
	height *= this->vScale;
	this->setMinimumWidth(width);
	this->setMinimumHeight(height);
	this->setMaximumWidth(width);
	this->setMaximumHeight(height);
	this->resize(width, height);
	printf("%d %d -> %d %d\n", dim->get_width(), dim->get_height(), width, height);
	this->update();
}

void MinimapWidget::viewportChanged(QRect rect) {
	this->viewport = rect;
	this->update();
}

void MinimapWidget::paintEvent(QPaintEvent *) {
	if (this->map) {
		QRect rect(QPoint(0,0),this->size());
		QPainter painter(this);
		for (int layer = MinimapLayer::Terrain; layer < MinimapLayer::COUNT; layer++) {
			this->mapControllers.minimapLayers[layer]->update(this->map, painter, rect, this->hScale, this->vScale);
		}
		CHKSectionDIM *dim = this->map->get_chk()->get_section<CHKSectionDIM>();
		float width = dim->get_width() * 32;
		float height = dim->get_height() * 32;
		float x = this->viewport.x() / width;
		float y = this->viewport.y() / height;
		float w = this->viewport.width() / width;
		float h = this->viewport.height() / height;
		painter.setPen(Qt::white);
		painter.drawRect(x * this->size().width(), y * this->size().height(), (int)(w * this->size().width()) - 1, (int)(h * this->size().height()) - 1);
	}
}

void MinimapWidget::mousePressEvent(QMouseEvent *event) {
	if (this->map) {
		float x = event->pos().x() / (float)this->size().width();
		float y = event->pos().y() / (float)this->size().height();
		CHKSectionDIM *dim = this->map->get_chk()->get_section<CHKSectionDIM>();
		emit centerOn(QPoint(x * dim->get_width() * 32, y * dim->get_height() * 32));
	}
}

void MinimapWidget::mouseMoveEvent(QMouseEvent *event) {
	this->mousePressEvent(event);
}
