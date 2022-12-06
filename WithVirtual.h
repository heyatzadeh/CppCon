#pragma once

#include <memory>
#include <vector>

struct FooInterface
{
    FooInterface() = default;
    FooInterface(const FooInterface&) = default;
    FooInterface(FooInterface&&) = default;
    FooInterface& operator=(const FooInterface&) = default;
    FooInterface& operator=(FooInterface&&) = default;
    virtual ~FooInterface() = default;

    [[nodiscard]] virtual auto func() const -> int = 0;
};

struct Foo final : public FooInterface
{
    Foo() = default;
    Foo(const Foo&) = default;
    Foo(Foo&&) = default;
    Foo& operator=(const Foo&) = default;
    Foo& operator=(Foo&&) = default;
    virtual ~Foo() = default;

    [[nodiscard]] auto func() const -> int override { return 42; }
};

// owning polymorphic type
class Bar
{
public:
    constexpr Bar(std::unique_ptr<FooInterface> input_foo) : foo{std::move(input_foo)} {}

    constexpr auto set_foo(std::unique_ptr<FooInterface> input_foo) { foo = std::move(input_foo); }

private:
    std::unique_ptr<FooInterface> foo{};
};

// storing multiply types
class Baz
{
public:
    auto store(std::unique_ptr<FooInterface> value) -> void { data.push_back(std::move(value)); }

private:
    std::vector<std::unique_ptr<FooInterface>> data{};
};
