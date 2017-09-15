#include "IndexedMembers.h"

#include <initializer_list>
#include <iostream>
#include <functional>

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


template<int ID, typename T>
struct AddId: T
{
    using T::T;
    static constexpr int id = ID;
};    

template< int ID >
struct HasID
{
    static constexpr int id = ID;
};

struct One
{
    void operator()() const
    {
        std::cout << "One" << std::endl;
    }
};
    
struct Two
{
    void operator()() const
    {
        std::cout << "Two" << std::endl;
    }
};

struct Ten
{
    void operator()() const
    {
        std::cout << "Ten" << std::endl;
    }
};

struct Lost
{
    void operator()() const
    {
        std::cout << "Lost" << std::endl;
    }
};

//IndexedMembers< AddId<1, One>, AddId<2, Two>, AddId<10, Ten> > bar;

void callBar()
{
    bar.handle( 1 );
}
int
main()
{
    callBar();
    // std::cout << "b[ 0 ] == " << b[ 0 ] << std::endl
    //           << "b[ 1 ] == " << b[ 1 ] << std::endl
    //           << "b[ 8 ] == " << b[ 8 ] << std::endl;
//    O1Map< double, 100 > map{ { std::make_pair( 10, 2.1 ), std::make_pair( 45, 75.3 ) } };

    // std::cout << "bar() : " << bar() << std::endl;
    
    // O1Map< double, 100 > map2{ std::make_pair( 10, 2.1 ), std::make_pair( 45, 75.3 ) };

//    std::cout << "size of handlers: " << foo.handlers.size() << std::endl;

//    foo.handle( 1 );
    // bar.handle( 1 );
    // foo.handle( 2 );
    // foo.handle( 5 );
    // foo.handle( 9 );
    // foo.handle( 10 );

    // foo.handleAll();
}


