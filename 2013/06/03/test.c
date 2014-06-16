#include <stdlib.h>
#include <string.h>
#include "CuTest.h"

typedef struct Lens
{
	char* name;
	int radius;
} Lens;

static Lens* lens;



void Test_setup(CuTest* tc)
{
	lens = malloc(sizeof(Lens));
	lens->name = malloc(sizeof(char)*256);
	strcpy(lens->name, "SiO2");
	lens->radius = 5;
	/*CuAssert(tc, "Setup", 1);*/
}

void Test_teardown(CuTest* tc)
{
	free(lens->name);
	free(lens);
	/*CuAssert(tc, "Teardown", 0);*/
}

void Test_lens(CuTest* tc)
{
	CuAssertStrEquals(tc, lens->name, "Si02");
	CuAssertIntEquals(tc, lens->radius, 4);
}

void Test_Fail(CuTest* tc)
{
	CuFail(tc, "失敗する");
}

void Test_Assert(CuTest* tc)
{
	int cond = 0;
	CuAssert(tc, "cond=0でアサートする", cond);
}

void Test_AssertTrue(CuTest* tc)
{
	int cond = 0;
	CuAssertTrue(tc, cond);
}

void Test_AssertStr(CuTest* tc)
{
	char* actual = "Helle";
	CuAssertStrEquals(tc, "Hello", actual);
	// １つのテストメソッドに複数のAssertマクロを入れる場合
	// 先に失敗すると次まで流れない。
	CuAssertStrEquals_Msg(tc, "Helloじゃないじゃん！Typoじゃね？", "Hello", actual);
}

void Test_AssertStrMsg(CuTest* tc)
{
	char* actual = "Helle";
	CuAssertStrEquals_Msg(tc, "Helloじゃないじゃん！Typoじゃね？", "Hello", actual);
}

void Test_AssertInt(CuTest* tc)
{
	CuAssertIntEquals(tc, 5, 6);
}

void Test_AssertDbl(CuTest* tc)
{
	CuAssertDblEquals(tc, 1.01, 1.02, 0.001);
}

void Test_AssertDblMsg(CuTest* tc)
{
	CuAssertDblEquals_Msg(tc, "Delta=0.001(こんな感じに誤差を書いたほうがいいかも)", 1.01, 1.02, 0.001);
}

void Test_AssertPtr(CuTest* tc)
{
	char* str = malloc(sizeof(char)*5);
	CuAssertPtrEquals(tc, NULL, str);
	free(str);
}

CuSuite* StrUtilGetSuite()
{
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, Test_setup);
	SUITE_ADD_TEST(suite, Test_Fail);
	SUITE_ADD_TEST(suite, Test_Assert);
	SUITE_ADD_TEST(suite, Test_AssertTrue);
	SUITE_ADD_TEST(suite, Test_AssertStr);
	SUITE_ADD_TEST(suite, Test_AssertStrMsg);
	SUITE_ADD_TEST(suite, Test_AssertInt);
	SUITE_ADD_TEST(suite, Test_AssertDbl);
	SUITE_ADD_TEST(suite, Test_AssertPtr);
	SUITE_ADD_TEST(suite, Test_teardown);
	return suite;
}
