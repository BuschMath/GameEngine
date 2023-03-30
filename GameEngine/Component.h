#ifndef COMPONENT_H
#define COMPONENT_H

#include "MessageReceiver.h"

class Component : MessageReceiver {
public:
    virtual ~Component() {}
    virtual void receiveMessage(Message* msg) override;

private:
    
};

#endif // !COMPONENT_H

