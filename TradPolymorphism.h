#pragma once

#include "FindByIdT.h"

#include <memory>
#include <array>

struct HandlerI
{
    virtual ~HandlerI() = default;
    virtual const char* operator()(
        const char* buffer,
        const MessageHeaderCompT& header,
        uint32_t& seqNo) const = 0;
};

template<typename Impl>
struct HandlerT: HandlerI
{
    Impl impl;

    const char* operator()(
        const char* buffer,
        const MessageHeaderCompT& header,
        uint32_t& seqNo) const override
    {
        return impl(buffer, header, seqNo);
    }
};

template<typename Signature, typename Default, typename... Bases >
struct TradPolymorphism;

template<typename Result, typename... Args, typename Default, typename... Bases >
struct TradPolymorphism<Result(Args...), Default, Bases...>: Default, Bases...
{
    static constexpr int minId = std::min( { Bases::id... } );
    static constexpr int maxId = std::max( { Bases::id... } );
    static constexpr int size  = maxId - minId + 1;

    using Handler = std::unique_ptr<HandlerI>;
    using Handlers = std::array< Handler, size >;

    template< std::size_t... i >
    static constexpr auto makeHandlers( std::index_sequence< i... > )
    {
        return Handlers{ std::make_unique<HandlerT<findByIdT< i + minId, Default, Bases... >>>()... };
    }

    const Handlers handlers{ makeHandlers( std::make_index_sequence< size >{} ) };

    Result handle( int i, Args... args ) const
    {
        if( i >= minId && i <= maxId )
        {
            return (*handlers[ i - minId ])(std::forward<Args>(args)...);
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
