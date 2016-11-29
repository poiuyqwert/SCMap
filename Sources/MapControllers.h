//
//  MapControllers.h
//  SCMap
//
//  Created by Zach Zahos on 2016-01-24.
//
//

#pragma once

#include "EditMode.h"
#include "MinimapLayer.h"
#include "ListGroup.h"
#include "MapLayer.h"


typedef struct {
	EditMode *editModes[EditMode::COUNT];
	MinimapLayer *minimapLayers[MinimapLayer::COUNT];
	ListGroup *listGroups[ListGroup::COUNT];
	MapLayer *mapLayers[MapLayer::COUNT];
} MapControllers;
