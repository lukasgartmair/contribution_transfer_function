
#include <iostream>
#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCase.h>

#include "CTF_functions.h"
#include <vector>
 
class TestCTF : public CppUnit::TestFixture {


public:
 
	static CppUnit::Test *suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("TestCTF");
 
		suiteOfTests->addTest(new CppUnit::TestCaller<TestCTF>("Test0 - Test the Test itsself",
				&TestCTF::testCTF_TestTheTest ));
				
		suiteOfTests->addTest(new CppUnit::TestCaller<TestCTF>("Test1 - Calculate Subvolumes",
				&TestCTF::testCTF_CalculateSubvolumes));
				
		suiteOfTests->addTest(new CppUnit::TestCaller<TestCTF>("Test2 - Calculate Voxel Contributions",
				&TestCTF::testCTF_CalculateVoxelContributions));

				
		return suiteOfTests;
	}
 
	/// Setup method
	void setUp() {}
 
	/// Teardown method
	void tearDown() {}
 
protected:
	void testCTF_TestTheTest() 
	{
		int x = 1;
		int z = 2;
		int u = x + z;
		CPPUNIT_ASSERT_EQUAL(3, u);
	}
	
	void testCTF_CalculateSubvolumes() 
	{	

		std::vector<float> atom_position = {0.5, 0.5, 0.5};
		std::vector<float> volumes_of_subcuboids;
		volumes_of_subcuboids = calcSubvolumes(atom_position);
	
		std::vector<float> assertion_subvolumes = {0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125};
		for (int i=0;i<volumes_of_subcuboids.size();i++)
		{
			CPPUNIT_ASSERT_EQUAL(assertion_subvolumes[i], volumes_of_subcuboids[i]);
		}
		
		
		atom_position = {0.25, 0.25, 0.25};

		volumes_of_subcuboids = calcSubvolumes(atom_position);
	
		assertion_subvolumes = {0.015625, 0.046875, 0.140625, 0.046875, 0.046875, 0.140625, 0.421875, 0.140625};
		for (int i=0;i<volumes_of_subcuboids.size();i++)
		{
			CPPUNIT_ASSERT_EQUAL(assertion_subvolumes[i], volumes_of_subcuboids[i]);
		}

	}
	
	void testCTF_CalculateVoxelContributions() 
	{	

/*

		std::vector<float> atom_position = {0.5, 0.5, 0.5};
		std::vector<float> contributions_of_subcuboids;
		contributions_of_subcuboids = calcVoxelContributions(atom_position);
	
		std::vector<float> assertion_contributions = {0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125};
		for (int i=0;i<volumes_of_subcuboids.size();i++)
		{
			CPPUNIT_ASSERT_EQUAL(assertion_subvolumes[i], volumes_of_subcuboids[i]);
		}
*/

	}
	

	
	

};
