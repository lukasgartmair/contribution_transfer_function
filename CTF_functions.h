#ifndef CTF_H
#define CTF_H

#include <vector>
#include <math.h>       /* modf */

double getIntegralPart(double number);
double getFractionalPart(double number);

std::vector<std::vector<float> > initializeCubeVertices();

std::vector<float> calcSubvolumes(std::vector<float> atom_position, float voxel_size);

std::vector<float> calcVoxelContributions(std::vector<float> volumes_of_subcuboids);

bool checkVertexCornerCoincidence(std::vector<float> atom_position, float voxel_size);

std::vector<float> handleVertexCornerCoincidence(std::vector<float> atom_position, float voxel_size);

#endif
