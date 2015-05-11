#ifndef COORDINATE_H
#define COORDINATE_H

namespace geometric {

	template<typename T>
	class Coordinate
	{

		// Constructors
	public:
		// Default constructor
		Coordinate() : x(0), y(0){};

		// Alternative constructor
		Coordinate(T _x, T _y) : x(_x), y(_y){};

		// Copy constructor
		Coordinate(const Coordinate<T>& coord)
		{
			*this = coord;
		}

		// Destructor
	public:
		~Coordinate() {};

		// Operators
	public:
		const Coordinate<T>& operator+= (const Coordinate<T>& coordinate);
		const Coordinate<T>& operator-= (const Coordinate<T>& coordinate);
		Coordinate<T> operator+ (const Coordinate<T>& coordinate) const;
		Coordinate<T> operator- (const Coordinate<T>& coordinate) const;
		Coordinate<T> operator- () const;
		Coordinate<T>& operator= (Coordinate<T> const & coordinate);

	public:
		Coordinate<T>& moveTo(Coordinate<T> coordinate);
		Coordinate<T>& offset(Coordinate<T> coordinate);
		Coordinate<T>& offset(const T x, const T y);

	public:
		T x;
		T y;
	};

	template<typename T>
	const Coordinate<T>& Coordinate<T>::operator+= (const Coordinate<T>& coordinate) 
	{
		x += coordinate.x;
		y += coordinate.y;
		return *this;
	}

	template<typename T>
	const Coordinate<T>& Coordinate<T>::operator-= (const Coordinate<T>& coordinate) 
	{
		x -= coordinate.x;
		y -= coordinate.y;
		return *this;
	}

	template<typename T>
	Coordinate<T> Coordinate<T>::operator+ (const Coordinate<T>& coordinate) const
	{
		Coordinate<T> temp(*this);
		temp += coordinate;
		return temp;
	}

	template<typename T>
	Coordinate<T> Coordinate<T>::operator- (const Coordinate<T>& coordinate) const
	{
		Coordinate<T> temp(*this);
		temp -= coordinate;
		return temp;
	}

	template<typename T>
	Coordinate<T> Coordinate<T>::operator- () const
	{
		Coordinate<T> temp(*this);
		temp.x = -temp.x;
		temp.y = -temp.y;
		return temp;
	}

	template<typename T>
	Coordinate<T>& Coordinate<T>::operator= (Coordinate<T> const & coordinate)
	{
		if(&coordinate != this)   
		{      
			x = coordinate.x;
			y = coordinate.y;
		}
		return *this;
	}

	template<typename T>
	Coordinate<T>& Coordinate<T>::moveTo(Coordinate<T> coordinate)
	{
		x = coordinate.x;
		y = coordinate.y;
		return *this;
	}

	template<typename T>
	Coordinate<T>& Coordinate<T>::offset(Coordinate<T> coordinate)
	{
		x += coordinate.x;
		y += coordinate.y;
		return *this;
	}

	template<typename T>
	Coordinate<T>& Coordinate<T>::offset(const T x, const T y)
	{
		this->x += x;
		this->y += y;
		return *this;
	}
}
#endif