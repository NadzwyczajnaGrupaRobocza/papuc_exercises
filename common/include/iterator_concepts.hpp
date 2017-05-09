#ifndef PAPUC_COMMON_ITERATOR_CONCEPTS
#define PAPUC_COMMON_ITERATOR_CONCEPTS 1

#if defined(__cpp_concepts)
#include <type_traits>
// clang-format off
template <typename T>
concept bool IsEqualityComparable = requires(T x)
{
    { x == x } -> bool;
};

template <typename T>
concept bool HasIteratorTraits = requires (T x)
{
    typename std::iterator_traits<T>::value_type;
    typename std::iterator_traits<T>::difference_type;
    typename std::iterator_traits<T>::reference;
    typename std::iterator_traits<T>::pointer;
    typename std::iterator_traits<T>::iterator_category;
};

template <typename T>
concept bool Iterator = std::is_copy_constructible<T>::value
    && std::is_copy_assignable<T>::value
    && std::is_destructible<T>::value
    && HasIteratorTraits<T>
    && requires (T x)
{
    { *x };
    { ++x } -> T&;
};


template <typename T>
concept bool InputIterator = Iterator<T>
    && IsEqualityComparable<T>
    && requires (T x)
{
    std::is_same<decltype(*x),
                 typename std::iterator_traits<T>::reference>::value;
    std::is_convertible<typename std::iterator_traits<T>::reference,
                        typename std::iterator_traits<T>::value_type>::value;

    { x != x } -> bool;
    { x++ } -> T&;
};

template <typename T>
concept bool ForwardIterator = InputIterator<T>
    && std::is_default_constructible<T>::value;

template <typename T>
concept bool BidirectionalIterator = ForwardIterator<T>
    && requires(T x)
{
    { --x } -> T&;
    std::is_convertible<decltype(x--),
                        const T&>::value;
    { *x-- } -> typename std::iterator_traits<T>::reference;

};

template <typename T>
concept bool RandomAccessIterator = BidirectionalIterator<T>;

// clang-format on
#else
#define IsEqualityComparable typename
//#define Iterator typename
#define InputIterator typename
#define ForwardIterator typename
#define BidirectionalIterator typename
#define RandomAccessIterator typename
#endif

#endif // PAPUC_COMMON_ITERATOR_CONCEPTS
