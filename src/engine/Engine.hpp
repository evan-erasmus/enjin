class Engine {
public:
    Engine();
    ~Engine();

    void initialize();
    void run();
    void shutdown();
    void restart();
    void cleanup();
    void handleError();
    void handleEvent();
    void handleSignal();        
};