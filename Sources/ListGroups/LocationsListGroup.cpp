//
//  LocationsListGroup.cpp
//  SCMap
//
//  Created by Zach Zahos on 2016-01-15.
//
//

#include "LocationsListGroup.h"
#include "Map.h"
#include "MapSubWindow.h"

#include <libSCMS/Types.h>
#include <libSCMS/CHK.h>
#include <libSCMS/CHKSectionMRGN.h>
#include <libSCMS/CHKSectionSTR.h>

#include <QStandardItem>

LocationsListGroup::LocationsListGroup(QStandardItem *parent)
	: ListGroup(parent, "Locations")
{
	
}

void LocationsListGroup::update(Map *map) {
	QStandardItem *root = this->get_root();
	root->removeRows(0, root->rowCount());
	if (map) {
		CHK *chk = map->get_chk();
		CHKSectionMRGN *mrgn = chk->get_section<CHKSectionMRGN>();
		CHKSectionSTR *str = chk->get_section<CHKSectionSTR>();
		for (int i = 0; i < mrgn->max_locations(); i++) {
			if (i == CHKSectionMRGN::AnywhereID) {
				continue;
			}
			CHKLocation location = mrgn->get_location(i);
			if (location.stringID) {
				CHKString string = str->get_string(location.stringID-1);
				if (!string.isNull()) {
					QStandardItem *item = new QStandardItem((char *)string.string);
					item->setData(QVariant(i));
					item->setEditable(false);
					root->appendRow(item);
				}
			}
		}
	}
}

void LocationsListGroup::itemSelected(MapSubWindow *window, QStandardItem *item) {
	Map *map = window->get_map();
	map->set_editMode(EditMode::Locations);
	if (!item->data().isValid()) {
		return;
	}
	int locationID = item->data().toInt();
	map->set_selectedLocation(locationID);
	CHK *chk = map->get_chk();
	CHKSectionMRGN *mrgn = chk->get_section<CHKSectionMRGN>();
	CHKLocation location = mrgn->get_location(locationID);
	QRect rect = QRect(
					   QPoint(location.rect.left, location.rect.top),
					   QPoint(location.rect.right, location.rect.bottom)
					   )
						.normalized();
	window->centerOn(rect.center());
}
