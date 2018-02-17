//
//  Map.h
//  SCMap
//
//  Created by Zach Zahos on 2016-01-10.
//
//

#pragma once

#include "EditMode.h"
#include "Properties.h"

#include <QObject>
#include <QPoint>

#include <libSCMS/Tileset.h>
#include <libSCMS/CHKTile.h>

class CHK;

class Map : public QObject {
	Q_OBJECT

	GETTER(CHK*, chk);
	GETTER(Tileset, tileset);
	
	GET_set(EditMode::Mode, editMode);
	
	GET_SET(QPoint, mouse);
	GET_SET(int, selectedLocation);
	
	std::map<u16, Pixels> megatiles;
public:
	Map(CHK *chk, Tileset tileset)
		: chk(chk),tileset(tileset),editMode(EditMode::Terrain) {};
	
	static Map *fromCHK(CHK *chk);
	static Map *loadMap(QString filename);
	static Map *newMap();
	
	Pixels get_megatile(CHKTile tile);
signals:
	void editModeChanged(EditMode::Mode mode);
};
