
#include "MainWindow.h"
#include "Map.h"
#include "MapSubWindow.h"
#include "TerrainEditMode.h"
#include "LocationsEditMode.h"
#include "UnitsEditMode.h"
#include "TerrainMinimapLayer.h"
#include "UnitsMinimapLayer.h"
#include "TerrainListGroup.h"
#include "LocationsListGroup.h"
#include "UnitsListGroup.h"
#include "SpritesListGroup.h"
#include "DoodadsListGroup.h"
#include "MinimapWidget.h"
#include "TerrainMapLayer.h"
#include "GridMapLayer.h"
#include "LocationsMapLayer.h"
#include "DataManager.h"

#include <QSplitter>
#include <QToolBar>
#include <QAction>
#include <QStatusBar>
#include <QLabel>
#include <QStyle>
#include <QMdiArea>
#include <QComboBox>
#include <QVBoxLayout>
#include <QTreeView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QResizeEvent>
#include <QTextEdit>
#include <QStyle>
#include <QFileDialog>
#include <QApplication>


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	this->setWindowTitle("SCMap v0.0.1");
	
	DataManager::getInstance().load_data();
	
	this->mapControllers.editModes[EditMode::Terrain] = new TerrainEditMode();
	this->mapControllers.editModes[EditMode::Locations] = new LocationsEditMode();
	this->mapControllers.editModes[EditMode::Units] = new UnitsEditMode();
	this->mapControllers.minimapLayers[MinimapLayer::Terrain] = new TerrainMinimapLayer();
	this->mapControllers.minimapLayers[MinimapLayer::Units] = new UnitsMinimapLayer();
	QStandardItemModel *model = new QStandardItemModel();
	QStandardItem *root = model->invisibleRootItem();
	this->mapControllers.listGroups[ListGroup::Terrain] = new TerrainListGroup(root);
	this->mapControllers.listGroups[ListGroup::Locations] = new LocationsListGroup(root);
	this->mapControllers.listGroups[ListGroup::Units] = new UnitsListGroup(root);
	this->mapControllers.listGroups[ListGroup::Sprites] = new SpritesListGroup(root);
	this->mapControllers.listGroups[ListGroup::Doodads] = new DoodadsListGroup(root);
	this->mapControllers.mapLayers[MapLayer::Terrain] = new TerrainMapLayer();
	this->mapControllers.mapLayers[MapLayer::Grid] = new GridMapLayer();
	this->mapControllers.mapLayers[MapLayer::Locations] = new LocationsMapLayer();
	
	QSplitter *splitter = new QSplitter(this);
	QWidget *widget = new QWidget(splitter);
	QVBoxLayout *layout = new QVBoxLayout(widget);
	layout->setContentsMargins(5, 5, 5, 5);
	layout->setSpacing(5);
	QFrame *frame = new QFrame();
	frame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	QHBoxLayout *innerLayout = new QHBoxLayout();
	innerLayout->setContentsMargins(5, 5, 5, 5);
	QFrame *innerFrame = new QFrame();
	innerFrame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	QHBoxLayout *minimapLayout = new QHBoxLayout();
	minimapLayout->setContentsMargins(0, 0, 0, 0);
	this->minimap = new MinimapWidget(this->mapControllers);
	connect(this->minimap, SIGNAL(centerOn(QPoint)), this, SLOT(centerOn(QPoint)));
	minimapLayout->addWidget(this->minimap);
	innerFrame->setLayout(minimapLayout);
	innerLayout->addWidget(innerFrame);
	frame->setLayout(innerLayout);
	layout->addWidget(frame);
	this->treeView = new FixedTreeView();
	this->treeView->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
	this->treeView->header()->hide();
	this->treeView->setAttribute(Qt::WA_MacShowFocusRect, false);
	this->treeView->setModel(model);
	this->treeView->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	layout->addWidget(this->treeView);
	connect(this->treeView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&,const QItemSelection&)), this, SLOT(listSelectionChanged(const QItemSelection&, const QItemSelection&)));
	widget->setLayout(layout);
	splitter->addWidget(widget);
	splitter->setStretchFactor(0, 0);
	
	QSplitter *vert = new QSplitter(Qt::Vertical, splitter);
	this->mdi = new QMdiArea(vert);
	this->mdi->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	vert->addWidget(this->mdi);
	connect(this->mdi, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(mapSubWindowActivated(QMdiSubWindow*)));
	vert->setStretchFactor(0, 1);
	vert->setCollapsible(0, false);
	QTextEdit *text = new QTextEdit();
	text->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	vert->addWidget(text);
	vert->setStretchFactor(1, 0);
	splitter->addWidget(vert);
	splitter->setStretchFactor(1, 1);
	splitter->setCollapsible(1, false);
	this->setCentralWidget(splitter);
	
	QToolBar *toolbar = this->addToolBar(tr("File"));
	toolbar->setMovable(false);
	toolbar->setIconSize(QSize(16,16));
	QIcon newIcon = this->style()->standardIcon(QStyle::SP_FileIcon);
	QAction *action = toolbar->addAction(newIcon, tr("New"));
	connect(action, SIGNAL(triggered()), this, SLOT(newPressed()));
	QIcon openIcon = this->style()->standardIcon(QStyle::SP_FileDialogStart);
	action = toolbar->addAction(openIcon, tr("Open"));
	connect(action, SIGNAL(triggered()), this, SLOT(openPressed()));
	this->comboBox = new QComboBox(toolbar);
	for (int mode = EditMode::Terrain; mode < EditMode::COUNT; mode++) {
		this->comboBox->addItem(this->mapControllers.editModes[mode]->name());
	}
	connect(this->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeEditMode(int)));
	toolbar->addWidget(this->comboBox);
	
	QStatusBar *statusBar = new QStatusBar(this);
	QLabel *label = new QLabel(tr("Load a map"));
	statusBar->addWidget(label);
	this->setStatusBar(statusBar);
	
	
}

