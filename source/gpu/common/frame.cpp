#include <memory>
#include "frame_buffer/module.h"
#include "frame.h"
#include "video_driver.h"
#include "render/module.h"
#include "renderable_builder.h"
#include "primitive_type.h"
#include "texture/module.h"
#include "texture/text_surface.h"

namespace Gpu
{
    Frame::Frame(VideoDriver* driver)
    {
        m_driver = driver;
        m_state.push(new CoreState);
    }

    Frame::~Frame()
    {
        //	next should be delete in destructor
        while (!m_state.empty())
        {
            delete m_state.top();
            m_state.pop();
        }

        while (!m_texts.empty())
        {
            delete m_texts.back();
            m_texts.pop_back();
        }
    }  

    void Frame::SetClearColor(const Math::vec4& value)
    {
        Top()->render_state->m_clear_color = value;
    }

    void Frame::SetClearColor(float r, float g, float b, float a)
    {
        Top()->render_state->m_clear_color.Set(r, g, b, a);
    }

    void Frame::SetClearDepth(float value)
    {
        Top()->render_state->m_clear_depth = value;
    }

    void Frame::Clear(bool color, bool depth, bool stencil)
    {
        if (!Top()->m_active_rendering)
            throw System::PunkException(L"Can't perform clear operation, because target is not specified");
        GetVideoDriver()->SetClearColor(Top()->render_state->m_clear_color);
        GetVideoDriver()->SetClearDepth(Top()->render_state->m_clear_depth);
        GetVideoDriver()->Clear(color, depth, stencil);
//        m_current_target->SetClearColor(Top()->render_state->m_clear_color);
//        m_current_target->SetClearDepth(Top()->render_state->m_clear_depth);
//        m_current_target->Clear(color, depth, stencil);
    }

    const Math::vec4 Frame::GetClearColor() const
    {
        return Top()->render_state->m_clear_color;
    }

    void Frame::BeginRendering(FrameBuffer *target)
    {
        if (Top()->m_active_rendering)
            throw System::PunkException(L"Rendering is already started. Call EndRendering() before");
        Top()->m_active_rendering = true;
        m_current_frame_buffer = target;
        if (m_current_frame_buffer)
            m_current_frame_buffer->Bind();
        GetVideoDriver()->SetViewport(0, 0, GetVideoDriver()->GetWindow()->GetWidth(), GetVideoDriver()->GetWindow()->GetHeight());
    }

    void Frame::BeginRendering()
    {
        BeginRendering(nullptr);
    }

//    void Frame::BeginRendering(Texture2D *color_buffer, Texture2D *depth_buffer)
//    {
//        if (Top()->m_active_rendering)
//            throw System::PunkException(L"Rendering is already started. Call EndRendering() before");
//        m_current_target = m_driver->CreateRenderTargetToTexture2D(color_buffer, depth_buffer);
//        BeginRendering(m_current_target, true);
//    }

    void Frame::EndRendering()
    {
        //	array of batches should be submitted to the actual rendering
        RenderPass pass(m_driver, m_batches);
        pass.Run();
        m_batches.clear();
        //m_driver->SwapBuffers();
        Top()->m_active_rendering = false;
        if (m_current_frame_buffer)
            m_current_frame_buffer->Unbind();
    }

    void Frame::Submit(Renderable* value, bool destroy)
    {
        if (!value)
            return;
        Batch* batch = new Batch;
        batch->m_renderable = value;
        batch->m_state = m_state.top()->Clone(CoreState::ALL_STATES);
        batch->m_destroy = destroy;
        m_batches.push_back(batch);
    }

    void Frame::PushAllState()
    {
        m_state.push(m_state.top()->Clone(CoreState::ALL_STATES));
    }

    void Frame::PopAllState()
    {
        if (!m_state.top()->Dec())
            delete m_state.top();
        m_state.pop();
    }

    void Frame::PushViewState()
    {
        CoreState* state = m_state.top();
        state = state->Clone(CoreState::VIEW_STATE);
        m_state.push(state);
    }

