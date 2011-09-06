/*
File: OctTree.h
Author: Abramov Nickolai
Description: a way for maybe efficient rendering of large scale of terrain
*/

#ifndef _H_OCTTREE
#define _H_OCTTREE

#include "os.h"
#include "bounding_box.h"

class OctTree
{
public:
	static const int MaxFaceCount = 8;
	static const int MaxDepth = 20;
	int currentDepth;
	OctTree* RightFrontUp;
	OctTree* RightFrontDown;
	OctTree* RightBackUp;
	OctTree* RightBackDown;
	OctTree* LeftFrontUp;
	OctTree* LeftFrontDown;
	OctTree* LeftBackUp;
	OctTree* LeftBackDown;
	OctTree* Parent;
	BoundingBox bbox;
	unsigned short indexCount;
	unsigned short* index;
	float* vertex;
	unsigned vertexCount;
	bool isFinal;

	OctTree();
	OctTree(OctTree* parent);
	~OctTree();
	void SetData(unsigned short* i, int iCount, float* v, unsigned offset, unsigned vCount);
	OctTree* Build(unsigned short* ind, int iCount, float* v, unsigned vCount);
};


#endif	//	_H_OCTTREE
