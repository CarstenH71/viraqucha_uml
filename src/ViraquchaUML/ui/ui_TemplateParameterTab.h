/********************************************************************************
** Form generated from reading UI file 'TemplateParameterTab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEMPLATEPARAMETERTAB_H
#define UI_TEMPLATEPARAMETERTAB_H

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

class Ui_TemplateParameterTab
{
public:
    QHBoxLayout *horizontalLayout;
    QTableView *parameterList;
    QVBoxLayout *verticalLayout;
    QPushButton *addButton;
    QPushButton *removeButton;
    QSpacerItem *verticalSpacer;
    QPushButton *moveUpButton;
    QPushButton *moveDownButton;

    void setupUi(QWidget *TemplateParameterTab)
    {
        if (TemplateParameterTab->objectName().isEmpty())
            TemplateParameterTab->setObjectName(QString::fromUtf8("TemplateParameterTab"));
        TemplateParameterTab->resize(400, 300);
        TemplateParameterTab->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        horizontalLayout = new QHBoxLayout(TemplateParameterTab);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        parameterList = new QTableView(TemplateParameterTab);
        parameterList->setObjectName(QString::fromUtf8("parameterList"));
        parameterList->setAutoScroll(false);
        parameterList->setProperty("showDropIndicator", QVariant(true));
        parameterList->setDragDropOverwriteMode(true);
        parameterList->setAlternatingRowColors(true);
        parameterList->setSelectionMode(QAbstractItemView::SingleSelection);
        parameterList->setSelectionBehavior(QAbstractItemView::SelectItems);
        parameterList->setTextElideMode(Qt::ElideNone);
        parameterList->setCornerButtonEnabled(false);
        parameterList->horizontalHeader()->setHighlightSections(false);
        parameterList->verticalHeader()->setVisible(false);

        horizontalLayout->addWidget(parameterList);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        addButton = new QPushButton(TemplateParameterTab);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        verticalLayout->addWidget(addButton);

        removeButton = new QPushButton(TemplateParameterTab);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));

        verticalLayout->addWidget(removeButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        moveUpButton = new QPushButton(TemplateParameterTab);
        moveUpButton->setObjectName(QString::fromUtf8("moveUpButton"));
        moveUpButton->setEnabled(false);

        verticalLayout->addWidget(moveUpButton);

        moveDownButton = new QPushButton(TemplateParameterTab);
        moveDownButton->setObjectName(QString::fromUtf8("moveDownButton"));
        moveDownButton->setEnabled(false);

        verticalLayout->addWidget(moveDownButton);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(TemplateParameterTab);

        QMetaObject::connectSlotsByName(TemplateParameterTab);
    } // setupUi

    void retranslateUi(QWidget *TemplateParameterTab)
    {
        TemplateParameterTab->setWindowTitle(QApplication::translate("TemplateParameterTab", "TemplateParameterTab", nullptr));
        addButton->setText(QApplication::translate("TemplateParameterTab", "&Add", nullptr));
        removeButton->setText(QApplication::translate("TemplateParameterTab", "&Delete", nullptr));
        moveUpButton->setText(QApplication::translate("TemplateParameterTab", "Move &Up", nullptr));
        moveDownButton->setText(QApplication::translate("TemplateParameterTab", "Move &Down", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TemplateParameterTab: public Ui_TemplateParameterTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMPLATEPARAMETERTAB_H
