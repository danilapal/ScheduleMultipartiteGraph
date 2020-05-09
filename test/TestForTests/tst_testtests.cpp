#include <QtTest>

// add necessary includes here

class TestTests : public QObject
{
    Q_OBJECT

public:
    TestTests();
    ~TestTests();

private slots:
    void test_case1();

};

TestTests::TestTests()
{

}

TestTests::~TestTests()
{

}

void TestTests::test_case1()
{

}

QTEST_APPLESS_MAIN(TestTests)

#include "tst_testtests.moc"
