#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>
 
#include "TestSuiteCTF.h"
#include "CTF_functions.h"

//sudo g++ TestRunner.cpp -lcppunit -o RunTests
//  sudo g++ TestRunner.cpp CTF_functions.cpp -lcppunit -std=c++11 -o RunTests

 
using namespace std;
 
int main() {
	CppUnit::TextUi::TestRunner runner;
 
	cout << "Creating Test Suites:" << endl;
	runner.addTest(TestCTF::suite());
	cout<< "Running the unit tests."<<endl;
	runner.run();
 
	return 0;
}
