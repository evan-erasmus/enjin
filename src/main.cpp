#include "app/Application.hpp"
#include <iostream>
#include <exception>

int main(int argc, char** argv) {
    try {
        Application app(argc, argv);
        app.run();
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}