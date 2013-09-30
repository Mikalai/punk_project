#include "test13.h"
#include <type_traits>

namespace Test13
{
//    class Selectable
//    {
//    public:
//        int m_index;
//        float m_t;
//        Math::mat4 m_view_model;
//        float m_width;
//        float m_height;
//        float m_fovy;
//        Math::vec3 m_view_position;
//        Math::vec3 m_view_direction;
//        float m_mouse_x;
//        float m_mouse_y;

//        void Select(const std::vector<Math::Line3D>& lines)
//        {
//            using namespace Math;
//            //	view-world camera
//            mat4 view_world(m_view_model);

//            //	aspect ratio as used in opengl
//            float aspect = m_width / m_height;
//            //	translate x and y to projection plane
//            float proj_x = aspect*(-1.0f + 2.0f * (float)mouse_x / m_width);
//            float proj_y = -1.0f + 2.0f * (float)(m_height - mouse_y) / m_height;

//            //	find mouse point in the view space
//            vec3 mouse_in_view(proj_x, proj_y, -1.0f / tan(m_fovy/2.0f));
//            //	translate mouse point to the world space
//            vec4 mouse_in_world_4 = (view_world.Inversed() * vec4(mouse_in_view, 1.0f));
//            mouse_in_world_4 /= mouse_in_world_4[3];
//            vec3 mouse_in_world = mouse_in_world_4.ToVec3();
//            m_mouse_world = mouse_in_world;
//            //	find second point
//            proj_x = aspect*(-1.0f + 2.0f * (float)(mouse_x + m_selection_size) / m_width);
//            proj_y = -1.0f + 2.0f * (float)(m_height - (mouse_y + m_selection_size) ) / m_height;
//            vec3 near_point_in_view(proj_x, proj_y, -1.0f / tan(m_fovy/2.0f));
//            vec4 near_point_in_view_4d = (view_world.Inversed() * vec4(near_point_in_view, 1.0f));
//            near_point_in_view_4d /= near_point_in_view_4d[3];
//            vec3 near_point_in_world = near_point_in_view_4d.ToVec3();
//            //	translate view center to the world
//            vec3 view_pos((view_world.Inversed() * vec4(0,0,0, 1.0f)).ToVec3());
//            m_view_position = view_pos;
//            m_view_direction = mouse_in_world - view_pos;

//            //	find size of selection region in the world
//            float max_dst = (near_point_in_world - mouse_in_world).Length()/(view_pos - mouse_in_world).Length();

//            //	create a ray to intersect everything with it
//            Line3D ray;
//            ray.SetOriginDestination(view_pos, mouse_in_world);
//            Result res;

//            float min_dst = std::numeric_limits<float>::infinity();
//            int index;
//            for (int track_index = 0; track_index < lines.size(); ++track_index)
//            {
//                const Line3D missile_track = lines[track_index];

//                float dst;
//                CrossLineLine(ray, missile_track, t1, t2, dst);
//                if (dst < min_dst)
//                {
//                    min_dst = dst;
//                    index = track_index;
//                }

//            }

//            return m_last_result = res;
//        }
//    };

    class TestApp : public Punk::Application
    {
        std::map<int, std::map<int, std::pair<int, Math::Line3D>>> result;
        Gpu::Renderable* m_renderable;
        Gpu::Renderable* m_renderable2;
        Gpu::Renderable* m_renderable3;
        Gpu::Renderable* m_renderable4;
        Math::FrustumCore m_frustum;
        Math::mat4 m_projection;
        float m_a;
        float a, b, h;
        float m_rz;
    public:

