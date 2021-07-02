/********************************************************************************
** Form generated from reading UI file 'AttributesTab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ATTRIBUTESTAB_H
#define UI_ATTRIBUTESTAB_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AttributesTab
{
public:
    QHBoxLayout *horizontalLayout;
    QTableView *tableView;
    QVBoxLayout *verticalLayout;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *removeButton;
    QSpacerItem *verticalSpacer;
    QPushButton *moveUpButton;
    QPushButton *moveDownButton;

    void setupUi(QWidget *AttributesTab)
    {
        if (AttributesTab->objectName().isEmpty())
            AttributesTab->setObjectName(QString::fromUtf8("AttributesTab"));
        AttributesTab->resize(400, 300);
        AttributesTab->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        horizontalLayout = new QHBoxLayout(AttributesTab);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tableView = new QTableView(AttributesTab);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        horizontalLayout->addWidget(tableView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        addButton = new QPushButton(AttributesTab);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        verticalLayout->addWidget(addButton);

        editButton = new QPushButton(AttributesTab);
        editButton->setObjectName(QString::fromUtf8("editButton"));

        verticalLayout->addWidget(editButton);

        removeButton = new QPushButton(AttributesTab);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));

        verticalLayout->addWidget(removeButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        moveUpButton = new QPushButton(AttributesTab);
        moveUpButton->setObjectName(QString::fromUtf8("moveUpButton"));

        verticalLayout->addWidget(moveUpButton);

        moveDownButton = new QPushButton(AttributesTab);
        moveDownButton->setObjectName(QString::fromUtf8("moveDownButton"));

        verticalLayout->addWidget(moveDownButton);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(AttributesTab);

        QMetaObject::connectSlotsByName(AttributesTab);
    } // setupUi

    void retranslateUi(QWidget *AttributesTab)
    {
        AttributesTab->setWindowTitle(QApplication::translate("AttributesTab", "AttributesTab", nullptr));
        addButton->setText(QApplication::translate("AttributesTab", "&Add", nullptr));
        editButton->setText(QApplication::translate("AttributesTab", "&Edit...", nullptr));
        removeButton->setText(QApplication::translate("AttributesTab", "&Remove", nullptr));
        moveUpButton->setText(QApplication::translate("AttributesTab", "Move &Up", nullptr));
        moveDownButton->setText(QApplication::translate("AttributesTab", "Move &Down", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AttributesTab: public Ui_AttributesTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATTRIBUTESTAB_H
