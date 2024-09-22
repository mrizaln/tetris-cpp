#pragma once

#include "util/traits.hpp"

#include <tl/expected.hpp>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <magic_enum.hpp>

#include <chrono>
#include <concepts>
#include <random>
#include <ranges>
#include <type_traits>

namespace tet
{
    namespace rr = std::ranges;
    namespace rv = std::views;

    using i8  = std::int8_t;
    using i16 = std::int16_t;
    using i32 = std::int32_t;
    using i64 = std::int64_t;

    using u8  = std::uint8_t;
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;

    using usize = std::size_t;
    using isize = std::ptrdiff_t;

    using f32 = float;
    using f64 = double;

    template <typename T, typename E>
    using Expect = tl::expected<T, E>;

    using Clock    = std::chrono::steady_clock;
    using Duration = std::chrono::milliseconds;

    // used to visit std::variants
    template <typename... Fs>
    struct Overload : Fs...
    {
        using Fs::operator()...;
    };

    /**
     * @brief randomly generate number in range `[min, max]` for integral or `[min, max)` for floating point
     *
     * @tparam T whether integral or floating point type
     * @param min minimum value
     * @param max maximum value
     * @return the randomly generated number
     */
    template <typename T>
        requires std::integral<T> or std::floating_point<T>
    T random(T min, T max)
    {
        thread_local static auto rng = std::mt19937{};
        if constexpr (std::integral<T>) {
            auto dist = std::uniform_int_distribution{ min, max };
            return dist(rng);
        } else if (std::floating_point<T>) {
            auto dist = std::uniform_real_distribution{ min, max };
            return dist(rng);
        }
    }
}

namespace tet::operators::inline visit_operator
{
    template <typename T, typename... Fs>
        requires util::VariantOrTupleTraits<std::decay_t<T>>::isVariant
    constexpr decltype(auto) operator>>(T&& variant, Overload<Fs...>&& visitor)
    {
        return std::visit(std::forward<Overload<Fs...>>(visitor), std::forward<T>(variant));
    }
}
