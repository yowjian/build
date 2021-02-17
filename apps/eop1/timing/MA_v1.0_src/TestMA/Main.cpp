#include "TestAMQManager.h"
#include "TestMessageHandler.h"
#include "TestMissionPlan.h"
#include "TestSchedule.h"
#include "TestUtils.h"
#include "TestStore.h"
#include "TestHeartBeat.h"
#include "TestDetect.h"
#include "TestGroundMovers.h"
#include "TestISRM.h"
#include "TestISRMFindFix.h"
#include "TestISRMPlan.h"
#include "TestMPU.h"
#include "TestMaintainProduct.h"
#include "TestMissionExecution.h"
#include "TestMPX.h"
#include "TestTOI.h"
#include "TestRDR.h"
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <fstream>
#include <ostream>
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(TestAMQManager);
CPPUNIT_TEST_SUITE_REGISTRATION(TestMessageHandler);
CPPUNIT_TEST_SUITE_REGISTRATION(TestMissionPlan);
CPPUNIT_TEST_SUITE_REGISTRATION(TestSchedule);
CPPUNIT_TEST_SUITE_REGISTRATION(TestUtils);
CPPUNIT_TEST_SUITE_REGISTRATION(TestStore);
CPPUNIT_TEST_SUITE_REGISTRATION(TestHeartBeat);
CPPUNIT_TEST_SUITE_REGISTRATION(TestDetect);
CPPUNIT_TEST_SUITE_REGISTRATION(TestGroundMovers);
CPPUNIT_TEST_SUITE_REGISTRATION(TestISRM);
CPPUNIT_TEST_SUITE_REGISTRATION(TestISRMFindFix);
CPPUNIT_TEST_SUITE_REGISTRATION(TestISRMPlan);
CPPUNIT_TEST_SUITE_REGISTRATION(TestMPU);
CPPUNIT_TEST_SUITE_REGISTRATION(TestMaintainProduct);
CPPUNIT_TEST_SUITE_REGISTRATION(TestMissionExecution);
CPPUNIT_TEST_SUITE_REGISTRATION(TestMPX);
CPPUNIT_TEST_SUITE_REGISTRATION(TestTOI);
CPPUNIT_TEST_SUITE_REGISTRATION(TestRDR);

int main(int argc, char* argv[])
{	
	// informs test-listener about testresults
	CPPUNIT_NS::TestResult testresult;

	// register listener for collecting the test-results
	CPPUNIT_NS::TestResultCollector collectedresults;
	testresult.addListener(&collectedresults);

	// register listener for per-test progress output
	CPPUNIT_NS::BriefTestProgressListener progress;
	testresult.addListener(&progress);

	// insert test-suite at test-runner by registry
	CPPUNIT_NS::TestRunner testrunner;
	testrunner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
	testrunner.run(testresult);

	// output results in compiler-format
	CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
	compileroutputter.write();

	// Output XML for Jenkins CPPunit plugin
	ofstream xmlFileOut("maTestResults.xml");
	CPPUNIT_NS::XmlOutputter xmlOut(&collectedresults, xmlFileOut);
	xmlOut.write();

	// return 0 if tests were successful
	return collectedresults.wasSuccessful() ? 0 : 1;
}