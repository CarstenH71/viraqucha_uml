/********************************************************************************
** Form generated from reading UI file 'OperationsTab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPERATIONSTAB_H
#define UI_OPERATIONSTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OperationsTab
{
public:
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *removeButton;
    QSpacerItem *verticalSpacer;
    QPushButton *moveUpButton;
    QPushButton *moveDownButton;

    void setupUi(QWidget *OperationsTab)
    {
        if (OperationsTab->objectName().isEmpty())
            OperationsTab->setObjectName(QString::fromUtf8("OperationsTab"));
        OperationsTab->resize(400, 300);
        horizontalLayout = new QHBoxLayout(OperationsTab);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tableWidget = new QTableWidget(OperationsTab);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        horizontalLayout->addWidget(tableWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        addButton = new QPushButton(OperationsTab);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        verticalLayout->addWidget(addButton);

        editButton = new QPushButton(OperationsTab);
        editButton->setObjectName(QString::fromUtf8("editButton"));

        verticalLayout->addWidget(editButton);

        removeButton = new QPushButton(OperationsTab);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));

        verticalLayout->addWidget(removeButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        moveUpButton = new QPushButton(OperationsTab);
        moveUpButton->setObjectName(QString::fromUtf8("moveUpButton"));

        verticalLayout->addWidget(moveUpButton);

        moveDownButton = new QPushButton(OperationsTab);
        moveDownButton->setObjectName(QString::fromUtf8("moveDownButton"));

        verticalLayout->addWidget(moveDownButton);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(OperationsTab);

        QMetaObject::connectSlotsByName(OperationsTab);
    } // setupUi

    void retranslateUi(QWidget *OperationsTab)
    {
        OperationsTab->setWindowTitle(QApplication::translate("OperationsTab", "OperationsTab", nullptr));
        addButton->setText(QApplication::translate("OperationsTab", "&Add", nullptr));
        editButton->setText(QApplication::translate("OperationsTab", "&Edit...", nullptr));
        removeButton->setText(QApplication::translate("OperationsTab", "&Remove", nullptr));
        moveUpButton->setText(QApplication::translate("OperationsTab", "Move &Up", nullptr));
        moveDownButton->setText(QApplication::translate("OperationsTab", "Move &Down", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OperationsTab: public Ui_OperationsTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPERATIONSTAB_H
