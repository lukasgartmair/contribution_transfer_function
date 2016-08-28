#include "CTF_functions.h"
#include <vector>
#include <iostream>
#include <stdlib.h>     /* abs */
#include <cmath>	/*modf */
#include <limits>	/*modf */
#include <algorithm>	/*std::min_element */
#include <iterator>	/*std::begin, std::end */


std::vector<std::vector<float> > initializeCubeVertices(float start_index)
{
	int number_of_vertices = 8;
	int xyz = 3;
	std::vector<std::vector<float> > vertices(number_of_vertices, std::vector<float>(xyz));

	vertices[0][0] = start_index;
	vertices[0][1] = start_index;
	vertices[0][2] = start_index;

	vertices[1][0] = start_index+1;
	vertices[1][1] = start_index;
	vertices[1][2] = start_index;

	vertices[2][0] = start_index+1;
	vertices[2][1] = start_index+1;
	vertices[2][2] = start_index;

	vertices[3][0] = start_index;
	vertices[3][1] = start_index+1;
	vertices[3][2] = start_index;

	vertices[4][0] = start_index;
	vertices[4][1] = start_index;
	vertices[4][2] = start_index+1;

	vertices[5][0] = start_index+1;
	vertices[5][1] = start_index;
	vertices[5][2] = start_index+1;

	vertices[6][0] = start_index+1;
	vertices[6][1] = start_index+1;
	vertices[6][2] = start_index+1;

	vertices[7][0] = start_index;
	vertices[7][1] = start_index+1;
	vertices[7][2] = start_index+1;
	
	return vertices;
}

double getFractionalPart(double number)
{	double fractpart, intpart;
	fractpart = modf(number , &intpart);
	// important to return the absolute value with fabs not abs!
	return fabs(fractpart);
}

double getIntegralPart(double number)
{	
	double intpart;
	modf(number , &intpart);
	return intpart;
}

std::vector<float> projectAtompositionToUnitvoxel(std::vector<float> atom_position, float voxel_size)
{
	std::vector<float> position_in_voxel = {0, 0, 0};
	std::vector<float> unit_voxel_index = {0, 0, 0};
	
	for (int i=0;i<position_in_voxel.size();i++)
	{
		// get the remainder 
		position_in_voxel[i] = std::fmod(atom_position[i], voxel_size);
		// normalize to unit voxel size
		unit_voxel_index[i] = position_in_voxel[i] / voxel_size;
		// get the absolute value
		unit_voxel_index[i] = fabs(unit_voxel_index[i]);
	}	
	return unit_voxel_index;
	
}

std::vector<std::vector<float> > determineSurroundingVoxelVertices(std::vector<float> atom_position, float voxel_size)
{
	int quot;   // quotient
	int rem;    // remainder
	std::vector<float> quotients = {0, 0, 0}; 
	std::vector<std::vector<float> > surr_voxel_indices;
	
	for (int i=0;i<atom_position.size();i++)
	{
		div_t divresult;
  		divresult = div(atom_position[i],voxel_size);
		quotients[i] = divresult.quot;
	}
	// get the minimum element from the divisions in order to find the bottom corner of the 8 surrounding voxel values (min, min, min)
	// The return value from std::min_element() is an iterator so it needs to be dereferenced.

	float bottom_corner = *std::min_element(quotients.begin(), quotients.end());
	std::cout << bottom_corner << std::endl;
	
	surr_voxel_indices = initializeCubeVertices(bottom_corner);
	
	return surr_voxel_indices;
}

bool checkVertexCornerCoincidence(std::vector<float> atom_position, float voxel_size)
{
	bool conincidence = false;
	float start_index = 0;
	std::vector<std::vector<float> > vertices = initializeCubeVertices(start_index);
	for (int i=0;i<vertices.size();i++)
	{
		if (atom_position[0] == vertices[i][0] && (atom_position[1] == vertices[i][1] && (atom_position[2] == vertices[i][2])))
		{
			conincidence = true;
		}
	}
	return conincidence;
}

std::vector<float> handleVertexCornerCoincidence(std::vector<float> atom_position, float voxel_size)
{
	std::vector<float> normalized_voxel_contributions = {0, 0, 0, 0, 0, 0, 0, 0};
	float start_index = 0;
	std::vector<std::vector<float> > vertices = initializeCubeVertices(start_index);
	for (int i=0;i<vertices.size();i++)
	{
		if (atom_position[0] == vertices[i][0] && (atom_position[1] == vertices[i][1] && (atom_position[2] == vertices[i][2])))
		{
			normalized_voxel_contributions[i] = 1;
		}
	}
	return normalized_voxel_contributions;
}

std::vector<float> calcSubvolumes(std::vector<float> atom_position, float voxel_size)
{
	float start_index = 0;
	std::vector<std::vector<float> > vertices = initializeCubeVertices(start_index);

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


































