#ifndef SYSTEM_BASE_H
#define SYSTEM_BASE_H

class SystemBase {
public:
    virtual ~SystemBase() {}

    virtual void update(float deltaTime) = 0;
};

#endif // !SYSTEM_BASE_H

