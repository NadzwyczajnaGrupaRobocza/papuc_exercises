// Implementation of examples from
// http://www.fluentcpp.com/2017/05/19/crtp-helper/

#include <iostream>

template <typename T, template <typename> class crtpType>
struct crtp
{
    T& underlying()
    {
        return static_cast<T&>(*this);
    }

    const T& underlying() const
    {
        return static_cast<const T&>(*this);
    }

private:
    crtp()
    {
    }

    friend crtpType<T>;
};

template <typename T>
struct Scalable : crtp<T, Scalable>
{
    void scale(double factor)
    {
        this->underlying().set_value(this->underlying().get_value() *
                                     factor);
    }
};

template <typename T>
struct Squarable : crtp<T, Squarable>
{
    void square()
    {
        this->underlying().set_value(this->underlying().get_value() *
                                     this->underlying().get_value());
    }
};

class Sensitivity : public Scalable<Sensitivity>,
                    public Squarable<Sensitivity>
{
public:
    Sensitivity(double init) : m_value{init}
    {
    }

    Sensitivity() : Sensitivity(0.0)
    {
    }

    double get_value() const
    {
        return m_value;
    }

    void set_value(double value)
    {
        m_value = value;
    }

private:
    double m_value;
};

template <typename T>
void set_scale(Scalable<T>& item, double new_scale)
{
    item.scale(new_scale);
}

template <typename T>
void square_the_thing(Squarable<T>& thing)
{
    thing.square();
}

int main()
{
    auto s = Sensitivity{2.0};
    std::cout << "the value is: " << s.get_value() << '\n';
    set_scale(s, 3.0);
    std::cout << "the value is: " << s.get_value() << '\n';
    square_the_thing(s);
    std::cout << "the value is: " << s.get_value() << '\n';

    return 0;
}
