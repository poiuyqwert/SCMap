//
//  ListGroup.cpp
//  SCMap
//
//  Created by Zach Zahos on 2016-01-12.
//
//

#include "ListGroup.h"
#include "Map.h"

#include <QStandardItem>

ListGroup::ListGroup(QStandardItem *parent, char const *name)
	: parent(parent)
{
	QStandardItem *terrain = new QStandardItem(name);
	terrain->setFlags(terrain->flags() & ~Qt::ItemIsEditable);
	this->parent->appendRow(terrain);
	this->root = terrain;
}
