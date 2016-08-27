
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

		int number_of_vertices = 8;
		int xyz = 3;
		std::vector<std::vector<float> > vertices(number_of_vertices, std::vector<float>(xyz));

		vertices[0][0] = 0;
		vertices[0][1] = 0;
		vertices[0][2] = 0;

		vertices[1][0] = 1;
		vertices[1][1] = 0;
		vertices[1][2] = 0;

		vertices[2][0] = 1;
		vertices[2][1] = 1;
		vertices[2][2] = 0;

		vertices[3][0] = 0;
		vertices[3][1] = 1;
		vertices[3][2] = 0;

		vertices[4][0] = 0;
		vertices[4][1] = 0;
		vertices[4][2] = 1;

		vertices[5][0] = 1;
		vertices[5][1] = 0;
		vertices[5][2] = 1;

		vertices[6][0] = 1;
		vertices[6][1] = 1;
		vertices[6][2] = 1;

		vertices[7][0] = 0;
		vertices[7][1] = 1;
		vertices[7][2] = 1;

		std::vector<float> atom_position = {0.5, 0.5, 0.5};
		std::vector<float> volumes_of_subcuboids;
		volumes_of_subcuboids = calcSubvolumes(atom_position, vertices);
	
		std::vector<float> assertion_subvolumes = {0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125};
		for (int i=0;i<volumes_of_subcuboids.size();i++)
		{
			CPPUNIT_ASSERT_EQUAL(assertion_subvolumes[i], volumes_of_subcuboids[i]);
		}
		
		
		atom_position = {0.25, 0.25, 0.25};

		volumes_of_subcuboids = calcSubvolumes(atom_position, vertices);
	
		assertion_subvolumes = {0.015625, 0.046875, 0.140625, 0.046875, 0.046875, 0.140625, 0.421875, 0.140625};
		for (int i=0;i<volumes_of_subcuboids.size();i++)
		{
			CPPUNIT_ASSERT_EQUAL(assertion_subvolumes[i], volumes_of_subcuboids[i]);
		}
	}
	
	
	
	

};
