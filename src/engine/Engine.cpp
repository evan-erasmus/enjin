#include "Engine.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

Engine::Engine()
{
}
Engine::~Engine()
{
}
void Engine::initialize()
{
    std::cout << "Engine initialized." << std::endl;
}