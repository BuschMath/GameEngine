#ifndef MESSAGING_SYSTEM_H
#define MESSAGING_SYSTEM_H

#include "Message.h"
#include "MessageReceiver.h"
#include "Component.h"
#include <vector>

// A messaging system that components can use to send and receive messages
class MessagingSystem {
public:
    // Registers a component with the messaging system
    void registerComponent(MessageReceiver* component);

    // Unregisters a component from the messaging system
    void unregisterComponent(MessageReceiver* component);

    // Broadcasts a message to all registered components
    void broadcastMessage(Message* msg);

    // Sends a message to a specific component
    void sendMessage(Message* msg, MessageReceiver* recipient);

    void update(float deltaTime);

private:
    std::vector<MessageReceiver*> m_components;
};

#endif // !MESSAGING_SYSTEM_H
