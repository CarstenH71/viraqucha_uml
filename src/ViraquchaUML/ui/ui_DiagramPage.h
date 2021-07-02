/********************************************************************************
** Form generated from reading UI file 'DiagramPage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIAGRAMPAGE_H
#define UI_DIAGRAMPAGE_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DiagramPage
{
public:
    QAction *actionEditShape;
    QAction *actionEditProperties;
    QAction *actionDeleteFromDiagram;
    QAction *actionDeleteFromModel;
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *DiagramPage)
    {
        if (DiagramPage->objectName().isEmpty())
            DiagramPage->setObjectName(QString::fromUtf8("DiagramPage"));
        DiagramPage->resize(400, 300);
        DiagramPage->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        actionEditShape = new QAction(DiagramPage);
        actionEditShape->setObjectName(QString::fromUtf8("actionEditShape"));
        actionEditProperties = new QAction(DiagramPage);
        actionEditProperties->setObjectName(QString::fromUtf8("actionEditProperties"));
        actionDeleteFromDiagram = new QAction(DiagramPage);
        actionDeleteFromDiagram->setObjectName(QString::fromUtf8("actionDeleteFromDiagram"));
        actionDeleteFromModel = new QAction(DiagramPage);
        actionDeleteFromModel->setObjectName(QString::fromUtf8("actionDeleteFromModel"));
        verticalLayout = new QVBoxLayout(DiagramPage);
        verticalLayout->setSpacing(5);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        graphicsView = new QGraphicsView(DiagramPage);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setLineWidth(0);
        graphicsView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        graphicsView->setSceneRect(QRectF(0, 0, 5000, 5000));
        graphicsView->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        graphicsView->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing|QPainter::SmoothPixmapTransform|QPainter::TextAntialiasing);
        graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
        graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

        verticalLayout->addWidget(graphicsView);


        retranslateUi(DiagramPage);

        QMetaObject::connectSlotsByName(DiagramPage);
    } // setupUi

    void retranslateUi(QWidget *DiagramPage)
    {
        DiagramPage->setWindowTitle(QApplication::translate("DiagramPage", "DiagramPage", nullptr));
        actionEditShape->setText(QApplication::translate("DiagramPage", "Shape...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionEditShape->setToolTip(QApplication::translate("DiagramPage", "Opens the properties dialog for the shape.", nullptr));
#endif // QT_NO_TOOLTIP
        actionEditProperties->setText(QApplication::translate("DiagramPage", "Properties...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionEditProperties->setToolTip(QApplication::translate("DiagramPage", "Opens the properties dialog for the UML element.", nullptr));
#endif // QT_NO_TOOLTIP
        actionDeleteFromDiagram->setText(QApplication::translate("DiagramPage", "Delete from Diagram", nullptr));
#ifndef QT_NO_TOOLTIP
        actionDeleteFromDiagram->setToolTip(QApplication::translate("DiagramPage", "Deletes the shape from the diagram.", nullptr));
#endif // QT_NO_TOOLTIP
        actionDeleteFromModel->setText(QApplication::translate("DiagramPage", "Delete from Model", nullptr));
#ifndef QT_NO_TOOLTIP
        actionDeleteFromModel->setToolTip(QApplication::translate("DiagramPage", "Deletes the shape from the diagram and the UML element from the model.", nullptr));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class DiagramPage: public Ui_DiagramPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIAGRAMPAGE_H
