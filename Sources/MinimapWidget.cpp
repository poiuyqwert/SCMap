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

#include <cmath>

MinimapWidget::MinimapWidget(MapControllers controllers, QWidget *parent)
	: QWidget(parent), map(nullptr), viewport(QRect()), mapControllers(controllers)
{
	this->setMinimumWidth(128);
	this->setMinimumHeight(128);
	this->setMaximumWidth(128);
	this->setMaximumHeight(128);
	this->resize(128, 128);
}

void MinimapWidget::set_map(Map *map) {
	this->map = map;
	CHKSectionDIM *dim = map->get_chk()->get_section<CHKSectionDIM>();
	Size<u16> mapSize = dim->get_size();
	QSize size(mapSize.width,mapSize.height);
	u16 largeDim = max(mapSize.width,mapSize.height);
	if (largeDim > CHKSectionDIM::Medium) {
		size /= 2;
	} else if (largeDim <= CHKSectionDIM::Tiny) {
		size *= 2;
	}
	QSize sizeDiff = this->size() - size;
	QPoint offset(sizeDiff.width() / 2, sizeDiff.height() / 2);
	this->outputRect = QRect(offset, size);
	this->update();
}

void MinimapWidget::viewportChanged(QRect rect) {
	this->viewport = rect;
	this->update();
}

void MinimapWidget::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.fillRect(QRect({0,0},this->size()), Qt::black);
	if (this->map) {
		painter.translate(this->outputRect.topLeft());
		QSize outputSize = this->outputRect.size();
		QRect drawRect({0,0},outputSize);
		for (int layer = MinimapLayer::Terrain; layer < MinimapLayer::COUNT; layer++) {
			this->mapControllers.minimapLayers[layer]->update(this->map, painter, drawRect);
		}
		CHKSectionDIM *dim = this->map->get_chk()->get_section<CHKSectionDIM>();
		Size<u16> mapSize = dim->get_size();
		float width = mapSize.width * 32;
		float height = mapSize.height * 32;
		float x = this->viewport.x() / width * outputSize.width();
		float y = this->viewport.y() / height * outputSize.height();
		float w = round(this->viewport.width() / width * outputSize.width()) - 1;
		float h = round(this->viewport.height() / height * outputSize.height()) - 1;
		painter.setPen(Qt::white);
		painter.drawRect(x, y, w, h);
		painter.drawRect(drawRect.marginsAdded({1,1,0,0}));
	}
}

void MinimapWidget::mousePressEvent(QMouseEvent *event) {
	if (this->map) {
		QPoint pos = event->pos() - this->outputRect.topLeft();
		float x = pos.x() / (float)this->outputRect.width();
		float y = pos.y() / (float)this->outputRect.height();
		CHKSectionDIM *dim = this->map->get_chk()->get_section<CHKSectionDIM>();
		Size<u16> mapSize = dim->get_size();
		emit centerOn(QPoint(x * mapSize.width * 32, y * mapSize.height * 32));
	}
}

void MinimapWidget::mouseMoveEvent(QMouseEvent *event) {
	this->mousePressEvent(event);
}
