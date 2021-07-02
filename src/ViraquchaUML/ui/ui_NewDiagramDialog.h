/********************************************************************************
** Form generated from reading UI file 'NewDiagramDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWDIAGRAMDIALOG_H
#define UI_NEWDIAGRAMDIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NewDiagramDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label1;
    QComboBox *comboBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NewDiagramDialog)
    {
        if (NewDiagramDialog->objectName().isEmpty())
            NewDiagramDialog->setObjectName(QString::fromUtf8("NewDiagramDialog"));
        NewDiagramDialog->setWindowModality(Qt::NonModal);
        NewDiagramDialog->resize(255, 108);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NewDiagramDialog->sizePolicy().hasHeightForWidth());
        NewDiagramDialog->setSizePolicy(sizePolicy);
        NewDiagramDialog->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        NewDiagramDialog->setModal(true);
        verticalLayout = new QVBoxLayout(NewDiagramDialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label1 = new QLabel(NewDiagramDialog);
        label1->setObjectName(QString::fromUtf8("label1"));

        verticalLayout->addWidget(label1);

        comboBox = new QComboBox(NewDiagramDialog);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout->addWidget(comboBox);

        buttonBox = new QDialogButtonBox(NewDiagramDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(NewDiagramDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewDiagramDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewDiagramDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewDiagramDialog);
    } // setupUi

    void retranslateUi(QDialog *NewDiagramDialog)
    {
        NewDiagramDialog->setWindowTitle(QApplication::translate("NewDiagramDialog", "New Diagram", nullptr));
        label1->setText(QApplication::translate("NewDiagramDialog", "Please choose a diagram type:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewDiagramDialog: public Ui_NewDiagramDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWDIAGRAMDIALOG_H
