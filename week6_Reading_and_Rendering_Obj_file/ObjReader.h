#pragma once

#include <iostream>
/*
Authored by Prof. Jeong-Mo Hong, CSE Dongguk University
for Introduction to Computer Graphics, 2017 Spring
*/


#include <fstream>
#include <vector>
#include "Vector3.h"
#include <algorithm>

class OBJReader
{
public:
	std::vector<Vector3<float> > pos_stack_;
	std::vector<Vector3<unsigned int> > ix_stack_;
	//Note: vector push_back is slow   백터는 느리기때문에 추천하지않는다.
	//Note: use unsigned int for indices

	void readObj(const char* filename)
	{
		using namespace std;

		std::cout << "Start reading OBJ file " << filename << std::endl;

		// to check if this obj file contains vt or vn data 
		bool read_vt(false), read_vn(false);

		ifstream file(filename);

		// check if file is opened correctly
		if (file.is_open() == false) {
			std::cout << filename << " does not exist. Program terminated." << std::endl; exit(-1);
		}

		char c[255]; //file read buffer

		while (true)
		{
			file >> c;

			if (file.eof() != 0) break;						// finish reading if file is ended

			if (strcmp(c, "#") == 0) file.getline(c, 255);  // comments (less than 255 characters)
			else if (strcmp(c, "v") == 0) // vertices
			{
				float x, y, z;
				file >> x >> y >> z;

				//std::cout << x << " " << y << " " << z << std::endl;
				pos_stack_.push_back(Vector3<float>(x, y, z));  //slow
			}
			else if (strcmp(c, "vt") == 0)
			{
				read_vt = true;

				float u, v;
				file >> u >> v;

				//TODO: save texture coordinates

			}
			else if (strcmp(c, "vn") == 0)
			{
				read_vn = true;

				float nx, ny, nz;
				file >> nx >> nz >> ny;

				//TODO: save normal vectors
			}
			else if (strcmp(c, "f") == 0)
			{
				int v[3], vt[3], vn[3];
				if (read_vt == true && read_vn == true)
				{
					for (int i = 0; i < 3; i++)
					{
						file >> v[i]; file.get(c, 2);
						file >> vt[i]; file.get(c, 2);
						file >> vn[i];

						v[i]--;
						vt[i]--;
						vn[i]--;
					}
				}
				else if (read_vt == false && read_vn == true)
				{
					for (int i = 0; i < 3; i++)
					{
						file >> v[i]; file.get(c, 2); file.get(c, 2);
						file >> vn[i];
						v[i]--;
						vn[i]--;
					}
				}
				else if (read_vt == false && read_vn == false)
				{
					for (int i = 0; i < 3; i++)
					{
						file >> v[i];
						v[i]--;
					}
				}

				//std::cout << v[0] << " " << v[1] << " " << v[2] << std::endl;
				ix_stack_.push_back(Vector3<unsigned int>(v[0], v[1], v[2]));

				if (read_vt == true) {
					//TODO
				}

				if (read_vn == true) {
					//TODO
				}
			}
		}

		file.clear();
		file.close();

		std::cout << "Reading complete." << std::endl;
		std::cout << "# of vertices " << pos_stack_.size() << std::endl;
		std::cout << "# of triangles " << ix_stack_.size() << std::endl;

		//TODO: move to min corner to origin

		//TODO: scale down the BB to a unit cube		
	}

	void scaleToUnitBox()
	{
		using namespace std;
		const float fmin = std::numeric_limits<float>::min();
		const float fmax = numeric_limits<float>::max();
		//BB
		Vector3<float> bb_max(fmin, fmin, fmin);
		Vector3<float> bb_min(fmax, fmax, fmax);

		for (int i = 0; i < pos_stack_.size(); i++)
		{
			const Vector3<float>& vp = pos_stack_[i];

			bb_max.x_ = std::max(vp.x_, bb_max.x_);
			bb_max.y_ = std::max(vp.y_, bb_max.y_);
			bb_max.z_ = std::max(vp.z_, bb_max.z_);

			bb_min.x_ = std::min(vp.x_, bb_min.x_);
			bb_min.y_ = std::min(vp.y_, bb_min.y_);
			bb_min.z_ = std::min(vp.z_, bb_min.z_);
		}
		bb_min.print();
		cout << "  ";
		bb_max.print();

		//move min corner of BB to the origin
		for (int i = 0; i < pos_stack_.size(); i++)
		{
			Vector3<float>& vp = pos_stack_[i];

			vp.x_ -= bb_min.x_;
			vp.x_ -= bb_min.x_;
			vp.x_ -= bb_min.x_;
		}
		const float dx = bb_max.x_ - bb_min.x_;
		const float dy = bb_max.y_ - bb_min.y_;
		const float dz = bb_max.z_ - bb_min.z_;

		const float dm = max(max(dx, dy), dz);
		const double inv_dm = 1.0 / (double)dm;

		//scale the longest edge to unit (1) length
		for (int i = 0; i < pos_stack_.size(); i++)
		{
			Vector3<float>& vp = pos_stack_[i];

			vp.x_ *= inv_dm;
			vp.y_ *= inv_dm;
			vp.z_ *= inv_dm;
		}
	}

	void dump()
	{
		for (int i = 0; i < pos_stack_.size(); i++)
		{
			pos_stack_[i].print();
			std::cout << std::endl;
		}

		// scale down the BB to a unit cube
		for (int i = 0; i < pos_stack_.size(); i++)
		{
			ix_stack_[i].print();
			std::cout << std::endl;
		}
	}
};
