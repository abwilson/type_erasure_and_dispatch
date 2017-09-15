#pragma once
#include <x86intrin.h>
#include <cpuid.h>

#include <atomic>

class TickCounter
{
    volatile uint64_t startTicks;
    volatile uint64_t& resultHolder;
    volatile uint32_t processor;

public:
    TickCounter(uint64_t& i):
        resultHolder(i)
    {
        unsigned tmp;
        __cpuid(0, tmp, tmp, tmp, tmp);                   // cpuid is a serialising call
//        dont_remove = tmp;
        processor = tmp;
        _mm_lfence();
        std::atomic_thread_fence(std::memory_order_seq_cst);
        startTicks = __rdtsc();
        std::atomic_thread_fence(std::memory_order_seq_cst);
        _mm_lfence();

        
    }

    ~TickCounter()
    {
        uint32_t processor2;
        unsigned tmp;
        __cpuid(0, tmp, tmp, tmp, tmp);                   // cpuid is a serialising call
        processor2 = tmp;

        _mm_lfence();
        std::atomic_thread_fence(std::memory_order_seq_cst);
        auto endTicks = __rdtsc();
        _mm_lfence();
        std::atomic_thread_fence(std::memory_order_seq_cst);
        resultHolder += endTicks - startTicks; 
        
        if(processor != processor2)
        {
            std::cout << "processor: " << processor
                      << ", processor2: " << processor2
                      << std::endl;
            resultHolder ++;
        }
    }
};
