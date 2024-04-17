#pragma once

#include <array>
#include <stddef.h>

template <typename T, size_t Size>
class CircularBuffer
{
public:
    void add(T value)
    {
        buffer[index] = value;
        index = (index + 1) % Size;
        if (count < Size)
        {
            count++;
        }
    }

    T getAverage() const
    {
        if (count == 0)
            return T();

        T sum = T();
        for (size_t i = 0; i < count; ++i)
        {
            sum += buffer[i];
        }
        return sum / count;
    }

private:
    std::array<T, Size> buffer{};
    size_t index = 0;
    size_t count = 0;
};