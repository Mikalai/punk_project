#ifndef MATRIX_WITH_HEADERS_H
#define MATRIX_WITH_HEADERS_H

#include "smart_matrix.h"

namespace Math
{
	//
	//	матрица с заголовками. теперь каждой строке и столбу соот
	//	ветсвует заголовок. По сути рапер над умной матрицей
	//
	template<class T, class C, class R>
	class HeaderMatrix
	{
		Matrix<T> m_body;
		Matrix<C> m_column_header;
		Matrix<R> m_row_header;

	public:
		const Matrix<T>& Body() const
		{
			return m_body;
		}

		Matrix<T>& Body()
		{
			return m_body;
		}

		const Matrix<T>& ColumnHeader() const
		{
			return m_column_header;
		}

		Matrix<C>& ColumnHeader()
		{
			return m_column_header;
		}

		const Matrix<R>& RowHeader() const
		{
			return m_row_header;
		}

		Matrix<R>& RowHeader()
		{
			return m_row_header;
		}

		Matrix<T> ExpandedMatrix(T& det) const
		{
			return m_body.ExpandedMatrix();
		}

		HeaderMatrix()
		{
		}

		HeaderMatrix(int row_count, int column_count) : m_body(row_count, column_count),
			m_column_header(1, column_count), m_row_header(row_count, 1)
		{}

		HeaderMatrix<T, C, R>(const HeaderMatrix<T, C, R>& m)
		{
			m_body = m.m_body;
			m_column_header = m.m_column_header;
			m_row_header = m.m_row_header;			
		}

		HeaderMatrix<T, C, R>& operator = (const HeaderMatrix<T, C, R>& m)
		{
			if (this == &m)
				return *this;
			m_body = m.m_body;
			m_column_header = m.m_column_header;
			m_row_header = m.m_row_header;			
			return *this;
		}

		~HeaderMatrix() {}

		T& At(int row, int column)
		{
			return m_body.At(row, column);
		}

		R& AtRowHeader(int row)
		{
			return m_row_header.At(row, 0);
		}

		C& AtColumnHeader(int column)
		{
			return m_column_header.At(0, column);
		}

		const T& At(int row, int column) const
		{
			return m_body.At(row, column);
		}

		R& AtRowHeader(int row) const
		{
			return m_row_header.At(row, 0);
		}

		C& AtColumnHeader(int column) const
		{
			return m_column_header.At(0, column);
		}

		void SetSize(int row_count, int column_count)
		{
			m_body.SetSize(row_count, column_count);
			m_column_header.SetSize(1, column_count);
			m_row_header.SetSize(row_count, 1);
		}

		Matrix<T> Transposed() const
		{
			return m_body.Transposed();
		}

		int RowCount() const
		{
			return m_body.RowCount();
		}

		int ColumnCount() const
		{
			return m_body.ColumnCount();
		}

		void Identify()
		{
			m_body.Identify();
		}

		void SwapRows(int row1, int row2)
		{
			m_body.SwapRows(row1, row2);
			m_row_header.SwapRows(row1, row2);
		}

		void SwapColumns(int column1, int column2)
		{
			m_body.SwapColumns(column1, column2);
			m_column_header.SwapColumns(column1, column2);
		}

		Matrix<T> SubMatrix(int row1, int column1, int row2, int column2) const
		{
			return m_body.SubMatrix(row1, column1, row2, column2);
		}

		HeaderMatrix<T, C, R>& JoinLeft(const HeaderMatrix<T, C, R>& mat)
		{
			m_body.JoinLeft(mat.m_body);
			m_column_header.JoinLeft(mat.m_column_header);
			return *this;
		}

		HeaderMatrix<T, C, R>& JoinBottom(const HeaderMatrix<T, C, R>& mat)
		{
			m_body.JoinBottom(mat.m_body);
			m_row_header.JoinBottom(mat.m_row_header);
			return *this;
		}

		Matrix<T> Row(int row) const
		{
			return m_body.Row(row);
		}

		Matrix<T> Column(int column) const
		{
			return m_body.Column(column);
		}

		T Determinant() const
		{
			return m_body.Determinant();
		}



		Matrix<T> Inversed() const
		{
			return m_body.Inversed();
		}

		HeaderMatrix<T, C, R>& SetRow(int row, const HeaderMatrix<T, C, R>& new_row)
		{
			m_body.SetRow(row, new_row.m_body);
			m_row_header.SetRow(row, new_row.m_row_header);
			return *this;
		}

		HeaderMatrix<T, C, R>& SetColumn(int column, const HeaderMatrix<T, C, R>& new_column)
		{
			m_body.SetColumn(column, new_column.m_body);
			m_column_header.SetColumn(column, new_column.m_column_header);
			return *this;
		}

		HeaderMatrix<T, C, R>& operator += (const HeaderMatrix<T, C, R>& m2)
		{
			m_body += m2.m_body;
			return *this;
		}

