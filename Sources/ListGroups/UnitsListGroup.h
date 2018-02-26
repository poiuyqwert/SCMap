//
//  UnitsListGroup.h
//  SCMap
//
//  Created by Zach Zahos on 2016-01-16.
//
//

#pragma once

#include "ListGroup.h"

class UnitsListGroup : public ListGroup {
	bool dirty;
public:
	UnitsListGroup(QStandardItem *parent);
				   
	void update(Map *map);
	void itemSelected(MapSubWindow *window, QStandardItem *item);
};
