#include "gridOperations.hpp"
#include <iostream>

int modulo(int a, int b)
{
	int c = a%b;
	if (c<0){c = c+b;}
	
	return c;
}

int numberOfNeighbours(std::vector<std::vector<int>> &grid, int x, int y)
{
	int gridWidth = grid[0].size();
	int gridHeigth = grid.size();
	int numNeighbours = 0;
	
	if(grid[modulo(y-1,gridHeigth)][x]==1){numNeighbours++;}
	if(grid[y][modulo(x+1,gridWidth )]==1){numNeighbours++;}
	if(grid[modulo(y+1,gridHeigth)][x]==1){numNeighbours++;}
	if(grid[y][modulo(x-1,gridWidth )]==1){numNeighbours++;}
	
	return numNeighbours;
}

void placeInitialCrystal(std::vector<std::vector<int>> &grid, int x, int y)
{
	grid[x][y] = 1;
	
	grid[x+1][y] = 1;
	grid[x][y+1] = 1;
	grid[x-1][y] = 1;
	grid[x][y-1] = 1;
}

void addWalkerBoundary(std::vector<std::vector<int>> &walkerList, 
	int gridWidth, int gridHeigth, int seed)
{
	srand(seed);
	
	bool flag = false;
	for (int i=0; i<walkerList.size(); i++)
	{
		if (walkerList[i][0] == -1)		// no walker there
		{
			switch (rand()%4) 
			{
				case 0: // north
				{
					walkerList[i][0] = 0;	// y position 
					walkerList[i][1] = rand()%gridWidth;
					break;
				}
				case 1: // east
				{
					walkerList[i][0] = rand()%gridHeigth;
					walkerList[i][1] = gridWidth-1;
					break;
				}
				case 2: // south
				{
					walkerList[i][0] = gridHeigth-1;
					walkerList[i][1] = rand()%gridWidth;
					break;
				}
				case 3: // west
				{
					walkerList[i][0] = rand()%gridHeigth;
					walkerList[i][1] = 0;
					break;
				}
			}
			flag = true;
		}
		
		if (flag){break;}
	}
}

void moveWalkers(std::vector<std::vector<int>> &walkerList, 
	int gridWidth, int gridHeigth, int seed)
{
	srand(seed);
	
	for (int i=0; i<walkerList.size(); i++)
	{
		if (walkerList[i][0] != -1)
		{
				switch (rand()%4)
				{
					case 0: // north
					{
						walkerList[i][0] = modulo(walkerList[i][0]-1, 		
							gridHeigth);
						break;
					}
					case 1: // east
					{
						walkerList[i][1] = modulo(walkerList[i][1]+1, 		
							gridWidth);
						break;
					}
					case 2: // south
					{
						walkerList[i][0] = modulo(walkerList[i][0]+1, 		
							gridHeigth);
						break;
					}
					case 3: // west
					{
						walkerList[i][1] = modulo(walkerList[i][1]-1, 		
							gridWidth);
						break;
					}
				}
		}
	}
}

void ifCloseToCrystal(std::vector<std::vector<int>> &grid,
	std::vector<std::vector<int>> &walkerList)
{	
	int gridWidth = grid[0].size();
	int gridHeigth = grid.size();
	
	for (int i=0; i<walkerList.size(); i++)
	{
		int x = walkerList[i][0];
		int y = walkerList[i][1];
		
		if (x!=-1)
		{
			if (numberOfNeighbours(grid, x, y)>=1)
			{	
				grid[y][x] = 1;
				walkerList[i] = {-1,-1};
			}
		}
	}
}

bool isClusterBigEnough(std::vector<std::vector<int>> &grid, 
	int minDistanceToBorder)
{
	bool clusterBigEnough = false;
	
	int gridWidth = grid[0].size();
	int gridHeigth = grid.size();
	
	for (int i=0; i<minDistanceToBorder; i++)
	{
		for (int j=0; j<gridWidth; j++) 	// north
		{
			if (grid[i][j] == 1){clusterBigEnough = true;}
		}
		for (int j=0; j<gridHeigth; j++) 	// east
		{
			if (grid[j][gridWidth-1-i] == 1){clusterBigEnough = true;}
		}
		for (int j=0; j<gridWidth; j++) 	// south
		{
			if (grid[gridHeigth-1-i][j] == 1){clusterBigEnough = true;}
		}
		for (int j=0; j<gridHeigth; j++) 	// west
		{
			if (grid[j][i] == 1){clusterBigEnough = true;}
		}
	}
	
	return clusterBigEnough;
}

