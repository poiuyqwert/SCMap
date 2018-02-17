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

Point<u32> colorLookup[2][2] = {
	{
		{7,6},{32-7,6}
	},
	{
		{7,32-6},{32-7,32-6}
	}
};

void TerrainMinimapLayer::update(Map *map, QPainter &painter, QRect) {
	CHK *chk = map->get_chk();
	Tileset tileset = map->get_tileset();
	
	CHKSectionDIM *dim = chk->get_section<CHKSectionDIM>();
	CHKSectionMTXM *mtxm = chk->get_section<CHKSectionMTXM>();
	
	Size<u16> mapSize = dim->get_size();
	u16 largeDim = max(mapSize.width,mapSize.height);
	
	u8 step = (largeDim > CHKSectionDIM::Medium ? 2 : 1);
	u8 size = (largeDim <= CHKSectionDIM::Tiny ? 2 : 1);
	
	for (u8 y = 0; y < mapSize.height / step; y += 1) {
		for (u8 x = 0; x < mapSize.width / step; x += 1) {
			for (u8 yo = 0; yo < size; yo++) {
				for (u8 xo = 0; xo < size; xo++) {
					CHKTile tile = mtxm->get_tile({(u8)(x * step), (u8)(y * step)});
					Pixels megatile = map->get_megatile(tile);
					RGB rgb = tileset.wpe->get_color(megatile.get(colorLookup[yo][xo]));
					painter.fillRect(x*size+xo,y*size+yo,1,1, QColor(rgb.r, rgb.g, rgb.b));
				}
			}
		}
	}
}
