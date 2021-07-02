/********************************************************************************
** Form generated from reading UI file 'ClassifierTab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLASSIFIERTAB_H
#define UI_CLASSIFIERTAB_H

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

class Ui_ClassifierTab
{
public:
    QFormLayout *formLayout;
    QLabel *languageLabel;
    QComboBox *languageCombo;
    QGroupBox *flagsGroup;
    QVBoxLayout *verticalLayout;
    QCheckBox *isAbstractBox;
    QCheckBox *isActiveBox;
    QCheckBox *isFinalBox;
    QCheckBox *isLeafBox;

    void setupUi(QWidget *ClassifierTab)
    {
        if (ClassifierTab->objectName().isEmpty())
            ClassifierTab->setObjectName(QString::fromUtf8("ClassifierTab"));
        ClassifierTab->resize(400, 300);
        formLayout = new QFormLayout(ClassifierTab);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        languageLabel = new QLabel(ClassifierTab);
        languageLabel->setObjectName(QString::fromUtf8("languageLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, languageLabel);

        languageCombo = new QComboBox(ClassifierTab);
        languageCombo->setObjectName(QString::fromUtf8("languageCombo"));

        formLayout->setWidget(0, QFormLayout::FieldRole, languageCombo);

        flagsGroup = new QGroupBox(ClassifierTab);
        flagsGroup->setObjectName(QString::fromUtf8("flagsGroup"));
        verticalLayout = new QVBoxLayout(flagsGroup);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        isAbstractBox = new QCheckBox(flagsGroup);
        isAbstractBox->setObjectName(QString::fromUtf8("isAbstractBox"));

        verticalLayout->addWidget(isAbstractBox);

        isActiveBox = new QCheckBox(flagsGroup);
        isActiveBox->setObjectName(QString::fromUtf8("isActiveBox"));

        verticalLayout->addWidget(isActiveBox);

        isFinalBox = new QCheckBox(flagsGroup);
        isFinalBox->setObjectName(QString::fromUtf8("isFinalBox"));

        verticalLayout->addWidget(isFinalBox);

        isLeafBox = new QCheckBox(flagsGroup);
        isLeafBox->setObjectName(QString::fromUtf8("isLeafBox"));

        verticalLayout->addWidget(isLeafBox);


        formLayout->setWidget(1, QFormLayout::SpanningRole, flagsGroup);


        retranslateUi(ClassifierTab);

        QMetaObject::connectSlotsByName(ClassifierTab);
    } // setupUi

    void retranslateUi(QWidget *ClassifierTab)
    {
        ClassifierTab->setWindowTitle(QApplication::translate("ClassifierTab", "ClassifierTab", nullptr));
        languageLabel->setText(QApplication::translate("ClassifierTab", "Language:", nullptr));
        flagsGroup->setTitle(QApplication::translate("ClassifierTab", "Flags:", nullptr));
        isAbstractBox->setText(QApplication::translate("ClassifierTab", "Is Abstract", nullptr));
        isActiveBox->setText(QApplication::translate("ClassifierTab", "Is Active", nullptr));
        isFinalBox->setText(QApplication::translate("ClassifierTab", "Is Final", nullptr));
        isLeafBox->setText(QApplication::translate("ClassifierTab", "Is Leaf", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClassifierTab: public Ui_ClassifierTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLASSIFIERTAB_H
