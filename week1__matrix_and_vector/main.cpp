#include <iostream>
#include "Vector2D.h"
#include "Vector3D.h"
#include "Matrix3X3.h"
#include "Matrix2X2.h"
int main()
{
	/// Vector2D 확인코드

	//Vector2D<float> v0;
	//v0.assing(1.0f, 0.0f);
	//v0.print();
	//Vector2D<float> v1;
	//v1.assing(0.0f, 1.0f);
	//v1.print();
	//v0 += v1;
	//v0.print();
	//std::cout << "Dot product = " << dotProduct<float>(v0, v1) << std::endl;

	Matrix3X3 m;
	int count = 0;
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
			m.value_[row][col] = (float)count++;
	}

	m.print();

	Vector3D<float> mv(1, 2, 3);
	Vector3D<float> res;
	res = m.multiply(m, mv);
	res.print();


	///Matrix2X2 확인코드

	//Matrix2X2<float> matrix(1, 0, 0, 1);
	//Vector2D<float> car(1.0f, 2.0f);
	//Vector2D<float> ans = matrix.multiplyWith(car);
	//ans.print();
	//

	/// 백터곱 확인코드
	//Vector3D<float> my_vector_1, my_vector_2;
	//my_vector_1.x_ = 0.0f;
	//my_vector_1.y_ = 0.0f;
	//my_vector_1.z_ = 9.0f;

	//my_vector_2.x_ = 0.0f;
	//my_vector_2.y_ = 1.0f;
	//my_vector_2.z_ = 0.0f;

	//Vector3D<float> cross_v1_v2 = crossProduct(my_vector_1, my_vector_2);

	//cross_v1_v2.print();
	//for (int d = 0; d < 3; d++)
	//	std::cout << cross_v1_v2.values_[d] << std::endl;


	return 0;
}