		HeaderMatrix<T, C, R>& operator -= (const HeaderMatrix<T, C, R>& m2)
		{
			m_body += m2.m_body;
			return *this;
		}

		HeaderMatrix<T, C, R>& operator *= (const T& value)
		{
			m_body *= value;
			return *this;
		}

		HeaderMatrix<T, C, R>& operator /= (const T& value)
		{
			m_body /= value;
			return *this;
		}

		HeaderMatrix<T, C, R>& operator |= (const T& value)
		{
			m_body |= value;
			return *this;
		}

		HeaderMatrix<T, C, R>& operator &= (const T& value)
		{
			m_body |= value;
			return *this;
		}

		HeaderMatrix<T, C, R>& operator ^= (const T& value)
		{
			m_body ^= value;
			return *this;
		}

		T AlgebraicCofactor(int erow, int ecolumn) const
		{
			return m_body.AlgebraicCofactor(erow, ecolumn);
		}

		Matrix<T> Minor(int erow, int ecolumn) const
		{
			return m_body.Minor(erow, ecolumn);
		}

		HeaderMatrix<T, C, R>& SetSubMatrix(int row, int column, const Matrix<T>& matrix)
		{
			m_body.SetSubMatrix(row, column, matrix);
			return *this;
		}

		HeaderMatrix<T, C, R>& AddRow()
		{			
			Matrix<T> m(1, ColumnCount());
			m_body.JoinBottom(m);
			Matrix<R> r(1, 1);
			m_row_header.JoinBottom(r);
			return *this;
		}

		HeaderMatrix<T, C, R>& AddColumn()
		{
			Matrix<T> m(RowCount(), 1);
			m_body.JoinLeft(m);
			Matrix<C> c(1, 1);
			m_column_header.JoinLeft(c);
			return *this;
		}

		HeaderMatrix<T, C, R>& RemoveRow(int row_to_del)
		{
			m_body.RemoveRow(row_to_del);
			m_row_header.RemoveRow(row_to_del);
			return *this;
		}

		HeaderMatrix<T, C, R>& RemoveColumn(int col_to_del)
		{
			m_body.RemoveColumn(col_to_del);
			m_column_header.RemoveColumn(col_to_del);
			return *this;
		}

		T Length() const
		{
			return m_body.Length();
		}

		HeaderMatrix<T, C, R>& FillRow(int row, T value)
		{
                        m_body.FillRow(row, value);
                        return *this;
		}

		HeaderMatrix<T, C, R>& FillColumn(int col, T value)
		{
			m_body.FillColumn(col, value);
			return *this;
		}
	};

	template<class T, class C, class R>
	bool operator == (const HeaderMatrix<T, C, R>& m1, const HeaderMatrix<T, C, R>& m2)
	{
		return m1.m_body == m2.m_body;
	}

	template<class T, class C, class R>
	HeaderMatrix<T, C, R> operator + (const HeaderMatrix<T, C, R>& m1, const HeaderMatrix<T, C, R>& m2)
	{
		HeaderMatrix<T, C, R> m(m1);
		return m += m2;
	}

	template<class T, class C, class R> 
	HeaderMatrix<T, C, R> operator - (const HeaderMatrix<T, C, R>& m1, const HeaderMatrix<T, C, R>& m2)
	{
		HeaderMatrix<T, C, R> m(m1);
		return m -= m2;
	}

	template<class T, class C, class R>
	HeaderMatrix<T, C, R> operator * (const HeaderMatrix<T, C, R>& m1, const T& value)
	{
		HeaderMatrix<T, C, R> m(m1);
		return m *= value;
	}

	template<class T, class C, class R>
	HeaderMatrix<T, C, R> operator * (const T& value, const HeaderMatrix<T, C, R>& m1)
	{
		HeaderMatrix<T, C, R> m(m1);
		return m *= value;
	}

	template<class T, class C, class R>
	HeaderMatrix<T, C, R> operator / (const HeaderMatrix<T, C, R>& m1, const T& value)
	{
		HeaderMatrix<T, C, R> m(m1);
		return m /= value;
	}

	template<class T, class C, class R>
	Matrix<T> operator * (const HeaderMatrix<T, C, R>& m1, const HeaderMatrix<T, C, R>& m2)
	{
		return m1.Body() * m2.Body();
	}

	template<class T, class C, class R>
	T FindRowMinimum(const HeaderMatrix<T, C, R>& m, int row, int& min_col)
	{
		return FindRowMinimum<T>(m.Body(), row, min_col);
	}

	template<class T, class C, class R>
	T FindRowMaximum(const HeaderMatrix<T, C, R>& m, int row, int& max_col)
	{
		return FindRowMaximum<T>(m.Body(), row, max_col);
	}

	template<class T, class C, class R>
	const Matrix<T> PerElementMultiplication(const HeaderMatrix<T, C, R>& m1, const HeaderMatrix<T, C, R>& m2)
	{
		return PerElementMultiplication<T>(m1.Body(), m2.Body());
	}
}

#endif
