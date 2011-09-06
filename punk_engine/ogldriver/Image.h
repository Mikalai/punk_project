#ifndef _PUNK_IMAGE
#define _PUNK_IMAGE

#include "../PunkEngine/PunkEngine.h"

class TDriver;

class TImage : public IImage
{
public:	
	virtual ~TImage();
	virtual IImage& operator = (const IImage& image);

	virtual void LoadJPEG(const char* filename);
	virtual void LoadBMP(const char* filename);
	virtual void LoadTGA(const char* filename);
	virtual void LoadDDS(const char* filename);

	virtual unsigned char* GetData();
	virtual int GetWidth() const;
	virtual int GetHeight() const;
	virtual int GetBitsPerPixel() const;

private:
	TImage(TDriver* driver);
	TImage(const IImage& image);
	TImage(const TImage& image);
	unsigned char* m_data;
	int m_width;
	int m_height;
	int m_bitPerPixel;

	friend class Scene;
};

#endif