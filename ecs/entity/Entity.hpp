#ifndef _ENTITY_
    #define _ENTITY_

#include <cstddef>

class Registry;

class Entity
{
  public:
    explicit operator size_t() const;
    bool operator==(Entity const& other) const;
    bool operator!=(Entity const& other) const;

  private:
    explicit Entity(size_t id);
    size_t _id;
    friend class Registry;
};

#endif
