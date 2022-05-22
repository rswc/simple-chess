#pragma once

#include <iostream>
#include <bitset>

struct Bitmask
{
public:
    enum Flags
    {
        NONE = 0,
        EMPTY = 1,
        FULL = 2
    };
private:
    unsigned long long data;
    Bitmask(unsigned long long state) : data(state) {};
public:

    bool get(int x, int y)
    {
        return (data >> (8 * x + y)) & (x >= 0 && y >= 0 && x <= 7 && y <= 7);
    }

    bool isEmpty()
    {
        return data == 0ULL;
    }

    void set(int x, int y, bool v = true)
    {
        if (x < 0 || y < 0 || x > 7 || y > 7)
            return;
        
        if (!v)
            data = ~data;

        data |= 1ULL << (8 * x + y);

        if (!v)
            data = ~data;
    }

    void print()
    {
        unsigned long long d = data;

        std::cout << "Bitmask data:\n";

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                std::cout << (1 & d);
                d >>= 1;
            }
            std::cout << "\n";
        }
    }

    Bitmask(Flags flags = NONE)
    {
        if (flags & FULL)
        {
            data = ~0ULL;
        }
        else
        {
            data = 0ULL;
        }
    }

    Bitmask operator| (const Bitmask& other)
    {
        return Bitmask(data | other.data);
    }

    Bitmask& operator|= (const Bitmask& other)
    {
        data |= other.data;
        return *this;
    }

    Bitmask operator& (const Bitmask& other)
    {
        return Bitmask(data & other.data);
    }

    Bitmask& operator&= (const Bitmask& other)
    {
        data &= other.data;
        return *this;
    }

    Bitmask operator~ ()
    {
        return Bitmask(~data);
    }
};

