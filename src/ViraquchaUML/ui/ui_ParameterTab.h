/********************************************************************************
** Form generated from reading UI file 'ParameterTab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETERTAB_H
#define UI_PARAMETERTAB_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParameterTab
{
public:
    QGridLayout *gridLayout;
    QTableView *parameterList;
    QVBoxLayout *verticalLayout;
    QPushButton *addItem;
    QPushButton *editItem;
    QPushButton *removeItems;
    QSpacerItem *verticalSpacer;
    QPushButton *moveItemsUp;
    QPushButton *moveItemsDown;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *ParameterTab)
    {
        if (ParameterTab->objectName().isEmpty())
            ParameterTab->setObjectName(QString::fromUtf8("ParameterTab"));
        ParameterTab->resize(400, 300);
        ParameterTab->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        gridLayout = new QGridLayout(ParameterTab);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        parameterList = new QTableView(ParameterTab);
        parameterList->setObjectName(QString::fromUtf8("parameterList"));
        parameterList->setAutoScroll(false);
        parameterList->setSelectionBehavior(QAbstractItemView::SelectRows);
        parameterList->horizontalHeader()->setHighlightSections(false);
        parameterList->verticalHeader()->setVisible(false);
        parameterList->verticalHeader()->setHighlightSections(false);

        gridLayout->addWidget(parameterList, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        addItem = new QPushButton(ParameterTab);
        addItem->setObjectName(QString::fromUtf8("addItem"));

        verticalLayout->addWidget(addItem);

        editItem = new QPushButton(ParameterTab);
        editItem->setObjectName(QString::fromUtf8("editItem"));

        verticalLayout->addWidget(editItem);

        removeItems = new QPushButton(ParameterTab);
        removeItems->setObjectName(QString::fromUtf8("removeItems"));

        verticalLayout->addWidget(removeItems);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        moveItemsUp = new QPushButton(ParameterTab);
        moveItemsUp->setObjectName(QString::fromUtf8("moveItemsUp"));
        moveItemsUp->setToolTipDuration(4);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/moveup_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        moveItemsUp->setIcon(icon);

        verticalLayout->addWidget(moveItemsUp);

        moveItemsDown = new QPushButton(ParameterTab);
        moveItemsDown->setObjectName(QString::fromUtf8("moveItemsDown"));
        moveItemsDown->setToolTipDuration(4);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/movedown_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        moveItemsDown->setIcon(icon1);

        verticalLayout->addWidget(moveItemsDown);


        gridLayout->addLayout(verticalLayout, 1, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit = new QLineEdit(ParameterTab);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(ParameterTab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 2);


        retranslateUi(ParameterTab);

        QMetaObject::connectSlotsByName(ParameterTab);
    } // setupUi

    void retranslateUi(QWidget *ParameterTab)
    {
        ParameterTab->setWindowTitle(QApplication::translate("ParameterTab", "ParameterTab", nullptr));
        addItem->setText(QApplication::translate("ParameterTab", "&Add", nullptr));
        editItem->setText(QApplication::translate("ParameterTab", "&Edit...", nullptr));
        removeItems->setText(QApplication::translate("ParameterTab", "&Remove", nullptr));
#ifndef QT_NO_TOOLTIP
        moveItemsUp->setToolTip(QApplication::translate("ParameterTab", "Moves the selected parameter one row up", nullptr));
#endif // QT_NO_TOOLTIP
        moveItemsUp->setText(QString());
#ifndef QT_NO_TOOLTIP
        moveItemsDown->setToolTip(QApplication::translate("ParameterTab", "Moves the selected parameter one row down", nullptr));
#endif // QT_NO_TOOLTIP
        moveItemsDown->setText(QString());
        lineEdit->setPlaceholderText(QApplication::translate("ParameterTab", "Enter parameter list here", nullptr));
        pushButton->setText(QApplication::translate("ParameterTab", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ParameterTab: public Ui_ParameterTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETERTAB_H
