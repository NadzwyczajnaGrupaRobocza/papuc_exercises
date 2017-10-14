#include <memory>

template <typename T>
class non_owning_ptr
{
public:
    non_owning_ptr(T* p) : ptr{p} {}
    explicit non_owning_ptr(std::unique_ptr<T> up) : non_owning_ptr{up.get()} {}
    explicit non_owning_ptr(std::shared_ptr<T> sp) : non_owning_ptr{sp.get()} {}
    non_owning_ptr() : non_owning_ptr{nullptr} {}

    non_owning_ptr(const non_owning_ptr<T>&) = delete;
    non_owning_ptr<T>& operator=(const non_owning_ptr<T>&) = delete;

    non_owning_ptr(non_owning_ptr<T>&&) = default;
    non_owning_ptr<T>& operator=(non_owning_ptr<T>&&) = default;

    // make copying explicit to avoid accidents
    non_owning_ptr<T> clone() const
    {
        return non_owning_ptr<T>{ptr};
    }


    T* operator->() { return ptr; }
    T& operator*() { return *ptr; }

    T const* operator->() const { return ptr; }
    T const& operator*() const { return *ptr; }

    T* get() { return ptr; }
    T const* get() const { return ptr; }

private:
    T* ptr;
};

template <typename A, typename B>
bool operator==(non_owning_ptr<A> lhs, non_owning_ptr<B> rhs)
{
    return lhs.get() == rhs.get();
}

template <typename A, typename B>
bool operator!=(non_owning_ptr<A> lhs, non_owning_ptr<B> rhs)
{
    return lhs.get() != rhs.get();
}

template <typename T>
non_owning_ptr<T> make_non_owning_ptr(std::shared_ptr<T> sp)
{
    return non_owning_ptr<T>(sp);
}

template <typename T>
non_owning_ptr<T> make_non_owning_ptr(std::unique_ptr<T> up)
{
    return non_owning_ptr<T>(up);
}
