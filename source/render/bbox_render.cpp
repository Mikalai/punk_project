//#include "../math/bounding_box.h"
//#include "../math/mat4.h"
//#include "bbox_render.h"
//#include "../system/driver/video/driver.h"
//
//namespace Render
//{
//	void BBoxRender::Render(const Math::BoundingBox& bbox, const Math::mat4& world, const Math::mat4& view, const Math::mat4& proj)
//	{
//		bbox.TransformNode(world);
//		const Math::vec3* p = bbox.TransformedPoints();
//
//		line.SetColor(0,1,0,1);
//		line.SetViewTranform(view);
//		line.SetProjectionTransform(proj);
//		line.Draw(p[0], p[1]);
//		line.Draw(p[1], p[3]);
//		line.Draw(p[3], p[2]);
//		line.Draw(p[2], p[0]);
//
//		line.Draw(p[4], p[5]);
//		line.Draw(p[5], p[7]);
//		line.Draw(p[7], p[6]);
//		line.Draw(p[6], p[4]);
//
//		line.Draw(p[0], p[4]);
//		line.Draw(p[1], p[5]);
//		line.Draw(p[3], p[7]);
//		line.Draw(p[2], p[6]);
//	}
//
//	void BBoxRender::RenderAABB(const Math::BoundingBox& bbox, const Math::mat4& world, const Math::mat4& view, const Math::mat4& proj)
//	{
//		Math::vec3 m_min;
//		Math::vec3 m_max;
//		bbox.TransformNode(world, m_min, m_max);
//
//		Math::vec3 p[8];
//
//		p[0] = Math::vec3(m_min[0], m_min[1], m_min[2]);
//		p[1] = Math::vec3(m_min[0], m_min[1], m_max[2]);
//		p[2] = Math::vec3(m_min[0], m_max[1], m_min[2]);
//		p[3] = Math::vec3(m_min[0], m_max[1], m_max[2]);
//		p[4] = Math::vec3(m_max[0], m_min[1], m_min[2]);
//		p[5] = Math::vec3(m_max[0], m_min[1], m_max[2]);
//		p[6] = Math::vec3(m_max[0], m_max[1], m_min[2]);
//		p[7] = Math::vec3(m_max[0], m_max[1], m_max[2]);
//
//		line.SetColor(1,0,0,1);
//		line.SetViewTranform(view);
//		line.SetProjectionTransform(proj);
//		line.Draw(p[0], p[1]);
//		line.Draw(p[1], p[3]);
//		line.Draw(p[3], p[2]);
//		line.Draw(p[2], p[0]);
//
//		line.Draw(p[4], p[5]);
//		line.Draw(p[5], p[7]);
//		line.Draw(p[7], p[6]);
//		line.Draw(p[6], p[4]);
//
//		line.Draw(p[0], p[4]);
//		line.Draw(p[1], p[5]);
//		line.Draw(p[3], p[7]);
//		line.Draw(p[2], p[6]);
//	}
//}
