#include "scaled_grid.h"

namespace OpenGL
{

	//	for terrain width and height supposed to be 1 and nothing else
	void ScaledGridObject::Cook(float width, float height, unsigned hor_slices, unsigned vert_slices, int levels)
	{		
		hor_slices += 1;
		vert_slices += 1;
		int vertex_per_cell = (hor_slices+1)*(vert_slices+1);
		int index_per_cell = 6*hor_slices*vert_slices;
		//	outter plus interrior
		int total_cells = 12*levels + 16;
		int total_vertex_count = total_cells * vertex_per_cell;
		int total_index_count = total_cells * index_per_cell;
		std::vector<Utility::Vertex<VertexType>> v(total_vertex_count);
		std::vector<unsigned int> index(total_index_count);

		int cur_v = 0;
		int cur_i = 0;

		//	iterate through all required levels
		for (int lev = 0; lev != levels+1; ++lev)
		{
			//	find scale factor for coordinates offset
			int k = 1 << lev;

			//	iterate through all cells 
			for (int ix = -2; ix != 2; ++ix)
			{
				for (int iy = -2; iy != 2; ++iy)
				{
					//	find cell offset
					float x = float(ix);
					float y = float(iy);

					//	we skip very center at any leve, except zero one
					if (lev != 0 && (ix >= -1 && ix <= 0 && iy >= -1 && iy <= 0))
						continue;

					int base_vertex = cur_v;

					//	iterate through each vertex of current cell
					for (int i = 0; i < (int)vert_slices + 1; i++)
					{
						for (int j = 0; j < (int)hor_slices + 1; j++)
						{
							//	get access to the current vertex
							Utility::Vertex<VertexType>& cur = v[cur_v];
							
							//	check if it is a border and odd vertex
							//	its position should be adjusted in the shader
							float w = 0;
							bool left_vertical = (ix == -2 && j == 0 && (i % 2) != 0);
							bool right_vertical = (ix == 1 && j == hor_slices && (i % 2) != 0);
							if (left_vertical || right_vertical)
							{
								w = -1.0f;	//	y neighbours needed
							}
							
							bool top_horizontal = (iy == 1 && i == vert_slices && (j % 2) != 0);
							bool bottom_horizontal = (iy == -2 && i == 0 && (j % 2) != 0);
							if (top_horizontal || bottom_horizontal)
							{
								w = 1.0f;	// x neighbours needed
							}
							
							cur.m_position.Set(
								k*(width/float(hor_slices)*float(j) + x),
								0,
								k*(height/float(vert_slices)*float(i) + y),
								w);

							//	store in the w component scale factor (level)
							cur.m_normal.Set(0, 1.0f, 0, (float)k);

							//	store in the z w components number of hor and ver slices
							cur.m_texture0.Set(
								1.0f/float(hor_slices)*float(j),
								1.0f/float(vert_slices)*float(i), (float)hor_slices, (float)vert_slices);			
							++cur_v;
						}
					}			

					for (int i = 0; i < (int)vert_slices; i++)
					{
						for (int j = 0; j < (int)hor_slices; j++)
						{
							index[cur_i++] = base_vertex + i*(hor_slices+1) + j + 0;
							index[cur_i++] = base_vertex + (i+1)*(hor_slices+1) + j;
							index[cur_i++] = base_vertex + i*(hor_slices+1) + j + 1;					

							index[cur_i++] = base_vertex + i*(hor_slices+1) + j + 1;
							index[cur_i++] = base_vertex + (i+1)*(hor_slices+1) + j;
							index[cur_i++] = base_vertex + (i+1)*(hor_slices+1) + j + 1;
						}
					}
				}
			}
		}
		SetVertexBuffer(v);
		SetIndexBuffer(index);
		VertexArrayObject2<PrimitiveType, VertexType>::Cook();/**/
	}
}