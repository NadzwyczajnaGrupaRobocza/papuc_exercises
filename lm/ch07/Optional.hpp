#pragma once
#ifdef _WINDOWS

#include <boost/optional.hpp>
template <typename T>
using Optional = boost::optional<T>;

#else

#include <experimental/optional>
template <typename T>
using Optional = std::experimental::optional<T>;

#endif
