#ifndef _H_HELPER_MATH
#define _H_HELPER_MATH

#include "../config.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"
#include "mat3.h"
#include "smart_matrix.h"
#include "quat.h"

namespace Math
{
	PUNK_ENGINE mat4 ProjectionMatrix(float fov, float aspect, float zNear, float zFar);
    PUNK_ENGINE mat4 OrthoMatrix(float width, float height, float bottom, float top);
    PUNK_ENGINE mat4 Rotate(vec4 v);
    PUNK_ENGINE mat4 Translate(vec3 pos);
    PUNK_ENGINE mat4 Scale(vec3 scale);
    PUNK_ENGINE mat4 TargetCamera(vec3 eye, vec3 pos, vec3 up);
    PUNK_ENGINE mat4 FreeCamera(vec3 pos, vec3 dir, vec3 up);
	PUNK_ENGINE mat4 RotationMatrixFromQuaternion(const quat& q);
    PUNK_ENGINE mat3 NormalMatrixFromWorldView(const mat4& worldView);

	template<class T> 
	Vector3<T> CalculateNormal(const Vector3<T>& p1, const Vector3<T>& p2, const Vector3<T>& p3)
	{
		return ((p2-p1).Cross(p3-p1)).Normalize();
	}

	template<class T>
	static void CalculateTBN(const Vector3<T>& p1, const Vector3<T>& p2, const Vector3<T>& p3, 
		const Vector2<T>& tex1, const Vector2<T>& tex2, const Vector2<T>& tex3, 
		Vector3<T>& tng, Vector3<T>& btn, Vector3<T>& nrm, T& mm)
	{
		nrm = CalculateNormal(p1, p2, p3);
		Matrix<T> s(2,2);
		s.At(0,0) = (tex2 - tex1)[0];
		s.At(0,1) = (tex2 - tex1)[1];
		s.At(1,0) = (tex3 - tex1)[0];
		s.At(1,1) = (tex3 - tex1)[1];

		Matrix<T> q(2, 3);
		q.At(0,0) = (p2 - p1)[0];
		q.At(0,1) = (p2 - p1)[1];
		q.At(0,2) = (p2 - p1)[2];
		q.At(1,0) = (p3 - p1)[0];
		q.At(1,1) = (p3 - p1)[1];
		q.At(1,2) = (p3 - p1)[2];

		Matrix<T> tb = s.Inversed()*q;

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
			tng = (tng - tng.Dot(nrm)*nrm).Normalize();
			btn = (btn - btn.Dot(nrm)*nrm - btn.Dot(tng)*tng).Normalize();
					
			Matrix<T> m(3,3);
			m.At(0,0) = tng[0]; m.At(0,1) = tng[1]; m.At(0,2) = tng[2];
			m.At(1,0) = btn[0]; m.At(1,1) = btn[1]; m.At(1,2) = btn[2];
			m.At(2,0) = nrm[0]; m.At(2,1) = nrm[1]; m.At(2,2) = nrm[2];
			
			mm = m.Determinant();/**/
		}
	}

}

#endif 
