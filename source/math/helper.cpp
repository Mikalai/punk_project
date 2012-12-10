#include <algorithm>
#include "helper.h"
#include "root_find.h"

namespace Math
{
	const mat4 Translate(vec3 pos)
	{
		mat4 res;
		res[12] = pos[0];
		res[13] = pos[1];
		res[14] = pos[2];
		return res;
	}

	const mat4 ProjectionMatrix(float fovx, float aspect, float znear, float zfar)
	{
		float e = 1.0f / tanf(fovx / 2.0f);
		float aspectInv = 1.0f / aspect;
		float fovy = 2.0f * atanf(aspectInv / e);
		float xScale = 1.0f / tanf(0.5f * fovy);
		float yScale = xScale / aspectInv;
		mat4 res;
		float* m = &res[0];
		m[0*4 + 0] = xScale;
		m[0*4 + 1] = 0.0f;
		m[0*4 + 2] = 0.0f;
		m[0*4 + 3] = 0.0f;

		m[1*4 + 0] = 0.0f;
		m[1*4 + 1] = yScale;
		m[1*4 + 2] = 0.0f;
		m[1*4 + 3] = 0.0f;

		m[2*4 + 0] = 0.0f;
		m[2*4 + 1] = 0.0f;
		m[2*4 + 2] = (zfar + znear) / (znear - zfar);
		m[2*4 + 3] = -1.0f;

		m[3*4 + 0] = 0.0f;
		m[3*4 + 1] = 0.0f;
		m[3*4 + 2] = (2.0f * zfar * znear) / (znear - zfar);
		m[3*4 + 3] = 0.0f;
		return res;
	}

	const mat4 TargetCamera(vec3 eye, vec3 target, vec3 up)
	{
		// Builds a look-at style view matrix.
		// This is essentially the same matrix used by gluLookAt().
		vec3 zAxis = eye - target;
		zAxis.Normalize();

		vec3 xAxis = up.Cross(zAxis);
		xAxis.Normalize();

		vec3 yAxis = zAxis.Cross(xAxis);
		yAxis.Normalize();

		mat4 res;
		float* m = &res[0];

		m[0*4 + 0] = xAxis[0];
		m[1*4 + 0] = xAxis[1];
		m[2*4 + 0] = xAxis[2];
		m[3*4 + 0] = -xAxis.Dot(eye);

		m[0*4 + 1] = yAxis[0];
		m[1*4 + 1] = yAxis[1];
		m[2*4 + 1] = yAxis[2];
		m[3*4 + 1] = -yAxis.Dot(eye);

		m[0*4 + 2] = zAxis[0];
		m[1*4 + 2] = zAxis[1];
		m[2*4 + 2] = zAxis[2];
		m[3*4 + 2] = -zAxis.Dot(eye);

		m[0*4 + 3] = 0.0f;
		m[1*4 + 3] = 0.0f;
		m[2*4 + 3] = 0.0f;
		m[3*4 + 3] = 1.0f;
		return res;
	}

	const mat4 FreeCamera(vec3 eye, vec3 dir, vec3 up)
	{
		// Builds a look-at style view matrix.
		// This is essentially the same matrix used by gluLookAt().
		vec3 target = eye + dir;
		vec3 zAxis = eye - target;
		zAxis.Normalize();

		vec3 xAxis = up.Cross(zAxis);
		xAxis.Normalize();

		vec3 yAxis = zAxis.Cross(xAxis);
		yAxis.Normalize();

		mat4 res;
		float* m = &res[0];

		m[0*4 + 0] = xAxis[0];
		m[1*4 + 0] = xAxis[1];
		m[2*4 + 0] = xAxis[2];
		m[3*4 + 0] = -xAxis.Dot(eye);

		m[0*4 + 1] = yAxis[0];
		m[1*4 + 1] = yAxis[1];
		m[2*4 + 1] = yAxis[2];
		m[3*4 + 1] = -yAxis.Dot(eye);

		m[0*4 + 2] = zAxis[0];
		m[1*4 + 2] = zAxis[1];
		m[2*4 + 2] = zAxis[2];
		m[3*4 + 2] = -zAxis.Dot(eye);

		m[0*4 + 3] = 0.0f;
		m[1*4 + 3] = 0.0f;
		m[2*4 + 3] = 0.0f;
		m[3*4 + 3] = 1.0f;
		return res;
	}

	const mat3 NormalMatrixFromWorldView(const mat4& worldView)
	{
		mat3 res;
		float* m = res;
		m[0*3 + 0] = worldView[0*4 + 0];
		m[0*3 + 1] = worldView[0*4 + 1];
		m[0*3 + 2] = worldView[0*4 + 2];

		m[1*3 + 0] = worldView[1*4 + 0];
		m[1*3 + 1] = worldView[1*4 + 1];
		m[1*3 + 2] = worldView[1*4 + 2];

		m[2*3 + 0] = worldView[2*4 + 0];
		m[2*3 + 1] = worldView[2*4 + 1];
		m[2*3 + 2] = worldView[2*4 + 2];

		res = res.Inversed().Transposed();

		return res;
	}

