#ifndef OBSERVER_H
#define OBSERVER_H
class Square;

class Observer {
    public:
        virtual void notify(Square &c) = 0;
        virtual ~Observer() = default;
};

#endif