    void Frame::PopViewState()
    {
        PopAllState();
    }

    void Frame::PushLightState()
    {
        m_state.push(m_state.top()->Clone(CoreState::LIGHT_STATE));
    }

    void Frame::PopLightState()
    {
        PopAllState();
    }

    void Frame::PushRenderState()
    {
        m_state.push(m_state.top()->Clone(CoreState::RENDER_STATE));
    }

    void Frame::PopRenderState()
    {
        PopAllState();
    }

    void Frame::PushBatchState()
    {
        m_state.push(m_state.top()->Clone(CoreState::BATCH_STATE));
    }

    void Frame::PopBatchState()
    {
        PopAllState();
    }

    void Frame::PushTextureState()
    {
        m_state.push(m_state.top()->Clone(CoreState::TEXTURE_STATE));
    }

    void Frame::PopTextureState()
    {
        PopAllState();
    }

    void Frame::SetWorldMatrix(const Math::mat4& value)
    {
        Top()->batch_state->m_world = value;
    }

    void Frame::MultWorldMatrix(const Math::mat4& value)
    {
        Top()->batch_state->m_world *= value;
    }

    void Frame::SetViewMatrix(const Math::mat4& value)
    {
        Top()->view_state->m_view = value;
        Top()->view_state->m_camera_position = value.Inversed() * Math::vec3(0,0,0);
    }

    void Frame::SetProjectionMatrix(const Math::mat4& value)
    {
        Top()->view_state->m_projection = value;
    }

    void Frame::SetDiffuseColor(const Math::vec4& value)
    {
        Top()->batch_state->m_material.m_diffuse_color = value;
    }

    void Frame::SetDiffuseColor(float r, float g, float b, float a)
    {
        Top()->batch_state->m_material.m_diffuse_color.Set(r, g, b, a);
    }

    void Frame::SetDiffuseMap(int index, Texture2D *value, int slot)
    {
        Top()->texture_state->m_diffuse_map[index] = value;
        Top()->texture_state->m_diffuse_slot[index] = slot;
    }

    void Frame::SetNormalMap(Texture2D* value, int slot)
    {
        Top()->texture_state->m_normal_map = value;
        Top()->texture_state->m_normal_map_slot = slot;
    }

    void Frame::SetTextMap(Texture2D *value, int slot)
    {
        Top()->texture_state->m_text_map = value;
        Top()->texture_state->m_text_map_slot = slot;
    }    

    void Frame::SetFontMap(Texture2D* value, int slot)
    {
        Top()->texture_state->m_text_map = value;
        Top()->texture_state->m_text_map_slot = slot;
    }

    void Frame::EnableDiffuseShading(bool value)
    {
        Top()->render_state->m_enable_diffuse_shading = value;
    }

    void Frame::EnableSpecularShading(bool value)
    {
        Top()->render_state->m_enable_specular_shading = value;
    }

    //    void Frame::EnableBumpMapping(bool value)
    //    {
    //        Top()->render_state->m_enable_bump_maping_shading = value;
    //    }

    void Frame::EnableSkinning(bool value)
    {
        Top()->render_state->m_enable_skinning = value;
    }

    void Frame::SetBoneMatrix(int bone_index, const Math::mat4& value)
    {
        Top()->batch_state->m_bone_matrix[bone_index] = value;
    }

    void Frame::SetSpecularColor(const Math::vec4& value)
    {
        Top()->batch_state->m_material.m_specular_color = value;
    }

    void Frame::SetSpecularMap(Texture2D* value, int slot)
    {
        Top()->texture_state->m_specular_map = value;
        Top()->texture_state->m_specular_map_slot = slot;
    }

    void Frame::SetBumpMap(Texture2D* value, int slot)
    {
        Top()->texture_state->m_normal_map = value;
        Top()->texture_state->m_normal_map_slot = slot;
    }

    void Frame::CastShadows(bool value)
    {
        Top()->batch_state->m_cast_shadows = value;
    }

