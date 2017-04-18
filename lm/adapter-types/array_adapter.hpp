#pragma once

#include <cstdlib>
#include <iterator>
#include <type_traits>

namespace accs
{
template <typename T>
class array_adapter
{
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    array_adapter(T* data_, std::size_t N_)
        : data{data_}, N{N_}
    {}

    // clang-format off
    iterator begin() { return data; }
    iterator end() { return data + N; }
    const_iterator begin() const { return data; }
    const_iterator end() const { return data + N; }
    const_iterator cbegin() const { return data; }
    const_iterator cend() const { return data + N; }

    reverse_iterator rbegin() {
        return std::make_reverse_iterator(end()); }
    reverse_iterator rend() {
        return std::make_reverse_iterator(begin()); }
    const_reverse_iterator rbegin() const {
        return std::make_reverse_iterator(end()); }
    const_reverse_iterator rend() const {
        return std::make_reverse_iterator(begin()); }
    const_reverse_iterator crbegin() const { return rbegin(); }
    const_reverse_iterator crend() const { return rend(); }
    // clang-format on

    reference operator[](std::size_t index)
    {
        return *(data + index);
    }

    const_reference operator[](std::size_t index) const
    {
        return *(data + index);
    }

    size_type size() const { return N; }
    bool empty() const { return N == 0; }

private:
    T* data;
    size_type N;
};

template <std::size_t N, typename T>
auto adapt_array(T (&t)[N])
{
    return array_adapter<T>(t, N);
}

template <std::size_t N, typename T>
auto adapt_array(const T (&t)[N])
{
    return array_adapter<const T>(t, N);
}

template <std::size_t N, typename T>
auto adapt_array(T* t)
{
    return array_adapter<T>(t, N);
}

}
