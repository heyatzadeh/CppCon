#ifdef UseVirtual
// with virtual
#include "WithVirtual.h"
std::unique_ptr<FooInterface> foo = std::make_unique<Foo>();
auto func(std::unique_ptr<FooInterface> foo2)
{
    // do something
}

Bar bar{std::make_unique<Foo>()};

#endif

#ifndef UseVirtual
// without virtual
#include "WithoutVirtual.h"
Foo foo{};
auto func(CFoo auto& foo2)
{
    // do something
}

Bar<Foo> bar{Foo{}};
// Bar<Foo1, Foo2> bar{Foo1{}};
#endif

int main(int argc, char* argv[]) { return 0; }
