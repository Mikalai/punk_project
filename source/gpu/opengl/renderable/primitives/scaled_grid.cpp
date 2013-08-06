#include "scaled_grid.h"

namespace GPU
{
	namespace OpenGL
	{
		int64_t ScaledGridObject::VertexType = Vertex<VertexComponent::Position, 
				VertexComponent::Normal, 
				VertexComponent::Texture0>::Value();

		//	for terrain width and height supposed to be 1 and nothing else
		void ScaledGridObject::Cook(float width, float height, unsigned hor_slices, unsigned vert_slices, int levels)
		{		
			int quads_per_cell_x = hor_slices + 1;
			int quads_per_cell_y = vert_slices + 1;
			int vertex_per_cell_x = quads_per_cell_x + 1;
			int vertex_per_cell_y = quads_per_cell_y + 1;
			int vertex_per_cell = (vertex_per_cell_x)*(vertex_per_cell_y);
			int index_per_cell = 6*quads_per_cell_x*quads_per_cell_y;
			//	outter plus interrior
			int total_cells = 12*levels + 16;
			int total_vertex_count = total_cells * vertex_per_cell;
			int total_index_count = total_cells * index_per_cell;
			std::vector<CurrentVertex> v(total_vertex_count);
			std::vector<unsigned int> index(total_index_count);
			float total_width = 0;
			for (int i = 1; i != levels+1; ++i)
			{			
				total_width += powf(2.0f, float(i +1)) * width;
			}
			m_total_width = total_width = total_width + 4.0f * width;

			float total_height = 0;
			for (int i = 1; i != levels+1; ++i)
			{
				total_height += (powf(2.0f, float(i+1))) * height;
			}
			m_total_height = total_height = total_height + 4.0f * height;

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
						float x = float(ix) * width;
						float y = float(iy) * height;

						//	we skip very center at any leve, except zero one
						if (lev != 0 && (ix >= -1 && ix <= 0 && iy >= -1 && iy <= 0))
							continue;

						int base_vertex = cur_v;

						//	iterate through each vertex of current cell
						for (int i = 0; i != (int)vertex_per_cell_x; i++)
						{
							for (int j = 0; j != (int)vertex_per_cell_y; j++)
							{
								//	get access to the current vertex
								CurrentVertex& cur = v[cur_v];

								//	check if it is a border and odd vertex
								//	its position should be adjusted in the shader
								float w = 0;
								bool left_vertical = (ix == -2 && j == 0 && (i % 2) != 0);
								bool right_vertical = (ix == 1 && j == quads_per_cell_x && (i % 2) != 0);

								//bool left_vertical = (ix == -2 && j == 0);
								//bool right_vertical = (ix == 1 && j == hor_slices);
								if (left_vertical || right_vertical)
								{
									w = -1.0f;	//	y neighbours needed
								}

								bool top_horizontal = (iy == 1 && i == quads_per_cell_y && (j % 2) != 0);
								bool bottom_horizontal = (iy == -2 && i == 0 && (j % 2) != 0);
								//bool top_horizontal = (iy == 1 && i == vert_slices);
								//bool bottom_horizontal = (iy == -2 && i == 0);
								if (top_horizontal || bottom_horizontal)
								{
									w = 1.0f;	// x neighbours needed
								}

								float pos_x = k*(width/float(quads_per_cell_x)*float(j) + x);
								float pos_y = k*(height/float(quads_per_cell_y)*float(i) + y);
								
								cur.m_position.Set(
									pos_x,
									0,
									pos_y,
									w);

								//	store in the w component scale factor (level)
								cur.m_normal.Set(0, 1.0f, 0, (float)k);
								
								//	store in the z w components number of hor and ver slices
								//	texture coordinates are calculated with shift to make them positive
								cur.m_texture0.Set(
									(total_width / 2.0f + pos_x) / total_width,
									(total_height / 2.0f + pos_y) / total_height,
									(float)(double(width) * double(k) / (double)(quads_per_cell_x) / (double)total_width), 
									(float)total_width);			
								++cur_v;
							}
						}			

						for (int i = 0; i < (int)quads_per_cell_x; i++)
						{
							for (int j = 0; j < (int)quads_per_cell_y; j++)
							{
								index[cur_i++] = base_vertex + i*(quads_per_cell_x + 1) + j + 0;
								index[cur_i++] = base_vertex + (i+1)*(quads_per_cell_x + 1)+ j;
								index[cur_i++] = base_vertex + i*(quads_per_cell_x + 1) + j + 1;					

								index[cur_i++] = base_vertex + i*(quads_per_cell_x + 1) + j + 1;
								index[cur_i++] = base_vertex + (i+1)*(quads_per_cell_x + 1) + j;
								index[cur_i++] = base_vertex + (i+1)*(quads_per_cell_x + 1) + j + 1;
							}
						}
					}
				}
			}
			SetVertexBuffer(v);
			SetIndexBuffer(index);
			VertexArrayObject2<PrimitiveType, CurrentVertex>::Cook();/**/
		}

		float ScaledGridObject::GetTotalWidth() const
		{
			return m_total_width;
		}

		float ScaledGridObject::GetTotalHeight() const
		{
			return m_total_height;
		}
	}
}