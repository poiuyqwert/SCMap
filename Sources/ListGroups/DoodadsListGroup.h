//
//  DoodadsListGroup.h
//  SCMap
//
//  Created by Zach Zahos on 2016-01-16.
//
//

#pragma once

#include "ListGroup.h"

class DoodadsListGroup : public ListGroup {
public:
	DoodadsListGroup(QStandardItem *parent);
	
	void update(Map *map);
	void itemSelected(QModelIndex index);
};
