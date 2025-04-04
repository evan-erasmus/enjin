#pragma once

#include <queue>
#include <functional>

class Application;

enum class EventType {
    KEYBOARD,
    MOUSE,
    WINDOW,
    CUSTOM
};

struct Event {
    EventType type;
    int code;
    std::function<void(Event)> callback;
};

class EventHandler {
public:
    EventHandler();
    ~EventHandler();

    void initialize();
    void cleanup();
    void setApplication(Application* app);
    bool hasEvents();
    void queueEvent(const Event& event);
    void processEvent();
    void generateTestEvents();

private:
    bool is_initialized;
    std::queue<Event> event_queue;
    Application* application;
};

// Singleton accessor
EventHandler& getEventHandler();