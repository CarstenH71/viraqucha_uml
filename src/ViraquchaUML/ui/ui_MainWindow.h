/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "ProjectTreeView.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionHelp;
    QAction *actionAbout;
    QAction *actionPreferences;
    QAction *actionExit;
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionClose;
    QAction *actionImport;
    QAction *actionExport;
    QAction *actionRecentlyUsed;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionDelete;
    QAction *actionProperties;
    QAction *actionViewProject;
    QAction *actionViewToolbox;
    QAction *actionViewProperties;
    QAction *actionAlign;
    QAction *actionZoomIn;
    QAction *actionMoveUp;
    QAction *actionMoveDown;
    QAction *actionExpand;
    QAction *actionCollapse;
    QAction *actionAddClass;
    QAction *actionAddInterface;
    QAction *actionAddDatatype;
    QAction *actionAddEnumeration;
    QAction *actionAddPrimitive;
    QAction *actionAddSignal;
    QAction *actionAddDiagram;
    QAction *actionAddPackage;
    QAction *actionCopy2Clipboard;
    QAction *actionOpenDiagram;
    QAction *actionAddModel;
    QAction *actionAddAttribute;
    QAction *actionAddOperation;
    QAction *actionStartPage;
    QAction *actionSaveToFile;
    QAction *actionSaveToClipboard;
    QAction *actionShowGrid;
    QAction *actionZoomOut;
    QAction *actionSettings;
    QTabWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuApplication;
    QMenu *menuProject;
    QMenu *menuEdit;
    QMenu *menuDiagram;
    QMenu *menuSaveImage;
    QMenu *menuElement;
    QMenu *menuAddElement;
    QMenu *menuAdd_Feature;
    QMenu *menuWindows;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *projDock;
    QWidget *projDockLayout;
    QVBoxLayout *verticalLayout;
    QToolBar *projToolBar;
    QComboBox *filterCombo;
    ProjectTreeView *projTreeView;
    QDockWidget *toolDock;
    QToolBox *toolBox;
    QDockWidget *propDock;
    QTreeView *propTable;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(934, 650);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/appicon_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowClass->setWindowIcon(icon);
        MainWindowClass->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        actionHelp = new QAction(MainWindowClass);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/help_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHelp->setIcon(icon1);
        actionAbout = new QAction(MainWindowClass);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionPreferences = new QAction(MainWindowClass);
        actionPreferences->setObjectName(QString::fromUtf8("actionPreferences"));
        actionExit = new QAction(MainWindowClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/exit_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon2);
        actionNew = new QAction(MainWindowClass);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/new_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon3);
        actionOpen = new QAction(MainWindowClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/open_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon4);
        actionSave = new QAction(MainWindowClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/save_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon5);
        actionSaveAs = new QAction(MainWindowClass);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        actionClose = new QAction(MainWindowClass);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/close_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClose->setIcon(icon6);
        actionImport = new QAction(MainWindowClass);
        actionImport->setObjectName(QString::fromUtf8("actionImport"));
        actionExport = new QAction(MainWindowClass);
        actionExport->setObjectName(QString::fromUtf8("actionExport"));
        actionRecentlyUsed = new QAction(MainWindowClass);
        actionRecentlyUsed->setObjectName(QString::fromUtf8("actionRecentlyUsed"));
        actionUndo = new QAction(MainWindowClass);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/undo_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUndo->setIcon(icon7);
        actionRedo = new QAction(MainWindowClass);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/images/redo_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRedo->setIcon(icon8);
        actionCut = new QAction(MainWindowClass);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        actionCopy = new QAction(MainWindowClass);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        actionPaste = new QAction(MainWindowClass);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        actionDelete = new QAction(MainWindowClass);
        actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
        actionProperties = new QAction(MainWindowClass);
        actionProperties->setObjectName(QString::fromUtf8("actionProperties"));
        actionViewProject = new QAction(MainWindowClass);
        actionViewProject->setObjectName(QString::fromUtf8("actionViewProject"));
        actionViewProject->setCheckable(true);
        actionViewProject->setChecked(true);
        actionViewToolbox = new QAction(MainWindowClass);
        actionViewToolbox->setObjectName(QString::fromUtf8("actionViewToolbox"));
        actionViewToolbox->setCheckable(true);
        actionViewToolbox->setChecked(true);
        actionViewProperties = new QAction(MainWindowClass);
        actionViewProperties->setObjectName(QString::fromUtf8("actionViewProperties"));
        actionViewProperties->setCheckable(true);
        actionViewProperties->setChecked(true);
        actionAlign = new QAction(MainWindowClass);
        actionAlign->setObjectName(QString::fromUtf8("actionAlign"));
        actionZoomIn = new QAction(MainWindowClass);
        actionZoomIn->setObjectName(QString::fromUtf8("actionZoomIn"));
        actionMoveUp = new QAction(MainWindowClass);
        actionMoveUp->setObjectName(QString::fromUtf8("actionMoveUp"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/images/moveup_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMoveUp->setIcon(icon9);
        actionMoveDown = new QAction(MainWindowClass);
        actionMoveDown->setObjectName(QString::fromUtf8("actionMoveDown"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/images/movedown_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMoveDown->setIcon(icon10);
        actionExpand = new QAction(MainWindowClass);
        actionExpand->setObjectName(QString::fromUtf8("actionExpand"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/images/expand_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExpand->setIcon(icon11);
        actionCollapse = new QAction(MainWindowClass);
        actionCollapse->setObjectName(QString::fromUtf8("actionCollapse"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/images/collapse_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCollapse->setIcon(icon12);
        actionAddClass = new QAction(MainWindowClass);
        actionAddClass->setObjectName(QString::fromUtf8("actionAddClass"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/images/class_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddClass->setIcon(icon13);
        actionAddInterface = new QAction(MainWindowClass);
        actionAddInterface->setObjectName(QString::fromUtf8("actionAddInterface"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/images/interface_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddInterface->setIcon(icon14);
        actionAddDatatype = new QAction(MainWindowClass);
        actionAddDatatype->setObjectName(QString::fromUtf8("actionAddDatatype"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/images/datatype_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddDatatype->setIcon(icon15);
        actionAddEnumeration = new QAction(MainWindowClass);
        actionAddEnumeration->setObjectName(QString::fromUtf8("actionAddEnumeration"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/images/enum_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddEnumeration->setIcon(icon16);
        actionAddPrimitive = new QAction(MainWindowClass);
        actionAddPrimitive->setObjectName(QString::fromUtf8("actionAddPrimitive"));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/images/primitive_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddPrimitive->setIcon(icon17);
        actionAddSignal = new QAction(MainWindowClass);
        actionAddSignal->setObjectName(QString::fromUtf8("actionAddSignal"));
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/images/signal_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddSignal->setIcon(icon18);
        actionAddDiagram = new QAction(MainWindowClass);
        actionAddDiagram->setObjectName(QString::fromUtf8("actionAddDiagram"));
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/images/diagram_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddDiagram->setIcon(icon19);
        actionAddPackage = new QAction(MainWindowClass);
        actionAddPackage->setObjectName(QString::fromUtf8("actionAddPackage"));
        QIcon icon20;
        icon20.addFile(QString::fromUtf8(":/images/package_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddPackage->setIcon(icon20);
        actionCopy2Clipboard = new QAction(MainWindowClass);
        actionCopy2Clipboard->setObjectName(QString::fromUtf8("actionCopy2Clipboard"));
        actionOpenDiagram = new QAction(MainWindowClass);
        actionOpenDiagram->setObjectName(QString::fromUtf8("actionOpenDiagram"));
        actionAddModel = new QAction(MainWindowClass);
        actionAddModel->setObjectName(QString::fromUtf8("actionAddModel"));
        QIcon icon21;
        icon21.addFile(QString::fromUtf8(":/images/model_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddModel->setIcon(icon21);
        actionAddAttribute = new QAction(MainWindowClass);
        actionAddAttribute->setObjectName(QString::fromUtf8("actionAddAttribute"));
        QIcon icon22;
        icon22.addFile(QString::fromUtf8(":/images/attribute_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddAttribute->setIcon(icon22);
        actionAddOperation = new QAction(MainWindowClass);
        actionAddOperation->setObjectName(QString::fromUtf8("actionAddOperation"));
        QIcon icon23;
        icon23.addFile(QString::fromUtf8(":/images/operation_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddOperation->setIcon(icon23);
        actionStartPage = new QAction(MainWindowClass);
        actionStartPage->setObjectName(QString::fromUtf8("actionStartPage"));
        actionStartPage->setCheckable(true);
        actionStartPage->setChecked(true);
        actionSaveToFile = new QAction(MainWindowClass);
        actionSaveToFile->setObjectName(QString::fromUtf8("actionSaveToFile"));
        actionSaveToClipboard = new QAction(MainWindowClass);
        actionSaveToClipboard->setObjectName(QString::fromUtf8("actionSaveToClipboard"));
        actionShowGrid = new QAction(MainWindowClass);
        actionShowGrid->setObjectName(QString::fromUtf8("actionShowGrid"));
        actionShowGrid->setCheckable(true);
        actionShowGrid->setChecked(true);
        actionZoomOut = new QAction(MainWindowClass);
        actionZoomOut->setObjectName(QString::fromUtf8("actionZoomOut"));
        actionSettings = new QAction(MainWindowClass);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        centralWidget = new QTabWidget(MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setTabsClosable(true);
        centralWidget->setMovable(true);
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 934, 30));
        menuApplication = new QMenu(menuBar);
        menuApplication->setObjectName(QString::fromUtf8("menuApplication"));
        menuApplication->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        menuProject = new QMenu(menuBar);
        menuProject->setObjectName(QString::fromUtf8("menuProject"));
        menuProject->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuEdit->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        menuDiagram = new QMenu(menuBar);
        menuDiagram->setObjectName(QString::fromUtf8("menuDiagram"));
        menuSaveImage = new QMenu(menuDiagram);
        menuSaveImage->setObjectName(QString::fromUtf8("menuSaveImage"));
        menuElement = new QMenu(menuBar);
        menuElement->setObjectName(QString::fromUtf8("menuElement"));
        menuAddElement = new QMenu(menuElement);
        menuAddElement->setObjectName(QString::fromUtf8("menuAddElement"));
        menuAdd_Feature = new QMenu(menuElement);
        menuAdd_Feature->setObjectName(QString::fromUtf8("menuAdd_Feature"));
        menuWindows = new QMenu(menuBar);
        menuWindows->setObjectName(QString::fromUtf8("menuWindows"));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setIconSize(QSize(16, 16));
        mainToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindowClass->setStatusBar(statusBar);
        projDock = new QDockWidget(MainWindowClass);
        projDock->setObjectName(QString::fromUtf8("projDock"));
        projDockLayout = new QWidget();
        projDockLayout->setObjectName(QString::fromUtf8("projDockLayout"));
        verticalLayout = new QVBoxLayout(projDockLayout);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        projToolBar = new QToolBar(projDockLayout);
        projToolBar->setObjectName(QString::fromUtf8("projToolBar"));
        projToolBar->setIconSize(QSize(16, 16));

        verticalLayout->addWidget(projToolBar);

        filterCombo = new QComboBox(projDockLayout);
        filterCombo->setObjectName(QString::fromUtf8("filterCombo"));
        filterCombo->setEditable(true);
        filterCombo->setFrame(true);

        verticalLayout->addWidget(filterCombo);

        projTreeView = new ProjectTreeView(projDockLayout);
        projTreeView->setObjectName(QString::fromUtf8("projTreeView"));
        projTreeView->setContextMenuPolicy(Qt::CustomContextMenu);
        projTreeView->setHeaderHidden(true);

        verticalLayout->addWidget(projTreeView);

        projDock->setWidget(projDockLayout);
        MainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), projDock);
        toolDock = new QDockWidget(MainWindowClass);
        toolDock->setObjectName(QString::fromUtf8("toolDock"));
        toolBox = new QToolBox();
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        toolDock->setWidget(toolBox);
        MainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), toolDock);
        propDock = new QDockWidget(MainWindowClass);
        propDock->setObjectName(QString::fromUtf8("propDock"));
        propTable = new QTreeView();
        propTable->setObjectName(QString::fromUtf8("propTable"));
        propDock->setWidget(propTable);
        MainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), propDock);

        menuBar->addAction(menuApplication->menuAction());
        menuBar->addAction(menuProject->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuElement->menuAction());
        menuBar->addAction(menuDiagram->menuAction());
        menuBar->addAction(menuWindows->menuAction());
        menuApplication->addAction(actionHelp);
        menuApplication->addAction(actionAbout);
        menuApplication->addSeparator();
        menuApplication->addAction(actionPreferences);
        menuApplication->addSeparator();
        menuApplication->addAction(actionExit);
        menuProject->addAction(actionNew);
        menuProject->addSeparator();
        menuProject->addAction(actionOpen);
        menuProject->addAction(actionSave);
        menuProject->addAction(actionSaveAs);
        menuProject->addAction(actionClose);
        menuProject->addSeparator();
        menuProject->addAction(actionImport);
        menuProject->addAction(actionExport);
        menuProject->addSeparator();
        menuProject->addAction(actionSettings);
        menuProject->addSeparator();
        menuProject->addAction(actionRecentlyUsed);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addAction(actionDelete);
        menuEdit->addSeparator();
        menuEdit->addAction(actionProperties);
        menuDiagram->addAction(actionOpenDiagram);
        menuDiagram->addSeparator();
        menuDiagram->addAction(actionAlign);
        menuDiagram->addSeparator();
        menuDiagram->addAction(actionZoomIn);
        menuDiagram->addAction(actionZoomOut);
        menuDiagram->addSeparator();
        menuDiagram->addAction(actionShowGrid);
        menuDiagram->addSeparator();
        menuDiagram->addAction(menuSaveImage->menuAction());
        menuSaveImage->addAction(actionSaveToClipboard);
        menuSaveImage->addAction(actionSaveToFile);
        menuElement->addAction(actionAddDiagram);
        menuElement->addAction(menuAddElement->menuAction());
        menuElement->addAction(menuAdd_Feature->menuAction());
        menuElement->addAction(actionAddModel);
        menuElement->addAction(actionAddPackage);
        menuAddElement->addAction(actionAddClass);
        menuAddElement->addAction(actionAddInterface);
        menuAddElement->addAction(actionAddDatatype);
        menuAddElement->addAction(actionAddEnumeration);
        menuAddElement->addAction(actionAddPrimitive);
        menuAddElement->addAction(actionAddSignal);
        menuAdd_Feature->addAction(actionAddAttribute);
        menuAdd_Feature->addAction(actionAddOperation);
        menuWindows->addAction(actionViewProject);
        menuWindows->addAction(actionViewToolbox);
        menuWindows->addAction(actionViewProperties);
        menuWindows->addSeparator();
        menuWindows->addAction(actionStartPage);
        mainToolBar->addAction(actionNew);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionSave);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionUndo);
        mainToolBar->addAction(actionRedo);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionCut);
        mainToolBar->addAction(actionCopy);
        mainToolBar->addAction(actionPaste);
        mainToolBar->addAction(actionDelete);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionHelp);
        projToolBar->addAction(actionExpand);
        projToolBar->addAction(actionCollapse);
        projToolBar->addSeparator();
        projToolBar->addAction(actionMoveUp);
        projToolBar->addAction(actionMoveDown);

        retranslateUi(MainWindowClass);
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindowClass, SLOT(close()));

        toolBox->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "ViraquchaUML", nullptr));
        actionHelp->setText(QApplication::translate("MainWindowClass", "Help...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionHelp->setToolTip(QApplication::translate("MainWindowClass", "Shows online help", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionHelp->setStatusTip(QApplication::translate("MainWindowClass", "Show online help", nullptr));
#endif // QT_NO_STATUSTIP
        actionAbout->setText(QApplication::translate("MainWindowClass", "About...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionAbout->setToolTip(QApplication::translate("MainWindowClass", "Shows the About dialog", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionAbout->setStatusTip(QApplication::translate("MainWindowClass", "Show About dialog", nullptr));
#endif // QT_NO_STATUSTIP
        actionPreferences->setText(QApplication::translate("MainWindowClass", "Preferences...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionPreferences->setToolTip(QApplication::translate("MainWindowClass", "Opens the Preferences dialog", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionPreferences->setStatusTip(QApplication::translate("MainWindowClass", "Edit preferences", nullptr));
#endif // QT_NO_STATUSTIP
        actionExit->setText(QApplication::translate("MainWindowClass", "Exit", nullptr));
#ifndef QT_NO_TOOLTIP
        actionExit->setToolTip(QApplication::translate("MainWindowClass", "Exits ViraquchaUML", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionExit->setStatusTip(QApplication::translate("MainWindowClass", "Exit", nullptr));
#endif // QT_NO_STATUSTIP
        actionNew->setText(QApplication::translate("MainWindowClass", "New...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionNew->setToolTip(QApplication::translate("MainWindowClass", "Creates a new project", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionNew->setStatusTip(QApplication::translate("MainWindowClass", "Create new project", nullptr));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_SHORTCUT
        actionNew->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+N", nullptr));
#endif // QT_NO_SHORTCUT
        actionOpen->setText(QApplication::translate("MainWindowClass", "Open...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("MainWindowClass", "Opens an existing project", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionOpen->setStatusTip(QApplication::translate("MainWindowClass", "Open existing project", nullptr));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_SHORTCUT
        actionOpen->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        actionSave->setText(QApplication::translate("MainWindowClass", "Save...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("MainWindowClass", "Saves the currently opened project", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionSave->setStatusTip(QApplication::translate("MainWindowClass", "Save project", nullptr));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_SHORTCUT
        actionSave->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionSaveAs->setText(QApplication::translate("MainWindowClass", "Save as...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSaveAs->setToolTip(QApplication::translate("MainWindowClass", "Saves the currently opened project under a new name", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionSaveAs->setStatusTip(QApplication::translate("MainWindowClass", "Save project under new name", nullptr));
#endif // QT_NO_STATUSTIP
        actionClose->setText(QApplication::translate("MainWindowClass", "Close", nullptr));
#ifndef QT_NO_TOOLTIP
        actionClose->setToolTip(QApplication::translate("MainWindowClass", "Closes the currently opened project", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionClose->setStatusTip(QApplication::translate("MainWindowClass", "Close project", nullptr));
#endif // QT_NO_STATUSTIP
        actionImport->setText(QApplication::translate("MainWindowClass", "Import...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionImport->setToolTip(QApplication::translate("MainWindowClass", "Imports a project from XMI", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionImport->setStatusTip(QApplication::translate("MainWindowClass", "Import from XMI", nullptr));
#endif // QT_NO_STATUSTIP
        actionExport->setText(QApplication::translate("MainWindowClass", "Export...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionExport->setToolTip(QApplication::translate("MainWindowClass", "Exports the currently opened project to XMI", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionExport->setStatusTip(QApplication::translate("MainWindowClass", "Export to XMI", nullptr));
#endif // QT_NO_STATUSTIP
        actionRecentlyUsed->setText(QApplication::translate("MainWindowClass", "Recently used", nullptr));
        actionUndo->setText(QApplication::translate("MainWindowClass", "Undo", nullptr));
#ifndef QT_NO_TOOLTIP
        actionUndo->setToolTip(QApplication::translate("MainWindowClass", "Undos the last action", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionUndo->setStatusTip(QApplication::translate("MainWindowClass", "Undo last action", nullptr));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_SHORTCUT
        actionUndo->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+Z", nullptr));
#endif // QT_NO_SHORTCUT
        actionRedo->setText(QApplication::translate("MainWindowClass", "Redo", nullptr));
#ifndef QT_NO_TOOLTIP
        actionRedo->setToolTip(QApplication::translate("MainWindowClass", "Redoes the last action", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionRedo->setStatusTip(QApplication::translate("MainWindowClass", "Redo last action", nullptr));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_SHORTCUT
        actionRedo->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+Y", nullptr));
#endif // QT_NO_SHORTCUT
        actionCut->setText(QApplication::translate("MainWindowClass", "Cut", nullptr));
#ifndef QT_NO_TOOLTIP
        actionCut->setToolTip(QApplication::translate("MainWindowClass", "Cuts an element from the project tree or a diagram", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionCut->setStatusTip(QApplication::translate("MainWindowClass", "Cut element", nullptr));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_SHORTCUT
        actionCut->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+X", nullptr));
#endif // QT_NO_SHORTCUT
        actionCopy->setText(QApplication::translate("MainWindowClass", "Copy", nullptr));
#ifndef QT_NO_TOOLTIP
        actionCopy->setToolTip(QApplication::translate("MainWindowClass", "Copies an element in the project tree or a diagram", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionCopy->setStatusTip(QApplication::translate("MainWindowClass", "Copy element", nullptr));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_SHORTCUT
        actionCopy->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+C", nullptr));
#endif // QT_NO_SHORTCUT
        actionPaste->setText(QApplication::translate("MainWindowClass", "Paste", nullptr));
#ifndef QT_NO_TOOLTIP
        actionPaste->setToolTip(QApplication::translate("MainWindowClass", "Pastes an element into the project tree or a diagram", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionPaste->setStatusTip(QApplication::translate("MainWindowClass", "Paste element", nullptr));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_SHORTCUT
        actionPaste->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+V", nullptr));
#endif // QT_NO_SHORTCUT
        actionDelete->setText(QApplication::translate("MainWindowClass", "Delete", nullptr));
        actionDelete->setIconText(QApplication::translate("MainWindowClass", "Delete", nullptr));
#ifndef QT_NO_TOOLTIP
        actionDelete->setToolTip(QApplication::translate("MainWindowClass", "Deletes an element from the project tree or a diagram", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionDelete->setStatusTip(QApplication::translate("MainWindowClass", "Delete element", nullptr));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_SHORTCUT
        actionDelete->setShortcut(QApplication::translate("MainWindowClass", "Del", nullptr));
#endif // QT_NO_SHORTCUT
        actionProperties->setText(QApplication::translate("MainWindowClass", "Properties...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionProperties->setToolTip(QApplication::translate("MainWindowClass", "Opens the Properties dialog for a selected element for editing", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionProperties->setStatusTip(QApplication::translate("MainWindowClass", "Edit element properties", nullptr));
#endif // QT_NO_STATUSTIP
        actionViewProject->setText(QApplication::translate("MainWindowClass", "Project", nullptr));
        actionViewToolbox->setText(QApplication::translate("MainWindowClass", "Toolbox", nullptr));
        actionViewProperties->setText(QApplication::translate("MainWindowClass", "Properties", nullptr));
        actionAlign->setText(QApplication::translate("MainWindowClass", "Align", nullptr));
        actionZoomIn->setText(QApplication::translate("MainWindowClass", "Zoom in", nullptr));
#ifndef QT_NO_SHORTCUT
        actionZoomIn->setShortcut(QApplication::translate("MainWindowClass", "+", nullptr));
#endif // QT_NO_SHORTCUT
        actionMoveUp->setText(QApplication::translate("MainWindowClass", "Move Up", nullptr));
#ifndef QT_NO_TOOLTIP
        actionMoveUp->setToolTip(QApplication::translate("MainWindowClass", "Moves the selected element one up.", nullptr));
#endif // QT_NO_TOOLTIP
        actionMoveDown->setText(QApplication::translate("MainWindowClass", "Move Down", nullptr));
#ifndef QT_NO_TOOLTIP
        actionMoveDown->setToolTip(QApplication::translate("MainWindowClass", "Moves the selected element one down.", nullptr));
#endif // QT_NO_TOOLTIP
        actionExpand->setText(QApplication::translate("MainWindowClass", "Expand", nullptr));
#ifndef QT_NO_TOOLTIP
        actionExpand->setToolTip(QApplication::translate("MainWindowClass", "Expands the selecte node.", nullptr));
#endif // QT_NO_TOOLTIP
        actionCollapse->setText(QApplication::translate("MainWindowClass", "Collapse", nullptr));
#ifndef QT_NO_TOOLTIP
        actionCollapse->setToolTip(QApplication::translate("MainWindowClass", "Collapses the selected node.", nullptr));
#endif // QT_NO_TOOLTIP
        actionAddClass->setText(QApplication::translate("MainWindowClass", "Class", nullptr));
#ifndef QT_NO_TOOLTIP
        actionAddClass->setToolTip(QApplication::translate("MainWindowClass", "Adds a classifier of type Class to the project", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionAddClass->setStatusTip(QApplication::translate("MainWindowClass", "Add new Class", nullptr));
#endif // QT_NO_STATUSTIP
        actionAddInterface->setText(QApplication::translate("MainWindowClass", "Interface", nullptr));
#ifndef QT_NO_TOOLTIP
        actionAddInterface->setToolTip(QApplication::translate("MainWindowClass", "Adds a classifier of type Interface to the project", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionAddInterface->setStatusTip(QApplication::translate("MainWindowClass", "Add new Interface", nullptr));
#endif // QT_NO_STATUSTIP
        actionAddDatatype->setText(QApplication::translate("MainWindowClass", "Data Type", nullptr));
#ifndef QT_NO_TOOLTIP
        actionAddDatatype->setToolTip(QApplication::translate("MainWindowClass", "Adds a classifier of type Data Type to the project", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionAddDatatype->setStatusTip(QApplication::translate("MainWindowClass", "Add new Data Type", nullptr));
#endif // QT_NO_STATUSTIP
        actionAddEnumeration->setText(QApplication::translate("MainWindowClass", "Enumeration", nullptr));
        actionAddEnumeration->setIconText(QApplication::translate("MainWindowClass", "Adds a classifier of type Enumeration to the project", nullptr));
#ifndef QT_NO_TOOLTIP
        actionAddEnumeration->setToolTip(QApplication::translate("MainWindowClass", "Add new Enumeration", nullptr));
#endif // QT_NO_TOOLTIP
        actionAddPrimitive->setText(QApplication::translate("MainWindowClass", "Primitive", nullptr));
#ifndef QT_NO_TOOLTIP
        actionAddPrimitive->setToolTip(QApplication::translate("MainWindowClass", "Adds a classifier of type Primitive to the project", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionAddPrimitive->setStatusTip(QApplication::translate("MainWindowClass", "Add new Primitive", nullptr));
#endif // QT_NO_STATUSTIP
        actionAddSignal->setText(QApplication::translate("MainWindowClass", "Signal", nullptr));
#ifndef QT_NO_TOOLTIP
        actionAddSignal->setToolTip(QApplication::translate("MainWindowClass", "Adds a classifier of type Signal to the project", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionAddSignal->setStatusTip(QApplication::translate("MainWindowClass", "Add new Signal", nullptr));
#endif // QT_NO_STATUSTIP
        actionAddDiagram->setText(QApplication::translate("MainWindowClass", "Add & Diagram...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionAddDiagram->setToolTip(QApplication::translate("MainWindowClass", "Adds a new diagram to the project", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionAddDiagram->setStatusTip(QApplication::translate("MainWindowClass", "Add new diagram", nullptr));
#endif // QT_NO_STATUSTIP
        actionAddPackage->setText(QApplication::translate("MainWindowClass", "Add &Package", nullptr));
#ifndef QT_NO_TOOLTIP
        actionAddPackage->setToolTip(QApplication::translate("MainWindowClass", "Adds a new Package to the project", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionAddPackage->setStatusTip(QApplication::translate("MainWindowClass", "Add new Package", nullptr));
#endif // QT_NO_STATUSTIP
        actionCopy2Clipboard->setText(QApplication::translate("MainWindowClass", "Copy to Clipboard", nullptr));
        actionOpenDiagram->setText(QApplication::translate("MainWindowClass", "&Open", nullptr));
#ifndef QT_NO_TOOLTIP
        actionOpenDiagram->setToolTip(QApplication::translate("MainWindowClass", "Opens a diagram", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionOpenDiagram->setStatusTip(QApplication::translate("MainWindowClass", "Open diagram", nullptr));
#endif // QT_NO_STATUSTIP
        actionAddModel->setText(QApplication::translate("MainWindowClass", "Add &Model", nullptr));
#ifndef QT_NO_TOOLTIP
        actionAddModel->setToolTip(QApplication::translate("MainWindowClass", "Adds a new Model to the project", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionAddModel->setStatusTip(QApplication::translate("MainWindowClass", "Add new Model", nullptr));
#endif // QT_NO_STATUSTIP
        actionAddAttribute->setText(QApplication::translate("MainWindowClass", "&Attribute", nullptr));
#ifndef QT_NO_TOOLTIP
        actionAddAttribute->setToolTip(QApplication::translate("MainWindowClass", "Adds a feature of type Attribute to a classifier", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionAddAttribute->setStatusTip(QApplication::translate("MainWindowClass", "Add new Attribute", nullptr));
#endif // QT_NO_STATUSTIP
        actionAddOperation->setText(QApplication::translate("MainWindowClass", "&Operation", nullptr));
#ifndef QT_NO_TOOLTIP
        actionAddOperation->setToolTip(QApplication::translate("MainWindowClass", "Adds a feature of type Operation to a classifier", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionAddOperation->setStatusTip(QApplication::translate("MainWindowClass", "Add new Operation", nullptr));
#endif // QT_NO_STATUSTIP
        actionStartPage->setText(QApplication::translate("MainWindowClass", "Start Page", nullptr));
#ifndef QT_NO_TOOLTIP
        actionStartPage->setToolTip(QApplication::translate("MainWindowClass", "Shows or hides the Start Page", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionStartPage->setStatusTip(QApplication::translate("MainWindowClass", "Show Start Page", nullptr));
#endif // QT_NO_STATUSTIP
        actionSaveToFile->setText(QApplication::translate("MainWindowClass", "To File...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSaveToFile->setToolTip(QApplication::translate("MainWindowClass", "Saves an image of a diagram to a file", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionSaveToFile->setStatusTip(QApplication::translate("MainWindowClass", "Save image to file", nullptr));
#endif // QT_NO_STATUSTIP
        actionSaveToClipboard->setText(QApplication::translate("MainWindowClass", "To Clipboard", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSaveToClipboard->setToolTip(QApplication::translate("MainWindowClass", "Saves an image of a diagram to Clipboard", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionSaveToClipboard->setStatusTip(QApplication::translate("MainWindowClass", "Save image to clipboard", nullptr));
#endif // QT_NO_STATUSTIP
        actionShowGrid->setText(QApplication::translate("MainWindowClass", "Show Grid", nullptr));
#ifndef QT_NO_TOOLTIP
        actionShowGrid->setToolTip(QApplication::translate("MainWindowClass", "Shows or hides a grid in the diagrams", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionShowGrid->setStatusTip(QApplication::translate("MainWindowClass", "Show grid in diagrams", nullptr));
#endif // QT_NO_STATUSTIP
        actionZoomOut->setText(QApplication::translate("MainWindowClass", "Zoom out", nullptr));
#ifndef QT_NO_SHORTCUT
        actionZoomOut->setShortcut(QApplication::translate("MainWindowClass", "-", nullptr));
#endif // QT_NO_SHORTCUT
        actionSettings->setText(QApplication::translate("MainWindowClass", "Settings...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSettings->setToolTip(QApplication::translate("MainWindowClass", "Opens the Project Settings dialog for editing", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionSettings->setStatusTip(QApplication::translate("MainWindowClass", "Edit project settings", nullptr));
#endif // QT_NO_STATUSTIP
        menuApplication->setTitle(QApplication::translate("MainWindowClass", "&ViraquchaUML", nullptr));
        menuProject->setTitle(QApplication::translate("MainWindowClass", "&Project", nullptr));
        menuEdit->setTitle(QApplication::translate("MainWindowClass", "&Edit", nullptr));
        menuDiagram->setTitle(QApplication::translate("MainWindowClass", "&Diagram", nullptr));
        menuSaveImage->setTitle(QApplication::translate("MainWindowClass", "Save Image", nullptr));
        menuElement->setTitle(QApplication::translate("MainWindowClass", "Ele&ment", nullptr));
        menuAddElement->setTitle(QApplication::translate("MainWindowClass", "Add &Element", nullptr));
        menuAdd_Feature->setTitle(QApplication::translate("MainWindowClass", "Add &Feature", nullptr));
        menuWindows->setTitle(QApplication::translate("MainWindowClass", "&Windows", nullptr));
        projDock->setWindowTitle(QApplication::translate("MainWindowClass", "Project", nullptr));
        filterCombo->setCurrentText(QString());
        toolDock->setWindowTitle(QApplication::translate("MainWindowClass", "Toolbox", nullptr));
        propDock->setWindowTitle(QApplication::translate("MainWindowClass", "Properties", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