void MainWindow::newPressed() {
	Map *map = Map::newMap();
	this->loadMap(map);
}

void MainWindow::openPressed() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Open Map"), ".", tr("All Maps (*.scm *.scx *.chk);;StarCraft Map (*.scm);;BroodWar Map (*.scx);;Raw Scenario (*.chk)"));
	if (filename == QString::null) {
		return;
	}
	Map *map = Map::loadMap(filename);
	if (map) {
		this->loadMap(map);
	}
}

void MainWindow::loadMap(Map *map) {
	connect(map, SIGNAL(editModeChanged(EditMode::Mode)), this, SLOT(editModeChanged(EditMode::Mode)));
	
	MapSubWindow *window = new MapSubWindow(map, this->mapControllers);
	this->mdi->addSubWindow(window);
	window->resize(300, 200);
	connect(window, SIGNAL(viewportChanged(QRect)), this->minimap, SLOT(viewportChanged(QRect)));
	window->showMaximized();
}

void MainWindow::mapSubWindowActivated(QMdiSubWindow *w) {
	if (w) {
		MapSubWindow *window = (MapSubWindow *)w;
		Map *map = window->get_map();
		this->comboBox->setCurrentIndex(map->get_editMode());
		this->minimap->set_map(map);
		this->minimap->viewportChanged(window->get_viewport());
		for (int group = ListGroup::Terrain; group < ListGroup::COUNT; group++) {
			this->mapControllers.listGroups[group]->update(map);
		}
	}
}

void MainWindow::listSelectionChanged(const QItemSelection &/*selected*/, const QItemSelection &/*unselected*/) {
	const QModelIndex index = this->treeView->selectionModel()->currentIndex();
	QStandardItemModel *model = (QStandardItemModel *)this->treeView->model();
	QStandardItem *item = model->itemFromIndex(index);
	QModelIndex groupIndex = index;
	while (groupIndex.parent() != QModelIndex()) {
		groupIndex = groupIndex.parent();
	}
	ListGroup *group = this->mapControllers.listGroups[groupIndex.row()];
	MapSubWindow *window = this->activeSubWindow();
	if (window) {
		group->itemSelected(window, item);
	}
}

void MainWindow::centerOn(QPoint point) {
	MapSubWindow *window = this->activeSubWindow();
	if (window) {
		window->centerOn(point);
	}
}

void MainWindow::changeEditMode(int mode) {
	MapSubWindow *window = this->activeSubWindow();
	if (window) {
		window->get_map()->set_editMode((EditMode::Mode)mode);
	}
}
void MainWindow::editModeChanged(EditMode::Mode mode) {
	this->comboBox->setCurrentIndex(mode);
}

MapSubWindow* MainWindow::activeSubWindow() {
	return (MapSubWindow *)this->mdi->activeSubWindow();
}

MainWindow::~MainWindow()
{
}
