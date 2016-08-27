#include "CTF_functions.h"
#include <vector>
#include <iostream>



std::vector<float> calcSubvolumes(std::vector<float> atom_position, std::vector<std::vector<float> > vertices)
{
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
