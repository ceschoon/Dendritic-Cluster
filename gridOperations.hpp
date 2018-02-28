#ifndef GRIDOPERATIONS_HPP
#define GRIDOPERATIONS_HPP

#include <vector>
#include <stdlib.h>

void placeInitialCrystal(std::vector<std::vector<int>> &grid, int x, int y);
void addWalkerBoundary(std::vector<std::vector<int>> &grid, int seed);
void moveWalkers(std::vector<std::vector<int>> &grid, int seed);
void ifCloseToCrystal(std::vector<std::vector<int>> &grid);

#endif