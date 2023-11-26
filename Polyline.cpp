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

template <typename T>
class Polyline
{
public:
    Polyline();
    Polyline(int size);
    Polyline(Polyline<T>& p);
    Polyline(const T& m1, const T& m2, int size);
    Polyline(const Polyline<T>& pol);
    Polyline(Polyline<T>&& pol)noexcept;
    ~Polyline();
    Polyline<T>& operator + (const Point<T>& p);
    void addPoint(const Point<T>& p);

    int getSize()const;

    Point<T>& operator[](int index);
    const Point<T>& operator[](int index)const;
    Polyline<T>& operator+(const Polyline<T>& p);
    double length()const;

    template<typename Q>
    friend
        std::ostream& operator << (std::ostream& out, const Polyline<Q>& pol);
private:
    Point<T>* points;
    int m_size;

};


