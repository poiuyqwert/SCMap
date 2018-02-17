//
//  UnitsMinimapLayer.cpp
//  SCMap
//
//  Created by Zach Zahos on 2018-02-11.
//

#include "UnitsMinimapLayer.h"
#include "Map.h"
#include "DataManager.h"

#include <libSCMS/Images.h>
#include <libSCMS/CHK.h>
#include <libSCMS/Tileset.h>
#include <libSCMS/CHKSectionDIM.h>
#include <libSCMS/CHKSectionUNIT.h>
#include <libSCMS/CHKSectionCOLR.h>
#include <libSCMS/UnitsDAT.h>
#include <libSCMS/Palette.h>
#include <libSCMS/PCX.h>

#include <QPainter>

void UnitsMinimapLayer::update(Map *map, QPainter &painter, QRect rect) {
	CHK *chk = map->get_chk();
	Tileset tileset = map->get_tileset();
	CHKSectionDIM *dim = chk->get_section<CHKSectionDIM>();
	Size<u16> mapSize = dim->get_size();
	CHKSectionUNIT *units = chk->get_section<CHKSectionUNIT>();
	CHKSectionCOLR *colr = chk->get_section<CHKSectionCOLR>();
	UnitsDAT *unitsDat = DataManager::getInstance().get_unitsDat();
	PCX *tminimap = DataManager::getInstance().get_tminimap();

	u8 colors[8];
	if (colr != nullptr) {
		for (int i = 0; i < 8; i++) {
			colors[i] = colr->get_color(i);
		}
	} else {
		memcpy(colors, CHKSectionCOLR::DEFAULTS, sizeof(colors));
	}
	
	float scaleX = mapSize.width * 32;
	float scaleY = mapSize.height * 32;
	
	for (int i = 0; i < (int)units->count(); i++) {
		CHKUnit unit = units->get_unit(i);
		int x1 = (unit.pos.x - unitsDat->unitSize[unit.unitID].start.x) / scaleX * rect.width();
		int y1 = (unit.pos.y - unitsDat->unitSize[unit.unitID].start.y) / scaleY * rect.height();
		int x2 = (unit.pos.x + unitsDat->unitSize[unit.unitID].end.x) / scaleX * rect.width();
		int y2 = (unit.pos.y + unitsDat->unitSize[unit.unitID].end.y) / scaleY * rect.height();
		u8 color = CHKSectionCOLR::Neutral;
		if (unit.properties.owner < SC::Player::COUNT_PLAYABLE) {
			color = colors[unit.properties.owner];
		}
		u8 paletteIndex = 0;
		if (color < tminimap->get_size().width) {
			paletteIndex = tminimap->get_pixels().get({color, 0});
		}
		RGB rgb = tileset.wpe->get_color(paletteIndex);
		painter.fillRect(x1, y1, max(2,x2-x1), max(2,y2-y1), QColor(rgb.r, rgb.g, rgb.b));
	}
}

