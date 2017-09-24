#include <array>
#include <algorithm>
#include <utility>
//
// Some helpers to pick out a type from a parameter
// pack given an integer id.
//
template<int key, typename Default, typename... Ts>
struct Find;

template<int key, typename Default, typename Head, typename... Tail>
struct Find<key, Default, Head, Tail...>
{
    using type = std::conditional_t<
        Head::id == key, Head, typename Find<key, Default, Tail...>::type>;
};

template<int key, typename Default>
struct Find<key, Default> { using type = Default; };

template<int key, typename Default, typename... Ts>
using find_t = typename Find<key, Default, Ts...>::type;

template<int ID>
struct DumbHandler
{
    static constexpr int id = ID;
    constexpr int handle() const { return id; }
};

using One = DumbHandler<1>;
using Two = DumbHandler<2>;
using Ten = DumbHandler<10>;
//
// A default for when something isn't found.
//
struct Lost
{
    constexpr int handle() const
    {
        return -1;
    }
};
//
// Make sure the Find helper actually works.
//
static_assert(
    std::is_same<Find<1, Lost, One, Two, Ten>::type, One>::value,
    "Should find type with id 1"
);

static_assert(
    std::is_same<Find<2, Lost, One, Two, Ten>::type, Two>::value,
    "Should find type with id 2"
);

static_assert(
    std::is_same<Find<10, Lost, One, Two, Ten>::type, Ten>::value,
    "Should find type with id 10"
);

static_assert(
    std::is_same<Find<7, Lost, One, Two, Ten>::type, Lost>::value,
    "Should return default is id not found."
);
//
// A template for building dispatcher class.
//
template<typename... Ts>
struct IndexedBases: Lost, Ts...
{
    //
    // We're going to keep a sparse array of pointers to
    // handlers. Work out the size of this array 
    // based on the range of ids we have.
    //
    static constexpr int minId = std::min({ Ts::id... });
    static constexpr int maxId = std::max({ Ts::id... });
    static constexpr int size  = maxId - minId + 1;
    //
    // In this context a Handler is a pointer to a member
    // function of ourselves.
    //
    using Handler = int (IndexedBases::*)() const;
    using Handlers = std::array<Handler, size>;
    //
    // This is a function that builds the sparse array where handle
    // with id x is in position x + minId. All other slots are filled
    // with a default handler.
    //
    template<std::size_t... i>
    static constexpr auto makeHandlers(std::index_sequence<i...>)
    {
        //
        // This is the interest bit.
        //
        return Handlers{ 
            &find_t<i + minId, Lost, Ts...>::handle... 
            //
            // Because we've derived from all our handlers in this context
            // their handle methods all have the type of member of the derived
            // class - hence type erasure.
            //
        };
    }
    const Handlers handlers{ makeHandlers( std::make_index_sequence< size >{} ) };
    constexpr IndexedBases() = default;
    constexpr int handle( int i ) const
    {
        //
        // This call is a direct call to method (with appropriate
        // this adjustment), but without going via a vtable.
        //
        return (this->*handlers[ i - minId ])();
    }
};

//
// And example dispatcher for One, Two and Ten handlers.
//
constexpr const IndexedBases< One, Two, Ten > foo;

static_assert(foo.handle(1) == 1, "Calls correct handler for 1.");
static_assert(foo.handle(2) == 2, "Calls correct handler for 2.");
static_assert(foo.handle(10) == 10, "Calls correct handler for 10.");
static_assert(foo.handle(7) == -1, "Calls default handler when not found.");

void callFoo(int i)
{
    foo.handle(i);
}
