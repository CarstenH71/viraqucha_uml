/********************************************************************************
** Form generated from reading UI file 'CommentTab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMENTTAB_H
#define UI_COMMENTTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CommentTab
{
public:
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *textEdit;

    void setupUi(QWidget *CommentTab)
    {
        if (CommentTab->objectName().isEmpty())
            CommentTab->setObjectName(QString::fromUtf8("CommentTab"));
        CommentTab->resize(400, 300);
        verticalLayout = new QVBoxLayout(CommentTab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textEdit = new QPlainTextEdit(CommentTab);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout->addWidget(textEdit);


        retranslateUi(CommentTab);

        QMetaObject::connectSlotsByName(CommentTab);
    } // setupUi

    void retranslateUi(QWidget *CommentTab)
    {
        Q_UNUSED(CommentTab);
    } // retranslateUi

};

namespace Ui {
    class CommentTab: public Ui_CommentTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMENTTAB_H