        void MakeResult()
        {
            int i, j;
            Math::vec3 org, dir;

            {
                i = 0;
                j = 1;
                org.Set(-5.5229, 0, -10);
                dir.Set(0, -1,  0);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }

            {
                i = 0;
                j = 2;
                org.Set(0, 0, 0);
                dir.Set(-0.4545, 0.34087, -0.82294);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }

            {
                i = 0;
                j = 3;
                org.Set(0, 0, 0);
                dir.Set(0.4545, 0.34087, 0.82294);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }

            {
                i = 0;
                j = 4;
                org.Set(-0.55228, 0, -1);
                dir.Set(0, 1, 0);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }

            {
                i = 0;
                j = 5;
                org.Set(0.012392, 0.072105, 0.022437);
                dir.Set(-0.45553, 0.33495, -0.82481);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }

            {
                i = 0;
                j = 6;
                org.Set(0.012392, -0.072105, 0.022437);
                dir.Set(0.45553, 0.33495, 0.82481);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }

            {
                i = 0;
                j = 7;
                org.Set(-12.5595, 0, -22.741);
                dir.Set(0, -1, 0);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }

            {
                i = 1;
                j = 2;
                org.Set(-0.017349, 4.1651, -10);
                dir.Set(0.99999, 0.0041652, 0);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }

            {
                i = 1;
                j = 3;
                org.Set(-0.017349, -4.1651, -10);
                dir.Set(-0.99999, 0.0041652, 0);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }

            {
                i = 1;
                j = 4;
                org.Set(-154.6876, 0, -10);
                dir.Set(0, 1, 0);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }

            {
                i = 1;
                j = 5;
                org.Set(0, 4.1421, -10);
                dir.Set(1, 0, 0);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }

            {
                i = 1;
                j = 6;
                org.Set(0, -4.1421, -10);
                dir.Set(-1, 0, 0);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }

            {
                i = 1;
                j = 7;
                org.Set(5.5229, 0, -10);
                dir.Set(0, -1, 0);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }

            {
                i = 2;
                j = 3;
                org.Set(0, 0, 0);
                dir.Set(0.99995, 0, 0.0099998);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }
            {
                i = 2;
                j = 4;
                org.Set(0.064386, 0.40178, -0.96399);
                dir.Set(0.9981, -0.020117, 0.058279);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }
            {
                i = 2;
                j = 5;
                org.Set(3.0699, 2.7475, -6.5658);
                dir.Set(-0.91822, 0.14902, -0.36697);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }
            {
                i = 2;
                j = 6;
                org.Set(-0.00041535, -0.041124, 0.098729);
                dir.Set(0.99999, 0.0020562, 0.0050634);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }
            {
                i = 2;
                j = 7;
                org.Set(7.2536, 3.6874, -8.7805);
                dir.Set(-0.79551, 0.23015, -0.56052);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }
            {
                i = 3;
                j = 4;
                org.Set(0.064386, -0.40178, -0.96399);
                dir.Set(-0.9981, -0.020117, -0.058279);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }
            {
                i = 3;
                j = 5;
                org.Set(-0.00041535, 0.041124, 0.098729);
                dir.Set(-0.99999, 0.0020562, -0.0050634);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }
            {
                i = 3;
                j = 6;
                org.Set(3.0699, -2.7475, -6.5658);
                dir.Set(0.91822, 0.14902, 0.36697);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }
            {
                i = 3;
                j = 7;
                org.Set(7.2536, -3.6874, -8.7805);
                dir.Set(0.79551, 0.23015, 0.56052);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }
            {
                i = 4;
                j = 5;
                org.Set(0.067484, 0.47261, -0.96381);
                dir.Set(-0.99802, 0.023665, -0.058275);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }
            {
                i = 4;
                j = 6;
                org.Set(0.067484, -0.47261, -0.96381);
                dir.Set(0.99802, 0.023665, 0.058275);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }
            {
                i = 4;
                j = 7;
                org.Set(19.999, 0, 0.2);
                dir.Set(0, 1, 0);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }
            {
                i = 5;
                j = 6;
                org.Set(0, -6.9389e-018, 0.2);
                dir.Set(1, 0, 0);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }
            {
                i = 5;
                j = 7;
                org.Set(7.2389, 3.6511, -8.7909);
                dir.Set(-0.79597, 0.22776, -0.56085);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }
            {
                i = 6;
                j = 7;
                org.Set(7.2389, -3.6511, -8.7909);
                dir.Set(0.79597, 0.22776, 0.56085);
                result[i][j].first = 0;
                result[i][j].second.SetOriginDirection(org, dir);
            }
        }

