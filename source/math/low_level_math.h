/*
File: LowLevelMath.h
Author: Abramau Mikalaj
Description: Some math functions
*/

#ifndef _H_LOW_LEVEL_MATH
#define _H_LOW_LEVEL_MATH

#include <string.h>
#include <limits>
#include "helper.h"
#include "vec3.h"
#include "vec2.h"

namespace Math
{
	static float threshold = std::numeric_limits<float>::epsilon();

	inline float glMin2D(float a, float b)
	{
		return a < b ? a : b;
	}
	inline float glMax2D(float a, float b)
	{
		return a > b ? a : b;
	}

	inline float glMin3D(float a, float b, float c)
	{
		return a < b ? (a < c ? a : c) : (b < c ? b : c);
	}
	inline float glMax3D(float a, float b, float c)
	{
		return a > b ? (a > c ? a : c) : (b > c ? b : c);
	}

	inline void glCreatePoint3(float* out, float x, float y, float z)
	{
		out[0] = x;
		out[1] = y;
		out[2] = z;
	}

	inline float* glNegate3fv(float* out, const float* const v)
	{
		out[0] = -v[0];
		out[1] = -v[1];
		out[2] = -v[2];
		return out;
	}

	inline float* glSumVector3fv(float* out, const float* const a, const float* const b)
	{
		out[0] = a[0]+b[0];
		out[1] = a[1]+b[1];
		out[2] = a[2]+b[2];
		return out;
	}

	inline float* glSubVector3fv(float* out, const float* const a, const float* const b)
	{
		out[0] = a[0] - b[0];
		out[1] = a[1] - b[1];
		out[2] = a[2] - b[2];
		return out;
	}

	inline float* glMulVector3fv(float* out, const float* const a, float s)
	{
		out[0] = a[0]*s;
		out[0] = a[1]*s;
		out[0] = a[2]*s;
		return out;
	}

	inline float glLength3fv(const float * const v)
	{
		return sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
	}

