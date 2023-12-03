#ifndef OBSERVER_H
#define OBSERVER_H

#include <memory>

class Square;

class Observer {
    public:
        virtual void notify(Square* s) = 0;
        virtual ~Observer() = default;
};

#endif
