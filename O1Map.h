#include <utility>

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
