#pragma once

#include <type_traits>

template< int key, typename Default, typename... Ts >
struct FindById;

template< int key, typename Default, typename Head, typename... Tail >
struct FindById< key, Default, Head, Tail... >
{
    using type = std::conditional_t<
        Head::id == key, Head, typename FindById< key, Default, Tail... >::type >;
};

template< int key, typename Default  >
struct FindById< key, Default >
{
    using type = Default;
};

template< int key, typename Default, typename... Ts >
using findByIdT = typename FindById< key, Default, Ts...>::type;

