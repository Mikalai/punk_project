#include <algorithm>
#include "helper.h"
#include "root_find.h"

namespace Math
{
    float DegToRad(float value)
    {
        auto res = value / 45.0 * atan(1);
        return res;
    }

    float RadToDeg(float value)
    {
        auto res = value / atan(1) * 45.0;
        return res;
    }

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

    const vec3 CalculateAverage(const std::vector<vec3>& points)
	{
		vec3 center;

        for (auto v : points)
			center += v;

        center /= (float)points.size();

		return center;
	}

    const mat3 CreateCovarianceMatrix(const std::vector<vec3>& points)
	{
		//	find average of the vertices
        vec3 center = CalculateAverage(points);

		//	find covariance matrix
		mat3 res;
		res.Zerofy();

        for (auto v : points)
		{
			res += MultTransposed((v - center), (v - center));
		}

        res /= (float)points.size();

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
				d = fabs(fabs(bb.Dot(bb0)) - 1.0f);
			}
			while (d > 1e-5);

			res[v] = bb;
			out_message() << res[v].ToString() << std::endl;

		}
		return true;
	}

	bool SymmetricEigenSystem(const mat3& m, vec3& value, mat3& r)
	{
		const int max_sweep = 32;
		const float epsilon = 1.0e-10f;
		float m11 = m.At(0,0);
		float m12 = m.At(0,1);
		float m13 = m.At(0,2);
		float m22 = m.At(1,1);
		float m23 = m.At(1,2);
		float m33 = m.At(2,2);

		r.Identity();

        for (int a = 0; a < max_sweep; ++a)
		{
			if ((Abs(m12) < epsilon) && (Abs(m13) < epsilon) && (Abs(m23) < epsilon))
				break;

			//	annihilate 1 2
			if (m12 != 0.0f)
			{
				float u = (m22 - m11) * 0.5f / m12;
				float u2 = u*u;
				float u2p1 = u2 + 1.0f;
				float t = (u2p1 != u2) ? ((u < 0.0f) ? -1.0f : 1.0f) * (sqrt(u2p1) - fabs(u)) : 0.5f / u;
				float c = 1.0f / sqrt(t*t + 1.0f);
				float s = c * t;

				m11 -= t * m12;
				m22 += t * m12;
                m12 = 0.0f;

				float temp = c*m13 - s * m23;
				m23 = s * m13 + c * m23;
				m13 = temp;

				for (int i = 0; i < 3; ++i)
				{
					float temp = c * r.At(i, 0) - s * r.At(i,1);
					r.At(i,1) = s * r.At(i,0) + c * r.At(i,1);
					r.At(i,0) = temp;
				}
			}

			//	annihilate 1 3
			if (m13 != 0.0f)
			{
				float u = (m33 - m11) * 0.5f / m13;
				float u2 = u*u;
				float u2p1 = u2 + 1.0f;
				float t = (u2p1 != u2) ? ((u < 0.0f) ? -1.0f : 1.0f) * (sqrt(u2p1) - fabs(u)) : 0.5f / u;
				float c = 1.0f / sqrt(t*t + 1.0f);
				float s = c * t;

				m11 -= t * m13;
				m33 += t * m13;
                m13 = 0.0f;

				float temp = c * m12 - s * m23;
				m23 = s * m12 + c * m23;
				m12 = temp;

				for (int i = 0; i < 3; ++i)
				{
					float temp = c * r.At(i, 0) - s * r.At(i, 2);
					r.At(i, 2) = s * r.At(i, 0) + c * r.At(i, 2);
					r.At(i, 0) = temp;
				}
			}

			//	annihilate 2 3
			if (m23 != 0.0f)
			{
				float u = (m33 - m22) * 0.5f / m23;
				float u2 = u*u;
				float u2p1 = u2 + 1.0f;
				float t = (u2p1 != u2) ? ((u < 0.0f) ? -1.0f : 1.0f) * (sqrt(u2p1) - fabs(u)) : 0.5f / u;
				float c = 1.0f / sqrt(t*t + 1.0f);
				float s = c * t;

				m22 -= t * m23;
				m33 += t * m23;
                m23 = 0.0f;

				float temp = c * m12 - s * m13;
				m13 = s * m12 + c * m13;
				m12 = temp;

				for (int i = 0; i < 3; ++i)
				{
					float temp = c * r.At(i, 1) - s * r.At(i, 2);
					r.At(i, 2) = s * r.At(i, 1) + c * r.At(i, 2);
					r.At(i, 1) = temp;
				}
			}
		}

		value.Set(m11, m22, m33);
		return true;
	}

    bool CalculateNativeAxis(const std::vector<vec3>& points, vec3& r, vec3& s, vec3& t)
	{	
		//	find covariance matrix
        mat3 c = CreateCovarianceMatrix(points);

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

    void CalculateTBN(const vec3& p1, const vec3& p2, const vec3& p3,
        const vec2& tex1, const vec2& tex2, const vec2& tex3,
        vec3& tng, vec3& btn, vec3& nrm, float& mm)
    {
        nrm = CalculateNormal(p1, p2, p3);
        Matrix<float> s(2,2);
        s.At(0,0) = (tex2 - tex1)[0];
        s.At(0,1) = (tex2 - tex1)[1];
        s.At(1,0) = (tex3 - tex1)[0];
        s.At(1,1) = (tex3 - tex1)[1];

        Matrix<float> q(2, 3);
        q.At(0,0) = (p2 - p1)[0];
        q.At(0,1) = (p2 - p1)[1];
        q.At(0,2) = (p2 - p1)[2];
        q.At(1,0) = (p3 - p1)[0];
        q.At(1,1) = (p3 - p1)[1];
        q.At(1,2) = (p3 - p1)[2];

        Matrix<float> tb = s.Inversed()*q;

        tng[0] = tb.At(0,0);
        tng[1] = tb.At(0,1);
        tng[2] = tb.At(0,2);

        btn[0] = tb.At(1,0);
        btn[1] = tb.At(1,1);
        btn[2] = tb.At(1,2);

        if (btn.Length()==0 || tng.Length() == 0)
        {
            nrm.Normalize();
            mm = 1;
        }
        else
        {
            //
            //	gram-shmidt normalization
            //
            nrm.Normalize();
            tng = (tng - tng.Dot(nrm)*nrm).Normalized();
            btn = (btn - btn.Dot(nrm)*nrm - btn.Dot(tng)*tng).Normalized();

            Matrix<float> m(3,3);
            m.At(0,0) = tng[0]; m.At(0,1) = tng[1]; m.At(0,2) = tng[2];
            m.At(1,0) = btn[0]; m.At(1,1) = btn[1]; m.At(1,2) = btn[2];
            m.At(2,0) = nrm[0]; m.At(2,1) = nrm[1]; m.At(2,2) = nrm[2];

            mm = m.Determinant();/**/
        }
    }

    const vec3 CalculateNormal(const vec3& p1, const vec3& p2, const vec3& p3)
    {
        return ((p2-p1).Cross(p3-p1)).Normalized();
    }
}
