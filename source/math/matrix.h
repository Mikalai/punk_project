//
//	File: matrix.h
//	Desc: Contains a common view matrix description
//	Author: Mikola
//

#ifndef _H_PUNK_MATRIX
#define _H_PUNK_MATRIX

#include "../config.h"
#include "math_error.h"
#include "mat4.h"
#include "mat3.h"
#include "mat2.h"

namespace Math
{
	template<class T>
	class MatrixNxM
	{
		struct Rep
		{						
            T* m_cell;
			int m_width;
			int m_height;			            
            int m_usage_count;

            Rep() : m_cell(nullptr), m_width(4), m_height(4), m_usage_count(1)
			{			
				SetSize(m_width, m_height);
			}

			Rep(const Rep& rep)
			{
				m_width = rep.m_width;
				m_height = rep.m_height;
				m_usage_count++;
				m_cell = rep.m_cell;
			}

            Rep(int width, int height) : m_cell(nullptr), m_width(width), m_height(height), m_usage_count(1)
			{
				SetSize(m_width, m_height);
			}

			~Rep()
			{
				delete[] m_cell;
			}

			Rep* GetOwnCopy()
			{
				if (m_usage_count == 1)
					return this;
				m_usage_count--;
				
				Rep* rep = new Rep(m_width, m_height);
				rep->Assign(m_width, m_height, m_cell);
				return rep;
			}

			void Assign(int width, int height, const T* cell)
			{
				if (m_width != width || m_height != height)
				{
					if (m_cell)
						delete[] m_cell;
					m_width = width;
					m_height = height;				
					m_cell = new T[m_width*m_height];				
				}
				memcpy(m_cell, cell, sizeof(T)*m_width*m_height);
			}

			void SetSize(int width, int height)
			{
				if (m_width == width && m_height == height)
				{
					if (m_cell)
						memset(m_cell, 0, sizeof(T)*m_width*m_height);
					else
					{
						m_cell = new T[m_width*m_height];
						memset(m_cell, 0, sizeof(T)*m_width*m_height);
					}
					return;
				}

				m_width = width;
				m_height = height;

				if (m_cell)
					delete[] m_cell;

				m_cell = new T[m_width*m_height];
				memset(m_cell, 0, sizeof(T)*m_width*m_height);
			}

			void CopyMatrix(const Rep& rep, int start_col, int start_row)
			{
				int width = rep.m_width;
				int height = rep.m_height;

				if (start_col + width >= m_width || start_row + height >= m_height)
					throw MathIndexOutOfRange();

				T* cells = rep.m_cell;

				for (int i = 0; i < height; i++)
					for (int j = 0; j < width; j++)
						m_cell[(start_row+i)*m_width + start_col+j] = cells[i*width+j];
			}

			void CopySubMatrix(const Rep& rep, int src_start_col, int src_start_row, int width, int height, int dst_start_col, int dst_start_row)
			{
				if (dst_start_col + width >= m_width || dst_start_row + height >= m_height)
					throw MathIndexOutOfRange();

				int src_width = rep.m_width;

				T* cells = rep.m_cell;

				for (int i = 0; i < height; i++)
					for (int j = 0; j < width; j++)
						m_cell[(i+dst_start_row)*m_width + j + dst_start_col] = cells[(src_start_row+i)*src_width + j + src_start_col];
			}

		};

		Rep* m_rep;

	public:
		MatrixNxM() : m_rep(new Rep()) {}
		MatrixNxM(int width, int height) : m_rep(new Rep(width, height)) {}
		MatrixNxM(const MatrixNxM& m)
		{
			if (--m_rep->m_usage_count == 0)
				delete m_rep;
			m_rep = m.m_rep;
			m_rep->m_usage_count++;
		}

		MatrixNxM<T>& operator = (const MatrixNxM<T>& m)
		{
			if (this != &m)
			{
				if (m_rep->m_usage_count == 1)
					m_rep->Assign(m.GetWidth(), m.GetHeight(), m.GetCells());
				else
				{
					m_rep->m_usage_count--;
					m_rep = new Rep(m.GetWidth(), m.GetHeight());
					m_rep->Assign(m.GetWidth(), m.GetHeight(), m.GetCells());
				}
			}

			return *this;
		}

		~MatrixNxM<T>()
		{
			if (--m_rep->m_usage_count == 0)
			{
				delete m_rep;
				m_rep = 0;
			}
		}

		void SetSize(int width, int height)
		{
			m_rep = m_rep->GetOwnCopy();
			m_rep->SetSize(width, height);
		}

