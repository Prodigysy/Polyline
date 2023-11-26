#include <iostream>
#include <utility>
#include <stdexcept>
#include <random>
#include <complex>
template <typename  T>
struct Point
{
    T x, y;
  
    Point()noexcept;
    Point(const T& _x, const T& _y)noexcept;
    Point(const Point<T>& other)noexcept;
    Point(Point<T>&& other)noexcept;
    Point<T>& operator = (const Point<T>& other)noexcept;
    Point<T>& operator = (Point<T>&& other)noexcept;
    ~Point(){}

    template<typename Q>
    friend
        std::ostream& operator<<(std::ostream& out, const Point<Q>& p);
    template<typename Q>
    friend
       Q dist(const Point<Q>& a, const Point<Q>& b);
};

