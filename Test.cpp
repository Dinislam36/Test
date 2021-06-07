#include <iostream>

struct Hello
{
    int helloworld() { return 0; }
};

struct Generic {};

// SFINAE test
template <typename T>
class has_helloworld
{
    typedef char one;
    struct two { char x[2]; };

    template <typename C> static one test( decltype(&C::helloworld) ) ;
    template <typename C> static two test(...);

public:
    enum { value = sizeof(test<T>(0)) == sizeof(one) };
};