    void Frame::ReceiveShadow(bool value)
    {
        Top()->batch_state->m_receive_shadows = value;
    }   

    const Math::mat4& Frame::GetWorldMatrix() const
    {
        return Top()->batch_state->m_world;
    }

    const Math::mat4& Frame::GetViewMatrix() const
    {
        return Top()->view_state->m_view;
    }

    const Math::mat4& Frame::GetProjectionMatrix() const
    {
        return Top()->view_state->m_projection;
    }

    const Math::vec4& Frame::GetDiffuseColor() const
    {
        return Top()->batch_state->m_material.m_diffuse_color;
    }

    const Texture2D* Frame::GetDiffuseMap(int index) const
    {
        return Top()->texture_state->m_diffuse_map[index];
    }

    const Math::mat4& Frame::GetBoneMatrix(int bone_index) const
    {
        return Top()->batch_state->m_bone_matrix[bone_index];
    }

    const Math::vec4& Frame::GetSpecularColor() const
    {
        return Top()->batch_state->m_material.m_specular_color;
    }

    const Texture2D* Frame::GetSpecularMap() const
    {
        return Top()->texture_state->m_specular_map;
    }

    const Texture2D* Frame::GetBumpMap() const
    {
        return Top()->texture_state->m_normal_map;
    }

    const Math::ClipSpace& Frame::GetClipSpace() const
    {
        return Top()->view_state->m_clip_space;
    }

    void Frame::EnableBlending(bool value)
    {
        Top()->render_state->m_enable_blending = value;
    }

    void Frame::EnableDepthTest(bool value)
    {
        Top()->render_state->m_depth_test = value;
    }

    void Frame::SetBlendColor(const Math::vec4& value)
    {
        Top()->render_state->m_blend_color = value;
    }

    void Frame::SetBlendColor(float r, float g, float b, float a)
    {
        Top()->render_state->m_blend_color.Set(r, g, b, a);
    }

    void Frame::SetBlendFunc(BlendFunction src, BlendFunction dst)
    {
        Top()->render_state->m_blend_src = src;
        Top()->render_state->m_blend_dst = dst;
    }

    //void Frame::EnableSpecularShading(bool value)
    //{
    //	Top()->m_enable_specular_shading = value;
    //}

    //void Frame::EnableBumpMapping(bool value)
    //{
    //	Top()->m_enable_bump_mapping = value;
    //}

    //void Frame::EnableDiffuseShading(bool value)
    //{
    //	Top()->m_enable_diffuse_shading = value;
    //}

    //void Frame::EnableSkinning(bool value)
    //{
    //	Top()->m_enable_skinning = value;
    //}

    void Frame::SetShadowModel(ShadowModel value)
    {
        Top()->render_state->m_shadow_model = value;
    }

    void Frame::SetTexture2DArray(Texture2DArray *value, int slot)
    {
        Top()->texture_state->m_texture_array = value;
        Top()->texture_state->m_texture_array_slot = slot;
    }

    void Frame::SetShadowMapIndex(int shadow_map, int index)
    {
        Top()->texture_state->m_texture_array_shadow_map_layer[shadow_map] = index;
    }

    void Frame::SetDiffuseMapIndex(int diffuse_map, int index)
    {
        Top()->texture_state->m_texture_array_diffuse_map_layer[diffuse_map] = index;
    }

    void Frame::SetNormalMapIndex(int index)
    {
        Top()->texture_state->m_texture_array_normal_map_layer = index;
    }

    void Frame::SetShadowMapSize(const Math::ivec2& value)
    {
        Top()->render_state->m_shadow_map_size = value;
    }

    void Frame::SetShadowMapSize(int width, int height)
    {
        Top()->render_state->m_shadow_map_size.Set(width, height);
    }

    void Frame::EnableWireframe(bool value)
    {
        Top()->render_state->m_enable_wireframe = value;
    }

    void Frame::EnableTerrainRendering(bool value)
    {
        Top()->render_state->m_enable_terrain = value;
    }

