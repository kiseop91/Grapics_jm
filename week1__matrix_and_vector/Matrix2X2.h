#pragma once
template<class T>
class Matrix2X2
{
public:
	T v00_, v01_;
	T v10_, v11_;

	Matrix2X2(const T& _v00, const T& _v01, const T& _v10, const T& _v11)
		: v00_(_v00), v01_(_v01), v10_(_v10), v11_(_v11)
	{
	}

	Vector2D<T> multiplyWith(const Vector2D<T>& vec)
	{
		Vector2D<T> vec_ans;
		vec_ans.x_ = v00_ * vec.x_ + v01_ * vec.y_;
		vec_ans.y_ = v10_ * vec.x_ + v11_ * vec.y_;

		return vec_ans;
	}
};
