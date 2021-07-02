/********************************************************************************
** Form generated from reading UI file 'MultiplicityTab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MULTIPLICITYTAB_H
#define UI_MULTIPLICITYTAB_H

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

class Ui_MultiplicityTab
{
public:
    QFormLayout *formLayout;
    QLabel *rangeLabel;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QCheckBox *isOrderedBox;
    QCheckBox *isUniqueBox;
    QComboBox *rangeCombo;

    void setupUi(QWidget *MultiplicityTab)
    {
        if (MultiplicityTab->objectName().isEmpty())
            MultiplicityTab->setObjectName(QString::fromUtf8("MultiplicityTab"));
        MultiplicityTab->resize(400, 300);
        MultiplicityTab->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        formLayout = new QFormLayout(MultiplicityTab);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        rangeLabel = new QLabel(MultiplicityTab);
        rangeLabel->setObjectName(QString::fromUtf8("rangeLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, rangeLabel);

        groupBox = new QGroupBox(MultiplicityTab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        isOrderedBox = new QCheckBox(groupBox);
        isOrderedBox->setObjectName(QString::fromUtf8("isOrderedBox"));

        verticalLayout->addWidget(isOrderedBox);

        isUniqueBox = new QCheckBox(groupBox);
        isUniqueBox->setObjectName(QString::fromUtf8("isUniqueBox"));

        verticalLayout->addWidget(isUniqueBox);


        formLayout->setWidget(2, QFormLayout::SpanningRole, groupBox);

        rangeCombo = new QComboBox(MultiplicityTab);
        rangeCombo->setObjectName(QString::fromUtf8("rangeCombo"));
        rangeCombo->setEditable(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, rangeCombo);


        retranslateUi(MultiplicityTab);

        QMetaObject::connectSlotsByName(MultiplicityTab);
    } // setupUi

    void retranslateUi(QWidget *MultiplicityTab)
    {
        MultiplicityTab->setWindowTitle(QApplication::translate("MultiplicityTab", "MultiplicityTab", nullptr));
        rangeLabel->setText(QApplication::translate("MultiplicityTab", "Range:", nullptr));
        groupBox->setTitle(QApplication::translate("MultiplicityTab", "Flags:", nullptr));
        isOrderedBox->setText(QApplication::translate("MultiplicityTab", "Is Ordered", nullptr));
        isUniqueBox->setText(QApplication::translate("MultiplicityTab", "Is Unique", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MultiplicityTab: public Ui_MultiplicityTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MULTIPLICITYTAB_H
