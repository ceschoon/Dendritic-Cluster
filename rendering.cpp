#include "rendering.hpp"

void renderGrid(sf::Image &image, std::vector<std::vector<int>> &grid,
	std::vector<std::vector<int>> &walkerList)
{
	for (int i=0; i<grid.size(); i++)
	{
		for (int j=0; j<grid[0].size(); j++)
		{
			switch(grid[i][j])
			{
				case 1: image.setPixel(i, j, sf::Color::Black); break;
			}
		}
	}
	
	for (int i=0; i<walkerList.size(); i++)
	{
		if (walkerList[i][0]>=0 && walkerList[i][1]>=0)
		{
			image.setPixel(walkerList[i][0], walkerList[i][1], sf::Color::Blue);
		}
	}
}