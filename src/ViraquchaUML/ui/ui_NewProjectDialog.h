/********************************************************************************
** Form generated from reading UI file 'NewProjectDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPROJECTDIALOG_H
#define UI_NEWPROJECTDIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_NewProjectDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *locationLabel;
    QLabel *nameLabel;
    QPushButton *browseButton;
    QLineEdit *nameEdit;
    QSpacerItem *verticalSpacer;
    QLabel *helpText;
    QPushButton *acceptButton;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer;
    QComboBox *locationEdit;

    void setupUi(QDialog *NewProjectDialog)
    {
        if (NewProjectDialog->objectName().isEmpty())
            NewProjectDialog->setObjectName(QString::fromUtf8("NewProjectDialog"));
        NewProjectDialog->resize(400, 153);
        NewProjectDialog->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        NewProjectDialog->setSizeGripEnabled(true);
        gridLayout = new QGridLayout(NewProjectDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        locationLabel = new QLabel(NewProjectDialog);
        locationLabel->setObjectName(QString::fromUtf8("locationLabel"));

        gridLayout->addWidget(locationLabel, 2, 1, 1, 1);

        nameLabel = new QLabel(NewProjectDialog);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        gridLayout->addWidget(nameLabel, 1, 1, 1, 1);

        browseButton = new QPushButton(NewProjectDialog);
        browseButton->setObjectName(QString::fromUtf8("browseButton"));

        gridLayout->addWidget(browseButton, 2, 4, 1, 1);

        nameEdit = new QLineEdit(NewProjectDialog);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

        gridLayout->addWidget(nameEdit, 1, 2, 1, 3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 1, 1, 4);

        helpText = new QLabel(NewProjectDialog);
        helpText->setObjectName(QString::fromUtf8("helpText"));

        gridLayout->addWidget(helpText, 0, 1, 1, 4);

        acceptButton = new QPushButton(NewProjectDialog);
        acceptButton->setObjectName(QString::fromUtf8("acceptButton"));

        gridLayout->addWidget(acceptButton, 4, 3, 1, 1);

        cancelButton = new QPushButton(NewProjectDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        gridLayout->addWidget(cancelButton, 4, 4, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 4, 2, 1, 1);

        locationEdit = new QComboBox(NewProjectDialog);
        locationEdit->setObjectName(QString::fromUtf8("locationEdit"));
        locationEdit->setEditable(true);
        locationEdit->setInsertPolicy(QComboBox::InsertAtTop);

        gridLayout->addWidget(locationEdit, 2, 2, 1, 2);


        retranslateUi(NewProjectDialog);
        QObject::connect(acceptButton, SIGNAL(clicked()), NewProjectDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), NewProjectDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewProjectDialog);
    } // setupUi

    void retranslateUi(QDialog *NewProjectDialog)
    {
        NewProjectDialog->setWindowTitle(QApplication::translate("NewProjectDialog", "New Project", nullptr));
        locationLabel->setText(QApplication::translate("NewProjectDialog", "Location:", nullptr));
        nameLabel->setText(QApplication::translate("NewProjectDialog", "Name:", nullptr));
        browseButton->setText(QApplication::translate("NewProjectDialog", "&Browse...", nullptr));
        helpText->setText(QApplication::translate("NewProjectDialog", "<html><head/><body><p>Please enter a name and a location (path) for the new project.<br/>Click on [Browse...] to open the systems' file open dialog.</p></body></html>", nullptr));
        acceptButton->setText(QApplication::translate("NewProjectDialog", "OK", nullptr));
        cancelButton->setText(QApplication::translate("NewProjectDialog", "&Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewProjectDialog: public Ui_NewProjectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPROJECTDIALOG_H
