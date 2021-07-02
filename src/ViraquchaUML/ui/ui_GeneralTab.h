/********************************************************************************
** Form generated from reading UI file 'GeneralTab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERALTAB_H
#define UI_GENERALTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GeneralTab
{
public:
    QFormLayout *formLayout;
    QLabel *nameLabel;
    QLineEdit *nameEdit;
    QLabel *visibLabel;
    QComboBox *visibCombo;
    QLabel *stereoLabel;
    QComboBox *stereoCombo;
    QLabel *commentLabel;
    QPlainTextEdit *commentEdit;

    void setupUi(QWidget *GeneralTab)
    {
        if (GeneralTab->objectName().isEmpty())
            GeneralTab->setObjectName(QString::fromUtf8("GeneralTab"));
        GeneralTab->resize(421, 293);
        formLayout = new QFormLayout(GeneralTab);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        nameLabel = new QLabel(GeneralTab);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, nameLabel);

        nameEdit = new QLineEdit(GeneralTab);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, nameEdit);

        visibLabel = new QLabel(GeneralTab);
        visibLabel->setObjectName(QString::fromUtf8("visibLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, visibLabel);

        visibCombo = new QComboBox(GeneralTab);
        visibCombo->setObjectName(QString::fromUtf8("visibCombo"));

        formLayout->setWidget(1, QFormLayout::FieldRole, visibCombo);

        stereoLabel = new QLabel(GeneralTab);
        stereoLabel->setObjectName(QString::fromUtf8("stereoLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, stereoLabel);

        stereoCombo = new QComboBox(GeneralTab);
        stereoCombo->setObjectName(QString::fromUtf8("stereoCombo"));
        stereoCombo->setEditable(true);

        formLayout->setWidget(2, QFormLayout::FieldRole, stereoCombo);

        commentLabel = new QLabel(GeneralTab);
        commentLabel->setObjectName(QString::fromUtf8("commentLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, commentLabel);

        commentEdit = new QPlainTextEdit(GeneralTab);
        commentEdit->setObjectName(QString::fromUtf8("commentEdit"));

        formLayout->setWidget(3, QFormLayout::FieldRole, commentEdit);


        retranslateUi(GeneralTab);

        QMetaObject::connectSlotsByName(GeneralTab);
    } // setupUi

    void retranslateUi(QWidget *GeneralTab)
    {
        GeneralTab->setWindowTitle(QApplication::translate("GeneralTab", "GeneralTab", nullptr));
        nameLabel->setText(QApplication::translate("GeneralTab", "Name:", nullptr));
        visibLabel->setText(QApplication::translate("GeneralTab", "Visibility:", nullptr));
        stereoLabel->setText(QApplication::translate("GeneralTab", "Stereotype:", nullptr));
        commentLabel->setText(QApplication::translate("GeneralTab", "Comment:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GeneralTab: public Ui_GeneralTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERALTAB_H
