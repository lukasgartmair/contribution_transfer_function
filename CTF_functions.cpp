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


std::vector<float> calcSubvolumes(std::vector<float> atom_position)
{

	std::vector<std::vector<float> > vertices = initializeCubeVertices();

	std::vector<float> volumes_of_subcuboids;
	int xyz_coordinates = 3;
	for (int i=0;i<vertices.size();i++)
	{
		// the ininitialization with one instead of zero makes the iterative multiplication possible
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

std::vector<float> calcVoxelContributions(std::vector<float> atom_position)
{
/*
float remainder = fmod(abs(numToRound), multiple);
*/
}



// this is the corresponding python function to reproduce

/* def calc_volumes_of_subcuboids(atom_position, vertices):
    volumes_of_subcuboids = []
    for v in vertices:
        
        edges_subcuboid = []
        for i,index in enumerate(v): 
            if index == 1:
                edgde_subcuboid = 1 - atom_position[i]
            else:
                edgde_subcuboid = 0 + atom_position[i]
                
            edges_subcuboid.append(edgde_subcuboid)
            
        volume_subcuboid = np.prod(np.array(edges_subcuboid))  
        volumes_of_subcuboids.append(volume_subcuboid)
        
    return volumes_of_subcuboids
*/
