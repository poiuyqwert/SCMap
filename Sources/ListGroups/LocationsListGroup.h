//
//  LocationsListGroup.h
//  SCMap
//
//  Created by Zach Zahos on 2016-01-15.
//
//

#pragma once

#import "ListGroup.h"

class LocationsListGroup : public ListGroup {
public:
	LocationsListGroup(QStandardItem *parent);
	
	void update(Map *map);
	void itemSelected(MapSubWindow *window, QStandardItem *item);
};
