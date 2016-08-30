
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

		suiteOfTests->addTest(new CppUnit::TestCaller<TestCTF>("Test3 - Project Atom Position to unit voxel",
				&TestCTF::testCTF_ProjectAtompositionToUnitvoxel));

		suiteOfTests->addTest(new CppUnit::TestCaller<TestCTF>("Test4 - Determine Surrounding Voxel Vertices",
				&TestCTF::testCTF_DetermineSurroundingVoxelVertices));
				
		suiteOfTests->addTest(new CppUnit::TestCaller<TestCTF>("Test5 - Calculate Voxel Contributions from an atom position",
				&TestCTF::testCTF_CalculateVoxelContributionsFromAtomposition));



				
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
		float voxel_size = 1;
		std::vector<float> atom_position = {0.5, 0.5, 0.5};
		std::vector<float> volumes_of_subcuboids;
		volumes_of_subcuboids = calcSubvolumes(atom_position, voxel_size);
	
		std::vector<float> assertion_subvolumes = {0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125};
		for (int i=0;i<volumes_of_subcuboids.size();i++)
		{
			CPPUNIT_ASSERT_EQUAL(assertion_subvolumes[i], volumes_of_subcuboids[i]);
		}
		
		atom_position = {0.25, 0.25, 0.25};

		volumes_of_subcuboids = calcSubvolumes(atom_position, voxel_size);
	
		assertion_subvolumes = {0.015625, 0.046875, 0.140625, 0.046875, 0.046875, 0.140625, 0.421875, 0.140625};
		for (int i=0;i<assertion_subvolumes.size();i++)
		{
			CPPUNIT_ASSERT_EQUAL(assertion_subvolumes[i], volumes_of_subcuboids[i]);
		}

	}
	
	void testCTF_CalculateVoxelContributions() 
	{	
		std::vector<float> test_subvolumes = {0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125};
		std::vector<float> contributions_of_subcuboids;
		
		contributions_of_subcuboids = calcVoxelContributions(test_subvolumes);
	
		std::vector<float> assertion_contributions = {0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125};
		for (int i=0;i<assertion_contributions.size();i++)
		{
			//std::cout << assertion_contributions[i] << std::endl;
			//std::cout << contributions_of_subcuboids.size() << std::endl;
			CPPUNIT_ASSERT_EQUAL(assertion_contributions[i], contributions_of_subcuboids[i]);
		}
		
		test_subvolumes = {0.015625, 0.046875, 0.140625, 0.046875, 0.046875, 0.140625, 0.421875, 0.140625};
		assertion_contributions = {0.421875,  0.140625,  0.046875,  0.140625,  0.140625,  0.046875, 0.015625,  0.046875};
		
		contributions_of_subcuboids = calcVoxelContributions(test_subvolumes);
		
		for (int i=0;i<assertion_contributions.size();i++)
		{
			//std::cout << assertion_contributions[i] << std::endl;
			//std::cout << contributions_of_subcuboids.size() << std::endl;
			CPPUNIT_ASSERT_DOUBLES_EQUAL(assertion_contributions[i], contributions_of_subcuboids[i], 0.01);
		}
	}
	
	
	
	void testCTF_ProjectAtompositionToUnitvoxel()
	{
		std::vector<float> atom_position = {0.5, 0.5, 0.5};
		std::vector<float> unit_position = {0, 0, 0};
		float voxel_size = 1;

		std::vector<float> position_in_unit_voxel = projectAtompositionToUnitvoxel(atom_position, voxel_size);

		std::vector<float> assert_position = {0, 0, 0};
		assert_position[0] = 0.5;
		assert_position[1] = 0.5;
		assert_position[2] = 0.5;
		for (int i=0;i<3;i++)
		{
			CPPUNIT_ASSERT_EQUAL(assert_position[i], position_in_unit_voxel[i]);
		}
		
		atom_position = {2.5, 2.5, 2.5};
		unit_position = {0, 0, 0};
		voxel_size = 1;

		position_in_unit_voxel = projectAtompositionToUnitvoxel(atom_position, voxel_size);

		assert_position = {0, 0, 0};
		assert_position[0] = 0.5;
		assert_position[1] = 0.5;
		assert_position[2] = 0.5;
		for (int i=0;i<3;i++)
		{
			CPPUNIT_ASSERT_EQUAL(assert_position[i], position_in_unit_voxel[i]);
		}
		
		atom_position = {-2.5, -2.5, -2.5};
		unit_position = {0, 0, 0};
		voxel_size = 1;

		position_in_unit_voxel = projectAtompositionToUnitvoxel(atom_position, voxel_size);

		assert_position = {0, 0, 0};
		assert_position[0] = 0.5;
		assert_position[1] = 0.5;
		assert_position[2] = 0.5;
		for (int i=0;i<3;i++)
		{
			CPPUNIT_ASSERT_EQUAL(assert_position[i], position_in_unit_voxel[i]);
		}
		
		atom_position = {-2.5, -2.5, -2.5};
		unit_position = {0, 0, 0};
		voxel_size = 2;

		position_in_unit_voxel = projectAtompositionToUnitvoxel(atom_position, voxel_size);

		assert_position = {0, 0, 0};
		assert_position[0] = 0.75;
		assert_position[1] = 0.75;
		assert_position[2] = 0.75;
		for (int i=0;i<3;i++)
		{
			CPPUNIT_ASSERT_EQUAL(assert_position[i], position_in_unit_voxel[i]);
		}
		
		atom_position = {-2.5, -2.5, -2.5};
		unit_position = {0, 0, 0};
		voxel_size = 3;

		position_in_unit_voxel = projectAtompositionToUnitvoxel(atom_position, voxel_size);

		assert_position = {0, 0, 0};
		assert_position[0] = 0.166;
		assert_position[1] = 0.166;
		assert_position[2] = 0.166;
		for (int i=0;i<3;i++)
		{
			CPPUNIT_ASSERT_DOUBLES_EQUAL(assert_position[i], position_in_unit_voxel[i], 0.001);
		}
	}
	
	void testCTF_DetermineSurroundingVoxelVertices()
	{
		// positive atom position
		std::vector<float>atom_position = {2.5, 2.5, 2.5};
		float voxel_size = 1;
		int number_of_vertices = 8;
		int xyzs = 3;
		std::vector<std::vector<float> > assert_voxel_vertices = initializeCubeVertices(2,2,2);
		
		std::vector<std::vector<float> > surr_voxel_vertices = determineSurroundingVoxelVertices(atom_position, voxel_size);
		
		for (int i=0;i<assert_voxel_vertices.size();i++)
		{
			for (int j=0;j<xyzs;j++)
			{
				CPPUNIT_ASSERT_DOUBLES_EQUAL(assert_voxel_vertices[i][j], surr_voxel_vertices[i][j], 0.01);
			}
		}
		
		// bigger voxelsize
	
		atom_position = {2.5, 2.5, 2.5};
		voxel_size = 2;
		assert_voxel_vertices = initializeCubeVertices(1,1,1);
		
		surr_voxel_vertices = determineSurroundingVoxelVertices(atom_position, voxel_size);
		
		for (int i=0;i<assert_voxel_vertices.size();i++)
		{
			for (int j=0;j<xyzs;j++)
			{
				CPPUNIT_ASSERT_DOUBLES_EQUAL(assert_voxel_vertices[i][j], surr_voxel_vertices[i][j], 0.01);
			}
		}

		// bigger voxelsize
	
		atom_position = {2.5, 2.5, 2.5};
		voxel_size = 3;
		assert_voxel_vertices = initializeCubeVertices(0,0,0);
		
		surr_voxel_vertices = determineSurroundingVoxelVertices(atom_position, voxel_size);
		
		for (int i=0;i<assert_voxel_vertices.size();i++)
		{
			for (int j=0;j<xyzs;j++)
			{
				CPPUNIT_ASSERT_DOUBLES_EQUAL(assert_voxel_vertices[i][j], surr_voxel_vertices[i][j], 0.01);
			}
		}
		// negative atom position
	
		atom_position = {-2.5, -2.5, -2.5};
		voxel_size = 1;
		assert_voxel_vertices = initializeCubeVertices(-3,-3,-3);
		
		surr_voxel_vertices = determineSurroundingVoxelVertices(atom_position, voxel_size);
		
		for (int i=0;i<assert_voxel_vertices.size();i++)
		{
			for (int j=0;j<xyzs;j++)
			{
				CPPUNIT_ASSERT_DOUBLES_EQUAL(assert_voxel_vertices[i][j], surr_voxel_vertices[i][j], 0.01);
			}
		}

		// negative atom position
	
		atom_position = {-1.7, -1.7, -1.7};
		voxel_size = 2;
		assert_voxel_vertices = initializeCubeVertices(-1,-1,-1);
		
		surr_voxel_vertices = determineSurroundingVoxelVertices(atom_position, voxel_size);
		
		for (int i=0;i<assert_voxel_vertices.size();i++)
		{
			for (int j=0;j<xyzs;j++)
			{
				CPPUNIT_ASSERT_DOUBLES_EQUAL(assert_voxel_vertices[i][j], surr_voxel_vertices[i][j], 0.01);
			}
		}

		// negative atom position and float voxel size
	
		atom_position = {-1.7, -1.7, -1.7};
		voxel_size = 1.5;
		assert_voxel_vertices = initializeCubeVertices(-2,-2,-2);
		
		surr_voxel_vertices = determineSurroundingVoxelVertices(atom_position, voxel_size);
		
		for (int i=0;i<assert_voxel_vertices.size();i++)
		{
			for (int j=0;j<xyzs;j++)
			{
				CPPUNIT_ASSERT_DOUBLES_EQUAL(assert_voxel_vertices[i][j], surr_voxel_vertices[i][j], 0.01);
			}
		}

		// negative atom position and float voxel size and arbitrary positions
	
		atom_position = {-1.9, -0.1, 0.7};
		voxel_size = 1.5;
		assert_voxel_vertices = initializeCubeVertices(-2,-1,0);
		
		surr_voxel_vertices = determineSurroundingVoxelVertices(atom_position, voxel_size);
		
		for (int i=0;i<assert_voxel_vertices.size();i++)
		{
			for (int j=0;j<xyzs;j++)
			{
				CPPUNIT_ASSERT_DOUBLES_EQUAL(assert_voxel_vertices[i][j], surr_voxel_vertices[i][j], 0.01);
			}
		}
	
		// negative atom position and float voxel size and arbitrary positions
	
		atom_position = {-2.9, -0.1, 0.7};
		voxel_size = 2;
		
		assert_voxel_vertices = initializeCubeVertices(-2,-1,0);
		
		surr_voxel_vertices = determineSurroundingVoxelVertices(atom_position, voxel_size);
		
		for (int i=0;i<assert_voxel_vertices.size();i++)
		{
			for (int j=0;j<xyzs;j++)
			{
				CPPUNIT_ASSERT_DOUBLES_EQUAL(assert_voxel_vertices[i][j], surr_voxel_vertices[i][j], 0.01);
			}
		}

	}
	
	void testCTF_CalculateVoxelContributionsFromAtomposition() 
	{	
	
		/// voxel position between 0 and 1
		float voxel_size =  1;
		std::vector<float> volumes_of_subcuboids;
		std::vector<float> contributions_of_subcuboids;
		std::vector<float> atom_position = {0.5, 0.5, 0.5};
		std::vector<float> assertion_contributions = {0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125};
		
		volumes_of_subcuboids = calcSubvolumes(atom_position, voxel_size);
		contributions_of_subcuboids = calcVoxelContributions(volumes_of_subcuboids);
		
		for (int i=0;i<assertion_contributions.size();i++)
		{
			CPPUNIT_ASSERT_DOUBLES_EQUAL(assertion_contributions[i], contributions_of_subcuboids[i], 0.01);
		}
		
		// atom position coincides with voxel position
		// produces volumes of zero -> division by zero when divided by one in the contribution calcultaion
		// this error has to be captured
		// if the volume of the subcube is zero the contribution will also be zero
		voxel_size =  1;
		volumes_of_subcuboids;
		contributions_of_subcuboids;
		atom_position = {1, 1, 1};
		assertion_contributions = {0, 0, 0, 0, 0, 0, 1, 0};
		
		bool vertex_corner_coincidence = checkVertexCornerCoincidence(atom_position, voxel_size);
		
		if (vertex_corner_coincidence == false)
		{
			volumes_of_subcuboids = calcSubvolumes(atom_position, voxel_size);
			contributions_of_subcuboids = calcVoxelContributions(volumes_of_subcuboids);
		}
		else
		{
			contributions_of_subcuboids = handleVertexCornerCoincidence(atom_position, voxel_size);
		}
		
		for (int i=0;i<assertion_contributions.size();i++)
		{
			CPPUNIT_ASSERT_DOUBLES_EQUAL(assertion_contributions[i], contributions_of_subcuboids[i], 0.01);
		}
		
		// arbitrary positive atom position
		voxel_size =  1;
		volumes_of_subcuboids;
		contributions_of_subcuboids;
		atom_position = {2.5, 2.5, 2.5};
		assertion_contributions = {0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125};
		
		std::vector<float> position_in_unit_voxel = projectAtompositionToUnitvoxel(atom_position, voxel_size);
		
		vertex_corner_coincidence = checkVertexCornerCoincidence(position_in_unit_voxel , voxel_size);
		
		if (vertex_corner_coincidence == false)
		{
			volumes_of_subcuboids = calcSubvolumes(position_in_unit_voxel , voxel_size);
			contributions_of_subcuboids = calcVoxelContributions(volumes_of_subcuboids);
		}
		else
		{
			contributions_of_subcuboids = handleVertexCornerCoincidence(position_in_unit_voxel, voxel_size);
		}
		
		for (int i=0;i<assertion_contributions.size();i++)
		{
			CPPUNIT_ASSERT_DOUBLES_EQUAL(assertion_contributions[i], contributions_of_subcuboids[i], 0.01);
		}
		
		// arbitrary negative atom position
		voxel_size =  1;
		volumes_of_subcuboids;
		contributions_of_subcuboids;
		atom_position = {-2.5, -2.5, -2.5};
		assertion_contributions = {0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125};
		
		position_in_unit_voxel = projectAtompositionToUnitvoxel(atom_position, voxel_size);
		
		vertex_corner_coincidence = checkVertexCornerCoincidence(position_in_unit_voxel , voxel_size);
		
		if (vertex_corner_coincidence == false)
		{
			volumes_of_subcuboids = calcSubvolumes(position_in_unit_voxel , voxel_size);
			contributions_of_subcuboids = calcVoxelContributions(volumes_of_subcuboids);
		}
		else
		{
			contributions_of_subcuboids = handleVertexCornerCoincidence(position_in_unit_voxel, voxel_size);
		}
		
		for (int i=0;i<assertion_contributions.size();i++)
		{
			CPPUNIT_ASSERT_DOUBLES_EQUAL(assertion_contributions[i], contributions_of_subcuboids[i], 0.01);
		}
		
	}

	
	

	
	

};
