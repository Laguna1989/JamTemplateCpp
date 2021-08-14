#ifndef OBSERVER_INTERFACE_GUARD
#define OBSERVER_INTERFACE_GUARD

template <typename T>
class ObserverInterface {
public:
    virtual ~ObserverInterface() = default;
    virtual void notify(T value) = 0;
};

#endif // !OBSERVER_INTERFACE_GUARD
