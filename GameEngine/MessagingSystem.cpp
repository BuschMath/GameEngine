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
