#pragma once

#include "util/traits.hpp"

#include <concepts>

namespace tet::util
{
    template <typename T, typename... Ts>
    concept AnyOf = (std::same_as<T, Ts> || ...);

    template <typename T, typename... Ts>
    concept AllOf = (std::same_as<T, Ts> && ...);

    template <typename Fn, typename Ret, typename... Args>
    concept Callable = std::invocable<Fn, Args...> and std::same_as<Ret, std::invoke_result_t<Fn, Args...>>;

    template <typename T, typename Var>
    concept TupleMember = VariantOrTupleTraits<Var>::template isMember<T>;

    template <typename T, typename Var>
    concept VariantMember = TupleMember<T, Var>;
}
