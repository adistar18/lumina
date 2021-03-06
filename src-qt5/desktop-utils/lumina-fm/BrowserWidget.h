//  Lumina-DE source code
//  Copyright (c) 2016, Ken Moore
//  Available under the 3-clause BSD license
//  See the LICENSE file for full details
//===========================================
//  This is the main browsing frontend for the file manager
//===========================================
#ifndef _LUMINA_FM_BROWSE_FRONTEND_H
#define _LUMINA_FM_BROWSE_FRONTEND_H

#include <QString>
#include <QWidget>
#include <QThread>

#include <LVideoWidget.h>
#include <LFileInfo.h>

#include "Browser.h"
#include "widgets/DDListWidgets.h"

class BrowserWidget : public QWidget{
	Q_OBJECT
private:
	Browser *BROWSER;
	QThread *bThread; //browserThread
	int numItems; //used for checking if all the items have loaded yet
	QString ID, statustip;
	QStringList date_format, historyList;
	QMap<QString,QPair<QTreeWidgetItem*, LVideoWidget*>> videoMap;
	bool freshload;
	int treeSortColumn;

	//The drag and drop brower widgets
	DDListWidget *listWidget;
	DDTreeWidget *treeWidget;

	QString DTtoString(QDateTime dt);  //QDateTime to string simplification routine

public:
	BrowserWidget(QString objID, QWidget *parent = 0);
	~BrowserWidget();

	QString id(){ return ID; }
	void stop();

	void changeDirectory(QString dir);
	QString currentDirectory(){ return BROWSER->currentDirectory(); }

	void showDetails(bool show);
	bool hasDetails();

	void showHiddenFiles(bool show);
	bool hasHiddenFiles();

	void showThumbnails(bool show);
	bool hasThumbnails();
	void setThumbnailSize(int px);
	int thumbnailSize();

	void setHistory(QStringList);
	QStringList history();

	void setShowActive(bool show); //used for accenting if the widget is "active"
	
	void setTreeWidgetSortColumn(int col, bool now = false);

	QString status(){ return statustip; }

	//Date format for show items
	void readDateFormat();

	//Return all the items which are currently selected
	QStringList currentSelection();
	QStringList currentItems(int type = 0); //type: 0=all, -1=files, +1=dirs

public slots:
	void retranslate();

private slots:
	//Browser connections
	void clearItems();
	void itemRemoved(QString);
	void itemDataAvailable(const QIcon*, LFileInfo*);
	void itemsLoading(int total);
	void selectionChanged();
	void loadStatistics(BrowserWidget *bw); //designed to be run in a background thread


protected:
	void resizeEvent(QResizeEvent *ev);

signals:
	//External signals
	void itemsActivated();
	void updateDirectoryStatus(QString);
	void contextMenuRequested();
	void DataDropped(QString, QStringList);
	void hasFocus(QString); //ID output
	void stopLoop();

	//Internal signal
	void dirChange(QString, bool); //current dir path, force
	void treeWidgetSortColumn(int);
};
#endif