        TestApp()            
        {            
            m_frustum = Math::FrustumCreateFromProjectionMatrix(m_projection);
            m_renderable = nullptr;
            m_renderable2 = nullptr;
            m_renderable3 = nullptr;
            m_a = Math::PI / 2.0f - 0.01f;
            a = 20;
            b = 20;
            h = 0;
            m_rz = 0;
            MakeResult();


            m_projection = Math::mat4::CreatePerspectiveProjection(Math::PI / 4.0f, 800, 600, 1, 10.0);
            m_frustum = Math::FrustumCreateFromProjectionMatrix(m_projection);

            //            Math::Plane p0(0.875370000000000, 0, -0.483454000000000, 0);
            //            Math::Plane p1(0, 0, 1, 10);
            //            Math::Plane p2(0.003845030000000, -0.923120000000000, -0.384492000000000, 0);
            //            Math::Plane p3(0.003845030000000, 0.923120000000000, -0.384492000000000, 0);
            //            Math::Plane p4(0.058291000000000, 0, -0.998300000000000, -0.966106000000000);
            //            Math::Plane p5(0, -0.926518000000000, -0.376251000000000, 0.075248600000000);
            //            Math::Plane p6(0, 0.926518000000000, -0.376251000000000, 0.075248600000000);
            //            Math::Plane p7(-0.575987000000000, 0, 0.817459000000000, 11.355700000000000);

            //Math::Plane p[] = { p0, p1, p2, p3, p4, p5, p6, p7 };
            auto p = Math::FrustumToClipSpace(m_frustum);
            size_t size = p.size();

            for (int i = 0; i != size; ++i)
            {
                for (int j = i+1; j != size; ++j)
                {
                    Math::Line3D line;
                    auto res = Math::CrossPlanePlane(p[i], p[j], line);
                    out_message() << L"Result for " << i << " <-> " << j << ": " << p[i].ToString() << L" <-> " << p[j].ToString() << std::endl;
                    if (res != Math::INTERSECT)
                        out_message() << L"\tNo intersection" << std::endl;
                    else
                    {
                        out_message() << L"\tIntersection: " << line.ToString() << std::endl;
                        out_message() << L"\t Should be: " << result[i][j].second.ToString() << std::endl;
                        float c1 = (line.GetOrigin() - result[i][j].second.GetOrigin()).Length();
                        float c2 = (line.GetDirection() - result[i][j].second.GetDirection()).Length();
                        if (c1 > 1e-5 || c2 > 1e-5)
                            out_message() << "FAILED" << std::endl;
                        else
                            out_message() << "SUCCEED" << std::endl;
                        //lines.push_back(line);
                    }
                }
            }

            //  auto p = m_frustum.ToClipSpace();

        }

        const Math::vec3 GetLightPosition()
        {
            auto res = Math::vec3(sin(m_a)*a, h, b*cos(m_a));
            return res;
        }

        const std::vector<Math::Line3D> RecalcLines(const Math::FrustumCore& frustum, const Math::vec3& point)
        {
            std::vector<Math::Line3D> lines;
            Math::ClipSpace space = Math::FrustumBuildClipSpaceFromPoint(frustum, point);
            auto p = space;
            size_t size = p.size();
            for (int i = 0; i != size; ++i)
            {
                for (int j = i+1; j != size; ++j)
                {
                    Math::Line3D line;
                    auto res = Math::CrossPlanePlane(p[i], p[j], line);
                    if (res == Math::INTERSECT)
                        lines.push_back(line);
                }
            }
            return lines;
        }

        const std::vector<Math::vec3> RecalcPoints(const std::vector<Math::Line3D>& lines)
        {
            std::vector<Math::vec3> res;
            Math::CrossLines(lines, res);
            return res;
        }

		const std::vector<Math::vec3> FilterPoints(const std::vector<Math::vec3>& points, const Math::ClipSpace& space)
		{
			std::vector<Math::vec3> res;
			for (auto p : points)
			{
				if (Math::ClassifyPoint(p, space) == Math::INSIDE)
					res.push_back(p);
			}
			return res;
		}

        virtual void OnInit(const Punk::Config&) override
        {
            GetWindow()->SetTitle("Test13");
            m_projection = Math::mat4::CreatePerspectiveProjection(Math::PI / 4.0f, 800, 600, 1, 10.0);
            m_frustum = Math::FrustumCreateFromProjectionMatrix(m_projection);

            if (m_renderable)
                delete m_renderable;
            if (GetVideoDriver())
            {
                Math::ClipSpace space = Math::FrustumBuildClipSpaceFromPoint(m_frustum, GetLightPosition());
                auto lines = RecalcLines(m_frustum, GetLightPosition());
                auto points = RecalcPoints(lines);
                m_renderable = Gpu::AsRenderable(&lines[0], lines.size(), 100.0f, GetVideoDriver());
                m_renderable2 = Gpu::AsRenderable(m_frustum, GetVideoDriver());
                m_renderable3 = Gpu::AsRenderable(space, GetVideoDriver());
                m_renderable4 = Gpu::AsRenderable(&points[0], points.size(), GetVideoDriver());
            }
        }

        virtual void OnMouseWheel(System::MouseWheelEvent *event) override
        {
        }

        virtual void OnMouseMove(System::MouseMoveEvent* event) override
        {
            if (event->rightButton)
                m_rz += 0.01f*float(event->x - event->x_prev);
        }

        virtual void OnResize(System::WindowResizeEvent *event) override
        {
            m_projection = Math::mat4::CreatePerspectiveProjection(Math::PI / 4.0f, event->width, event->height, 1, 10.0);
            m_frustum = Math::FrustumCreateFromProjectionMatrix(m_projection);

            if (m_renderable2)
            {
                delete m_renderable2;
                m_renderable2 = Gpu::AsRenderable(m_frustum, GetVideoDriver());
            }
        }

