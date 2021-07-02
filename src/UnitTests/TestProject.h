//---------------------------------------------------------------------------------------------------------------------
// TestProject.h                                                                                       (C) 2017 C.Huber 
//
// Declaration of class TestProject which tests UmlProject and other classes of lib UmlCommon and UmlClassifiers.
//---------------------------------------------------------------------------------------------------------------------
#pragma once

#include <QObject>
#include <QTest>

#include "UmlCommon.h"
#include "UmlClassifiers.h"

class TestProject : public QObject
{
   Q_OBJECT
public:
   TestProject();
   virtual ~TestProject();

private slots:
   // Will be called before the first test function is executed.
   void initTestCase();
   // Will be called after the last test function was executed.
   void cleanupTestCase();
   // Will be called before each test function is executed.
   void init();
   // Will be called after every test function.
   void cleanup();

   // UmlCommon tests:
   void testFactory();
   void testInsert();
   void testRemove();
   void testSave();
   void testLoad();

   // UmlClassifier tests:
   void testAttribute();
   void testOperation();

private:
   UmlModel* createModel(QUuid id, QString name, QString viewpt);
   UmlDiagram* createDiagram(QUuid id, QString name, DiagramKind kind);
   UmlComment* createComment(QUuid id, QString body);
   UmlPackage* createPackage(QUuid id, QString name, VisibilityKind kind);
   UmlLink* createLink(QUuid id, UmlElement* src, UmlElement* tgt);
   UmlDependency* createDependency(QUuid id, UmlElement* src, UmlElement* tgt, QString kwd);
   UmlClass* createClass(QUuid id, QString name);
};
