/*
Copyright 2017 Adobe
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/**************************************************************************************************/

#ifndef STLABFUTURE_SERIAL_QUEUE
#define STLABFUTURE_SERIAL_QUEUE

#include "config.hpp"

#include <deque>
#include <functional>
#include <memory>
#include <mutex>
#include <atomic>

#if STLAB_TASK_SYSTEM == STLAB_TASK_SYSTEM_LIBDISPATCH
#include <dispatch/dispatch.h>
#elif STLAB_TASK_SYSTEM == STLAB_TASK_SYSTEM_WINDOWS
#include <Windows.h>
#include <memory>
#elif STLAB_TASK_SYSTEM == STLAB_TASK_SYSTEM_PORTABLE
#endif

/**************************************************************************************************/

namespace stlab
{

/**************************************************************************************************/

inline namespace v1
{

#if STLAB_TASK_SYSTEM == STLAB_TASK_SYSTEM_PORTABLE

#if 0

namespace detail
{

template <typename Executor, typename Enabled = void>
struct shared_t;

template <typename Executor>
struct shared_t<Executor, typename std::enable_if_t<Executor::is_serial>> : std::enable_shared_from_this<shared_t<Executor>>
{
    Executor                                   _executor;
    std::deque<std::function<void()>>          _queue;
    bool                                       _running = false;

    shared_t(Executor executor)
            : _executor(std::move(executor)) {}

    template <typename F>
    void enqueue(F&& f) {
        _queue.emplace_back([_this = this->shared_from_this(), _f(std::forward<F>(f))]() {
            _f();
            _this->dequeue();
        });
        if (!_running)
            dequeue();
    }

    void dequeue() {
        std::function<void()> f;
        if (_queue.empty()) {
            _running = false;
            return;
        }
        _running = true;
        f = std::move(_queue.front());
        _queue.pop_front();

        _executor(f);
    }
};

template <typename Executor>
struct shared_t<Executor, std::enable_if_t<!Executor::is_serial>> : std::enable_shared_from_this<shared_t<Executor>>
{
    using lock_t = std::unique_lock<std::mutex>;

    Executor                                   _executor;
    std::mutex                                 _mutex;
    std::deque<std::function<void()>>          _queue;
    std::atomic_bool                           _running{false};

    shared_t(Executor executor)
            : _executor(std::move(executor)) {}

    template <typename F>
    void enqueue(F&& f) {
        {
            lock_t lock(_mutex);
            _queue.emplace_back([ _this = this->shared_from_this(), _f(std::forward<F>(f)) ]() {
                _f();
                _this->dequeue();
            });
        }
        if (!_running)
            dequeue();
    }

    void dequeue() {
        std::function<void()> f;
        {
            lock_t lock(_mutex);

            if (_queue.empty()) {
                _running = false;
                return;
            }
            _running = true;
            f = std::move(_queue.front());
            _queue.pop_front();
        }
        _executor(f);
    }
};

}

template <typename E>
class serial_queue
{

    std::shared_ptr<detail::shared_t<E>> _shared;

  public:

    serial_queue(E executor)
        : _shared(std::make_shared<detail::shared_t<E>>(std::move(executor))) {}

    // return an executor to schedule tasks serially
    auto executor() const {
        return [_shared = _shared](auto&& f) {
            _shared->enqueue(std::forward<decltype(f)>(f));
        };
    }
};

#endif

#elif STLAB_TASK_SYSTEM == STLAB_TASK_SYSTEM_LIBDISPATCH


class serial_queue_internal {
    dispatch_queue_t _q = dispatch_queue_create("com.stlab.serial_queue", NULL);
    
  public:
    serial_queue_internal() = default;
    serial_queue_internal(const char* name) : _q{ dispatch_queue_create(name, NULL) } { }
    ~serial_queue_internal() { dispatch_release(_q); }
    
    template <class Function, class... Args>
    auto async(Function&& f, Args&&... args )
    {
        using result_type = std::result_of_t<std::decay_t<Function>(std::decay_t<Args>...)>;
        using packaged_type = std::packaged_task<result_type()>;
        
        auto p = new packaged_type(std::bind([_f = std::forward<Function>(f)](Args&... args) {
            return _f(std::move(args)...);
        }, std::forward<Args>(args)...));
        
        auto result = p->get_future();

        dispatch_async_f(_q,
                p, [](void* f_) {
                    packaged_type* f = static_cast<packaged_type*>(f_);
                    (*f)();
                    delete f;
                });
        
        return result;
    }
};

class serial_queue 
{
    std::shared_ptr<serial_queue_internal> _shared;
public:
    auto executor() const {
        return [_shared = _shared](auto&& f) {
            _shared->async(std::forward<decltype(f)>(f));
        };
    }
};




#endif
} // namespace v1

/**************************************************************************************************/

} // namespace stlab

/**************************************************************************************************/

#endif