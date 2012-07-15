#ifndef _H_VISITOR
#define _H_VISITOR

namespace Logic
{
	class AbstractEntity;
	class ComplexEntity;
	class SimpleEntity;
	class SpaceEntity;

	class Visitor
	{
	public:
		virtual bool Visit(AbstractEntity* e) = 0;
		virtual bool Visit(ComplexEntity* e) = 0;
		virtual bool Visit(SimpleEntity* e) = 0;
		virtual bool Visit(SpaceEntity* e) = 0;
	};
}

#endif