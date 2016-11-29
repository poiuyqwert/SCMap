//
//  SpritesListGroup.h
//  SCMap
//
//  Created by Zach Zahos on 2016-01-16.
//
//

#pragma once

#include "ListGroup.h"

class SpritesListGroup : public ListGroup {
public:
	SpritesListGroup(QStandardItem *parent);
	
	void update(Map *map);
	void itemSelected(QModelIndex index);
};
