#ifndef MESSAGE_RECEIVER_H
#define MESSAGE_RECEIVER_H

#include "Message.h"

// An interface for components that can receive messages
class MessageReceiver {
public:
    virtual ~MessageReceiver() {}
    virtual void receiveMessage(Message* msg) = 0;
};

#endif // !MESSAGE_RECEIVER_H
