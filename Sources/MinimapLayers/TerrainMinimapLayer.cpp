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


void TerrainMinimapLayer::update(Map *map, QPainter &painter, QRect) {
	CHK *chk = map->get_chk();
	Tileset tileset = map->get_tileset();
	
	CHKSectionDIM *dim = chk->get_section<CHKSectionDIM>();
	CHKSectionMTXM *mtxm = chk->get_section<CHKSectionMTXM>();
	
	Size<u16> mapSize = dim->get_size();
	u16 largeDim = max(mapSize.width,mapSize.height);
	
	u8 step = (largeDim > CHKSectionDIM::Medium ? 2 : 1);
	u8 subpixels = (largeDim <= CHKSectionDIM::Tiny ? 2 : 1);
	
	for (u8 y = 0; y < mapSize.height / step; y += 1) {
		for (u8 x = 0; x < mapSize.width / step; x += 1) {
			CHKTile tile = mtxm->get_tile({(u8)(x * step), (u8)(y * step)});
			CV5Group group = tileset.cv5->get_group(tile.megatileGroup);
			u16 megatileID = group.megatiles[tile.megatile];
			VX4Megatile info = tileset.vx4->get_megatile(megatileID);
			for (u8 yo = 0; yo < subpixels; yo++) {
				for (u8 xo = 0; xo < subpixels; xo++) {
					VX4MinitileRef ref = info.minitiles[xo+yo*4];
					Pixels minitile = tileset.get_minitile(ref.minitile);
					RGB rgb = tileset.wpe->get_color(minitile.get({7,6}));
					painter.fillRect(x*subpixels+xo,y*subpixels+yo,1,1, QColor(rgb.r, rgb.g, rgb.b));
				}
			}
		}
	}
}
