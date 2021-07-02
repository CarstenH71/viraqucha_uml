/********************************************************************************
** Form generated from reading UI file 'StartPage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTPAGE_H
#define UI_STARTPAGE_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartPage
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *logoLabel;
    QFrame *line;
    QGridLayout *gridLayout;
    QLabel *introLabel;
    QLabel *templatesLabel;
    QLabel *aboutLabel;
    QLabel *startedLabel;
    QLabel *recentLabel;
    QPushButton *openProject;
    QPushButton *newProject;
    QListWidget *recentProjects;
    QListWidget *projectTemplates;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *StartPage)
    {
        if (StartPage->objectName().isEmpty())
            StartPage->setObjectName(QString::fromUtf8("StartPage"));
        StartPage->resize(778, 471);
        StartPage->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        verticalLayout = new QVBoxLayout(StartPage);
        verticalLayout->setSpacing(10);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        logoLabel = new QLabel(StartPage);
        logoLabel->setObjectName(QString::fromUtf8("logoLabel"));
        logoLabel->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        logoLabel->setFrameShape(QFrame::NoFrame);
        logoLabel->setTextFormat(Qt::AutoText);
        logoLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/logo.png")));
        logoLabel->setMargin(0);

        verticalLayout->addWidget(logoLabel);

        line = new QFrame(StartPage);
        line->setObjectName(QString::fromUtf8("line"));
        line->setMinimumSize(QSize(0, 10));
        line->setMaximumSize(QSize(16777215, 10));
        line->setAutoFillBackground(false);
        line->setStyleSheet(QString::fromUtf8("color: rgb(244,164,96)"));
        line->setFrameShadow(QFrame::Plain);
        line->setFrameShape(QFrame::HLine);

        verticalLayout->addWidget(line);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinimumSize);
        gridLayout->setHorizontalSpacing(15);
        gridLayout->setVerticalSpacing(5);
        gridLayout->setContentsMargins(10, -1, 10, -1);
        introLabel = new QLabel(StartPage);
        introLabel->setObjectName(QString::fromUtf8("introLabel"));
        introLabel->setTextFormat(Qt::RichText);
        introLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        introLabel->setWordWrap(true);

        gridLayout->addWidget(introLabel, 4, 2, 2, 1);

        templatesLabel = new QLabel(StartPage);
        templatesLabel->setObjectName(QString::fromUtf8("templatesLabel"));

        gridLayout->addWidget(templatesLabel, 4, 0, 1, 1, Qt::AlignLeft);

        aboutLabel = new QLabel(StartPage);
        aboutLabel->setObjectName(QString::fromUtf8("aboutLabel"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        aboutLabel->setFont(font);
        aboutLabel->setStyleSheet(QString::fromUtf8("color: rgb(244,164,96)"));

        gridLayout->addWidget(aboutLabel, 3, 2, 1, 1);

        startedLabel = new QLabel(StartPage);
        startedLabel->setObjectName(QString::fromUtf8("startedLabel"));
        startedLabel->setFont(font);
        startedLabel->setStyleSheet(QString::fromUtf8("color: rgb(244,164,96)"));

        gridLayout->addWidget(startedLabel, 0, 2, 1, 1);

        recentLabel = new QLabel(StartPage);
        recentLabel->setObjectName(QString::fromUtf8("recentLabel"));

        gridLayout->addWidget(recentLabel, 1, 0, 1, 1, Qt::AlignLeft);

        openProject = new QPushButton(StartPage);
        openProject->setObjectName(QString::fromUtf8("openProject"));
        openProject->setMaximumSize(QSize(32, 32));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/open_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        openProject->setIcon(icon);
        openProject->setFlat(true);

        gridLayout->addWidget(openProject, 0, 1, 1, 1);

        newProject = new QPushButton(StartPage);
        newProject->setObjectName(QString::fromUtf8("newProject"));
        newProject->setMaximumSize(QSize(32, 32));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/new_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        newProject->setIcon(icon1);
        newProject->setFlat(true);

        gridLayout->addWidget(newProject, 3, 1, 1, 1);

        recentProjects = new QListWidget(StartPage);
        recentProjects->setObjectName(QString::fromUtf8("recentProjects"));
        recentProjects->setFrameShadow(QFrame::Plain);

        gridLayout->addWidget(recentProjects, 2, 0, 1, 2);

        projectTemplates = new QListWidget(StartPage);
        projectTemplates->setObjectName(QString::fromUtf8("projectTemplates"));
        projectTemplates->setFrameShadow(QFrame::Plain);

        gridLayout->addWidget(projectTemplates, 5, 0, 1, 2);

        label = new QLabel(StartPage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: rgb(244,164,96)"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(StartPage);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(244,164,96)"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        gridLayout->setColumnStretch(1, 1);
        gridLayout->setColumnMinimumWidth(0, 250);

        verticalLayout->addLayout(gridLayout);


        retranslateUi(StartPage);

        QMetaObject::connectSlotsByName(StartPage);
    } // setupUi

    void retranslateUi(QWidget *StartPage)
    {
        StartPage->setWindowTitle(QApplication::translate("StartPage", "StartPage", nullptr));
        logoLabel->setText(QString());
        introLabel->setText(QApplication::translate("StartPage", "<html><head/><body><p>ViraquchaUML is an open source modeling tool for software developers. With ViraquchaUML you create models of software systems using the Unified Modeling Language (UML) version 2.5.</p><p>Version: 1.0<br/>Copyright (C) 2020 Carsten Huber<br/><a href=\"http://www.huberswelt.de\"><span style=\" text-decoration: underline; color:#2980b9;\">http://www.huberswelt.de</span></a></p></body></html>", nullptr));
        templatesLabel->setText(QApplication::translate("StartPage", "Project Templates:", nullptr));
        aboutLabel->setText(QApplication::translate("StartPage", "About", nullptr));
        startedLabel->setText(QApplication::translate("StartPage", "Get Started", nullptr));
        recentLabel->setText(QApplication::translate("StartPage", "Recent Projects:", nullptr));
        openProject->setText(QString());
        newProject->setText(QString());
        label->setText(QApplication::translate("StartPage", "Open Project", nullptr));
        label_2->setText(QApplication::translate("StartPage", "Create Project", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartPage: public Ui_StartPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTPAGE_H
