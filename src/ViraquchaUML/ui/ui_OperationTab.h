/********************************************************************************
** Form generated from reading UI file 'OperationTab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPERATIONTAB_H
#define UI_OPERATIONTAB_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OperationTab
{
public:
    QFormLayout *formLayout;
    QLabel *returnTypeLabel;
    QComboBox *returnTypeCombo;
    QLabel *callConcurrencyLabel;
    QComboBox *callConcurrencyCombo;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QCheckBox *isAbstractBox;

    void setupUi(QWidget *OperationTab)
    {
        if (OperationTab->objectName().isEmpty())
            OperationTab->setObjectName(QString::fromUtf8("OperationTab"));
        OperationTab->resize(400, 300);
        OperationTab->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        formLayout = new QFormLayout(OperationTab);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        returnTypeLabel = new QLabel(OperationTab);
        returnTypeLabel->setObjectName(QString::fromUtf8("returnTypeLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, returnTypeLabel);

        returnTypeCombo = new QComboBox(OperationTab);
        returnTypeCombo->setObjectName(QString::fromUtf8("returnTypeCombo"));
        returnTypeCombo->setEditable(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, returnTypeCombo);

        callConcurrencyLabel = new QLabel(OperationTab);
        callConcurrencyLabel->setObjectName(QString::fromUtf8("callConcurrencyLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, callConcurrencyLabel);

        callConcurrencyCombo = new QComboBox(OperationTab);
        callConcurrencyCombo->setObjectName(QString::fromUtf8("callConcurrencyCombo"));

        formLayout->setWidget(1, QFormLayout::FieldRole, callConcurrencyCombo);

        groupBox = new QGroupBox(OperationTab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        isAbstractBox = new QCheckBox(groupBox);
        isAbstractBox->setObjectName(QString::fromUtf8("isAbstractBox"));

        verticalLayout->addWidget(isAbstractBox);


        formLayout->setWidget(2, QFormLayout::SpanningRole, groupBox);


        retranslateUi(OperationTab);

        QMetaObject::connectSlotsByName(OperationTab);
    } // setupUi

    void retranslateUi(QWidget *OperationTab)
    {
        OperationTab->setWindowTitle(QApplication::translate("OperationTab", "OperationTab", nullptr));
        returnTypeLabel->setText(QApplication::translate("OperationTab", "Return Type:", nullptr));
        callConcurrencyLabel->setText(QApplication::translate("OperationTab", "Call Concurrency:", nullptr));
        groupBox->setTitle(QApplication::translate("OperationTab", "Flags", nullptr));
        isAbstractBox->setText(QApplication::translate("OperationTab", "Is Abstract", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OperationTab: public Ui_OperationTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPERATIONTAB_H
