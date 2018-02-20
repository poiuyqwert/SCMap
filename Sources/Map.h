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

#include <SFmpqapi.h>

class CHK;

class Map : public QObject {
	Q_OBJECT

	GETTER(CHK*, chk);
	GETTER(Tileset, tileset);
	MPQHANDLE mpq;
	
	GET_set(EditMode::Mode, editMode);
	
	GET_SET(QPoint, mouse);
	GET_SET(int, selectedLocation);
	
	std::map<u16, Pixels> megatiles;
public:
	Map(CHK *chk, Tileset tileset, MPQHANDLE mpq)
		: chk(chk),tileset(tileset),mpq(mpq),editMode(EditMode::Terrain) {};
	
	static Map *fromCHK(CHK *chk, MPQHANDLE mpq = nullptr);
	static Map *loadMap(QString filename);
	static Map *newMap();
	
	BOOL is_mpq()
		{ return (this->mpq != nullptr); }
	Pixels get_megatile(CHKTile tile);
signals:
	void editModeChanged(EditMode::Mode mode);
};