	inline float glLength4fv(const float * const v)
	{
		return sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]+v[3]*v[3]);
	}

	inline float* glCrossProduct3fv(float* out, const float * const a, const float * const b)
	{
		float res[3];
		res[0] = a[1] * b[2] - a[2] * b[1];
		res[1] = a[2] * b[0] - a[0] * b[2];
		res[2] = a[0] * b[1] - a[1] * b[0];
		memcpy(out, res, sizeof(res));
		return out;
	}

	inline float* glTransform3fv(float* out, const float * const m, const float* const v)
	{
		float res[3];
		res[0] = m[0]*v[0] + m[4]*v[1] + m[8]*v[2] + m[12];
		res[1] = m[1]*v[0] + m[5]*v[1] + m[9]*v[2] + m[13];
		res[2] = m[3]*v[0] + m[6]*v[1] + m[10]*v[2] + m[14];
		memcpy(out, res, sizeof(res));
		return out;
	}

	inline float glDotProduct3fv(const float* const a, const float* const b)
	{
		return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
	}

	inline float glAngle3fv(const float* v1, const float* v2)
	{
		return glDotProduct3fv(v1, v2) / (glLength3fv(v1)*glLength3fv(v2));
	}

	inline bool glClipSegment(float Min, float Max, float a, float b, float d, float* t0, float* t1)
	{
		if (fabs(d) < threshold)
		{
			if (d > 0.0f)
			{
				return !(b < Min || a > Max);
			}
			else
			{
				return !(a < Min || b > Max);
			}
		}

		float u0, u1;

		u0 = (Min - a) / (d);
		u1 = (Max - a) / (d);

		if (u0 > u1)
		{
			float temp = u0;
			u0 = u1;
			u1 = temp;
		}

		if (u1 < *t0 || u0 > *t1)
		{
			return false;
		}

		*t0 = glMax2D(u0, *t0);
		*t1 = glMin2D(u1, *t1);

		if (*t1 < *t0)
		{
			return false;
		}

		return true;
	}

	inline bool glClipSegment3D(const float* A, const float* B, const float* min, const float* max)
	{
		float t0 = 0.0f, t1 = 1.0f;
//		float S[3] = {A[0], A[1], A[2]};
		float D[3] = {B[0]-A[0], B[1]-A[1], B[2]-A[2]};

		if (!glClipSegment(min[0], max[0], A[0], B[0], D[0], &t0, &t1))
		{
			return false;
		}

		if (!glClipSegment(min[1], max[1], A[1], B[1], D[1], &t0, &t1))
		{
			return false;
		}

		if (!glClipSegment(min[2], max[2], A[2], B[2], D[2], &t0, &t1))
		{
			return false;
		}

		return true;
	}

	inline bool glClipSegment2D(const float* A, const float* B, const float* min, const float* max)
	{
		float t0 = 0.0f, t1 = 1.0f;
//		float S[2] = {A[0], A[1]};
		float D[2] = {B[0]-A[0], B[1]-A[1]};

		if (!glClipSegment(min[0], max[0], A[0], B[0], D[0], &t0, &t1))
		{
			return false;
		}

		if (!glClipSegment(min[1], max[1], A[1], B[1], D[1], &t0, &t1))
		{
			return false;
		}

		return true;
	}


	inline void glMultMatrix(float * out, const float* a, const float* b)
	{
		out[0] = a[0]*b[0]+a[1]*b[4]+a[2]*b[8]+a[3]*b[12];
		out[1] = a[0]*b[1]+a[1]*b[5]+a[2]*b[9]+a[3]*b[13];
		out[2] = a[0]*b[2]+a[1]*b[6]+a[2]*b[10]+a[3]*b[14];
		out[3] = a[0]*b[3]+a[1]*b[7]+a[2]*b[11]+a[3]*b[15];

		out[4] = a[4]*b[0]+a[5]*b[4]+a[6]*b[8]+a[7]*b[12];
		out[5] = a[4]*b[1]+a[5]*b[5]+a[6]*b[9]+a[7]*b[13];
		out[6] = a[4]*b[2]+a[5]*b[6]+a[6]*b[10]+a[7]*b[14];
		out[7] = a[4]*b[3]+a[5]*b[7]+a[6]*b[11]+a[7]*b[15];

		out[8] = a[8]*b[0]+a[9]*b[4]+a[10]*b[8]+a[11]*b[12];
		out[9] = a[8]*b[1]+a[9]*b[5]+a[10]*b[9]+a[11]*b[13];
		out[10] = a[8]*b[2]+a[9]*b[6]+a[10]*b[10]+a[11]*b[14];
		out[11] = a[8]*b[3]+a[9]*b[7]+a[10]*b[11]+a[11]*b[15];

		out[12] = a[12]*b[0]+a[13]*b[4]+a[14]*b[8]+a[15]*b[12];
		out[13] = a[12]*b[1]+a[13]*b[5]+a[14]*b[9]+a[15]*b[13];
		out[14] = a[12]*b[2]+a[13]*b[6]+a[14]*b[10]+a[15]*b[14];
		out[15] = a[12]*b[3]+a[13]*b[7]+a[14]*b[11]+a[15]*b[15];
	}

	inline float* glTransposeMatrix16fv(float out[16], float m[16])
	{
		float res[16];
		memcpy(res, m, sizeof(res));
		float  tmp;
#define Swap( a, b )    tmp = a; a = b; b = tmp
		Swap( res[1],  res[4]  );
		Swap( res[2],  res[8]  );
		Swap( res[3],  res[12] );
		Swap( res[6],  res[9]  );
		Swap( res[7],  res[13] );
		Swap( res[11], res[14] );
#undef Swap
		memcpy(out, res, sizeof(res));
		return out;
	}

	inline float* glReflect3fv(float* out, const float* const l, const float* const n)
	{
		return glSubVector3fv(out, glMulVector3fv(out, n, 2*glDotProduct3fv(l, n)), l);
	}

	inline float* glGetMatrixRow4f(float out[4], const float m[16], int row)
	{
		out[0] = m[row << 2];
		out[1] = m[(row << 2) + 1];
		out[2] = m[(row << 2) + 2];
		out[3] = m[(row << 2) + 3];
		return out;
	}

	inline float* glNormalize3fv(float* out, const float* const v)
	{
		float l = 1.0f / glLength3fv(v);
		out[0] = v[0] * l;
		out[1] = v[1] * l;
		out[2] = v[2] * l;
		return out;
	}

	inline float* glNormalize4fv(float* out, const float* const v)
	{
		float l = 1.0f / glLength4fv(v);
		out[0] = v[0] * l;
		out[1] = v[1] * l;
		out[2] = v[2] * l;
		out[3] = v[3] * l;
		return out;
	}

	inline float glDistanceToPlane(const float point[3], const float plane[4])
	{
		return plane[0]*point[0]+plane[1]*point[1]+plane[2]*point[2]+plane[3];
	}

	inline bool glIntersectPlaneByRay(float* out, const float* rayOrg, const float* rayDir, const float* plane)
	{
		float numer = -(plane[3] + plane[0]*rayOrg[0]+plane[1]*rayOrg[1]+plane[2]*rayOrg[2]);
		float denom = rayDir[0]*plane[0]+rayDir[1]*plane[1]+rayDir[2]*plane[2];
		if (fabs(denom) < std::numeric_limits<float>::epsilon())
			return false;
		*out = numer / denom;
		return true;
	}

	inline void glFlipPlane(float* out, const float* in)
	{
		out[0] = -in[0]; out[1] = - in[1]; out[2] = -in[2]; out[3] = -in[3];
	}

	inline bool glIsPointInFrontOfPlane(const float* point, const float* plane)
	{
		if (glDistanceToPlane(point, plane) < 0)
			return false;
		return true;
	}

	inline void glMakeNearPoint(float* out, const float* minPoint, const float* maxPoint, int nearPointMask)
	{
		out[0] = nearPointMask & 1 ? maxPoint[0] : minPoint[0];
		out[1] = nearPointMask & 2 ? maxPoint[1] : minPoint[1];
		out[2] = nearPointMask & 4 ? maxPoint[2] : minPoint[2];
	}

	inline void glMakeFarPoint(float* out, const float* minPoint, const float* maxPoint, int nearPointMask)
	{
		out[0] = nearPointMask & 1 ? minPoint[0] : maxPoint[0];
		out[1] = nearPointMask & 2 ? minPoint[1] : maxPoint[1];
		out[2] = nearPointMask & 4 ? minPoint[2] : maxPoint[2];
	}

	inline int glComputeNearPointMask ( const float* n )
	{
		if (n[0] > 0.0f)
			if (n[1] > 0.0f)
				if (n[2] > 0.0f)
					return 0;
				else
					return 4;
			else
				if (n[2] > 0.0f)
					return 2;
				else
					return 6;
		else
			if (n[1] > 0.0f)
				if (n[2] > 0.0f)
					return 1;
				else
					return 5;
			else
				if (n[2] > 0.0f)
					return 3;
				else
					return 7;
	}

	inline void glCreatePlane(float* out, const float p1[3], const float p2[3], const float p3[3])
	{
		float v1[3];
		float v2[3];
		glSubVector3fv(v1, p2, p1);
		glSubVector3fv(v2, p3, p1);
		glNormalize3fv(out, glCrossProduct3fv(out, v1, v2));
		out[3] = - p1[0] * (p2[1] * p3[2] - p3[1] * p2[2])
			- p2[0] * (p3[1] * p1[2] - p1[1] * p3[2])
			- p3[0] * (p1[1] * p2[2] - p2[1] * p1[2]);
	}

	inline float* glSetVector3fv(float* out, float* v)
	{
		if (out != v)
			memcpy(out, v, 3*sizeof(float));
		return out;
	}

	inline float* glInverseMatrix4fv(float* out, const float* const m)
	{
#define SWAP_ROWS(a, b) {  float * _tmp = a; (a)=(b); (b)=_tmp; }
#define MAT(m,r,c)     m [r*4+c]

		float	wtmp [4][8];
		float	m0, m1, m2, m3, s;
		float	* r0, * r1, * r2, * r3;

		r0 = wtmp [0];
		r1 = wtmp [1];
		r2 = wtmp [2];
		r3 = wtmp [3];

		r0 [0] = MAT(m,0,0);
		r0 [1] = MAT(m,0,1);
		r0 [2] = MAT(m,0,2);
		r0 [3] = MAT(m,0,3);
		r0 [4] = 1;
		r0 [5] =
			r0 [6] =
			r0 [7] = 0;

		r1 [0] = MAT(m,1,0);
		r1 [1] = MAT(m,1,1);
		r1 [2] = MAT(m,1,2);
		r1 [3] = MAT(m,1,3);
		r1 [5] = 1;
		r1 [4] =
			r1 [6] =
			r1 [7] = 0,

			r2 [0] = MAT(m,2,0);
		r2 [1] = MAT(m,2,1);
		r2 [2] = MAT(m,2,2);
		r2 [3] = MAT(m,2,3);
		r2 [6] = 1;
		r2 [4] =
			r2 [5] =
			r2 [7] = 0;

		r3 [0] = MAT(m,3,0);
		r3 [1] = MAT(m,3,1);
		r3 [2] = MAT(m,3,2);
		r3 [3] = MAT(m,3,3);
		r3 [7] = 1;
		r3 [4] =
			r3 [5] =
			r3 [6] = 0;

		// choose pivot - or die
		if ( fabs (r3 [0] )> fabs ( r2 [0] ) )
			SWAP_ROWS ( r3, r2 );

		if ( fabs ( r2 [0] ) > fabs ( r1 [0] ) )
			SWAP_ROWS ( r2, r1 );

		if ( fabs ( r1 [0] ) > fabs ( r0 [0 ] ) )
			SWAP_ROWS ( r1, r0 );

		if ( r0 [0] == 0 )
			return NULL;

		// eliminate first variable
		m1 = r1[0]/r0[0];
		m2 = r2[0]/r0[0];
		m3 = r3[0]/r0[0];

		s = r0[1];
		r1[1] -= m1 * s;
		r2[1] -= m2 * s;
		r3[1] -= m3 * s;

		s = r0[2];
		r1[2] -= m1 * s;
		r2[2] -= m2 * s;
		r3[2] -= m3 * s;

		s = r0[3];
		r1[3] -= m1 * s;
		r2[3] -= m2 * s;
		r3[3] -= m3 * s;

		s = r0[4];

		if ( s != 0)
		{
			r1[4] -= m1 * s; r2[4] -= m2 * s; r3[4] -= m3 * s;
		}

		s = r0[5];

		if ( s != 0.0 )
		{
			r1[5] -= m1 * s; r2[5] -= m2 * s; r3[5] -= m3 * s;
		}

		s = r0[6];

		if ( s != 0 )
		{
			r1[6] -= m1 * s; r2[6] -= m2 * s; r3[6] -= m3 * s;
		}

		s = r0[7];

		if ( s != 0 )
		{
			r1[7] -= m1 * s; r2[7] -= m2 * s; r3[7] -= m3 * s;
		}

		// choose pivot - or die
		if ( fabs (r3 [1] ) > fabs ( r2 [1] ) )
			SWAP_ROWS ( r3, r2 );

		if ( fabs ( r2 [1] ) > fabs ( r1 [1] ) )
			SWAP_ROWS ( r2, r1 );

		if ( r1 [1] == 0 )
			return NULL;


		// eliminate second variable
		m2     = r2[1]/r1[1]; m3     = r3[1]/r1[1];
		r2[2] -= m2 * r1[2];  r3[2] -= m3 * r1[2];
		r2[3] -= m2 * r1[3];  r3[3] -= m3 * r1[3];

		s = r1[4];

		if ( 0 != s )
		{
			r2[4] -= m2 * s; r3[4] -= m3 * s;
		}

		s = r1[5];

		if ( 0 != s )
		{
			r2[5] -= m2 * s; r3[5] -= m3 * s;
		}

		s = r1[6];

		if ( 0 != s )
		{
			r2[6] -= m2 * s; r3[6] -= m3 * s;
		}

		s = r1[7];

		if ( 0 != s )
		{
			r2[7] -= m2 * s; r3[7] -= m3 * s;
		}

		// choose pivot - or die
		if ( fabs ( r3 [2] ) > fabs ( r2 [2] ) )
			SWAP_ROWS ( r3, r2 );

		if ( r2 [2] == 0)
			return NULL;

		// eliminate third variable
		m3     = r3[2]/r2[2];
		r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
			r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6],
			r3[7] -= m3 * r2[7];

		// last check
		if ( r3 [3] == 0 )
			return NULL;


		// now back substitute row 3
		s      = 1.0f/r3[3];
		r3[4] *= s; r3[5] *= s; r3[6] *= s; r3[7] *= s;

		// now back substitute row 2
		m2    = r2[3];
		s     = 1.0f/r2[2];
		r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
			r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);

		m1     = r1[3];
		r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
			r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;

		m0     = r0[3];
		r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
			r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;

		// now back substitute row 1
		m1    = r1[2];
		s     = 1.0f/r1[1];
		r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
			r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);

		m0     = r0[2];
		r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
			r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;

		// now back substitute row 0
		m0    = r0[1];
		s     = 1.0f/r0[0];
		r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
			r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);

		MAT(out,0,0) = r0[4]; MAT(out,0,1) = r0[5];
		MAT(out,0,2) = r0[6]; MAT(out,0,3) = r0[7];
		MAT(out,1,0) = r1[4]; MAT(out,1,1) = r1[5];
		MAT(out,1,2) = r1[6]; MAT(out,1,3) = r1[7];
		MAT(out,2,0) = r2[4]; MAT(out,2,1) = r2[5];
		MAT(out,2,2) = r2[6]; MAT(out,2,3) = r2[7];
		MAT(out,3,0) = r3[4]; MAT(out,3,1) = r3[5];
		MAT(out,3,2) = r3[6]; MAT(out,3,3) = r3[7];

#undef MAT
#undef SWAP_ROWS

		return out;
	}
}

#endif
