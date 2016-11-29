//
//  LocationsListGroup.cpp
//  SCMap
//
//  Created by Zach Zahos on 2016-01-15.
//
//

#include "LocationsListGroup.h"
#include "Map.h"

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
		for (int i = 0; i < 255; i++) {
			CHKLocation location = mrgn->get_location(i);
			if (location.stringID) {
				CHKString string = str->get_string(location.stringID-1);
				if (!string.isNull()) {
					QStandardItem *terrain = new QStandardItem((char *)string.string);
					terrain->setFlags(terrain->flags() & ~Qt::ItemIsEditable);
					root->appendRow(terrain);
				}
			}
		}
	}
}

void LocationsListGroup::itemSelected(QModelIndex index) {
	
}
