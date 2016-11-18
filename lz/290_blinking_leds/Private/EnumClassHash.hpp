#pragma once

namespace utils
{
struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<typename std::underlying_type<T>::type>(t);
    }
};
}
