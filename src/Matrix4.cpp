#include "Matrix4.h"

namespace tetris
{
	const Matrix4 Matrix4::Zero;
	const Matrix4 Matrix4::I(1, 0, 0, 1);

	const Matrix4& getMatForRot90()
	{
		static Matrix4 s_mat(0, -1, 1, 0);
		return s_mat;
	}
}