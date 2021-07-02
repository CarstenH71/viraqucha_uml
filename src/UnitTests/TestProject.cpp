//---------------------------------------------------------------------------------------------------------------------
// TestProject.cpp                                                                                     (C) 2017 C.Huber 
//
// Implementation of class TestProject (unit tests).
//---------------------------------------------------------------------------------------------------------------------
#include "TestProject.h"

#include <QList>
#include <QSharedPointer>

TestProject::TestProject()
{
}

TestProject::~TestProject()
{
}

void TestProject::initTestCase()
{
   initCommon();
   initClassifiers();
}

void TestProject::cleanupTestCase()
{
}

void TestProject::init()
{
}

void TestProject::cleanup()
{
   //QDir dir(QDir::tempPath() + "/umlsavetest");
   //dir.removeRecursively();
}

/**
 * Tests the factory.
 */
void TestProject::testFactory()
{
   auto& fac = UmlElementFactory::instance();
   QVERIFY(fac.count() == 19);

   // Create a UmlDiagram instance using the factory:
   UmlElementPtr obj1 = UmlElementPtr(fac.build("UmlDiagram", QUuid::createUuid()));
   QVERIFY(dynamic_cast<UmlDiagram*>(obj1.pointee()) != nullptr);
   obj1->dispose();
   // Entity will be deleted automatically as soon as the UmlEntityPtr instance goes out of scope.

   UmlElementPtr obj2 = UmlElementPtr(fac.build("UmlAttribute", QUuid::createUuid()));
   QVERIFY(dynamic_cast<UmlAttribute*>(obj2.pointee()) != nullptr);
   obj2->dispose();
}

void TestProject::testInsert()
{
}

void TestProject::testRemove()
{
}

/**
 * Tests saving of an UmlProject with several objects.
 */
void TestProject::testSave()
{
   auto prj = QSharedPointer<UmlProject>(new UmlProject());
   QVERIFY(prj != nullptr);

   prj->create(QDir::tempPath(), "umlsavetest");
   prj->setAuthor("Carsten Huber");
   prj->setName("Test Project");
   prj->setComment("This is a test project.");
   
   auto* root = prj->root();

   auto* mdl = createModel(QUuid("{93635E6B-F0BB-4DB5-8CEE-E9D569E8A671}"), "Test Model", "Unit Test");
   prj->insert(mdl);
   root->insert(0, mdl);

   auto* cmt = createComment(QUuid("{3E387772-C457-423A-A11A-4419DA0EA80E}"), "These packages depend on each other");
   prj->insert(cmt);
   mdl->insert(0, cmt);

   auto* pkg1 = createPackage(QUuid("{16B0212F-7FB2-400E-BCDF-8FDF68A0B353}"), "Package One", VisibilityKind::Public);
   prj->insert(pkg1);
   mdl->insert(0, pkg1);

   auto* pkg2 = createPackage(QUuid("{645EAA99-6EED-41E7-B931-8C2F128876E3}"), "Package Two", VisibilityKind::Public);
   prj->insert(pkg2);
   mdl->insert(1, pkg2);

   auto* pkg3 = createPackage(QUuid("{B2947615-06E3-4477-86B5-AF7532E20D47}"), "Package Three", VisibilityKind::Public);
   prj->insert(pkg3);
   mdl->insert(2, pkg3);

   auto* pkg4 = createPackage(QUuid("{2AD42C6C-473E-4982-82DF-82A492F8D946}"), "Package Four", VisibilityKind::Public);
   prj->insert(pkg4);
   mdl->insert(3, pkg4);

   auto* par = new UmlTemplateParameter();
   par->setName("T");
   par->setType("class");
   pkg4->append(par);

   auto* lnk = createLink(QUuid("{8DEB91A5-D0C3-4754-8AB6-33AAC0696DF3}"), pkg1, cmt);
   prj->insert(lnk);
   mdl->insert(0, lnk);

   auto* dep1 = createDependency(QUuid("{1CC5D44C-DB3A-4DCB-916A-C7D4540FF61C}"), pkg1, pkg2, KwdImport);
   prj->insert(dep1);
   mdl->insert(0, dep1);

   auto* dep2 = createDependency(QUuid("{9007FBC8-E00D-4DDC-BC3A-6EC74E351794}"), pkg2, pkg3, KwdMerge);
   prj->insert(dep2);
   mdl->insert(0, dep2);

   auto* bnd = new UmlTemplateBinding("{C5FBC3B7-DD05-43FD-94FA-38A368E7650E}");
   bnd->setSource(pkg3);
   bnd->setTarget(pkg4);
   prj->insert(bnd);

   auto* sbt = new UmlParameterSubstitution();
   sbt->setTemplParam("T");
   sbt->setActualParam("int");
   bnd->append(sbt);

   auto* dia = createDiagram(QUuid("{2D6A36F5-DA6D-4878-B0C8-84CF29297EFC}"), "Package dependencies", DiagramKind::Packages);
   dia->setComment("Shows package dependencies modeled with ViraquchaUML");
   prj->insert(dia);
   mdl->insert(0, dia);

   auto* cls = createClass(QUuid("{DC9EFE50-330B-4BDF-A71A-78058A0CE165}"), "Class1");
   prj->insert(cls);
   pkg4->insert(0, cls);

   auto* n1 = dia->addNode(pkg1);
   n1->setPos(10, 10);
   n1->setSize(15, 17);
   n1->setFillColor(22);
   auto* n2 = dia->addNode(pkg2);
   n2->setPos(20, 20);
   n2->setSize(25, 27);
   n2->setFillColor(22);
   auto* n3 = dia->addNode(pkg3);
   n3->setPos(50, 50);
   n3->setSize(55, 57);
   n3->setFillColor(22);
   auto* n4 = dia->addNode(cmt);
   n4->setPos(60, 60);
   n4->setSize(65, 67);
   n4->setFillColor(22);
   auto* e1 = dia->addEdge(dep1);
   e1->setShape1(n1);
   e1->setShape2(n2);
   auto* e2 = dia->addEdge(dep2);
   e2->setShape1(n2);
   e2->setShape2(n3);
   auto* e3 = dia->addEdge(lnk);
   e3->setShape1(n1);
   e3->setShape2(n4);

   QCOMPARE(prj->count(), 13);

   int res = prj->save(QDir::tempPath() + "/umlsavetest/umlsavetest.uprj");
   QVERIFY(res == 0);

   prj->dispose();
}

