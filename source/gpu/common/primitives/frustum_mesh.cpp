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
							auto p1 = line.PointAt(-100);
							auto p2 = line.PointAt(100);
							line.SetOriginDestination(p1, p2);
						}

						bool was_start = false;
						bool was_end = false;
						bool skip = false;
						float t0 = 0;
						float t1 = 1;
						for (size_t k = 0; k != value.size(); ++k)
						{
							if (k == i || k == j)
								continue;

							float t;
							auto test = Math::CrossLinePlane(line, value[k], t);

							if (test != Math::Relation::INTERSECT)
							{
								if (test == Math::Relation::BACK)
								{
									skip = true;
									break;
								}
								continue;
							}

							{
								auto pp = line.PointAt(t);
								if (Math::ClassifyPoint(pp, value) == Math::Relation::OUTSIDE)
								{
									std::cout << "Wow" << std::endl;
									continue;
								}
							}

							if (!was_start)
							{
								was_start = true;
								t0 = t;
								line.SetOrigin(line.PointAt(t0));
							}
							else if (!was_end)
							{
								was_end = true;
								t1 = t;
								line.SetDestination(line.PointAt(t1));
							}
							else
							{
								if (t < 0 || t > 1)
									continue;
								if (t > 0.5)
									line.SetDestination(line.PointAt(t));
								else
									line.SetOrigin(line.PointAt(t));
							}
						}
						if (!skip && was_start && was_end && line.SegmentLength() > 1e-3)
						{
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

	GPU::Renderable* PUNK_ENGINE AsRenderable(const Math::Line3D* value, size_t count, float scale, VideoDriver* driver)
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

	GPU::Renderable* AsRenderable(const Math::Plane* planes, size_t count, const Math::Frustum& frustum, VideoDriver* driver);
	{
		RenderableBuilder r(driver);
		r.Begin(PrimitiveType::QUADS);
		for (size_t i = 0; i != count; ++i)
		{

		}
		r.End();
		return r.ToRenderable();
	}
}
