#pragma once

#include <concepts>
#include <variant>
#include <vector>

template <typename T>
concept CFoo = requires(T foo) {
                   //{ foo.func() } -> std::same_as<int>;
                   {
                       foo.func()
                       } -> std::integral;
               };

struct Foo
{
    [[nodiscard]] auto func() const -> int { return 42; }
};

static_assert(CFoo<Foo>);

// owning polymorphic type
template <typename T, typename... Ts>
concept same_as_any = (... or std::same_as<T, Ts>);

template <CFoo... TFoos>
class Bar
{
public:
    constexpr Bar(same_as_any<TFoos...> auto input_foo) : foo{input_foo} {}

    constexpr auto set_foo(same_as_any<TFoos...> auto input_foo) -> void { foo = input_foo; }

private:
    std::variant<TFoos...> foo{};
};

// storing multiply types
template <CFoo... TFoos>
class Baz
{
public:
    template <same_as_any<TFoos...> T>
    auto store(T value)
    {
        return std::get<std::vector<T>>(data).push_back(value);
    }

private:
    std::tuple<std::vector<TFoos>...> data{};
};