/**
 * Tests loading of an UmlProject from a project file.
 */
void TestProject::testLoad()
{
   auto prj = QSharedPointer<UmlProject>(new UmlProject());
   QVERIFY(prj != nullptr);

   int res = prj->load(QDir::tempPath() + "/umlsavetest/umlsavetest.uprj");
   QVERIFY(res == 0);
   QCOMPARE(prj->count(), 13);
   QVERIFY(prj->contains(QUuid("{4CD3CF41-E522-4101-B57D-402CD2E8DF50}")) == true);
   QVERIFY(prj->contains(QUuid("{93635E6B-F0BB-4DB5-8CEE-E9D569E8A671}")) == true);
   QVERIFY(prj->contains(QUuid("{3E387772-C457-423A-A11A-4419DA0EA80E}")) == true);
   QVERIFY(prj->contains(QUuid("{16B0212F-7FB2-400E-BCDF-8FDF68A0B353}")) == true);
   QVERIFY(prj->contains(QUuid("{645EAA99-6EED-41E7-B931-8C2F128876E3}")) == true);
   QVERIFY(prj->contains(QUuid("{B2947615-06E3-4477-86B5-AF7532E20D47}")) == true);
   QVERIFY(prj->contains(QUuid("{8DEB91A5-D0C3-4754-8AB6-33AAC0696DF3}")) == true);
   QVERIFY(prj->contains(QUuid("{1CC5D44C-DB3A-4DCB-916A-C7D4540FF61C}")) == true);
   QVERIFY(prj->contains(QUuid("{9007FBC8-E00D-4DDC-BC3A-6EC74E351794}")) == true);
   QVERIFY(prj->contains(QUuid("{2D6A36F5-DA6D-4878-B0C8-84CF29297EFC}")) == true);
   QVERIFY(prj->contains(QUuid("{DC9EFE50-330B-4BDF-A71A-78058A0CE165}")) == true);

   QCOMPARE(prj->root()->count(), 1);

   auto mdl = dynamic_cast<UmlModel*>(prj->root()->at(0));
   QVERIFY(mdl != nullptr);
   QCOMPARE(mdl->count(), 9);
   QCOMPARE(prj->root()->count(), 1);

   auto dia = dynamic_cast<UmlDiagram*>(prj->take(QUuid("{2D6A36F5-DA6D-4878-B0C8-84CF29297EFC}")));
   QVERIFY(dia != nullptr);
   QVERIFY(dia->nodeCount() == 4);
   QVERIFY(dia->edgeCount() == 3);

   prj->dispose();
}

