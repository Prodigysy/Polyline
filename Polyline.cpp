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

using std::complex;

template<typename T>

class Polyline<complex<T>> {

    Point<complex<T>>* points;
    int m_size;

public:
    int getSize()const { return this->m_size; }

    Polyline() : points{ nullptr }, m_size{ 0 } {};

    Polyline(int size) : m_size{ size } {
        if (size < 0) {
            throw std::out_of_range("Index out of ranges");
        }
        points = new Point<complex<T>>[size];
    }

    Polyline(Polyline<complex<T>>& other) {
        m_size = other.getSize();
        points = new Point<complex<T>>[m_size];
        for (int i = 0; i < m_size; ++i) {
            points[i] = other[i];
        }
    }

    Polyline(const complex<T>& m1, const complex<T>& m2, int size)
        : m_size{ static_cast<int>(size) } {

        if (size < 0) {
            throw std::out_of_range("Index out of range");
        }

        points = new Point<complex<T>>[m_size];
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<T> real_distrib(m1.real(), m2.real());
        for (int i = 0; i < m_size; i++) {
            T random_X = real_distrib(gen);
            T randomX = real_distrib(gen);
            T random_Y = real_distrib(gen);
            T randomY = real_distrib(gen);
            points[i] = Point<complex<T>>(std::complex<T>(random_X, randomX), std::complex<T>(random_Y, randomY));
        }
    }
    ~Polyline() {
        delete[] points;
    }

    void add(const Point<complex<T>>& point) {
        Point<complex<T>>* newElements = new Point<complex<T>>[m_size + 1];
        for (int i = 0; i < m_size; ++i) {
            newElements[i] = points[i];
        }
        newElements[m_size] = point;
        delete[] points;
        points = newElements;
        m_size += 1;
    }

    Point<complex<T>>& operator[](int index) {
        if (index < 0 || index >= m_size) {
            throw std::out_of_range("Index out of range");
        }
        return points[index];
    }

    const Point<complex<T>>& operator[](int index)const
    {
        if (index < 0 || index >= m_size) {
            throw std::out_of_range("Index out of range");
        }
        return points[index];

    }


