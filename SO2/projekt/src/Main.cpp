#include <iostream>

#include "App.hpp"

const unsigned int width = 800;
const unsigned int height = 600;

int main(int argc, char *argv[])
{
	unsigned int customers = 2;
	if(argc < 2)
		std::cout << "You don't provided numbers of customers. Using default one.\n";
	else
		customers = atoi(argv[1]);
	
	App app(width, height, customers);
	return app.run();
}
