#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Coordinate.h"

namespace geometric {

	//Rectangle assumes a left-handed coordinate system
	template<typename T>
	class Rectangle
	{
	public:
		Rectangle();
		Rectangle(Coordinate<T> topLeft, Coordinate<T> bottomRight);
		Rectangle(const T topLeftX, const T topLeftY, const T bottomRightX, const T bottomRightY);
		Rectangle(const Rectangle<T>& rectangle);

	public:
		~Rectangle();

	public:
		Rectangle<T>& operator= (Rectangle<T> const & rectangle);

	public:
		// Moves rectangles' top-Left corner to position without
		// resizing its width and height.
		Rectangle<T>& moveTo(Coordinate<T> position);

		//Sets new top-left and bottom-Right coordinates
		Rectangle<T>& resize(const Coordinate<T>& topLeft, const Coordinate<T>& bottomRight);

		//Sets new width and height without moving its topleft position
		Rectangle<T>& resize(const T width, const T height);

		// Moves rectangle relative to the position,
		// preserving width and height.
		Rectangle<T>& offset(Coordinate<T> coordinate);
		Rectangle<T>& offset(const T x, const T y);


		// Checks if the rectangle overlaps another rectangle
		bool overlap(const Rectangle<T>& rectangle) const;
		// overlap line
		//bool overlap(const Line<T>& line) const;

		Coordinate<T>& topLeft();
		Coordinate<T>& bottomRight();
		const Coordinate<T>& topLeft() const;
		const Coordinate<T>& bottomRight() const;

	private:
		Coordinate<T> m_topLeft;
		Coordinate<T> m_bottomRight;
	};

	template<typename T>
	Rectangle<T>::Rectangle() :
		m_topLeft(Coordinate<T>()),
		m_bottomRight(Coordinate<T>())
	{
	}

	template<typename T>
	Rectangle<T>::Rectangle(Coordinate<T> topLeft, Coordinate<T> bottomRight):
		m_topLeft(topLeft),
		m_bottomRight(bottomRight)
	{
	}

	template<typename T>
	Rectangle<T>::Rectangle(const Rectangle<T>& rectangle)
	{
		*this = rectangle;
	}

	template<typename T>
	Rectangle<T>::Rectangle(const T topLeftX, const T topLeftY, const T bottomRightX, const T bottomRightY) :
		m_topLeft(Coordinate<T>(topLeftX, topLeftY)),
		m_bottomRight(Coordinate<T>(bottomRightX, bottomRightY))
	{
	}

	template<typename T>
	Rectangle<T>::~Rectangle()
	{
	}

	template<typename T>
	Rectangle<T>& Rectangle<T>::operator= (Rectangle<T> const & rectangle)
	{
		if(&rectangle != this)   
		{      
			m_topLeft = rectangle.m_topLeft;
			m_bottomRight = rectangle.m_bottomRight;
		}
		return *this;
	}

	// Moves rectangles' top-Left corner to position without
	// resizing its width and height.
	template<typename T>
	Rectangle<T>& Rectangle<T>::moveTo(Coordinate<T> coordinate)
	{
		m_bottomRight += coordinate - m_topLeft;
		m_topLeft = coordinate;
		return *this;
	}

	//Sets new top-left and bottom-Right coordinates
	template<typename T>
	Rectangle<T>& Rectangle<T>::resize(const Coordinate<T>& topLeft, const Coordinate<T>& bottomRight)
	{
		m_topLeft = topLeft;
		m_bottomRight = bottomRight;
		return *this;
	}

	//Sets new width and height without moving its topleft position
	template<typename T>
	Rectangle<T>& Rectangle<T>::resize(const T width, const T height)
	{
		m_bottomRight.x = m_topLeft.x + width;
		m_bottomRight.y = m_topLeft.y + height;
	}

	// Moves rectangle relative to the position,
	// preserving width and height.
	template<typename T>
	Rectangle<T>& Rectangle<T>::offset(Coordinate<T> coordinate)
	{
		m_topLeft += coordinate;
		m_bottomRight += coordinate;
		return *this;
	}

	template<typename T>
	Rectangle<T>& Rectangle<T>::offset(const T x, const T y)
	{
		m_topLeft.x += x;
		m_topLeft.y += y;
		m_bottomRight.x += x;
		m_bottomRight.y += y;
		return *this;
	}

	// Checks if the rectangle overlaps another rectangle
	template<typename T>
	bool Rectangle<T>::overlap(const Rectangle<T>& rectangle) const
	{
		if ((rectangle.topLeft().x < m_bottomRight.x) &&
			(rectangle.topLeft().y < m_bottomRight.y) &&
			(rectangle.bottomRight().x > m_topLeft.x) &&
			(rectangle.bottomRight().y > m_topLeft.y))
			return true;

		return false;
	}

	template<typename T>
	Coordinate<T>& Rectangle<T>::topLeft()
	{
		return m_topLeft;
	}

	template<typename T>
	Coordinate<T>& Rectangle<T>::bottomRight()
	{
		return m_bottomRight;
	}

	template<typename T>
	const Coordinate<T>& Rectangle<T>::topLeft() const
	{
		return m_topLeft;
	}

	template<typename T>
	const Coordinate<T>& Rectangle<T>::bottomRight() const
	{
		return m_bottomRight;
	}

}

#endif