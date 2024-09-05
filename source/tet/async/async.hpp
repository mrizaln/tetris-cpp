#pragma once

#include "tet/async/as_expected.hpp"

#include <asio.hpp>
#include <asio/experimental/awaitable_operators.hpp>
#include <tl/expected.hpp>

#include <utility>

namespace tet::async
{
    using DefaultToken = AsExpected<asio::use_awaitable_t<>>;
    using Timer        = DefaultToken::as_default_on_t<asio::steady_timer>;
    using Context      = asio::io_context;
    using Executor     = Context::executor_type;
    using Errc         = asio::error_code;
    using ErrCat       = asio::error_category;

    template <typename T>
    using Task = asio::awaitable<T>;

    using asio::post;

    template <typename Exec, typename Awaited>
    auto spawn(Exec&& ex, Awaited&& func)
    {
        return co_spawn(std::forward<Exec>(ex), std::forward<Awaited>(func), asio::detached);
    }

    template <typename Exec, typename Awaited, typename Completion>
    auto spawn(Exec&& ex, Awaited&& func, Completion&& completion)
    {
        return co_spawn(
            std::forward<Exec>(ex),    //
            std::forward<Awaited>(func),
            std::forward<Completion>(completion)
        );
    }

    template <typename E>
    auto unexpected(E&& e)
    {
        return tl::make_unexpected(std::forward<E>(e));
    }

    namespace error     = asio::error;
    namespace this_coro = asio::this_coro;
}

namespace tet::operators::inline async_operators
{
    using namespace asio::experimental::awaitable_operators;
}
