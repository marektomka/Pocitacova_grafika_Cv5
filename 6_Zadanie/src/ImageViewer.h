#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets>
#include "ui_ImageViewer.h"
#include "ViewerWidget.h"
#include "NewImageDialog.h"


class MYPOINT {
private:
	int posX;
	int posY;
public:
	MYPOINT() { posX = 0, posY = 0; }
	MYPOINT(int posx, int posy) { posX = posx, posY = posy; }
	int set_posX(int posx) { posX = posx; return posX; }
	int set_posY(int posy) { posY = posy; return posY;}
	int get_posX() { return posX; }
	int get_posY() { return posY; }
};


class ImageViewer : public QMainWindow
{
	Q_OBJECT

public:
	ImageViewer(QWidget* parent = Q_NULLPTR);

private:
	Ui::ImageViewerClass* ui;
	NewImageDialog* newImgDialog;

	QSettings settings;
	QMessageBox msgBox;
	
	bool draw = FALSE;
	int count = 0;
	QColor current;
	QVector<MYPOINT> point;
	int method = 0, pt = 0;
	bool valChanged = FALSE;

	//ViewerWidget functions
	ViewerWidget* getViewerWidget(int tabId);
	ViewerWidget* getCurrentViewerWidget();

	//Event filters
	bool eventFilter(QObject* obj, QEvent* event);

	//ViewerWidget Events
	bool ViewerWidgetEventFilter(QObject* obj, QEvent* event);
	void ViewerWidgetMouseButtonPress(ViewerWidget* w, QEvent* event);
	void ViewerWidgetMouseButtonRelease(ViewerWidget* w, QEvent* event);
	void ViewerWidgetMouseMove(ViewerWidget* w, QEvent* event);
	void ViewerWidgetLeave(ViewerWidget* w, QEvent* event);
	void ViewerWidgetEnter(ViewerWidget* w, QEvent* event);
	void ViewerWidgetWheel(ViewerWidget* w, QEvent* event);

	//ImageViewer Events
	void closeEvent(QCloseEvent* event);

	//Image functions
	void openNewTabForImg(ViewerWidget* vW);
	bool openImage(QString filename);
	bool saveImage(QString filename);
	void clearImage();
	void setBackgroundColor(QColor color);

	//Inline functions
	inline bool isImgOpened() { return ui->tabWidget->count() == 0 ? false : true; }

private slots:
	//Tabs slots
	void on_tabWidget_tabCloseRequested(int tabId);
	void on_actionRename_triggered();

	//Image slots
	void on_actionNew_triggered();
	void newImageAccepted();
	void on_actionOpen_triggered();
	void on_actionSave_as_triggered();
	void on_actionClear_triggered();
	void on_actionSet_background_color_triggered();

	void on_pushButtonColor_clicked();
	void on_pushButtonClear_clicked();
	void on_pushButtonHermite_clicked();
	void on_pushButtonCoons_clicked();
	void on_pushButtonBezier_clicked();
	void on_doubleSpinBoxDegree_valueChanged();
	void on_spinBoxPoints_valueChanged();
	
	//------------------------------- Sphere slots---------------------------------------------------//
	void on_pushButtonSphere_clicked();

};