	const mat4 RotationMatrixFromQuaternion(const quat& q)
	{
		float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
		x2 = q[0] + q[0];
		y2 = q[1] + q[1];
		z2 = q[2] + q[2];
		xx = q[0] * x2;   xy = q[0] * y2;   xz = q[0] * z2;
		yy = q[1] * y2;   yz = q[1] * z2;   zz = q[2] * z2;
		wx = q[3] * x2;   wy = q[3] * y2;   wz = q[3] * z2;
		mat4 mat;
		float* m = &mat[0];
		m[0*4 + 0]=1.0f-(yy+zz); m[0*4 + 1]=xy-wz;        m[0*4 + 2]=xz+wy;
		m[1*4 + 0]=xy+wz;        m[1*4 + 1]=1.0f-(xx+zz); m[1*4 + 2]=yz-wx;
		m[2*4 + 0]=xz-wy;        m[2*4 + 1]=yz+wx;        m[2*4 + 2]=1.0f-(xx+yy);

		m[0*4 + 3] = m[1*4 + 3] = m[2*4 + 3] = 0;
		m[3*4 + 0] = m[3*4 + 1] = m[3*4 + 2] = 0;
		m[3*4 + 3] = 1;
		return mat;
	}

	const vec3 CalculateAverage(const float* points, int count, unsigned point_size)
	{
		vec3 center;

		for (int i = 0; i < count; ++i)
		{
			const vec3 v(points[i*(point_size/sizeof(float)) + 0], points[i*(point_size/sizeof(float)) + 1], points[i*(point_size/sizeof(float)) + 2]);
			center += v;
		}

		center /= (float)count;

		return center;
	}

	const mat3 CreateCovarianceMatrix(const float* points, int count, unsigned point_size)
	{
		//	find average of the vertices
		vec3 center = CalculateAverage(points, count, point_size);

		//	find covariance matrix
		mat3 res;
		res.Zerofy();

		for (int i = 0; i < count; ++i)
		{
			const vec3 v(points[i*(point_size/sizeof(float)) + 0], points[i*(point_size/sizeof(float)) + 1], points[i*(point_size/sizeof(float)) + 2]);
			res += MultTransposed((v - center), (v - center));
		}

		res /= (float)count;

		return res;
	}

	bool DiagonalizeMatrix(const mat3& m, mat3& res)
	{
		vec3 v;
		if (!EigenValues(m, v))
			return false;

		res.Identity();
		res[0] = v[0];
		res[4] = v[1];
		res[8] = v[2];

		return true;
	}

	bool EigenValues(const mat3& m, vec3& res)
	{
		double a = double(1);
		double b = -(m[0] + m[4] + m[8]);
		double c = (m[0]*m[4] + m[0]*m[8] + m[4]*m[8] - m[7]*m[5] - m[1]*m[3] - m[2]*m[6]);
		double d = -(m[0]*m[4]*m[8] - m[0]*m[7]*m[5] - m[1]*m[3]*m[8] + m[1]*m[6]*m[5] + m[2]*m[3]*m[7] - m[2]*m[6]*m[4]);

		double in[] = {d, c, b, a};
		double out[3];
		auto result = SolveCubic(in, out);
		if (result == RootFindResult::RESULT_NO_SOLUTION)
			return false;

		std::sort(out, out+3);

		res[0] = (float)out[2];
		res[1] = (float)out[1];
		res[2] = (float)out[0];

		return true;
	}

	bool EigenVectors(const mat3& m, const vec3& value, vec3 res[3])
	{
		for (int v = 0; v < 3; ++v)
		{
			//	use inverse power method
			vec3 bb0(1,1,1);
			vec3 bb = bb0;
			float d;
			do
			{
				bb0 = bb;
				bb = (m - (value[v] + 0.001f) * mat3::CreateIdentity()).Inversed() * bb;
				bb.Normalize();	
				d = fabs(1.0f + bb.Dot(bb0));
			}
			while (d > 1e-5 && fabs(d - 2.0f) > 1e-5);

			res[v] = bb;
			out_message() << res[v].ToString() << std::endl;

		}
		return true;
	}

	bool CalculateNativeAxis(const float* points, int count, unsigned vertex_size, vec3& r, vec3& s, vec3& t)
	{	
		//	find covariance matrix
		mat3 c = CreateCovarianceMatrix(points, count, vertex_size);

		//	find eigen values of the covariance matrix
		Math::vec3 eigen_values;
		if (!EigenValues(c, eigen_values))
			return (out_error() << "Can't find eigen values for matrix " << c.ToString() << std::endl, false);

		//	find eigen vectors of the covariance matrix
		Math::vec3 eigen_vectors[3];
		if (!EigenVectors(c, eigen_values, eigen_vectors))
			return (out_error() << "Can't find eigen values for matrix " << c.ToString() << " with eigen values " << eigen_values.ToString() << std::endl, false);

		r = eigen_vectors[0];
		s = eigen_vectors[1];
		t = eigen_vectors[2];

		mat3 a;
		a.SetColumn(0, r);
		a.SetColumn(1, s);
		a.SetColumn(2, t);

		out_message() << "Matrix a: " << a.ToString() << std::endl;

		mat3 tt = a.Transposed() * c * a;

		out_message() << "Matrix tt: " << tt.ToString() << std::endl;
		return true;
	}

	bool YawPitchRollToUpDirection(float yaw, float pitch, float roll, vec3& up, vec3& dir)
	{
		float cos_yaw = cos(yaw);
		float cos_pitch = cos(pitch);
		float cos_roll = cos(roll);
		float sin_yaw = sin(yaw);
		float sin_pitch = sin(pitch);
		float sin_roll = sin(roll);

		dir.Set(sin_yaw * cos_pitch, sin_pitch, cos_pitch * -cos_yaw);
		up.Set(-cos_yaw * sin_roll - sin_yaw * sin_pitch * cos_roll, cos_pitch * cos_roll, -sin_yaw * sin_roll - sin_pitch * cos_roll * -cos_yaw);

		up.Normalize();
		dir.Normalize();
		return true;
	}
}
