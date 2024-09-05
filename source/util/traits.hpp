#pragma once

#include <tuple>
#include <variant>

namespace tet::util
{
    template <typename>
    struct VariantOrTupleTraits
    {
        static constexpr bool isVariant = false;
        static constexpr bool isTuple   = false;
    };

    template <template <typename...> typename VT, typename... Ts>
    struct VariantOrTupleTraits<VT<Ts...>>
    {
        static constexpr bool        isVariant = std::same_as<VT<Ts...>, std::variant<Ts...>>;
        static constexpr bool        isTuple   = std::same_as<VT<Ts...>, std::tuple<Ts...>>;
        static constexpr std::size_t size      = sizeof...(Ts);

        template <typename T>
        static constexpr bool isMember = (std::same_as<T, Ts> || ...);

        using Types = std::tuple<Ts...>;

        template <std::size_t I>
        using Member = std::tuple_element_t<I, std::tuple<Ts...>>;    // A hack :D

        template <typename T>
            requires isMember<T>
        static constexpr std::size_t index = []() consteval {
            auto handler = []<std::size_t... Is>(std::index_sequence<Is...>) {
                return ((std::same_as<T, Ts> ? Is : 0) + ...);
            };
            return handler(std::make_index_sequence<size>{});
        }();
    };
}
