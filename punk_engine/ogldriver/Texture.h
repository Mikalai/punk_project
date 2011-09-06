#pragma once

class	Texture
{
protected:
	int	m_width;
	int	m_height;
	int	m_numComponents;
	int	m_format;
	char* m_data;
	int	m_levels;
	bool m_compressed;

public:
	Texture  ();
	Texture  ( int width, int height, int numComponents);
	virtual ~Texture ();

	int	GetWidth () const
	{
		return m_width;
	}

	int	GetHeight () const
	{
		return m_height;
	}

	int	GetNumComponents () const
	{
		return m_numComponents;
	}

	int	GetFormat () const
	{
		return m_format;
	}

	int	GetLevels () const
	{
		return m_levels;
	}

	bool IsCompressed () const
	{
		return m_compressed;
	}

	int	GetBytesPerLine () const
	{
		return m_width * m_numComponents;
	}

	char* GetData () const
	{
		return m_data;
	}
	
	void SetFormat ( int newFormat )
	{
		m_format = newFormat;
	}

	void GenerateId ();
	void PutLine ( int y, unsigned long * bits);

	virtual	bool Upload ( int target, bool mipmap = true );
};

inline	unsigned long makeRgba ( int red, int green, int blue, int alpha = 255 )
{
	return red + (green << 8) + (blue << 16) + (alpha << 24);
}