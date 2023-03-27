#ifndef ENTITY_H
#define ENTITY_H

class Entity {
public:
    Entity(int id) : m_id(id) {}
    int getID() const { return m_id; }
    bool operator==(Entity right) { return m_id == right.getID(); };
private:
    int m_id;
};

#endif // !ENTITY_H

