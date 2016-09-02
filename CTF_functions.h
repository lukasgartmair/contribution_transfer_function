#ifndef CTF_H
#define CTF_H

#include <vector>
#include <math.h>       /* modf */

typedef struct coordinate {
float x;
float y;
float z;
} coordinate;

std::vector<std::vector<float> > initializeCubeVertices(float xmin=0, float ymin=0, float zmin=0);

std::vector<float> projectAtompositionToUnitvoxel(std::vector<float> atom_position, float voxel_size);

bool checkVertexCornerCoincidence(std::vector<float> atom_position);

std::vector<float> handleVertexCornerCoincidence(std::vector<float> atom_position);

std::vector<float> calcSubvolumes(std::vector<float> atom_position);

std::vector<float> calcVoxelContributions(std::vector<float> volumes_of_subcuboids);

std::vector<std::vector<float> > determineSurroundingVoxelVertices(std::vector<float> atom_position, float voxel_size);

#endif