void TestProject::testAttribute()
{
   auto atr1 = QSharedPointer<UmlAttribute>(new UmlAttribute());
   QVERIFY(atr1 != nullptr);

   atr1->setName("test");
   atr1->setVisibility(VisibilityKind::Public);
   atr1->setAggregation(AggregationKind::Composite);
   atr1->setType("uint32");
   atr1->setDefaultValue("10");

   QString sig1 = atr1->signature();
   atr1->dispose();
   QVERIFY(sig1 == "+ test: uint32 = 10");

   auto atr2 = QSharedPointer<UmlAttribute>(new UmlAttribute());
   QVERIFY(atr2 != nullptr);

   atr2->setName("array");
   atr2->setVisibility(VisibilityKind::Private);
   atr2->setAggregation(AggregationKind::Composite);
   atr2->setType("string");
   atr2->setLower(1);
   atr2->setUpper(100);

   QString sig2 = atr2->signature();
   atr2->dispose();
   QVERIFY(sig2 == "- array: string [1..100]");
}

void TestProject::testOperation()
{
   auto opr1 = QSharedPointer<UmlOperation>(new UmlOperation());
   QVERIFY(opr1 != nullptr);

   opr1->setName("func");
   opr1->setVisibility(VisibilityKind::Public);
   opr1->setReturnType("bool");
   opr1->setLower(1);
   opr1->setUpper(22);

   auto* par1 = new UmlParameter();
   par1->setName("a");
   par1->setType("double");
   opr1->append(par1);

   auto* par2 = new UmlParameter();
   par2->setName("b");
   par2->setType("int");
   par2->setDefaultValue("0");
   opr1->append(par2);

   QString sig1 = opr1->signature();
   opr1->dispose();
   QVERIFY(sig1 == "+ func(a: double, b: int = 0): bool [1..22]");
}


UmlModel* TestProject::createModel(QUuid id, QString name, QString viewpt)
{
   auto mdl = new UmlModel(id);
   mdl->setName(name);
   mdl->setComment("This is a test model");
   mdl->setUri("http//www.huberswelt.de");
   mdl->setViewpoint(viewpt);
   return mdl;
}

UmlDiagram* TestProject::createDiagram(QUuid id, QString name, DiagramKind kind)
{
   auto dia = new UmlDiagram(id);
   dia->setName(name);
   dia->setComment("Shows package dependencies modeled with ViraquchaUML");
   dia->setKind(kind);
   return dia;
}

UmlComment* TestProject::createComment(QUuid id, QString body)
{
   auto cmt = new UmlComment(id);
   cmt->setBody(body);
   return cmt;
}

UmlPackage* TestProject::createPackage(QUuid id, QString name, VisibilityKind kind)
{
   auto pkg = new UmlPackage(id);
   pkg->setName(name);
   pkg->setComment("A package");
   pkg->setVisibility(kind);
   return pkg;
}

UmlLink* TestProject::createLink(QUuid id, UmlElement* src, UmlElement* tgt)
{
   auto lnk = new UmlLink(id);
   lnk->setSource(src);
   lnk->setTarget(tgt);
   return lnk;
}

UmlDependency* TestProject::createDependency(QUuid id, UmlElement* src, UmlElement* tgt, QString kwd)
{
   auto dep = new UmlDependency(id);
   dep->setKeywords(kwd);
   dep->setSource(src);
   dep->setTarget(tgt);
   return dep;
}

UmlClass* TestProject::createClass(QUuid id, QString name)
{
   auto cls = new UmlClass(id);
   cls->setName(name);
   return cls;
}

