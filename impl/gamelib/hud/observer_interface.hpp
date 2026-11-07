#pragma once

template <typename T>
class ObserverInterface {
public:
    virtual ~ObserverInterface() = default;
    virtual void notify(T value) = 0;
};
