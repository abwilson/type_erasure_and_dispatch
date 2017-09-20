#include <x86intrin.h>

#include <atomic>
#include <iostream>

class TickCounter
{
    uint64_t startTicks;
    uint64_t& resultHolder;

public:
    TickCounter(uint64_t& i):
        resultHolder(i)
    {
        std::atomic_thread_fence(std::memory_order_seq_cst);
        startTicks = __rdtsc();
        std::atomic_thread_fence(std::memory_order_seq_cst);
    }

    ~TickCounter()
    {
        std::atomic_thread_fence(std::memory_order_seq_cst);
        auto endTicks = __rdtsc();
        std::atomic_thread_fence(std::memory_order_seq_cst);
        resultHolder += endTicks - startTicks; 
    }
};
