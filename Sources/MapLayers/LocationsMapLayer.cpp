//
//  LocationsMapLayer.cpp
//  SCMap
//
//  Created by Zach Zahos on 2018-02-03.
//

#include "LocationsMapLayer.h"
#include "Map.h"

#include <libSCMS/CHK.h>
#include <libSCMS/CHKSectionMRGN.h>

#include <math.h>

#include <QPainter>


QColor normalFill = QColor(40, 29, 103);
QColor normalBorder = QColor(51, 37, 131);

QColor invertedFill = QColor(103, 29, 40);
QColor invertedBorder = QColor(131, 37, 51);

void LocationsMapLayer::update(Map *map, QPainter &painter, QRect rect) {
	if (map->get_editMode() != EditMode::Locations) {
		return;
	}
	CHK* chk = map->get_chk();
	
	CHKSectionMRGN *mrgn = chk->get_section<CHKSectionMRGN>();
	
	for (int l = 0; l < mrgn->max_locations(); l++) {
		if (l == CHKSectionMRGN::AnywhereID) {
			continue;
		}
		CHKLocation location = mrgn->get_location(l);
		if (location.rect.left == 0 && location.rect.right == 0 && location.rect.top == 0 && location.rect.bottom == 0) {
			continue;
		}
		QRect locationRect = QRect(
								   QPoint(location.rect.left, location.rect.top),
								   QPoint(location.rect.right,location.rect.bottom)
								   )
									.normalized();
		bool inverted = (location.rect.left > location.rect.right) || (location.rect.top > location.rect.bottom);
		locationRect.translate(-rect.topLeft());
		painter.setOpacity(0.5);
		if (inverted) {
			painter.fillRect(locationRect, invertedFill);
		} else {
			painter.fillRect(locationRect, normalFill);
		}
		painter.setOpacity(1);
		if (inverted) {
			painter.setPen(invertedBorder);
		} else {
			painter.setPen(normalBorder);
		}
		painter.drawRect(locationRect);
	}
}
