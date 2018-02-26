//
//  NewMapDialog.cpp
//  SCMap
//
//  Created by Zach Zahos on 2018-02-19.
//

#include "NewMapDialog.h"

#include <QVBoxLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>
#include <QHBoxLayout>
#include <QStandardItemModel>
#include <QListView>
#include <QComboBox>
#include <QPushButton>


NewMapDialog::NewMapDialog(QWidget *parent)
	: QDialog(parent)
{
	this->setWindowTitle("New Map");

	QVBoxLayout *mainLayout = new QVBoxLayout();
	
	QGroupBox *sizeBox = new QGroupBox("Scenario Size");
	QGridLayout *sizeLayout = new QGridLayout();
	QLabel *widthLabel = new QLabel("Width:");
	widthLabel->setAlignment(Qt::AlignRight);
	sizeLayout->addWidget(widthLabel, 0, 0);
	widthEdit = new QLineEdit("128");
	widthEdit->setValidator(new QIntValidator(1,256));
	sizeLayout->addWidget(widthEdit, 0, 1);
	QLabel *heightLabel = new QLabel("Width:");
	heightLabel->setAlignment(Qt::AlignRight);
	sizeLayout->addWidget(heightLabel, 0, 2);
	heightEdit = new QLineEdit("128");
	heightEdit->setValidator(new QIntValidator(1,256));
	sizeLayout->addWidget(heightEdit, 0, 3);
	QLabel *sizeHintLabel = new QLabel("Standard sizes are 64, 96, 128, 196, and 256.\nOther sizes may cause errors in StarCraft or StarEdit");
	sizeLayout->addWidget(sizeHintLabel, 1, 0, 1, 4);
	sizeBox->setLayout(sizeLayout);
	mainLayout->addWidget(sizeBox);
	
	QGroupBox *terrainBox = new QGroupBox("Scenario Terrain");
	QHBoxLayout *terrainLayout = new QHBoxLayout();
	terrainList = new QListView();
	QStandardItemModel *terrainModel = new QStandardItemModel();
	QStringList	terrainStrings; // TODO: Data driven
	terrainStrings \
		<< "Badlands" \
		<< "Space Platform" \
		<< "Installation" \
		<< "Ash World" \
		<< "Jungle World" \
		<< "Desert World" \
		<< "Ice World" \
		<< "Twilight World";
	for (int i = 0; i < terrainStrings.count(); i++) {
		QStandardItem *item = new QStandardItem(terrainStrings[i]);
		item->setEditable(false);
		terrainModel->appendRow(item);
	}
	terrainList->setModel(terrainModel);
	terrainList->selectionModel()->setCurrentIndex(terrainModel->index(0, 0), QItemSelectionModel::SelectionFlag::Select);
	terrainLayout->addWidget(terrainList);
	brushList = new QListView();
	QStandardItemModel *brushesModel = new QStandardItemModel(); // TODO: Terrain brushes
	QStandardItem *item = new QStandardItem("Debug Checkerbox");
	item->setEditable(false);
	brushesModel->appendRow(item);
	brushList->setModel(brushesModel);
	brushList->selectionModel()->setCurrentIndex(brushesModel->index(0, 0), QItemSelectionModel::SelectionFlag::Select);
	terrainLayout->addWidget(brushList);
	terrainBox->setLayout(terrainLayout);
	mainLayout->addWidget(terrainBox);
	
	QGroupBox *triggersBox = new QGroupBox("Default Triggers");
	QVBoxLayout *triggersLayout = new QVBoxLayout();
	triggersComboBox = new QComboBox();
	// TODO: Default triggers
	triggersLayout->addWidget(triggersComboBox);
	triggersBox->setLayout(triggersLayout);
	mainLayout->addWidget(triggersBox);
	
	QWidget *buttonsWidget = new QWidget();
	QHBoxLayout *buttonsLayout = new QHBoxLayout();
	buttonsLayout->setMargin(0);
	QPushButton *createButton = new QPushButton("Create Map");
	createButton->setDefault(true);
	connect(createButton, SIGNAL(clicked(bool)), this, SLOT(accept()));
	buttonsLayout->addWidget(createButton);
	QPushButton *cancelButton = new QPushButton("Cancel");
	connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
	buttonsLayout->addWidget(cancelButton);
	buttonsWidget->setLayout(buttonsLayout);
	mainLayout->addWidget(buttonsWidget);
	
	this->setLayout(mainLayout);

	// TODO: Minimize window size?
}

NewMapDetails NewMapDialog::get_details() {
	NewMapDetails details;
	details.size.width = widthEdit->text().toInt();
	details.size.height = heightEdit->text().toInt();
	details.terrain = terrainList->selectionModel()->currentIndex().row();
	// TODO: Brush
	// TODO: Default triggers
	return details;
}
