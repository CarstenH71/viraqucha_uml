/********************************************************************************
** Form generated from reading UI file 'AttributeTab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ATTRIBUTETAB_H
#define UI_ATTRIBUTETAB_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AttributeTab
{
public:
    QFormLayout *formLayout;
    QLabel *typeLabel;
    QComboBox *typeCombo;
    QLabel *defaultLabel;
    QLineEdit *defaultEdit;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QCheckBox *isCompositeBox;
    QCheckBox *isDerivedBox;
    QCheckBox *isDerivedUnionBox;
    QCheckBox *isIDBox;
    QCheckBox *isStaticBox;
    QCheckBox *isReadonlyBox;
    QComboBox *aggregationCombo;
    QLabel *aggregationLabel;

    void setupUi(QWidget *AttributeTab)
    {
        if (AttributeTab->objectName().isEmpty())
            AttributeTab->setObjectName(QString::fromUtf8("AttributeTab"));
        AttributeTab->resize(400, 342);
        AttributeTab->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        formLayout = new QFormLayout(AttributeTab);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        typeLabel = new QLabel(AttributeTab);
        typeLabel->setObjectName(QString::fromUtf8("typeLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, typeLabel);

        typeCombo = new QComboBox(AttributeTab);
        typeCombo->setObjectName(QString::fromUtf8("typeCombo"));
        typeCombo->setEditable(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, typeCombo);

        defaultLabel = new QLabel(AttributeTab);
        defaultLabel->setObjectName(QString::fromUtf8("defaultLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, defaultLabel);

        defaultEdit = new QLineEdit(AttributeTab);
        defaultEdit->setObjectName(QString::fromUtf8("defaultEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, defaultEdit);

        groupBox = new QGroupBox(AttributeTab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        isCompositeBox = new QCheckBox(groupBox);
        isCompositeBox->setObjectName(QString::fromUtf8("isCompositeBox"));
        isCompositeBox->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));

        verticalLayout->addWidget(isCompositeBox);

        isDerivedBox = new QCheckBox(groupBox);
        isDerivedBox->setObjectName(QString::fromUtf8("isDerivedBox"));

        verticalLayout->addWidget(isDerivedBox);

        isDerivedUnionBox = new QCheckBox(groupBox);
        isDerivedUnionBox->setObjectName(QString::fromUtf8("isDerivedUnionBox"));

        verticalLayout->addWidget(isDerivedUnionBox);

        isIDBox = new QCheckBox(groupBox);
        isIDBox->setObjectName(QString::fromUtf8("isIDBox"));

        verticalLayout->addWidget(isIDBox);

        isStaticBox = new QCheckBox(groupBox);
        isStaticBox->setObjectName(QString::fromUtf8("isStaticBox"));

        verticalLayout->addWidget(isStaticBox);

        isReadonlyBox = new QCheckBox(groupBox);
        isReadonlyBox->setObjectName(QString::fromUtf8("isReadonlyBox"));

        verticalLayout->addWidget(isReadonlyBox);


        formLayout->setWidget(5, QFormLayout::SpanningRole, groupBox);

        aggregationCombo = new QComboBox(AttributeTab);
        aggregationCombo->setObjectName(QString::fromUtf8("aggregationCombo"));

        formLayout->setWidget(3, QFormLayout::FieldRole, aggregationCombo);

        aggregationLabel = new QLabel(AttributeTab);
        aggregationLabel->setObjectName(QString::fromUtf8("aggregationLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, aggregationLabel);


        retranslateUi(AttributeTab);

        QMetaObject::connectSlotsByName(AttributeTab);
    } // setupUi

    void retranslateUi(QWidget *AttributeTab)
    {
        AttributeTab->setWindowTitle(QApplication::translate("AttributeTab", "AttributeTab", nullptr));
        typeLabel->setText(QApplication::translate("AttributeTab", "Type:", nullptr));
        defaultLabel->setText(QApplication::translate("AttributeTab", "Default:", nullptr));
        groupBox->setTitle(QApplication::translate("AttributeTab", "Flags:", nullptr));
        isCompositeBox->setText(QApplication::translate("AttributeTab", "Is Composite", nullptr));
        isDerivedBox->setText(QApplication::translate("AttributeTab", "Is Derived", nullptr));
        isDerivedUnionBox->setText(QApplication::translate("AttributeTab", "Is Derived Union", nullptr));
        isIDBox->setText(QApplication::translate("AttributeTab", "Is ID", nullptr));
        isStaticBox->setText(QApplication::translate("AttributeTab", "Is Static", nullptr));
        isReadonlyBox->setText(QApplication::translate("AttributeTab", "Is Readonly", nullptr));
        aggregationLabel->setText(QApplication::translate("AttributeTab", "Aggregation:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AttributeTab: public Ui_AttributeTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATTRIBUTETAB_H
