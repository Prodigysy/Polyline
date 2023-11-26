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

    Polyline<complex<T>>& operator+(const Polyline<complex<T>>& other) {
        int newSize = m_size + other.getSize();
        Point<complex<T>>* newPoints = new Point<complex<T>>[newSize];
        for (int i = 0; i < m_size; i++) {
            newPoints[i] = points[i];
        }
        for (int i = 0; i < other.getSize(); i++) {
            newPoints[m_size + i] = other.points[i];
        }
        delete[] points;
        points = newPoints;
        m_size = newSize;
        return *this;
    }

    Polyline<complex<T>>& operator+(const Point<complex<T>>& point) {
        Point<complex<T>>* newPoints = new Point<complex<T>>[m_size + 1];
        for (int i = 0; i < m_size; i++) {
            newPoints[i] = points[i];
        }
        newPoints[m_size] = point;
        delete[] points;
        points = newPoints;
        m_size++;
        return *this;
    }

    double length() const {

        double Length = 0.0;

        for (int i = 0; i < m_size - 1; i++) {

            complex<T> dx = points[i + 1].x - points[i].x;
            complex<T> dy = points[i + 1].y - points[i].y;
            double segmentLength = 0;

            segmentLength = abs(points[i + 1].x - points[i].x);
            segmentLength += abs(points[i + 1].y - points[i].y);
            Length += segmentLength;
        }
        return Length;
    }

    friend
        std::ostream& operator<<(std::ostream& os, const Polyline<complex<T>>& polyline) {
        for (int i = 0; i < polyline.getSize(); i++) {
            os << "(" << polyline.points[i].x << ",  " << polyline.points[i].y << ") ";
        }
        return os;
    }
};


template <typename T>
Polyline<T> createO(const Point<T>& startPoint,
    int width)
{
    /*
    _______
    |     |
    |_____|
    */
    Polyline<T> pol(4);
    pol[0] = startPoint;
    pol[1] = Point(startPoint.x, startPoint.y + width);
    pol[2] = Point(startPoint.x + width, startPoint.y);
    pol[3] = Point(startPoint.x + width, startPoint.y + width);
    return pol;
}


int main()
{
    Polyline<int> pol_i;
    Polyline<int> pol_example;
    std::cout << "polyline_default: " << std::endl;
    std::cout << pol_example << std::endl;

    Polyline<int> polyline_with_size(7);
    std::cout << "polyline_with_size: " << std::endl;
    std::cout << polyline_with_size << std::endl;

    Polyline<int> polyline_with_values(4, 8, 3);
    std::cout << "polyline_with_values: " << std::endl;
    std::cout << polyline_with_values << std::endl;

    Polyline<int> polyline_copy(polyline_with_values);
    std::cout << "polyline_copy: " << std::endl;
    std::cout << polyline_copy << std::endl;

    Point<int> new_point(8, 7);
    polyline_copy.addPoint(new_point);
    std::cout << "polyline_add_point: " << std::endl;
    std::cout << polyline_copy << std::endl;

    std::cout << "retrieved_point: " << std::endl;
    std::cout << polyline_copy[2] << std::endl;

    Polyline<int> other_polyline;
    Polyline<int> combined_polyline = polyline_with_values + polyline_copy;
    std::cout << "combined_polyline: " << std::endl;
    std::cout << combined_polyline << std::endl;


    Polyline<int> polyline_point = polyline_copy + new_point;
    std::cout << "polyline_point: " << std::endl;
    std::cout << polyline_point << std::endl;

    double combined_polyline_poly_length = combined_polyline.length();
    std::cout << "combined_polyline_poly_length: " << std::endl;
    std::cout << combined_polyline_poly_length << std::endl;

    Point<complex<float>> complex_point1(complex<float>(1, 2), complex<float>(3, 4));
    std::cout << "complex_point1: " << std::endl;
    std::cout << complex_point1 << std::endl;

    Polyline<complex<float>> polyline_with_complex_values(complex<float>(-3, -4),
        complex<float>(1, 1), 2);
    std::cout << "polyline_with_complex_values: " << std::endl;
    std::cout << polyline_with_complex_values << std::endl;

    Polyline<complex<float>> polyline_copy_complex(polyline_with_complex_values);
    std::cout << "polyline_copy_complex: " << std::endl;
    std::cout << polyline_copy_complex << std::endl;

    Point<complex<float>> complex_point2(complex<float>(1, 2), complex<float>(3, 4));
    polyline_copy_complex.add(complex_point2);
    std::cout << "polyline_add_complex_point: " << std::endl;
    std::cout << polyline_copy_complex << std::endl;

    std::cout << "retrieved_copmlex_point: " << std::endl;
    std::cout << polyline_copy_complex[2] << std::endl;

    Polyline<complex<float>> combined_complex_polyline = polyline_with_complex_values + polyline_copy_complex;
    std::cout << "combined_complex_polyline: " << std::endl;
    std::cout << combined_complex_polyline << std::endl;

    Polyline<complex<float>> polyline_point_complex = combined_complex_polyline + complex_point2;
    std::cout << "polyline_point_complex: " << std::endl;
    std::cout << polyline_point_complex << std::endl;

    double combined_polyline_complex_poly_length = polyline_point_complex.length();
    std::cout << "combined_polyline_complex_poly_length: " << std::endl;
    std::cout << combined_polyline_complex_poly_length << std::endl;

    auto myLastNameLetter = createO<int>({ 0,0 }, 45);
    std::cout << myLastNameLetter << std::endl;
    return 0;
}

template<typename T>
Point<T>::Point() noexcept
    :x{ T() }, y{ T() }
{
    //std::cout << "Constructor\n";
}

