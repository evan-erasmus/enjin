#include "SignalHandler.hpp"
#include <iostream>
#include <csignal>

bool SignalHandler::gotSignal = false;
int SignalHandler::lastSignal = 0;

// void SignalHandler::signalCallback(int signal) {
//     gotSignal = true;
//     lastSignal = signal;
// }

SignalHandler::SignalHandler() : is_initialized(true), signal_handlers()
{

}

SignalHandler::~SignalHandler()
{
    cleanup();
}

void SignalHandler::initialize()
{
    // setupSignals();
}

// void SignalHandler::setupSignals() {
//     std::signal(SIGINT, SignalHandler::signalCallback);
//     std::signal(SIGTERM, SignalHandler::signalCallback);
//     std::signal(SIGHUP, SignalHandler::signalCallback);
//     std::signal(SIGUSR1, SignalHandler::signalCallback);
//     std::signal(SIGUSR2, SignalHandler::signalCallback);
// }
SignalHandler &getSignalHandler()
{
    static SignalHandler instance;
    return instance;
}

bool SignalHandler::checkSignal(int &outSignal)
{
    if (gotSignal) {
        outSignal = lastSignal;
        gotSignal = false;
        return true;
    }
    return false;
}

void SignalHandler::processSignal(int signal)
{
    switch (signal)
    {
    case SIGINT:
    case SIGTERM:
        std::cout << "\n\n    --- Shutdown signal received --- \n"
                  << std::endl;
        break;
    case SIGHUP:
        std::cout << "\n\n    --- Reload configuration signal received --- \n"
                  << std::endl;
        break;
    case SIGUSR1:
        std::cout << "\n\n    --- User defined signal 1 received --- \n"
                  << std::endl;
        break;
    case SIGUSR2:
        std::cout << "\n\n    --- User defined signal 2 received --- \n"
                  << std::endl;
        break;
    default:
        std::cout << "\n\n    --- Unknown signal received:  --- \n"
                  << signal << std::endl;
    }
}

void SignalHandler::cleanup()
{
    std::signal(SIGINT, SIG_DFL);
    std::signal(SIGTERM, SIG_DFL);
    std::signal(SIGHUP, SIG_DFL);
    std::signal(SIGUSR1, SIG_DFL);
    std::signal(SIGUSR2, SIG_DFL);
}