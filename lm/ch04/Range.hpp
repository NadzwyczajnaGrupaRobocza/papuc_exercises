#pragma once
#include <iterator>

namespace lmlib
{
template <typename T>
class Range;

// concepts work in gcc 6.1
// template <class T> concept bool Incrementable = requires (T t)
// { ++t; t >= t; };
// template <Incrementable _Tp>
template <typename _Tp>
class RangeIter : public std::iterator<std::forward_iterator_tag, _Tp>
{
public:
    using type = _Tp;

    const _Tp& operator*()
    {
        return currentValue;
    }

    RangeIter& operator++()
    {
        ++currentValue;
        if (currentValue >= endValue)
        {
            this->isEndSentinel = true;
        }
        return *this;
    }

    RangeIter& operator++(int)
    {
        RangeIter tmp(*this);
        ++(*this);
        return tmp;
    }

    template<typename T>
    friend bool operator==(RangeIter<T> const& lhs, RangeIter<T> const& rhs);
    template<typename T>
    friend bool operator!=(RangeIter<T> const& lhs, RangeIter<T> const& rhs);

private:
    friend class Range<_Tp>;
    bool isEndSentinel;

    RangeIter() : isEndSentinel{true}
    {
    }

    RangeIter(_Tp initialValue, _Tp endValueInit)
        : isEndSentinel{false}, currentValue{initialValue},
          endValue{endValueInit}
    {
    }


    _Tp currentValue;
    _Tp endValue;
};

template <class _Tp>
bool operator==(const RangeIter<_Tp>& lhs, const RangeIter<_Tp>& rhs)
{
    if (lhs.isEndSentinel)
    {
        if (rhs.isEndSentinel)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (rhs.isEndSentinel)
        {
            return false;
        }
        else
        {
            return lhs.currentValue == rhs.currentValue;
        }
    }
}

template <class _Tp>
bool operator!=(const RangeIter<_Tp>& lhs, const RangeIter<_Tp>& rhs)
{
    return not (lhs == rhs);
}

template <typename T>
class Range
{
public:
    Range(T beginInit, T endInit) : beginVal{beginInit}, endVal{endInit}
    {
    }

    RangeIter<T> begin()
    {
        return RangeIter<T>(beginVal, endVal);
    }

    RangeIter<T> end()
    {
        return RangeIter<T>();
    }

private:
    T beginVal;
    T endVal;
};
}
