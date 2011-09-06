/*
File: OctTree.h
Author: Abramov Nickolai
Description: a way for maybe efficient rendering of large scale of terrain
*/

#include "oct_tree.h"

OctTree::OctTree()
{
	indexCount = 0;
	index = 0;
	vertexCount = 0;
	vertex = 0;
	Parent = 0;
}

OctTree::OctTree(OctTree* parent)
{
	indexCount = 0;
	index = 0;
	vertexCount = 0;
	vertex = 0;
	Parent = parent;
}

void OctTree::SetData(unsigned short* i, int iCount, float* v, unsigned offset, unsigned vCount)
{
	index = i;
	indexCount = iCount;
	vertex = v;
	vertexCount = vCount;
	currentDepth = 0;
	bbox.Create(vertex, offset, vertexCount);

	Build(index, iCount, vertex, vCount);
}

OctTree* OctTree::Build(unsigned short* ind, int iCount, float* v, unsigned vCount)
{
	currentDepth = Parent != 0 ? Parent->currentDepth + 1 : 0;
	if (currentDepth >= MaxDepth)
	{
		index = new unsigned short[iCount];
		for (int i = 0; i < iCount; i++)
		{
			index[i] = ind[i];
			indexCount++;
		}
		isFinal = true;
		return this;
	}
	index = new unsigned short[iCount];
	for (int i = 0; i < iCount; i++)
	{
		float* p1 = &v[3*i+0];
		float* p2 = &v[3*i+1];
		float* p3 = &v[3*i+2];

		if (bbox.DoCrossTriangle(p1,p2,p3))
		{
			index[indexCount+0] = i+0;
			index[indexCount+1] = i+1;
			index[indexCount+2] = i+2;
			indexCount +=3;
		}
	}
	if (Parent == 0 || indexCount/3 > MaxFaceCount && indexCount != Parent->indexCount)
	{
		float* min = bbox.min;
		float* max = bbox.max;
		float mid[3] = {(min[0] + max[0])*0.5f, (min[1] + max[1])*0.5f,(min[2] + max[2])*0.5f};
		RightFrontUp = new OctTree(this);
		Math::glCreatePoint3(RightFrontUp->bbox.min, mid[0], mid[1], mid[2]);
		Math::glCreatePoint3(RightFrontUp->bbox.max, max[0], max[1], max[2]);
		RightFrontUp->Build(index, indexCount, vertex, vertexCount);

		RightFrontDown = new OctTree(this);
		Math::glCreatePoint3(RightFrontDown->bbox.min, mid[0], mid[1], min[2]);
		Math::glCreatePoint3(RightFrontDown->bbox.max, max[0], max[1], mid[2]);
		RightFrontDown->Build(index, indexCount, vertex, vertexCount);

		LeftFrontUp = new OctTree(this);
		Math::glCreatePoint3(LeftFrontUp->bbox.min, min[0], mid[1], mid[2]);
		Math::glCreatePoint3(LeftFrontUp->bbox.max, mid[0], max[1], max[2]);
		LeftFrontUp->Build(index, indexCount, vertex, vertexCount);

		LeftFrontDown = new OctTree(this);
		Math::glCreatePoint3(LeftFrontDown->bbox.min, min[0], mid[1], min[2]);
		Math::glCreatePoint3(LeftFrontDown->bbox.max, mid[0], max[1], mid[2]);
		LeftFrontDown->Build(index, indexCount, vertex, vertexCount);
		///////////////////////////////////////////////

		RightBackUp = new OctTree(this);
		Math::glCreatePoint3(RightBackUp->bbox.min, mid[0], min[1], mid[2]);
		Math::glCreatePoint3(RightBackUp->bbox.max, max[0], mid[1], max[2]);
		RightBackUp->Build(index, indexCount, vertex, vertexCount);

		RightBackDown = new OctTree(this);
		Math::glCreatePoint3(RightBackDown->bbox.min, mid[0], min[1], min[2]);
		Math::glCreatePoint3(RightBackDown->bbox.max, max[0], mid[1], mid[2]);
		RightBackDown->Build(index, indexCount, vertex, vertexCount);

		LeftBackUp = new OctTree(this);
		Math::glCreatePoint3(LeftBackUp->bbox.min, min[0], min[1], mid[2]);
		Math::glCreatePoint3(LeftBackUp->bbox.max, mid[0], mid[1], max[2]);
		LeftBackUp->Build(index, indexCount, vertex, vertexCount);

		LeftBackDown = new OctTree(this);
		Math::glCreatePoint3(LeftBackDown->bbox.min, min[0], min[1], min[2]);
		Math::glCreatePoint3(LeftBackDown->bbox.max, mid[0], mid[1], mid[2]);
		LeftBackDown->Build(index, indexCount, vertex, vertexCount);
	}
	else
	{
		isFinal = true;
	}
	return this;
}
