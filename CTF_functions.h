#ifndef CTF_H
#define CTF_H

#include <vector>

std::vector<std::vector<float> > initializeCubeVertices();

std::vector<float> calcSubvolumes(std::vector<float> atom_position);

std::vector<float> calcVoxelContributions(std::vector<float> atom_position);

#endif
