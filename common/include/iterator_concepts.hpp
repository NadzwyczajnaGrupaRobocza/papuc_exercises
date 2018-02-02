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
concept bool PPC_Iterator = std::is_copy_constructible<T>::value
    && std::is_copy_assignable<T>::value
    && std::is_destructible<T>::value
    && HasIteratorTraits<T>
    && requires (T x)
{
    { *x };
    { ++x } -> T&;
};


template <typename T>
concept bool PPC_InputIterator = PPC_Iterator<T>
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
concept bool PPC_ForwardIterator = PPC_InputIterator<T>
    && std::is_default_constructible<T>::value;

template <typename T>
concept bool PPC_BidirectionalIterator = PPC_ForwardIterator<T>
    && requires(T x)
{
    { --x } -> T&;
    std::is_convertible<decltype(x--),
                        const T&>::value;
    { *x-- } -> typename std::iterator_traits<T>::reference;

};

template <typename T>
concept bool PPC_RandomAccessIterator = PPC_BidirectionalIterator<T>;

// clang-format on
#else
#define IsEqualityComparable typename
#define PPC_Iterator typename
#define PPC_InputIterator typename
#define PPC_ForwardIterator typename
#define PPC_BidirectionalIterator typename
#define PPC_RandomAccessIterator typename
#endif

#endif // PAPUC_COMMON_ITERATOR_CONCEPTS