    void Frame::EnableLighting(bool value)
    {
        Top()->render_state->m_enable_lighting = value;
    }

    void Frame::EnableShadows(bool value)
    {
        Top()->render_state->m_enable_shadows = value;
    }

    void Frame::EnableTexturing(bool value)
    {
        Top()->render_state->m_enable_texture = value;
    }

    void Frame::EnableFontRendering(bool value)
    {
        Top()->render_state->m_enable_font_rendering = value;
    }

    void Frame::SetAmbientColor(float value)
    {
        Top()->batch_state->m_material.m_ambient_color = value;
    }

    void Frame::SetClipSpace(const Math::ClipSpace& value)
    {
        Top()->view_state->m_clip_space = value;
    }

    void Frame::SetHeightMap(Texture2D* value, int slot)
    {
        Top()->texture_state->m_height_map = value;
        Top()->texture_state->m_height_map_slot = slot;
    }

    void Frame::SetLineWidth(float value)
    {
        Top()->render_state->m_line_width = value;
    }

    void Frame::SetPointSize(float value)
    {
        Top()->render_state->m_point_size = value;
    }

    void Frame::SetTextureMatrix(const Math::mat4& value)
    {
        Top()->batch_state->m_texture_matrix = value;
    }

    void Frame::SetLocalMatrix(const Math::mat4& value)
    {
        Top()->batch_state->m_local = value;
    }

    void Frame::SetBoundingSphere(const Math::BoundingSphere &value)
    {
        Top()->batch_state->m_bsphere = value;
    }

    void Frame::EnableBoundBoxRendering(bool value)
    {
        Top()->render_state->m_enable_bounding_box_rendering = value;
    }

    void Frame::EnableDepthRendering(bool value)
    {
        Top()->render_state->m_render_depth = value;
    }

    bool Frame::IsEnabledBoundingBoxRendering() const
    {
        return Top()->render_state->m_enable_bounding_box_rendering;
    }

    void Frame::EnableBoundingSphereRendering(bool value)
    {
        Top()->render_state->m_enable_bounding_sphere_rendering = value;
    }

    bool Frame::IsEnabledBoundingSphereRendering() const
    {
        return Top()->render_state->m_enable_bounding_sphere_rendering;
    }

    void Frame::EnableNaviMeshRendering(bool value)
    {
        Top()->render_state->m_enable_navi_mesh_rendering = value;
    }

    bool Frame::IsEnabledNaviMeshRendering()
    {
        return Top()->render_state->m_enable_navi_mesh_rendering;
    }

    void Frame::SetSpecularFactor(float value)
    {
        Top()->batch_state->m_material.m_specular_factor = value;
    }

    void Frame::SetTextColor(const Math::vec4& value)
    {
        Top()->batch_state->m_material.m_text_color = value;
    }

    void Frame::SetTextColor(float r, float g, float b, float a)
    {
        Top()->batch_state->m_material.m_text_color.Set(r, g, b, a);
    }

    void Frame::EnablePerVertexColor(bool value)
    {
        Top()->render_state->m_enable_vertex_color = value;
    }

    void Frame::SetLightModel(LightModel value)
    {
        Top()->light_state->m_light_model = value;
    }

    LightParameters& Frame::Light(int slot)
    {
        if (slot < MAX_LIGHTS)
            return Top()->light_state->m_lights[slot];
        throw System::PunkException(L"Too many light");
    }

    CoreState* Frame::Top()
    {
        return m_state.top();
    }

    const CoreState* Frame::Top() const
    {
        return m_state.top();
    }

    void Frame::DrawLine(const Math::vec3& start, const Math::vec3& end)
    {
        PushAllState();
        EnableLighting(false);
        EnableTexturing(false);
        RenderableBuilder b(m_driver);
        b.Begin(PrimitiveType::LINES);
        b.Vertex3fv(start);
        b.Vertex3fv(end);
        b.End();
        Renderable* r(b.ToRenderable());
        Submit(r, true);
        PopAllState();
    }

