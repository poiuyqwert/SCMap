//
//  DoodadsListGroup.cpp
//  SCMap
//
//  Created by Zach Zahos on 2016-01-16.
//
//

#include "DoodadsListGroup.h"

#include <QModelIndex>

DoodadsListGroup::DoodadsListGroup(QStandardItem *parent)
	: ListGroup(parent, "Doodads")
{
	
}

void DoodadsListGroup::update(Map *) {

}

void DoodadsListGroup::itemSelected(MapSubWindow *, QStandardItem *) {

}
