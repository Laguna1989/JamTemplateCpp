#ifndef OBSERVER_INTERFACE_HPP
#define OBSERVER_INTERFACE_HPP

template <typename T>
class ObserverInterface {
public:
    virtual ~ObserverInterface() = default;
    virtual void notify(T value) = 0;
};

#endif // !OBSERVER_INTERFACE_HPP
