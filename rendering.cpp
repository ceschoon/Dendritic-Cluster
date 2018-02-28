#include "rendering.hpp"

void renderGrid(sf::Image &image, std::vector<std::vector<int>> &grid)
{
	for (int i=0; i<grid.size(); i++)
	{
		for (int j=0; j<grid[0].size(); j++)
		{
			switch(grid[i][j])
			{
				case 1: image.setPixel(i, j, sf::Color::Black); break;
				case 2: image.setPixel(i, j, sf::Color::Blue); break;
			}
		}
	}
}