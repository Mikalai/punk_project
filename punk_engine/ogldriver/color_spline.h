/*
	File: ColorSpline.h
*/

#ifndef _H_COLOR_SPLINE
#define _H_COLOR_SPLINE

#define MAX_COLOR_SPLINE_ENTRIES 20

class ColorSpline
{
private:
	struct Entry
	{
		float t;
		float color[4];
		float delta[4];
	};
	Entry entries[MAX_COLOR_SPLINE_ENTRIES];
	int numEntries;

public:
	ColorSpline()
	{
		numEntries = 0;
	}
	void AddColorAt(float r, float g, float b, float a, float t)
	{
		float color[4] = {r, g, b, a};
		AddColorAt(color, t);
	}

	void AddColorAt(const float* color, float t)
	{
		if (numEntries >= MAX_COLOR_SPLINE_ENTRIES)
			return;

		entries[numEntries].t = t;
		memcpy(entries[numEntries].color, color, sizeof(float)*4);
		if (numEntries > 0)
		{
			entries[numEntries-1].delta[0] = 
				(entries[numEntries].color[0] - entries[numEntries-1].color[0]) /
				(entries[numEntries].t - entries[numEntries-1].t);
			entries[numEntries-1].delta[1] = 
				(entries[numEntries].color[1] - entries[numEntries-1].color[1]) /
				(entries[numEntries].t - entries[numEntries-1].t);
			entries[numEntries-1].delta[2] = 
				(entries[numEntries].color[2] - entries[numEntries-1].color[2]) /
				(entries[numEntries].t - entries[numEntries-1].t);
			entries[numEntries-1].delta[3] = 
				(entries[numEntries].color[3] - entries[numEntries-1].color[3]) /
				(entries[numEntries].t - entries[numEntries-1].t);
		}
		numEntries++;
	}

	void ValueAt(float t, float* v) const
	{
		if (t < entries[0].t)
		{
			memcpy(v, entries[0].color, 4*sizeof(float));
			return;
		}
		for (register int i = 1; i < numEntries; i++)
		{
			if (t <= entries[i].t)
			{
				v[0] = entries[i-1].color[0]+(t-entries[i-1].t)*entries[i-1].delta[0];
				v[1] = entries[i-1].color[1]+(t-entries[i-1].t)*entries[i-1].delta[1];
				v[2] = entries[i-1].color[2]+(t-entries[i-1].t)*entries[i-1].delta[2];
				v[3] = entries[i-1].color[3]+(t-entries[i-1].t)*entries[i-1].delta[3];
				return;
			}
		}
		memcpy(v, entries[numEntries-1].color, 4*sizeof(float));
	}
};

#endif