//
//  TerrainListGroup.h
//  SCMap
//
//  Created by Zach Zahos on 2016-01-12.
//
//

#pragma once

#import "ListGroup.h"

class TerrainListGroup : public ListGroup {
public:
	TerrainListGroup(QStandardItem *parent);
	
	void update(Map *map);
	void itemSelected(MapSubWindow *window, QStandardItem *item);
};
