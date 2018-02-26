//
//  NewMapDialog.h
//  SCMap
//
//  Created by Zach Zahos on 2018-02-19.
//

#pragma once

#include <libSCMS/Geometry.h>
#include <libSCMS/Types.h>

#include <QDialog>

struct NewMapDetails {
	Size<u16> size;
	u16 terrain;
};

class QLineEdit;
class QListView;
class QComboBox;

class NewMapDialog : public QDialog {
	Q_OBJECT
	
	QLineEdit *widthEdit;
	QLineEdit *heightEdit;
	QListView *terrainList;
	QListView *brushList;
	QComboBox *triggersComboBox;
public:
	NewMapDialog(QWidget *parent);
	
	NewMapDetails get_details();
};
