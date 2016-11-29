//
//  Map.h
//  SCMap
//
//  Created by Zach Zahos on 2016-01-10.
//
//

#pragma once

#include "EditMode.h"

#include <QObject>
#include <QPoint>

#include <libSCMS/Tileset.h>
#include <libSCMS/CHKTile.h>

class CHK;

class Map : public QObject {
	Q_OBJECT
	CHK *chk;
	Tileset tileset;
	
	EditMode::Mode editMode;
	
	QPoint mouse;
	
	std::map<u16, Pixels> megatiles;
public:
	Map(CHK *chk, Tileset tileset)
		: chk(chk),tileset(tileset),editMode(EditMode::Terrain) {};
	
	static Map *loadMap(QString filename);
	
	CHK* get_chk()
		{ return this->chk; }
	Tileset get_tileset()
		{ return this->tileset; }
	
	void set_editMode(EditMode::Mode editMode);
	int get_editMode()
		{ return this->editMode; }
	
	void set_mouse(QPoint mouse)
		{ this->mouse = mouse; }
	QPoint get_mouse()
		{ return this->mouse; }
	
	Pixels get_megatile(CHKTile tile);
signals:
	void editModeChanged(EditMode::Mode mode);
};
