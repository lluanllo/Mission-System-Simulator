#include "core/Mission_management.hpp"
#include <iostream>

int main(int argc, char** argv) {
	std::cout << "Mission System\n";

	Mission_Management::Application app;
	app.Run();
	
	return 0;
}