    void Frame::DrawLine(float x1, float y1, float x2, float y2)
    {
        PushAllState();
        EnableLighting(false);
        EnableTexturing(false);
        SetProjectionMatrix(Math::mat4::CreateIdentity());
        SetViewMatrix(Math::mat4::CreateIdentity());
        SetWorldMatrix(Math::mat4::CreateIdentity());

        float width = GetVideoDriver()->GetWindow()->GetWidth();
        float height = GetVideoDriver()->GetWindow()->GetHeight();

        Math::vec3 p1;
        p1[0] = -1.0f + 2.0f * x1 / width;
        p1[1] = -1.0f + 2.0f * y1 / height;
        p1[2] = 0;

        Math::vec3 p2;
        p2[0] = -1.0f + 2.0f * x2 / width;
        p2[1] = -1.0f + 2.0f * y2 / height;
        p2[2] = 0;

        RenderableBuilder b(m_driver);
        b.Begin(PrimitiveType::LINES);
        b.Vertex3fv(p1);
        b.Vertex3fv(p2);
        b.End();
        Renderable* r(b.ToRenderable());
        Submit(r, true);
        PopAllState();
    }

    void Frame::DrawPoint(float x, float y)
    {
        PushAllState();
        SetProjectionMatrix(Math::mat4::CreateIdentity());
        SetViewMatrix(Math::mat4::CreateIdentity());
        SetWorldMatrix(Math::mat4::CreateIdentity());

        float width = GetVideoDriver()->GetWindow()->GetWidth();
        float height = GetVideoDriver()->GetWindow()->GetHeight();

        Math::vec3 p1;
        p1[0] = -1.0f + 2.0f * x / width;
        p1[1] = -1.0f + 2.0f * y / height;
        p1[2] = 0;

        RenderableBuilder b(m_driver);
        b.Begin(PrimitiveType::POINTS);
        b.Vertex3fv(p1);
        b.End();
        Renderable* r(b.ToRenderable());
        Submit(r, true);
        PopAllState();
    }

    void Frame::DrawPoint(float x, float y, float z)
    {
        PushAllState();
        EnableLighting(false);
        EnableTexturing(false);
        RenderableBuilder b(m_driver);
        b.Begin(PrimitiveType::POINTS);
        b.Vertex3fv(Math::vec3(x, y, z));
        b.End();
        Renderable* r(b.ToRenderable());
        Submit(r, true);
        PopAllState();
    }

    void Frame::DrawPoint(const Math::vec3& v)
    {
        PushAllState();
        EnableLighting(false);
        EnableTexturing(false);
        RenderableBuilder b(m_driver);
        b.Begin(PrimitiveType::POINTS);
        b.Vertex3fv(v);
        b.End();
        Renderable* r(b.ToRenderable());
        Submit(r, true);
        PopAllState();
    }

    void Frame::DrawQuad(float x, float y, float width, float height)
    {
        PushAllState();
        EnableLighting(false);
        SetProjectionMatrix(Math::mat4::CreateOrthographicProjection2(0, GetVideoDriver()->GetWindow()->GetWidth(),
                                                                     0, GetVideoDriver()->GetWindow()->GetHeight(),
                                                                     -1, 1));
        RenderableBuilder b(GetVideoDriver());
        b.Begin(PrimitiveType::QUADS);
        b.TexCoord2f(0,0);
        b.Vertex3f(x, y, 0);
        b.TexCoord2f(1, 0);
        b.Vertex3f(x+width, y, 0);
        b.TexCoord2f(1,1);
        b.Vertex3f(x+width, y+height,0);
        b.TexCoord2f(0, 1);
        b.Vertex3f(x, y+height, 0);
        b.End();
        Renderable* r(b.ToRenderable());
        Submit(r, true);
        PopAllState();
    }

    void Frame::DrawQuad(const Math::Rect& rect)
    {
        DrawQuad(rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight());
    }

