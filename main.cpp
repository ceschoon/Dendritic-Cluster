#include <iostream>
#include <vector>
#include <thread>
#include <stdlib.h>
#include "SFML/Graphics.hpp"
#include "rendering.hpp"
#include "gridOperations.hpp"

int main()
{
	srand(time(NULL));
	
	// create the objects and initialise
	
	int gridWidth = 320;
	int gridHeigth = 320;
	int maxWalkers = (gridWidth*gridHeigth)/40+1;	// a good concentration
	
	std::vector<std::vector<int>> grid(gridHeigth, 
		std::vector<int>(gridWidth,0));
	std::vector<std::vector<int>> walkerList(maxWalkers, 
		std::vector<int>(2,-1));  
	
	placeInitialCrystal(grid, gridWidth/2, gridHeigth/2);
	
	// create the window
	
	sf::RenderWindow window(sf::VideoMode(640, 640), "Dendritic Cluster Growth");
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::View view(sf::FloatRect(0, 0, gridWidth, gridHeigth));

	image.create(gridWidth, gridHeigth, sf::Color::White);
	texture.create(gridWidth, gridHeigth);
	
	// main loop
	
	long loopExecutionTime = 0;
	long loopProcessingTime = 0;
	long loopRenderingTime = 0;
	int loopCounter = 0;
	bool doProcess = true;
	
	while (window.isOpen() && doProcess)
	{	
		std::chrono::system_clock::time_point start =
			std::chrono::system_clock::now();
			
		// event handling
		
		if (loopCounter%100 == 0)
		{
			sf::Event event;
        	while (window.pollEvent(event))
        	{
				if (event.type == sf::Event::Closed)
        		{
        		    window.close();
        		}
       		}
        }
        
        // periodically add a walker
        
        std::chrono::system_clock::time_point startProcessingTime =
			std::chrono::system_clock::now();
		//
        
        if (loopCounter%1 == 0)
        {
        	addWalkerBoundary(walkerList, gridWidth, gridHeigth, rand());
        }
        
        // processing
        
        moveWalkers(walkerList, gridWidth, gridHeigth, rand());
        ifCloseToCrystal(grid, walkerList);
        if (isClusterBigEnough(grid, 5)) {doProcess = false;}
        
        //
       	std::chrono::system_clock::time_point finishProcessingTime =
			std::chrono::system_clock::now();
		long nanosecsProcessing = 
			std::chrono::duration_cast<std::chrono::nanoseconds>
			(finishProcessingTime-startProcessingTime).count();
		loopProcessingTime += nanosecsProcessing;
        
        // rendering
        
        std::chrono::system_clock::time_point startRenderingTime =
			std::chrono::system_clock::now();
		//
        
        if (loopCounter%25 == 0)
        {
        	window.clear(sf::Color::White);
        	image.create(gridWidth, gridHeigth, sf::Color::White);
	
			renderGrid(image, grid, walkerList);
			texture.update(image);
			sprite.setTexture(texture);
			window.draw(sprite);
	
			window.setView(view);
	        
	        window.display();
        }
        
        //
       	std::chrono::system_clock::time_point finishRenderingTime =
			std::chrono::system_clock::now();
		long nanosecsRendering =
			std::chrono::duration_cast<std::chrono::nanoseconds>
			(finishRenderingTime-startRenderingTime).count();
		loopRenderingTime += nanosecsRendering;
        
        // miscellaneous
		
		std::chrono::system_clock::time_point finish =
			std::chrono::system_clock::now();
		long nanosecs = std::chrono::duration_cast<std::chrono::nanoseconds>
			(finish-start).count();
		loopExecutionTime += nanosecs;
        
        loopCounter++;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	
	// Timing results
	
	long nanosecsExecution = loopExecutionTime/loopCounter;
	
	std::cout << "Average loop execution time without pause: " 
			  << nanosecsExecution/1000000 << "." 
			  << (nanosecsExecution%1000000)/100000 
			  << (nanosecsExecution%100000)/10000
			  << (nanosecsExecution%10000)/1000
			  << " milliseconds" << std::endl;
			  
	long nanosecsProcessing = loopProcessingTime/loopCounter;
	
	std::cout << "Average processing time: " 
			  << nanosecsProcessing/1000000 << "." 
			  << (nanosecsProcessing%1000000)/100000 
			  << (nanosecsProcessing%100000)/10000
			  << (nanosecsProcessing%10000)/1000
			  << " milliseconds" << std::endl;
			  
	long nanosecsRendering = loopRenderingTime/loopCounter;
	
	std::cout << "Average rendering time: " 
			  << nanosecsRendering/1000000 << "." 
			  << (nanosecsRendering%1000000)/100000 
			  << (nanosecsRendering%100000)/10000
			  << (nanosecsRendering%10000)/1000
			  << " milliseconds" << std::endl;
			  
	std::cout << "Number of loops: " << loopCounter << std::endl;
	
	while (window.isOpen())
	{
		// event handling
		
		if (loopCounter%100 == 0)
		{
			sf::Event event;
        	while (window.pollEvent(event))
        	{
				if (event.type == sf::Event::Closed)
        		{
        		    window.close();
        		}
       		}
        }
		
		// rendering
        
        if (loopCounter%100 == 0)
        {
        	window.clear(sf::Color::White);
        	image.create(gridWidth, gridHeigth, sf::Color::White);
	
			renderGrid(image, grid, walkerList);
			texture.update(image);
			sprite.setTexture(texture);
			window.draw(sprite);
	
			window.setView(view);
	        
	        window.display();
        }
        
        loopCounter++;
	}
		
	return 0;
}