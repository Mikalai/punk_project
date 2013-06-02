#include <vector>
#include <fstream>
#include "../video_driver.h"
#include "../renderable_builder.h"
#include "../primitive_type.h"
#include "frustum_mesh.h"
#include "../../../math/relations.h"
#include "../../../math/line3d.h"
#include "../../../math/plane.h"

namespace GPU
{
	Renderable* AsRenderable(const Math::Frustum &value, VideoDriver *driver)
	{
		RenderableBuilder b(driver);
		b.Begin(PrimitiveType::LINES);
		b.Color3f(1,1,1);
		b.Vertex3fv(value.GetPoint(Math::Frustum::FLB));
		b.Color3f(1,1,1);
		b.Vertex3fv(value.GetPoint(Math::Frustum::FLT));

		b.Color3f(1,1,1);
		b.Vertex3fv(value.GetPoint(Math::Frustum::FLT));
		b.Color3f(1,1,1);
		b.Vertex3fv(value.GetPoint(Math::Frustum::FRT));

		b.Color3f(1,1,1);
		b.Vertex3fv(value.GetPoint(Math::Frustum::FRT));
		b.Color3f(1,1,1);
		b.Vertex3fv(value.GetPoint(Math::Frustum::FRB));

		b.Color3f(1,1,1);
		b.Vertex3fv(value.GetPoint(Math::Frustum::FRB));
		b.Color3f(1,1,1);
		b.Vertex3fv(value.GetPoint(Math::Frustum::FLB));


		b.Color3f(1,1,1);
		b.Vertex3fv(value.GetPoint(Math::Frustum::NLB));
		b.Color3f(1,1,1);
		b.Vertex3fv(value.GetPoint(Math::Frustum::NLT));

		b.Color3f(1,1,1);
		b.Vertex3fv(value.GetPoint(Math::Frustum::NLT));
		b.Color3f(1,1,1);
		b.Vertex3fv(value.GetPoint(Math::Frustum::NRT));

		b.Color3f(1,1,1);
		b.Vertex3fv(value.GetPoint(Math::Frustum::NRT));
		b.Color3f(1,1,1);
		b.Vertex3fv(value.GetPoint(Math::Frustum::NRB));

		b.Color3f(1,1,1);
		b.Vertex3fv(value.GetPoint(Math::Frustum::NRB));
		b.Color3f(1,1,1);
		b.Vertex3fv(value.GetPoint(Math::Frustum::NLB));


		b.Color3f(1,1,1);
		b.Vertex3fv(value.GetPoint(Math::Frustum::NLB));
		b.Color3f(1,1,1);
		b.Vertex3fv(value.GetPoint(Math::Frustum::FLB));

		b.Color3f(1,1,1);
		b.Vertex3fv(value.GetPoint(Math::Frustum::NLT));
		b.Color3f(1,1,1);
		b.Vertex3fv(value.GetPoint(Math::Frustum::FLT));

		b.Color3f(1,1,1);
		b.Vertex3fv(value.GetPoint(Math::Frustum::NRT));
		b.Color3f(1,1,1);
		b.Vertex3fv(value.GetPoint(Math::Frustum::FRT));

		b.Color3f(1,1,1);
		b.Vertex3fv(value.GetPoint(Math::Frustum::NRB));
		b.Color3f(1,1,1);
		b.Vertex3fv(value.GetPoint(Math::Frustum::FRB));
		b.End();

		return b.ToRenderable();
	}

	GPU::Renderable* AsRenderable(const Math::ClipSpace& value, VideoDriver* driver)
	{
//		std::vector<Math::Line3D> lines;
//		if (Math::NOT_INTERSECT == Math::CrossPlanes(value.GetPlanes(), lines))
//			return nullptr;

//		RenderableBuilder r(driver);
//		r.Begin(PrimitiveType::LINES);
//		//	look for lines pair intersection.
//		for (size_t i = 0; i != lines.size()-1; ++i)
//		{
//			Math::vec3 p[2];
//			int index = 0;
//			for (size_t j = i+1; j != lines.size(); ++j)
//			{
//				if (Math::CrossLineLine(lines[i], lines[j], p[index]) ==  Math::INTERSECT)
//				{
//					if (Math::ClassifyPoint(p[index], value) == Math::OUTSIDE)
//						continue;
//					else
//						++index;
//				}
//				if (index == 2)
//					break;
//			}

//			if (index == 2)
//			{
//				r.Color3f(1,1,1);
//				r.Vertex3fv(p[0]);
//				r.Color3f(1,1,1);
//				r.Vertex3fv(p[1]);
//			}
//		}
//		r.End();
//		return r.ToRenderable();
				RenderableBuilder r(driver);
				r.Begin(PrimitiveType::LINES);
				for (size_t i = 0; i != value.size(); ++i)
				{
					for (size_t j = i+1; j != value.size(); ++j)
					{
						const Math::Plane& a = value[i];
						const Math::Plane& b = value[j];
						Math::Line3D line;
						if (Math::CrossPlanePlane(a, b, line) != Math::Relation::INTERSECT)
							continue;
						{
							auto org = line.GetOrigin() - line.GetDirection() * 1000.0f;
							auto dst = line.GetOrigin() + line.GetDirection() * 1000.0f;
							line.SetOriginDestination(org, dst);
						}

						for (size_t k = 0; k != value.size(); ++k)
						{
							if (k == i || k == j)
								continue;
							Math::Line3D ray;
							if (Math::ClipExteriorLine(line, value[k], ray) == Math::INTERSECT)
								line = ray;
						}

						//if (!skip && was_start && was_end && line.SegmentLength() > 1e-3)
						{
							if (Math::ClassifyPoint(line.GetOrigin(), value) == Math::OUTSIDE ||
									Math::ClassifyPoint(line.GetDestination(), value) == Math::OUTSIDE)
								continue;
							r.Color3f(1,1,1);
							r.Vertex3fv(line.GetOrigin());
							r.Color3f(1,1,1);
							r.Vertex3fv(line.GetDestination());
						}
					}
				}
				r.End();

				return r.ToRenderable();
	}

	GPU::Renderable* PUNK_ENGINE_API AsRenderable(const Math::Line3D* value, size_t count, float scale, VideoDriver* driver)
	{
		RenderableBuilder r(driver);
		r.Begin(PrimitiveType::LINES);
		for (size_t i = 0; i != count; ++ i)
		{
			r.Color3f(1,1,1);
			r.Vertex3fv(value[i].GetOrigin() - value[i].GetDirection() * scale);
			r.Color3f(1,1,1);
			r.Vertex3fv(value[i].GetOrigin() + value[i].GetDirection() * scale);
		}
		r.End();
		return r.ToRenderable();
	}

	GPU::Renderable* AsRenderable(const Math::vec3* value, size_t count, VideoDriver* driver)
	{
		RenderableBuilder r(driver);
		r.Begin(PrimitiveType::POINTS);
		for (size_t i = 0; i != count; ++i)
		{
			r.Color3f(1,1,1);
			r.Vertex3fv(value[i]);
		}
		r.End();
		return r.ToRenderable();
	}

	GPU::Renderable* AsRenderable(const Math::Plane* planes, size_t count, const Math::Frustum& frustum, VideoDriver* driver)
	{
		return nullptr;
	}
}
