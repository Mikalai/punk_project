#ifndef _H_PUNK_UTLITY_SHAPE_BODY
#define _H_PUNK_UTLITY_SHAPE_BODY

namespace Virtual
{
	class Geometry;
}

namespace Phyiscs
{
	class ShapeBody
	{
	public:
		virtual void Init(Virtual::Geometry* geom);
		virtual ~ShapeBody() {}
	};
}
#endif	//	_H_PUNK_UTLITY_SHAPE_BODY