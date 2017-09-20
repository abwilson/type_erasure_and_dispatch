#pragma once

#include "FindByIdT.h"
#include "EOBIWrap.h"

#include <array>

template<typename Impl>
struct HandlerGenerator
{
    Impl impl;
    
    static const char* handle(
        const void* clientData,
        const char* buffer,
        const MessageHeaderCompT& header,
        uint32_t& seqNo)
    {
        const Impl* handler = reinterpret_cast<const Impl*>(clientData);
        return (*handler)(buffer, header, seqNo);
    }
};

template<typename Signature, typename Default, typename... Bases >
struct VoidStarFPtrs;

template<typename Result, typename... Args, typename Default, typename... Bases >
struct VoidStarFPtrs<Result(Args...), Default, Bases...>:
    HandlerGenerator<Default>,
    HandlerGenerator<Bases>...
{
    static constexpr int minId = std::min( { Bases::id... } );
    static constexpr int maxId = std::max( { Bases::id... } );
    static constexpr int size  = maxId - minId + 1;

    using HandlerFunction = const char* (*)(
        const void* clientData,
        const char* buffer,
        const MessageHeaderCompT& header,
        uint32_t& seqNo);

    struct Handler
    {
        HandlerFunction fun;
        const void* clientData;
    };

    Handler defaultHandler =
        {
            &HandlerGenerator<Default>::handle,
            static_cast<const HandlerGenerator<Default>*>(this)
        };
    using Handlers = std::array< Handler, size >;

    template<int i>
    using HandlerForI = findByIdT< i + minId, Default, Bases... >;

    template<typename H>
        Handler makeHandler()
    {
        return{ &HandlerGenerator<H>::handle,
                static_cast<const HandlerGenerator<H>*>(this) };
    }

    template< std::size_t... i >

        constexpr auto makeHandlers( std::index_sequence< i... > )
    {
        return Handlers{ makeHandler<HandlerForI<i>>()... };
    }

    const Handlers handlers{ makeHandlers( std::make_index_sequence< size >{} ) };

    Result handle( int i, Args... args ) const
    {
        const Handler& h = i >= minId && i <= maxId ?
            handlers[i - minId] :
            defaultHandler;
        
        return (h.fun)(h.clientData, std::forward<Args>(args)...);
    }

    void handleAll() const
    {
        for( auto&& i: handlers )
        {
            (this->*i)();
        }
    }
};