    void Frame::DrawCircleXY(float x, float y, float z, float r)
    {
        PushAllState();
        EnableBlending(false);
        EnableLighting(false);
        EnableDepthTest(false);        
        RenderableBuilder b(m_driver);
        b.Begin(PrimitiveType::LINES);
        int n = 32;
        float dphi = Math::PI / (float)n * 2.0f;
        for (int i = 0; i < n; ++i)
        {
            {
                float xx = x + r * cos(dphi*(float)i);
                float yy = y + r * sin(dphi*(float)i);
                float zz = z;
                b.Vertex3f(xx, yy, zz);
            }
            {
                float xx = x + r * cos(dphi*(float)(i+1));
                float yy = y + r * sin(dphi*(float)(i+1));
                float zz = z;
                b.Vertex3f(xx, yy, zz);
            }
        }
        Submit(b.ToRenderable(), true);
        PopAllState();
    }

    void Frame::DrawText2D(const Math::vec2 &pos, const Math::vec2 &size, const System::string &value)
    {
    }

    void Frame::DrawText2D(float x, float y, const System::string &value)
    {
        PushAllState();
        std::unique_ptr<TextSurface> surface(new TextSurface(GetVideoDriver()));
        surface->SetText(value);
        int text_width = surface->GetTexture()->GetWidth();
        int text_height = surface->GetTexture()->GetHeight();
        SetTextMap(surface->GetTexture(), 0);
        EnableDepthTest(false);
        EnableBlending(true);
        EnableTexturing(false);
        EnableLighting(false);
        EnableFontRendering(true);
        SetBlendFunc(BlendFunction::SourceAlpha, BlendFunction::OneMinusSrcAlpha);
        SetWorldMatrix(Math::mat4::CreateTranslate(x, y, 0));
        int width = GetVideoDriver()->GetWindow()->GetWidth();
        int height = GetVideoDriver()->GetWindow()->GetHeight();
        SetProjectionMatrix(Math::mat4::CreateOrthographicProjection2(0, width, 0, height, -1, 1));
        SetViewMatrix(Math::mat4::CreateIdentity());

        RenderableBuilder b(GetVideoDriver());
        b.Begin(PrimitiveType::QUADS);
        b.TexCoord2f(0, 0);
        b.Vertex3f(x, y, 0);
        b.TexCoord2f(1, 0);
        b.Vertex3f(x+text_width, y, 0);
        b.TexCoord2f(1, 1);
        b.Vertex3f(x+text_width, y+text_height, 0);
        b.TexCoord2f(0, 1);
        b.Vertex3f(x, y+text_height, 0);
        b.End();

        Submit(b.ToRenderable(), true);

        PopAllState();
        m_texts.push_back(surface.release());
    }

    void DrawCircleXY(const Math::vec3& c, float r);

    FogDescription& Frame::Fog()
    {
        return Top()->render_state->m_fog;
    }

    const FogDescription& Frame::Fog() const
    {
        return Top()->render_state->m_fog;
    }

    VideoDriver* Frame::GetVideoDriver() const
    {
        return m_driver;
    }

    std::vector<Batch*>& Frame::GetBatches()
    {
        return m_batches;
    }

    const std::vector<Batch*>& Frame::GetBatches() const
    {
        return m_batches;
    }

    void Frame::SetShadowMaps(Texture2DArray *value)
    {
        m_shadow_maps = value;
    }

    const Math::vec2 Frame::FindZRange(const Math::mat4 &view) const
    {
        float min = std::numeric_limits<float>::infinity();
        float max = -std::numeric_limits<float>::infinity();

        for (Batch* o : GetBatches())
        {
            auto transf = view*o->m_state->batch_state->m_bsphere.GetCenter();
            if (transf.Z() + o->m_state->batch_state->m_bsphere.GetRadius() > max)
                max = transf.Z() + o->m_state->batch_state->m_bsphere.GetRadius();
            if (transf.Z() - o->m_state->batch_state->m_bsphere.GetRadius() < min)
                min = transf.Z() - o->m_state->batch_state->m_bsphere.GetRadius();
        }
        return Math::vec2(min, max);
    }
}
