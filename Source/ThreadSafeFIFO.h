#ifndef THREAD_SAFE_FIFO_H
#define THREAD_SAFE_FIFO_H

#include <JuceHeader.h>

template <typename T>
class ThreadSafeFIFO
{
public:
    
    ThreadSafeFIFO() = default;

    void push(const T &item);
    void push(T &&item);
    
    bool pop(T &item);

    bool empty() const;
    int size() const;

    bool getProducing() const;
    void setProducing(bool);

private:
    bool isProducing = false;
    juce::Array<T> queue;
    mutable juce::CriticalSection mutex;
};

#endif // THREAD_SAFE_FIFO_H