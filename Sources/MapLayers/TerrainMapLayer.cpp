//
//  TerrainMapLayer.cpp
//  SCMap
//
//  Created by Zach Zahos on 2016-01-13.
//
//

#include "TerrainMapLayer.h"
#include "Map.h"

#include <libSCMS/Tileset.h>
#include <libSCMS/CHK.h>
#include <libSCMS/CHKSectionMTXM.h>
#include <libSCMS/CHKSectionDIM.h>
#include <libSCMS/Palette.h>

#include <math.h>

#include <QPainter>


void TerrainMapLayer::update(Map *map, QPainter &painter, QRect rect) {
	CHK *chk = map->get_chk();
	Tileset tileset = map->get_tileset();
	
	CHKSectionMTXM *mtxm = chk->get_section<CHKSectionMTXM>();
	CHKSectionDIM *dim = chk->get_section<CHKSectionDIM>();
	Size<u16> mapSize = dim->get_size();

	QVector<QRgb> colors;
	for (int n = 0; n < 256; n++) {
		int c = n;
		if (this->colorShift) {
			if (c >= 1 && c <= 6) {
				c -= this->colorShift;
				if (c < 1) {
					c += 6;
				}
			} else if (c >= 7 && c <= 13) {
				c -= this->colorShift;
				if (c < 7) {
					c += 7;
				}
			}
		}
		RGB rgb = tileset.wpe->get_color(c);
		colors.push_back(qRgb(rgb.r, rgb.g, rgb.b));
	}
	if (this->ticks == 0) {
		this->colorShift = (this->colorShift + 1) % 6;
	}
	this->ticks = (this->ticks + 1) % 8;
		
	int startX = rect.x() / 32.0;
	int startY = rect.y() / 32.0;
	int endX = min((int)(rect.right() / 32.0),(int)mapSize.width-1);
	int endY = min((int)(rect.bottom() / 32.0),(int)mapSize.height-1);
	Pixels megatile;
	for (int y = startY; y <= endY; y++) {
		int py = y * 32 - rect.y();
		for (int x = startX; x <= endX; x++) {
			int px = x * 32 - rect.x();
			CHKTile tile = mtxm->get_tile({(u8)x, (u8)y});
			megatile = map->get_megatile(tile);
			QImage image(megatile.pixels, megatile.size.width, megatile.size.height, QImage::Format_Indexed8);
			image.setColorTable(colors);
			painter.drawImage(px, py, image);
		}
	}
}
