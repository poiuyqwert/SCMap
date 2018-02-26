//
//  UnitListGroup.cpp
//  SCMap
//
//  Created by Zach Zahos on 2016-01-16.
//
//

#include "UnitsListGroup.h"
#include "DataManager.h"
#include "MapSubWindow.h"
#include "Map.h"

#include <libSCMS/Types.h>
#include <libSCMS/BroodWar.h>
#include <libSCMS/UnitsDAT.h>
#include <libSCMS/TBL.h>

#include <QModelIndex>
#include <QStandardItem>

struct UnitNode {
	QString name;
	u8 unitId;
};

typedef QList<UnitNode> UnitNodes;
typedef QMap<QString,UnitNodes> GroupNodes;
typedef QMap<QString,GroupNodes> RaceNodes;

UnitsListGroup::UnitsListGroup(QStandardItem *parent)
	: ListGroup(parent, "Units"),dirty(true)
{
	
}

void UnitsListGroup::update(Map *) {
	if (!this->dirty) {
		return;
	}
	this->dirty = false;
	QStandardItem *root = this->get_root();
	root->removeRows(0, root->rowCount());
	UnitsDAT *unitsDat = DataManager::getInstance().get_unitsDat();
	TBL *stat_txt = DataManager::getInstance().get_stat_txt();
	RaceNodes raceNodes;
	for (int i = 0; i < SC::Unit::COUNT; i++) {
		// TODO: Get races from TBL?
		QString race = "Neutral";
		if (unitsDat->starEditGroupFlags[i] & StarEditGroupFlags::RaceZerg) {
			race = "Zerg";
		} else if (unitsDat->starEditGroupFlags[i] & StarEditGroupFlags::RaceTerran) {
			race = "Terran";
		} else if (unitsDat->starEditGroupFlags[i] & StarEditGroupFlags::RaceProtoss) {
			race = "Protoss";
		}
		QString unitString = QString::fromStdString(stat_txt->get_string(i));
		QString group = "Other";
		if (unitString.count('\0') >= 3) {
			group = unitString.section('\0', 2, 2);
		}
		UnitNode node;
		node.name = unitString.section('\0', 0, 0); // TODO: Decompile
		node.unitId = i;
		raceNodes[race][group].append(node);
	}
	for (RaceNodes::const_iterator r = raceNodes.constBegin(); r != raceNodes.constEnd(); r++) {
		QStandardItem *raceItem = new QStandardItem(r.key());
		raceItem->setEditable(false);
		root->appendRow(raceItem);
		for (GroupNodes::const_iterator g = r.value().constBegin(); g != r.value().constEnd(); g++) {
			QStandardItem *groupItem = new QStandardItem(g.key());
			groupItem->setEditable(false);
			raceItem->appendRow(groupItem);
			for (UnitNodes::const_iterator u = g.value().constBegin(); u != g.value().constEnd(); u++) {
				QStandardItem *unitItem = new QStandardItem((*u).name);
				unitItem->setData(QVariant((*u).unitId));
				unitItem->setEditable(false);
				groupItem->appendRow(unitItem);
			}
		}
	}
}

void UnitsListGroup::itemSelected(MapSubWindow *window, QStandardItem *item) {
	Map *map = window->get_map();
	map->set_editMode(EditMode::Units);
	if (!item->data().isValid()) {
		return;
	}
}
