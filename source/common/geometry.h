#ifndef _H_PUNK_GEOMETRY
#define _H_PUNK_GEOMETRY

#include "../system/buffer.h"

namespace Common
{
	class StaticGeometry
	{
	public:

		struct Vertex
		{
			float x, y, z, w;
			float nx, ny, nz, nw;
			float u, v, s, t;
			float ix, iy, iz, iw;

			static const int PositionOffset = 0;
			static const int NormalOffset = 4*sizeof(float);
			static const int TextureCoordOffset = (4+4)*sizeof(float);
			static const int FlagsOffset = (4+4+4)*sizeof(float);

		};

	private:
		Vertex* m_vertex_buffer;
		float* m_vertex;
		float* m_normal;
		float* m_texture_coord;
		float m_bbox[8][3];
		int m_vertex_count;
		int m_index_count;
		unsigned short* m_index;

		bool Parse(System::Buffer& buffer);
		bool ReadBoundingBox(System::Buffer& buffer);
		bool ReadLocation(System::Buffer& buffer);
		bool ReadWorldMatrix(System::Buffer& buffer);
		bool ReadLocalMatrix(System::Buffer& buffer);
		bool ReadMesh(System::Buffer& buffer);
		bool ReadVertexPosition(System::Buffer& buffer);
		bool ReadVertexNormal(System::Buffer& buffer);
		bool ReadFaces(System::Buffer& buffer);
		bool ReadVertexPositionId(System::Buffer& buffer);
		bool ReadTexCoord(System::Buffer& buffer);


		void CreateVertexBufferInCPU();

	public:
		StaticGeometry();
		~StaticGeometry();

		void Set(Vertex* vertex_buffer, int vertex_count, unsigned short* index_buffer, int index_count);
		bool Load(const wchar_t* filename);
		bool Load(System::Buffer& buffer);

		void Clear();
		const void* GetVertexBuffer() const;
		const void* GetIndexBuffer() const;

		int GetIndexCount() const;
		int GetIndexSize() const;
		int GetIndexBufferSize() const;

		int GetVertexCount() const;
		int GetVertexSize() const;
		int GetVertexBufferSize() const;

		int GetPositionOffset() const;
		int GetNormalOffset() const;
		int GetTextureCoordOffset() const;
		int GetVertexFlagsOffset() const;

		void SaveBinary(System::Buffer& buffer);
		void LoadBinary(System::Buffer& buffer);
	};
}

#endif