template<typename T>
Point<T>::Point(const T& _x, const T& _y) noexcept
{
    this->x = _x;
    this->y = _y;
    //std::cout << "Constructor with parametr\n";
}

template<typename T>
Point<T>::Point(const Point<T>& other) noexcept
{
    if (this != &other)
    {
        this->x = other.x;
        this->y = other.y;
    }
}

template<typename T>
Point<T>::Point(Point<T>&& other) noexcept
{
    this->x = std::move(other.x);
    this->y = std::move(other.y);
    //std::cout << "Move Constructor\n";
}

template<typename T>
Point<T>& Point<T>::operator=(const Point<T>& other) noexcept
{
    this->x = other.x;
    this->y = other.y;
    return *this;
}

template<typename T>
Point<T>& Point<T>::operator=(Point<T>&& other) noexcept
{
    //std::cout << "=move\n";
    this->x = std::move(other.x);
    this->y = std::move(other.y);
    return *this;
}



template<typename T>
std::ostream& operator<<(std::ostream& out, const Point<T>& p)
{
    out << "(" << p.x << "," << p.y << ")";
    return out;
}

template<typename T>
T dist(const Point<T>& a, const Point<T>& b)
{
    T x = (a.x - b.x);
    T y = (a.y - b.y);
    return x * x + y * y;
}


//-------------------POLYLINE IMPLEMENTATION-------------------
template<typename T>
Polyline<T>::Polyline()
    :m_size{ 0 }, points{ nullptr }
{}

template<typename T>
Polyline<T>::Polyline(int size)
{
    if (size <= 0)
        throw std::out_of_range("Index out of ranges");
    points = new Point<T>[size];
    if (points == nullptr)
        throw std::bad_alloc();
    m_size = static_cast<int>(size);
}

template<typename T>
Polyline<T>::Polyline(Polyline<T>& p)
{
    m_size = p.getSize();
    points = new Point<T>[m_size];

    if (points == nullptr)
        throw std::bad_alloc();

    for (int i = 0; i < m_size; i++)
        points[i] = p[i];
}

template<typename T>
Polyline<T>::Polyline(const T& m1, const T& m2, int size)
{
    if (size <= 0)
        throw std::out_of_range("Index out of ranges");
    m_size = size;
    points = new Point<T>[m_size];
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<T> distrib(m1, m2);
    for (int i = 0; i < m_size; i++) {
        T randomX = distrib(gen);
        T randomY = distrib(gen);
        points[i] = Point<T>(randomX, randomY);
    }
}

template<typename T>
Polyline<T>::Polyline(const Polyline<T>& pol)
{
    m_size = pol.getSize();
    points = new Point<T>[m_size];

    if (points == nullptr)
        throw std::bad_alloc;

    for (int i = 0; i < m_size; i++)
        points[i] = pol[i];
}

template<typename T>
Polyline<T>::Polyline(Polyline<T>&& pol)noexcept
{
    m_size = std::move(pol.getSize());
    points = pol.points;
    pol.points = nullptr;
}

template<typename T>
Polyline<T>::~Polyline()
{
    delete[] points;
}

template<typename T>
Polyline<T>& Polyline<T>::operator+(const Point<T>& p)
{
    Point<T>* pnts = new Point<T>[getSize() + 1];

    if (pnts == nullptr)
        throw std::bad_alloc();

    for (int i = 0; i < getSize(); i++)
    {
        pnts[i] = points[i];
    }

    pnts[getSize()] = p;
    delete[]points;
    points = pnts;
    m_size++;
    return *this;
}

template<typename T>
void Polyline<T>::addPoint(const Point<T>& p)
{

    Point<T>* pnts = new Point<T>[getSize() + 1];

    if (pnts == nullptr)
        throw std::bad_alloc();

    for (int i = 0; i < getSize(); i++)
    {
        pnts[i] = points[i];
    }

    pnts[getSize()] = p;
    delete[]points;
    points = pnts;
    m_size++;
}

template<typename T>
int Polyline<T>::getSize() const
{
    return m_size;
}

template<typename T>
Point<T>& Polyline<T>::operator[](int index)
{
    if (index < 0 || index> getSize())
        throw std::out_of_range("Index out of range");
    return points[index];
}

template<typename T>
const Point<T>& Polyline<T>::operator[](int index) const
{
    if (index < 0 || index> getSize())
        throw std::out_of_range("Index out of range");
    return points[index];
}

template<typename T>
Polyline<T>& Polyline<T>::operator+(const Polyline<T>& p)
{
    int newSize = m_size + p.getSize();
    Point<T>* newPoints = new Point<T>[newSize];
    for (int i = 0; i < m_size; i++) {
        newPoints[i] = points[i];
    }

    for (int i = 0; i < p.getSize(); i++) {
        newPoints[m_size + i] = p[i];
    }

    delete[] points;
    points = newPoints;
    m_size = newSize;
    return *this;
}

template<typename T>
double Polyline<T>::length() const
{
    double len = 0.0;
    for (int i = 0; i < m_size - 1; i++)
    {
        T len_seg = dist(points[i], points[i + 1]);
        len += static_cast<double>(sqrt(len_seg));
    }
    return len;
}

template<typename Q>
std::ostream& operator<<(std::ostream& out, const Polyline<Q>& pol)
{
    out << "[ ";
    for (int i = 0; i < pol.getSize() - 1; i++)
        out << pol[i] << ";";
    if (pol.getSize() > 0)
        out << pol[static_cast<int>(pol.getSize() - 1)];
    out << " ]";
    return out;
}

