//
//  UnitListGroup.cpp
//  SCMap
//
//  Created by Zach Zahos on 2016-01-16.
//
//

#include "UnitsListGroup.h"

#include <QModelIndex>

UnitsListGroup::UnitsListGroup(QStandardItem *parent)
	: ListGroup(parent, "Units")
{
	
}

void UnitsListGroup::update(Map *map) {

}

void UnitsListGroup::itemSelected(QModelIndex index) {
	
}