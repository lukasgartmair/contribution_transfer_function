#include "CTF_functions.h"
#include <vector>
#include <iostream>


std::vector<std::vector<float> > initializeCubeVertices()
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
	
	return vertices;

}

bool checkVertexCornerCoincidence(std::vector<float> atom_position, float voxel_size)
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

std::vector<float> handleVertexCornerCoincidence(std::vector<float> atom_position, float voxel_size)
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

std::vector<float> calcSubvolumes(std::vector<float> atom_position, float voxel_size)
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
				edge_subcuboid = voxel_size - atom_position[j];
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


































