#pragma once

template <typename T>
class Vector2D
{
public:
	T x_, y_;

	Vector2D()
		:x_(0.0), y_(0.0)
	{}
	Vector2D(const T& _x, const T& _y)
		:x_(_x), y_(_y)
	{}


	void assing(const T& _x, const T& _y)
	{
		x_ = _x;
		y_ = _y;
	}

	T getMagnitude()
	{
		return sqrt(x_*x_ + y_ * y_);
	}

	void getMagnitude(T& mag)
	{
		mag = sqrt(x_*x_ + y_ * y_);
	}

	void normalize()
	{
		const T magnitude = getMagnitude();
		x_ /= magnitude;
		y_ /= magnitude;
	}

	Vector2D<T> getNormalized()
	{
		const T magnitude = getMagnitude();
		return Vector2D(x_ / magnitude, y_ / magnitude);
	}

	void print()
	{
		std::cout << x_ << " " << y_ << std::endl;
	}

	Vector2D& operator +=(const Vector2D& rhs)
	{
		x_ += rhs.x_;
		y_ += rhs.y_;

		return *this;
	}


};

template <typename T>
T dotProduct(const Vector2D<T>& v0, const Vector2D<T>& v1)  //½ºÄ®¶ó°ö (³»Àû)
	{
		return v0.x_ * v1.x_ + v0.y_ *v1.y_;
	}