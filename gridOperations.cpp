#include "gridOperations.hpp"
#include <iostream>

int modulo(int a, int b)
{
	int c = a%b;
	if (c<0){c = c+b;}
	
	return c;
}

void placeInitialCrystal(std::vector<std::vector<int>> &grid, int x, int y)
{
	grid[x][y] = 1;
}

void addWalkerBoundary(std::vector<std::vector<int>> &grid, int seed)
{
	srand(seed);
	
	int gridWidth = grid[0].size();
	int gridHeigth = grid.size();
	
	switch (rand()%4) 
	{
		case 0: // north
		{
			int randNum2 = rand()%gridWidth;
			grid[0][randNum2] = 2;
			break;
		}
		case 1: // east
		{
			int randNum2 = rand()%gridHeigth;
			grid[randNum2][gridWidth-1] = 2;
			break;
		}
		case 2: // south
		{
			int randNum2 = rand()%gridWidth;
			grid[gridHeigth-1][randNum2] = 2;
			break;
		}
		case 3: // west
		{
			int randNum2 = rand()%gridHeigth;
			grid[randNum2][0] = 2;
			break;
		}
	}
}

void moveWalkers(std::vector<std::vector<int>> &grid, int seed)
{
	srand(seed);
	
	int gridWidth = grid[0].size();
	int gridHeigth = grid.size();
	
	for (int i=0; i<grid.size(); i++)
	{
		for (int j=0; j<grid[0].size(); j++)
		{	
			if (grid[i][j] == 2)
			{	
				switch (rand()%4)
				{
					case 0: // north
					{
						grid[modulo(i-1,gridHeigth)][j] = 2;
						break;
					}
					case 1: // east
					{
						grid[i][modulo(j+1,gridWidth)] = 2;
						break;
					}
					case 2: // south
					{
						grid[modulo(i+1,gridHeigth)][j] = 2;
						break;
					}
					case 3: // west
					{
						grid[i][modulo(j-1,gridWidth)] = 2;
						break;
					}
				}
				
				grid[i][j] = 0;
			}
		}
	}
}

void ifCloseToCrystal(std::vector<std::vector<int>> &grid)
{	
	int gridWidth = grid[0].size();
	int gridHeigth = grid.size();
	
	for (int i=0; i<grid.size(); i++)
	{
		for (int j=0; j<grid[0].size(); j++)
		{
			if (grid[i][j] == 2)
			{
				if (grid[modulo(i-1,gridHeigth)][j]==1 || 
					grid[i][modulo(j+1,gridWidth)] ==1 || 
					grid[modulo(i+1,gridHeigth)][j]==1 || 
					grid[i][modulo(j-1,gridWidth)] ==1)
				{
					grid[i][j] = 1;
				}
			}
		}
	}
}

