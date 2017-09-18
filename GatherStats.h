#pragma once
#include <cstdint>
#include <type_traits>

template<typename...> using void_t = void;

struct StatsHolder
{
    static uint64_t total;

    void operator()(const void*) const
    {
    }

    template<typename T>
    void operator()(const T* msg, decltype(&T::OrderDetails) = &T::OrderDetails) const
    {
        total += msg->OrderDetails.DisplayQty;
    }

    template<typename T>
    void operator()(const T* msg, decltype(&T::LastQty) = &T::LastQty) const
    {
        total += msg->LastQty;
    }
    
};

template<typename T, typename = void>
struct GatherStats: StatsHolder
{
    static void gather(const T& msg) {}
};

template<typename T>
struct GatherStats<T, void_t<decltype(T::OrderDetails)>>: StatsHolder
{
    static void gather(const T& msg)
    {
        total += msg.OrderDetails.DisplayQty;
    }
};