        virtual void OnKeyDown(System::KeyDownEvent *event) override
        {
            if (event->key == System::PUNK_KEY_LEFT)
                m_a -= 0.01;
            else if (event->key == System::PUNK_KEY_RIGHT)
                m_a += 0.01;

            delete m_renderable;
            delete m_renderable3;
            delete m_renderable4;
            m_renderable4 = nullptr;
            Math::ClipSpace space2;
            Math::vec3 v(1,1,0);
            v.Normalize();
            space2.Add(Math::Plane(v[0], v[1], v[2], 5));
            v.Set(-1,1,0);
            v.Normalize();
            space2.Add(Math::Plane(v[0], v[1], v[2], 5));
            space2.Add(Math::Plane(0, 1, 0, 5));
            space2.Add(Math::Plane(0, -1, 0, 5));
            space2.Add(Math::Plane(0, 0, 1, 5));
            space2.Add(Math::Plane(0, 0, -1, 5));

            Math::ClipSpace space = Math::FrustumBuildClipSpaceFromPoint(m_frustum, GetLightPosition());
            auto lines = RecalcLines(m_frustum, GetLightPosition());
//            std::vector<Math::Line3D> lll;
//            static int kk = 0;
//            static int ll = 0;

//            if (event->key == System::PUNK_KEY_A)
//            {
//                --ll;
//                if (ll < 0)
//                {
//                    --kk;
//                    ll = lines.size()-1;

//                    if (kk < 0)
//                    {
//                        kk = lines.size()-1;
//                    }
//                }

//            }
//            else if (event->key == System::PUNK_KEY_D)
//            {
//                ++ll;
//                if (ll >= lines.size())
//                {
//                    ++kk;
//                    ll = 0;

//                    if (kk >= lines.size())
//                    {
//                        kk = 0;
//                    }
//                }
//            }

//            lll.push_back(lines[kk]);
//            lll.push_back(lines[ll]);

			auto points = RecalcPoints(lines);

			points = FilterPoints(points, space);
			m_renderable = Gpu::AsRenderable(&lines[0], lines.size(), 100.0f, GetVideoDriver());
            m_renderable3 = Gpu::AsRenderable(space, GetVideoDriver());
            if (!points.empty())
                m_renderable4 = Gpu::AsRenderable(&points[0], points.size(), GetVideoDriver());
        }


        virtual void OnRender(Gpu::Frame* frame) override
        {
            frame->SetClearColor(Math::vec4(0.5, 0.5, 0.5, 1));
            frame->EnableDiffuseShading(true);
            float width = GetWindow()->GetWidth();
            float height = GetWindow()->GetHeight();
            frame->SetProjectionMatrix(m_projection);
            frame->SetViewMatrix(Math::mat4::CreateTargetCameraMatrix(Math::vec3(-50, -50, -50), Math::vec3(0, 0, 0), Math::vec3(0, 1, 0)));
            frame->EnableDepthTest(false);
            frame->EnableBlending(true);
            //frame->SetBlendFunc(Gpu::BlendFunction::);
            frame->PushAllState();

            frame->BeginRendering();
            frame->Clear(true, true, true);
            frame->SetWorldMatrix(Math::mat4::CreateTranslate(0, 0, 0));
            //			frame->MultWorldMatrix(Math::mat4::CreateRotation(1, 0, 0, m_x));
            //			frame->MultWorldMatrix(Math::mat4::CreateRotation(0, 1, 0, m_y));
            frame->MultWorldMatrix(Math::mat4::CreateRotation(0, 1, 0, m_rz));
            frame->SetLineWidth(1);
			frame->SetDiffuseColor(1,1,1,0.5);
			//frame->Render(m_renderable);
            frame->SetLineWidth(5);
            frame->SetDiffuseColor(1,0,0,0.5);
		   // frame->Render(m_renderable2);
            frame->SetLineWidth(3);
            frame->SetDiffuseColor(0,0,1,0.5);
            frame->Submit(m_renderable3);
            frame->SetPointSize(10);
			frame->SetDiffuseColor(0, 1, 0, 0.5);
            if (m_renderable4)
			   // frame->Render(m_renderable4);
            frame->PopAllState();

            frame->EndRendering();
        }
    };

    void Test::Run()
    {
        m_result = true;
        TestApp app;
        try
        {
            app.Init(Punk::Config());
            System::Mouse::Instance()->LockInWindow(false);
            app.Run();
        }
        catch(System::PunkException& e)
        {
            out_error() << e.ToString() << std::endl;
            m_result = false;
        }
        catch(...)
        {
            m_result = false;
        }
    }

    bool Test::Succeed()
    {
        return m_result;
    }

}
