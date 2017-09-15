#include <array>
#include <algorithm>
#include <initializer_list>
#include <utility>
//#include <iostream>
#include <tuple>
#include <functional>
#if 0
template< typename T, std::size_t N >
struct O1Map: std::array< T, N >
{
//    using Idx = int;
    // template< typename Idx >
    // O1Map( std::initializer_list< std::pair< Idx, T > > members )
    // {
    //     for( const auto& i: members )
    //     {
    //         (*this)[ i.first ] = i.second;
    //     }
    // }

    O1Map() = default;    

    template< typename Idx, typename... Ts >
    O1Map( std::pair< Idx, T > head, Ts&&... tail ):
        O1Map( std::forward<Ts>( tail )... )
    {
        (*this)[ head.first ] = head.second;
    }
};
#endif

template< int idx, typename... Ts >
constexpr auto find(  Ts... tail )
{
    int result{};
    auto matcher = [&]( auto item )
    {
        return result += item.first == idx ? item.second : 0;
    };
    int tmp[] = { matcher( tail )... };
    return result;
}

#if 0

template< typename Key, typename Val >
void find2( Key key, std::initializer_list< std::pair< Key, Val > > )
{
}

int
testFind2()
{
    O1Map< int, 10 > m{ std::make_pair( 1, 20 ), std::make_pair( 3, 40 ) };

    auto x = find<10>( std::make_pair( 10, 1 ) );

    find2( 10, { std::make_pair( 10, 1 ) } );

    std::cout << "x: " << x << std::endl;

    return m[ 1 ];
}
#endif
template< int key, typename Default, typename... Ts >
struct Find;

template< int key, typename Default, typename... Ts >
using find_t = typename Find< key, Default, Ts...>::type;

template< int key, typename Default, typename Head, typename... Tail >
struct Find< key, Default, Head, Tail... >
{
    using type = std::conditional_t<
        Head::id == key, Head, typename Find< key, Default, Tail... >::type >;
};

template< int key, typename Default, typename Head >
struct Find< key, Default, Head >
{
    using type = std::conditional_t< Head::id == key, Head, Default >;
};

template< int key, typename Default  >
struct Find< key, Default >
{
    using type = Default;
};

template< int ID >
struct HasID
{
    static constexpr int id = ID;
    static constexpr bool found = true;

};

int count{};

struct One: HasID< 1 >
{
    void handle() const
    {
        count += 1;
        //std::cout << "One" << std::endl;
    }
};
    
struct Two: HasID< 2 >
{
    void handle() const
    {
        count += 2;
        //std::cout << "Two" << std::endl;
    }
};

struct Ten: HasID< 10 >
{
    void handle() const
    {
        count += 10;
//        std::cout << "Ten" << std::endl;
    }
};

struct Lost
{
    static constexpr bool found = false;
    void handle() const
    {
        count = 0;
//        std::cout << "Lost" << std::endl;
    }
};

template< typename... Ts >
struct IndexedBases final: Lost, Ts...
{
    static constexpr int minId = std::min( { Ts::id... } );
    static constexpr int maxId = std::max( { Ts::id... } );
    static constexpr int size  = maxId - minId + 1;

    using Handler = void (IndexedBases::*)() const;
    using Handlers = std::array< Handler, size >;

    template< std::size_t... i >
        static constexpr auto findHandlers( std::index_sequence< i... > )
    {
        return Handlers{ &find_t< i + minId, Lost, Ts... >::handle... };
    }

    static constexpr Handlers handlers{ findHandlers( std::make_index_sequence< size >{} ) };

    constexpr IndexedBases() {};

    void handle( int i ) const
    {
        (this->*handlers[ i - minId ])();
    }

    void handleAll() const
    {
        for( auto&& i: handlers )
        {
            (this->*i)();
        }
    }
};

template< typename... Ts >
constexpr typename IndexedBases< Ts... >::Handlers
IndexedBases< Ts... >::handlers;

constexpr IndexedBases< One, Two, Ten > foo;

template< typename... Ts >
struct IndexedMembers
{
    std::tuple< Lost, Ts... > handlers;
    
    static constexpr int minId = std::min( { Ts::id... } );
    static constexpr int maxId = std::max( { Ts::id... } );
    static constexpr int size  = maxId - minId + 1;

    using Handler = std::function< void() >;
    using Handlers = std::array< Handler, size >;

    template< typename H >
    void callHandler()
    {
        std::get< H >( handlers ).handle();
    }

    template< typename H >
    constexpr auto makeHandler()
    {
        return [ this ]{ callHandler< H >(); };
    }

    template< std::size_t... i >
    constexpr auto findHandlers( std::index_sequence< i... > )
    {
        return Handlers{
            makeHandler< find_t< i + minId, Lost, Ts... > >()... };
    }

    const Handlers handlerFs{ findHandlers( std::make_index_sequence< size >{} ) };

    constexpr IndexedMembers() {};

    void handle( int i ) const
    {
        handlerFs[ i - minId ]();
    }

    void handleAll() const
    {
        for( auto&& i: handlers )
        {
            (this->*i)();
        }
    }
};

const IndexedMembers< One, Two, Ten > bar;

void callFoo( int idx )
{
    foo.handle( idx );
}

void callBar( int idx )
{
  bar.handle( idx );
}
int
main()
{
    callFoo( 1 );
  //  callBar( 1 );
    // std::cout << "b[ 0 ] == " << b[ 0 ] << std::endl
    //           << "b[ 1 ] == " << b[ 1 ] << std::endl
    //           << "b[ 8 ] == " << b[ 8 ] << std::endl;
//    O1Map< double, 100 > map{ { std::make_pair( 10, 2.1 ), std::make_pair( 45, 75.3 ) } };

    // std::cout << "bar() : " << bar() << std::endl;
    
    // O1Map< double, 100 > map2{ std::make_pair( 10, 2.1 ), std::make_pair( 45, 75.3 ) };

//    std::cout << "size of handlers: " << foo.handlers.size() << std::endl;

    // foo.handle( 1 );
    // bar.handle( 1 );
    // foo.handle( 2 );
    // foo.handle( 5 );
    // foo.handle( 9 );
    // foo.handle( 10 );

    // foo.handleAll();
}
