#pragma once
template <typename T>
class Vector3D
{
public:

	union
	{
		struct { T x_, y_, z_; };
		struct { T v0_, v1_, v2_; };
		struct { int i_, j_, k_; };
		T values_[3];
	};


	Vector3D()
		:x_(0.0), y_(0.0), z_(0.0)
	{

	}

	Vector3D(const T& _x, const T& _y, const T& _z)
		:x_(_x), y_(_y), z_(_z)
	{}

	void assing(const T& _x, const T& _y, const T& _z)
	{
		x_ = _x;
		y_ = _y;
		z_ = _z;
	}

	T getMagnitude()
	{
		return sqrt(x_*x_ + y_ * y_ + z_ * z_);
	}

	void getMagnitude(T& mag)
	{
		mag = sqrt(x_*x_ + y_ * y_ + z_ * z_);
	}

	void normalize()
	{
		const T magnitude = getMagnitude();
		x_ /= magnitude;
		y_ /= magnitude;
		z_ /= magnitude;
	}

	Vector2D<T> getNormalized()
	{
		const T magnitude = getMagnitude();
		return Vector2D<T>(x_ / magnitude, y_ / magnitude, z_ / magnitude);
	}

	void print()
	{
		std::cout << x_ << " " << y_ << " " << z_ << std::endl;
	}

	Vector3D& operator +=(const Vector3D& rhs)
	{
		x_ += rhs.x_;
		y_ += rhs.y_;
		z_ += rhs.z_;

		return *this;
	}


};

/////백터곱
template<class T> Vector3D<T> crossProduct(const Vector3D<T>& v0, const Vector3D<T>& v1)
{
	return Vector3D<T>(v0.y_*v1.z_ - v0.z_*v1.y_, v0.z_*v1.x_ - v0.x_*v1.z_, v0.x_*v1.y_ - v0.y_*v1.x_);
}


// 내적의 리턴은 실수형이지만 백터곱은 백터가나온다.
//float dotProduct(const Vector3D& v0, const Vector3D& v1)  //스칼라곱 (내적)
//{
//	return v0.x_ * v1.x_ + v0.y_ *v1.y_ + v0.z_ * v1.z_;
//}