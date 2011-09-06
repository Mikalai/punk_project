
#ifndef VERTEX_CACHE_H

#define VERTEX_CACHE_H

#include <memory.h>

class VertexCache
{

public:

	VertexCache(int size);
	VertexCache();
	~VertexCache();
	bool InCache(int entry);
	int AddEntry(int entry);
    void Clear();
	void Copy(VertexCache* inVcache);
	int At(int index);
	void Set(int index, int value);

private:

  unsigned short *entries;
  int numEntries;

};

#endif
