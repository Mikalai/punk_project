#include <utility>
#include <type_traits>
#include "primitive_type.h"

namespace GPU
{
	using PrimitiveTypeDesc = std::pair<PrimitiveType, System::string>;
	static const PrimitiveTypeDesc g_primitive_types[] = {
		PrimitiveTypeDesc(PrimitiveType::POINTS, L"POINT"),
		PrimitiveTypeDesc(PrimitiveType::LINE_STRIP, L"LINE_STRIP"),
		PrimitiveTypeDesc(PrimitiveType::LINE_LOOP, L"LINE_LOOP"),
		PrimitiveTypeDesc(PrimitiveType::LINES, L"LINES"),
		PrimitiveTypeDesc(PrimitiveType::LINE_STRIP_ADJANCECY, L"LINE_STRIP_ADJANCECY"),
		PrimitiveTypeDesc(PrimitiveType::LINES_ADJANCENCY, L"LINES_ADJANCENCY"),
		PrimitiveTypeDesc(PrimitiveType::TRIANGLE_STRIP, L"TRIANGLE_STRIP"),
		PrimitiveTypeDesc(PrimitiveType::TRIANGLE_FAN, L"TRIANGLE_FAN"),
		PrimitiveTypeDesc(PrimitiveType::TRIANGLES, L"TRIANGLES"),
		PrimitiveTypeDesc(PrimitiveType::TRIANGLE_STRIP_ADJANCECY, L"TRIANGLE_STRIP_ADJANCECY"),
		PrimitiveTypeDesc(PrimitiveType::TRIANGLES_ADJANCECY, L"TRIANGLES_ADJANCECY"),
		PrimitiveTypeDesc(PrimitiveType::QUADS, L"QUADS")
	};

	const System::string AsString(const PrimitiveType& v)
	{
		for (size_t i = 0; i != std::extent<decltype(g_primitive_types)>::value; ++i)
		{
			if (g_primitive_types[i].first == v)
				return g_primitive_types[i].second;
		}
		return L"ERROR";
	}
}
