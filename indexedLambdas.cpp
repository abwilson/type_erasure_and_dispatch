#include "reader.h"
#include "MsgReader.h"
#include "FindByIdT.h"

#include <array>
#include <algorithm>
#include <functional>

template<typename Signature, typename Default, typename... Bases >
struct IndexedMembers;

template<typename Result, typename... Args, typename Default, typename... Bases >
struct IndexedMembers<Result(Args...), Default, Bases...>
{
    std::tuple< Default, Bases... > handlers;
    
    static constexpr int minId = std::min( { Bases::id... } );
    static constexpr int maxId = std::max( { Bases::id... } );
    static constexpr int size  = maxId - minId + 1;

    using Handler = std::function< Result(Args...) >;
    using Handlers = std::array< Handler, size >;

    template<typename H>
    auto makeHandler()
    {
        return [ this ](Args... args){ return std::get< H >( handlers )(args...); };
    }

    template< std::size_t... i >
    constexpr auto makeHandlers( std::index_sequence< i... > )
    {
        return Handlers{ makeHandler<findByIdT< i + minId, Default, Bases... > >()... };
    }

    const Handlers handlerFs{ makeHandlers( std::make_index_sequence< size >{} ) };

    constexpr IndexedMembers() {};

    Result handle( int i, Args... args  ) const
    {
        if( i >= minId && i <= maxId )
        {
            return handlerFs[ i - minId ](args...);
        }
        return std::get< Default >( handlers )(std::forward<Args>(args)...);
    }
};


int main(const int argc, const char** argv)
{
    using Reader = ReaderT<IndexedMembers, NullReader, MsgReader>;
    Reader underTest;
    return runner("IndexedLambdas", underTest, argc, argv);
}
