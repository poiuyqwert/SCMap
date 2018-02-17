//
//  LocationsEditMode.cpp
//  SCMap
//
//  Created by Zach Zahos on 2016-01-25.
//
//

#include "LocationsEditMode.h"
#include "Map.h"

#include <libSCMS/CHK.h>
#include <libSCMS/CHKSectionMRGN.h>

#include <QPainter>
#include <QRect>
#include <QPoint>

void LocationsEditMode::update(Map *map, QPainter &painter, QRect rect) {
	if (map->get_editMode() != EditMode::Locations) {
		return;
	}
	int selectedLocation = map->get_selectedLocation();
	if (selectedLocation < 0 || selectedLocation > 254) {
		return;
	}
	CHK* chk = map->get_chk();
	
	CHKSectionMRGN *mrgn = chk->get_section<CHKSectionMRGN>();

	CHKLocation location = mrgn->get_location(selectedLocation);
	QRect locationRect = QRect(QPoint(location.rect.left, location.rect.top), QPoint(location.rect.right,location.rect.bottom));
	locationRect.translate(-rect.topLeft());
	painter.setPen(QColor(255, 255, 255));
	painter.drawRect(locationRect);
}

void LocationsEditMode::click(Map *map, QPoint point) {
	if (map->get_editMode() != EditMode::Locations) {
		return;
	}
	CHK* chk = map->get_chk();
	
	CHKSectionMRGN *mrgn = chk->get_section<CHKSectionMRGN>();
	
	for (int l = 0; l < mrgn->max_locations(); l++) {
		if (l > 20) {
			continue;
		}
		CHKLocation location = mrgn->get_location(l);
		QRect locationRect = QRect(
								   QPoint(location.rect.left, location.rect.top),
								   QPoint(location.rect.right,location.rect.bottom)
								   )
									.normalized();
		if (locationRect.contains(point)) {
			map->set_selectedLocation(l);
			break;
		}
	}
}
