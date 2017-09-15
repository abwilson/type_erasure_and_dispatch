#pragma once
#include <cstdint>

template<typename...> using void_t = void;

struct StatsHolder
{
    static uint64_t total;
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
