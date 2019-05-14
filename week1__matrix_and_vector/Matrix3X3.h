#pragma once
#include "Vector3D.h"
class Matrix3X3
{
public:
	float value_[3][3];

	void print()
	{
		for (int row = 0; row < 3; row++)
		{
			for (int col = 0; col < 3; col++)
				std::cout << value_[row][col] << " ";
			
			std::cout << std::endl;
		}
		
	}
	//3x3 mulpy 3x1 (vector)  = 3x1 matrix (vector)
	template <typename T>
	Vector3D<T> multiply(const Matrix3X3& m, const Vector3D<T>& v)
	{
		Vector3D<T> ans;
		ans.x_ = m.value_[0][0] * v.x_ + m.value_[0][1] * v.y_ + m.value_[0][2] * v.z_;
		ans.y_ = m.value_[1][0] * v.x_ + m.value_[1][1] * v.y_ + m.value_[1][2] * v.z_;
		ans.z_ = m.value_[2][0] * v.x_ + m.value_[2][1] * v.y_ + m.value_[2][2] * v.z_;

		return ans;
	}
};