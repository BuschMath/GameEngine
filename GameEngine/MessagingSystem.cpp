#include "MessagingSystem.h"

void MessagingSystem::registerComponent(MessageReceiver* component) {
    m_components.push_back(component);
}

void MessagingSystem::unregisterComponent(MessageReceiver* component) {
    auto it = std::find(m_components.begin(), m_components.end(), component);
    if (it != m_components.end()) {
        m_components.erase(it);
    }
}

void MessagingSystem::broadcastMessage(Message* msg) {
    for (auto component : m_components) {
        component->receiveMessage(msg);
    }
}

void MessagingSystem::sendMessage(Message* msg, MessageReceiver* recipient) {
    recipient->receiveMessage(msg);
}

void MessagingSystem::update(float deltaTime) {
    // Process all messages in the queue
    while (!m_messageQueue.empty()) {
        // Get the next message from the front of the queue
        Message message = m_messageQueue.front();
        m_messageQueue.pop();

        // Find the entity with the corresponding ID
        auto entityIt = m_entities.find(message.entityID);
        if (entityIt == m_entities.end()) {
            // Entity not found, ignore the message
            continue;
        }

        // Get the message handler components for the entity
        auto messageHandlers = entityIt->second->getComponents<MessageHandlerComponent>();
        for (auto& messageHandler : messageHandlers) {
            // Check if the message type matches any of the registered handlers
            auto& handlers = messageHandler->getHandlers();
            auto handlerIt = handlers.find(message.type);
            if (handlerIt != handlers.end()) {
                // Call the corresponding message handler function with the message data
                handlerIt->second(message.data);
            }
        }
    }
}

