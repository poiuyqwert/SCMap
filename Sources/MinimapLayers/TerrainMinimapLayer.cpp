//
//  TerrainMinimapLayer.cpp
//  SCMap
//
//  Created by Zach Zahos on 2016-01-22.
//
//

#include "TerrainMinimapLayer.h"
#include "Map.h"

#include <libSCMS/Images.h>
#include <libSCMS/CHK.h>
#include <libSCMS/CHKSectionDIM.h>
#include <libSCMS/CHKSectionMTXM.h>
#include <libSCMS/CHKTile.h>
#include <libSCMS/Tileset.h>
#include <libSCMS/Palette.h>

#include <QPainter>

void TerrainMinimapLayer::update(Map *map, QPainter &painter, QRect rect, float hScale, float vScale) {
	CHK *chk = map->get_chk();
	Tileset tileset = map->get_tileset();
	
	CHKSectionDIM *dim = chk->get_section<CHKSectionDIM>();
	CHKSectionMTXM *mtxm = chk->get_section<CHKSectionMTXM>();
	
	float xstep = (dim->get_width() > 128 ? dim->get_width() / 128.0f : 1);
	float ystep = (dim->get_height() > 128 ? dim->get_height() / 128.0f : 1);
	int w = (dim->get_width() <= 64 ? 2 : 1);
	int h = (dim->get_height() <= 64 ? 2 : 1);
	
	Pixels megatile;
	for (float fy = 0; fy < dim->get_height(); fy += ystep) {
		int y = fy;
		for (float fx = 0; fx < dim->get_width(); fx += xstep) {
			int x = fx;
			CHKTile tile = mtxm->get_tile(x, y);
			megatile = map->get_megatile(tile);
			RGB rgb = tileset.wpe->get_color(megatile.pixels[6*megatile.width+7]);
			painter.setPen(QColor(rgb.r, rgb.g, rgb.b));
			painter.drawRect(x*w,y*h,w-1,h-1);
		}
	}
}
