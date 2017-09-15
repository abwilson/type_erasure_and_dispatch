#pragma once

#include "FindByIdT.h"

#include <type_traits>
#include <algorithm>
#include <array>

template<typename Signature, typename Default, typename... Bases >
struct IndexedBases;

template<typename Result, typename... Args, typename Default, typename... Bases >
struct IndexedBases<Result(Args...), Default, Bases...>: Default, Bases...
{
    static constexpr int minId = std::min( { Bases::id... } );
    static constexpr int maxId = std::max( { Bases::id... } );
    static constexpr int size  = maxId - minId + 1;

    using Handler = Result (IndexedBases::*)(Args...) const;
    using Handlers = std::array< Handler, size >;

    template< std::size_t... i >
    static constexpr auto makeHandlers( std::index_sequence< i... > )
    {
        return Handlers{ &findByIdT< i + minId, Default, Bases... >::operator()... };
    }

    const Handlers handlers{ makeHandlers( std::make_index_sequence< size >{} ) };

    constexpr IndexedBases(){}

    Result handle(int i, Args... args) const
    {
        if( i >= minId && i <= maxId )
        {
            return (this->*handlers[ i - minId ])(std::forward<Args>(args)...);
        }
        return Default::operator()(std::forward<Args>(args)...);
    }

    void handleAll() const
    {
        for( auto&& i: handlers )
        {
            (this->*i)();
        }
    }
};
