//
//  ListGroup.h
//  SCMap
//
//  Created by Zach Zahos on 2016-01-12.
//
//

#pragma once

class Map;
class MapSubWindow;
class QStandardItem;
class QModelIndex;

class ListGroup {
	QStandardItem *parent;
	QStandardItem *root;
public:
	enum {
		Terrain,
		Locations,
		Units,
		Sprites,
		Doodads,
		
		COUNT
	};
	
	ListGroup(QStandardItem *parent, char const *name);

	virtual void update(Map *map) = 0;
	virtual void itemSelected(MapSubWindow *window, QStandardItem *item) = 0;
	
	QStandardItem *get_root()
		{ return this->root; }
};

