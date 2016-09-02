#include "CTF_functions.h"
#include <vector>
#include <iostream>
#include <stdlib.h>     /* abs */
#include <cmath>	/*modf */
#include <limits>	/*modf */
#include <algorithm>	/*std::min_element, std::next_permutation, std::sort */
#include <iterator>	/*std::begin, std::end */


// create shared library of this with sudo g++ -std=c++11 -fPIC -shared CTF_functions.cpp -o /usr/lib/libCTF_functions.so

std::vector<std::vector<float> > initializeCubeVertices(float xmin, float ymin, float zmin)
{
	int number_of_vertices = 8;
	int xyz = 3;
	std::vector<std::vector<float> > vertices(number_of_vertices, std::vector<float>(xyz));

	vertices[0][0] = xmin;
	vertices[0][1] = ymin;
	vertices[0][2] = zmin;

	vertices[1][0] = xmin+1;
	vertices[1][1] = ymin;
	vertices[1][2] = zmin;

	vertices[2][0] = xmin+1;
	vertices[2][1] = ymin+1;
	vertices[2][2] = zmin;

	vertices[3][0] = xmin;
	vertices[3][1] = ymin+1;
	vertices[3][2] = zmin;

	vertices[4][0] = xmin;
	vertices[4][1] = ymin;
	vertices[4][2] = zmin+1;

	vertices[5][0] = xmin+1;
	vertices[5][1] = ymin;
	vertices[5][2] = zmin+1;

	vertices[6][0] = xmin+1;
	vertices[6][1] = ymin+1;
	vertices[6][2] = zmin+1;

	vertices[7][0] = xmin;
	vertices[7][1] = ymin+1;
	vertices[7][2] = zmin+1;
	
	return vertices;
}


std::vector<float> projectAtompositionToUnitvoxel(std::vector<float> atom_position, float voxel_size)
{
	std::vector<float> fractional_position_in_voxel = {0, 0, 0};
	std::vector<float> atom_position_in_unit_voxel = {0, 0, 0};
	
	for (int i=0;i<fractional_position_in_voxel.size();i++)
	{
		// get the remainder position for coarse classification 
		fractional_position_in_voxel[i] = std::fmod(atom_position[i], voxel_size);
		// normalize to unit voxel size
		atom_position_in_unit_voxel[i] = fractional_position_in_voxel[i] / voxel_size;
		
		if (atom_position_in_unit_voxel[i] < 0)
		{
			atom_position_in_unit_voxel[i] = 1 - fabs(atom_position_in_unit_voxel[i]);
		}
		else
		{	// this is just for clarification that there
			// has to be made a distinction between positive and negative voxels
			atom_position_in_unit_voxel[i] = atom_position_in_unit_voxel[i];
		}
	}	
	return atom_position_in_unit_voxel;
}

bool checkVertexCornerCoincidence(std::vector<float> atom_position)
{
	bool conincidence = false;
	std::vector<std::vector<float> > vertices = initializeCubeVertices();
	for (int i=0;i<vertices.size();i++)
	{
		if (atom_position[0] == vertices[i][0] && (atom_position[1] == vertices[i][1] && (atom_position[2] == vertices[i][2])))
		{
			conincidence = true;
		}
	}
	return conincidence;
}

std::vector<float> handleVertexCornerCoincidence(std::vector<float> atom_position)
{
	std::vector<float> normalized_voxel_contributions = {0, 0, 0, 0, 0, 0, 0, 0};
	std::vector<std::vector<float> > vertices = initializeCubeVertices();
	for (int i=0;i<vertices.size();i++)
	{
		if (atom_position[0] == vertices[i][0] && (atom_position[1] == vertices[i][1] && (atom_position[2] == vertices[i][2])))
		{
			normalized_voxel_contributions[i] = 1;
		}
	}
	return normalized_voxel_contributions;
}

std::vector<float> calcSubvolumes(std::vector<float> atom_position)
{
	std::vector<std::vector<float> > vertices = initializeCubeVertices();

	std::vector<float> volumes_of_subcuboids;
	int xyz_coordinates = 3;
	for (int i=0;i<vertices.size();i++)
	{
		// the initialization with one instead of zero makes the iterative multiplication possible
		float volume_subcuboid = 1; 
		
		for (int j=0; j<xyz_coordinates;j++)
		{
			float edge_subcuboid = 0;
			
			if (vertices[i][j] == 1)
			{
				// 1 - as this is a unit cube with edge lengths 1,1,1
				edge_subcuboid = 1 - atom_position[j];
			}
			else
			{
				edge_subcuboid = 0 + atom_position[j];
			}
			volume_subcuboid = volume_subcuboid * edge_subcuboid;		
		} 
		volumes_of_subcuboids.push_back(volume_subcuboid);
	}
	return volumes_of_subcuboids;
}

std::vector<float> calcVoxelContributions(std::vector<float> volumes_of_subcuboids)
{
	std::vector<float> absolute_voxel_contributions;
	std::vector<float> normalized_voxel_contributions;
	int number_of_vertices = 8;

	// absolute contribution
	for (int i=0;i<number_of_vertices;i++)
	{
		float absolute_contribution = 0;

		absolute_contribution = 1 / volumes_of_subcuboids[i];

		absolute_voxel_contributions.push_back(absolute_contribution);
	}
	// sum of absolute contributions
	float sum_of_all_absolute_contributions = 0;
	for (int i=0;i<number_of_vertices;i++)
	{
		sum_of_all_absolute_contributions = sum_of_all_absolute_contributions + absolute_voxel_contributions[i];
	}
	// normalized contributions
	for (int i=0;i<number_of_vertices;i++)
	{
		float normalized_contribution = 0;
		normalized_contribution = absolute_voxel_contributions[i] / sum_of_all_absolute_contributions;
		normalized_voxel_contributions.push_back(normalized_contribution);
	}
	return normalized_voxel_contributions;
}

std::vector<std::vector<float> > determineAdjacentVoxelVertices(std::vector<float> atom_position, float voxel_size)
{
	std::vector<float> floored_voxel_indices = {0, 0, 0}; 
	std::vector<std::vector<float> > adjacent_voxel_indices;
	
	for (int i=0;i<atom_position.size();i++)
	{	
		// for reference http://www.cplusplus.com/reference/cmath/floor/
		/*	floor of 2.3 is 2.0
			floor of 3.8 is 3.0
			floor of -2.3 is -3.0
			floor of -3.8 is -4.0 */
			
		floored_voxel_indices[i] = floor(atom_position[i] / voxel_size);
	}
	adjacent_voxel_indices = initializeCubeVertices(floored_voxel_indices[0], floored_voxel_indices[1], floored_voxel_indices[2]);
	
	return adjacent_voxel_indices;
}


