		void CopyMatrix(const MatrixNxM<T>& m, int start_col, int start_row)
		{
			m_rep = m_rep->GetOwnCopy();
			m_rep->CopyMatrix(*m.m_rep, start_col, start_row); 
		}

		void CopySubMatrix(const MatrixNxM<T>&m , int src_start_col, int src_start_row, int src_width, int src_height, int dst_start_col, int dst_start_row)
		{
			m_rep = m_rep->GetOwnCopy();
			m_rep->CopySubMatrix(*m.m_rep, src_start_col, src_start_row, src_width, src_height, dst_start_col, dst_start_row);
		}

		MatrixNxM<T> GetSubMatrix(int start_col, int start_row, int width, int height)
		{
			if (start_col + width >= m_rep->m_width || start_row + height >= m_rep->m_height)
				throw MathIndexOutOfRange();

			MatrixNxM<T> matrix(width, height);
			matrix.CopySubMatrix(*this, start_col, start_row, width, height, 0, 0);
			
			return matrix;
		}

		T& At(int column, int row) 
		{
			m_rep = m_rep->GetOwnCopy();
			return m_rep->m_cell[row*m_rep->m_width+column];
		}

		const T& At(int column, int row) const
		{
			return m_rep->m_cell[row*m_rep->m_width+column];
		}

		const T* GetCells() const
		{
			return m_rep->m_cell;
		}

		T* GetCells() 
		{
			return m_rep->m_cell;
		}

		int GetWidth() const
		{
			return m_rep->m_width;
		}

		int GetHeight() const
		{
			return m_rep->m_height;
		}

		void SwapRows(int a, int b)
		{
			if (a >= m_rep->m_height || b >= m_rep->m_height)
				throw MathIndexOutOfRange();
			m_rep = m_rep->GetOwnCopy();
			T* tmp = new T[m_rep->m_width];
			memcpy(tmp, m_rep->m_cell + m_rep->m_width*a, sizeof(T)*m_rep->m_width);
			memcpy(m_rep->m_cell + m_rep->m_width*a, m_rep->m_cell + m_rep->m_width*b, sizeof(T)*m_rep->m_width);
			memcpy(m_rep->m_cell + m_rep->m_width*b, tmp, sizeof(T)*m_rep->m_width);
			delete[] tmp;
		}

		void SwapColumns(int a, int b)
		{
			if (a >= m_rep->m_width || b >= m_rep->m_width)
				throw MathIndexOutOfRange();

			for (int i = 0; i < m_rep->m_height; i++)
			{
				T tmp = m_rep->m_cell[m_rep->m_width*i+a];
				m_rep->m_cell[m_rep->m_width*i+a] = m_rep->m_cell[m_rep->m_width*i + b];
				m_rep->m_cell[m_rep->m_width*i+b] = tmp;
			}
		}

		void SwapCells(int col1, int row1, int col2, int row2)
		{
			if (col1 >= m_rep->m_width || col2 >= m_rep->m_width || row1 >= m_rep->m_height || row2 >= m_rep->m_height)
				throw MathIndexOutOfRange();
			m_rep = m_rep->GetOwnCopy();
			T t = m_rep->m_cell[m_rep->m_width*row1+col1];
			m_rep->m_cell[m_rep->m_width*row1+col1] = m_rep->m_cell[m_rep->m_width*row2+col2];
			m_rep->m_cell[m_rep->m_width*row2+col2] = t;
		}

		MatrixNxM<T> GetRow(int row)
		{
			if (row >= m_rep->m_height)
				throw MathIndexOutOfRange();
			MatrixNxM<T> m(m_rep->m_width, 1);
			m.CopySubMatrix(*this, 0, row, m_rep->m_width, 1, 0, 0);
			return m;
		}

		MatrixNxM<T> GetColumn(int col)
		{
			if (col >= m_rep->m_width)
				throw MathIndexOutOfRange();
			MatrixNxM<T> m(1, m_rep->m_height);
			m.CopySubMatrix(*this, col, 0, 1, m_rep->m_height, 0, 0);
			return m;
		}
	};

	template class PUNK_ENGINE_PUBLIC MatrixNxM<float>;
	template class PUNK_ENGINE_PUBLIC MatrixNxM<int>;
	template class PUNK_ENGINE_PUBLIC MatrixNxM<bool>;

	typedef MatrixNxM<float> matNxM;
	typedef MatrixNxM<int> imatNxM;
	typedef MatrixNxM<bool> bmatNxM;
}

#endif
