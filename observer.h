#ifndef OBSERVER_H
#define OBSERVER_H
class Square;

class Observer {
    public:
        virtual void notify(shared_ptr<Square> s) = 0;
        virtual ~Observer() = default;
};

#endif
