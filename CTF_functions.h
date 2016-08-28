#ifndef CTF_H
#define CTF_H

#include <vector>
#include <math.h>       /* modf */

typedef struct coordinate {
float x;
float y;
float z;
} coordinate;

double getIntegralPart(double number);
double getFractionalPart(double number);

std::vector<float> projectAtompositionToUnitvoxel(std::vector<float> atom_position, float voxel_size);

std::vector<std::vector<float> > initializeCubeVertices();

std::vector<float> calcSubvolumes(std::vector<float> atom_position, float voxel_size);

std::vector<float> calcVoxelContributions(std::vector<float> volumes_of_subcuboids);

bool checkVertexCornerCoincidence(std::vector<float> atom_position, float voxel_size);

std::vector<float> handleVertexCornerCoincidence(std::vector<float> atom_position, float voxel_size);

#endif
