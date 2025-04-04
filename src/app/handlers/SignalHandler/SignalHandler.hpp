#pragma once

#include <csignal>
#include <functional>
#include <map>

class SignalHandler {
public:
    SignalHandler();
    ~SignalHandler();

    void initialize();
    void cleanup();
    bool checkSignal(int& signal);
    void processSignal(int signal);
    void registerHandler(int signal, std::function<void(int)> handler);

private:
    bool is_initialized;
    std::map<int, std::function<void(int)>> signal_handlers;
    
    static SignalHandler* instance;
    static void signalHandler(int signal);

    static bool gotSignal;
    static int lastSignal;
};

// Singleton accessor
SignalHandler& getSignalHandler();
