
#pragma once

#include "MapControllers.h"

#include <vector>

#include <QMainWindow>
#include <QTreeView>


class FixedTreeView : public QTreeView {
	Q_OBJECT
public:
	FixedTreeView()
		: QTreeView() {}
	
	QSize sizeHint() const {
		return QSize(50,50);
	}
};

class MinimapWidget;
class MapSubWindow;
class QComboBox;
class QMdiArea;
class QMdiSubWindow;
class QItemSelection;



class MainWindow : public QMainWindow
{
    Q_OBJECT
	
	MapControllers mapControllers;

	QComboBox *comboBox;
	MinimapWidget *minimap;
	FixedTreeView *treeView;
	QMdiArea *mdi;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
	void newPressed();
	void openPressed();
	
	void mapSubWindowActivated(QMdiSubWindow *window);
	void listSelectionChanged(const QItemSelection &selected, const QItemSelection &unselected);
	
	void centerOn(QPoint point);
	void changeEditMode(int mode);
	void editModeChanged(EditMode::Mode mode);
private:
	void loadMap(Map *map);
	MapSubWindow* activeSubWindow();
};
