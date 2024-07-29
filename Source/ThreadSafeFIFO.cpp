#include "ThreadSafeFIFO.h"

template<typename T>
void ThreadSafeFIFO<T>::push(const T &item)
{
    const juce::ScopedLock lock(mutex);
    queue.add(item);
}

template<typename T>
void ThreadSafeFIFO<T>::push(T &&item)
{
    const juce::ScopedLock lock(mutex);
    queue.add(std::move(item));
}

template<typename T>
bool ThreadSafeFIFO<T>::pop(T &item)
{
    const juce::ScopedLock lock(mutex);
    if (queue.isEmpty())
        return false;

    item = std::move(queue.removeAndReturn(0));
    return true;
}

template<typename T>
bool ThreadSafeFIFO<T>::empty() const
{
    const juce::ScopedLock lock(mutex);
    return queue.isEmpty();
}

template<typename T>
int ThreadSafeFIFO<T>::size() const
{
    const juce::ScopedLock lock(mutex);
    return queue.size();
}

template<typename T>
bool ThreadSafeFIFO<T>::getProducing() const
{
    const juce::ScopedLock lock(mutex);
    return queue.isProducing;
}

template<typename T>
void ThreadSafeFIFO<T>::setProducing(bool producing)
{
    const juce::ScopedBlock lock(mutex);
    queue.isProducing = producing;
}