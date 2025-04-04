#include "EventHandler.hpp"
#include "../../Application.hpp"
#include <iostream>

using EventCallback = std::function<void(const Event &)>;

EventHandler::EventHandler() : is_initialized(true), event_queue(), application(nullptr)
{
}

EventHandler::~EventHandler()
{
    cleanup();
}

EventHandler &getEventHandler()
{
    static EventHandler instance;
    return instance;
}

void EventHandler::initialize()
{
    this->generateTestEvents();
}

void EventHandler::setApplication(Application *app)
{
    application = app;
}

void EventHandler::queueEvent(const Event &event)
{
    // if (event) {
    event_queue.push(event);
    // }
}

void EventHandler::processEvent()
{
    if (event_queue.empty())
    {
        return;
    }

    Event event = event_queue.front();
    event_queue.pop();

    if (event.callback)
    {
        event.callback(event);
    }
}

bool EventHandler::hasEvents()
{
    return !event_queue.empty();
}

// void EventHandler::subscribe(EventType type, EventCallback callback) {
//     eventCallbacks[type].push_back(callback);
// }

// void EventHandler::unsubscribe(EventType type) {
//     eventCallbacks.erase(type);
// }

void EventHandler::generateTestEvents()
{
    // queueEvent(KeyboardEvent(65, true, false, false));
    // queueEvent(std::make_shared<MouseEvent>(100, 200, 1, true, false));
    return;
}

void EventHandler::cleanup()
{
    while (!event_queue.empty())
    {
        event_queue.pop();
    }

    // eventCallbacks.clear();
}