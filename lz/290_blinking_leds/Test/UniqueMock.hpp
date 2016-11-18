#pragma once
#include <cassert>
#include <gmock/gmock.h>
#include <gsl/gsl_assert>
#include <memory>
#include <type_traits>

namespace ut
{
namespace
{
template <class T>
class UniqueMock
{
    static_assert(
        std::has_virtual_destructor<T>::value,
        "UniqueMock require type inherited from class with virtual destructor");

public:
    template <class... Args>
    UniqueMock(Args&&... args)
        : _unique{std::make_unique<
              ::testing::StrictMock<UniqueObserver<Args...>>>(
              &raw, std::forward(args)...)},
          raw{_unique.get()}
    {
    }

    T* release()
    {
        return _unique.release();
    }

    std::unique_ptr<T>&& unique()
    {
        return std::move(_unique);
    }

    T& operator*() const
    {
        Expects(raw != nullptr);
        return *raw;
    }

    T* operator->() const
    {
        Expects(raw != nullptr);
        return raw;
    }

    T* get()
    {
        return raw;
    }

private:
    template <class... Args>
    class UniqueObserver : public T
    {
    public:
        UniqueObserver(T** ptr_raw, Args&&... args)
            : T{std::forward(args)...}, raw{ptr_raw}
        {
        }

        ~UniqueObserver()
        {
            *raw = nullptr;
        }

    private:
        T** raw;
    };

    std::unique_ptr<T> _unique;
    T* raw;
};
}
template <class T>
using unique_mock = UniqueMock<T>;
}
