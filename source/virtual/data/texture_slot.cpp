#include <memory>
#include "../../images/module.h"
#include "../../system/environment.h"
#include "material.h"
#include "texture_slot.h"

namespace Virtual
{
    TextureSlot::Cache::Cache(TextureSlot& slot)
        : m_texture(nullptr)
        , m_slot(slot)
    {}

    TextureSlot::Cache::~Cache()
    {
        Drop();
    }

    Gpu::Texture2D* TextureSlot::Cache::GetTexture()
    {        
        return m_texture;
    }

    void TextureSlot::Cache::Drop()
    {
        delete m_texture;
        m_texture = nullptr;
    }

    void TextureSlot::Cache::Update(Gpu::VideoDriver* driver)
    {
        Drop();
        ImageModule::Importer importer;
        std::unique_ptr<ImageModule::Image> image(importer.LoadAnyImage(System::Environment::Instance()->GetTextureFolder() + m_slot.GetFilename()));
        m_texture = driver->CreateTexture2D(*image, image->GetImageFormat(), true);
    }

    /**
     * @brief IsOnGpu
     * @return true if data is on gpu, false otherwise
     */
    bool TextureSlot::Cache::IsOnGpu() const
    {
        return m_texture != nullptr;
    }

    /**
     * @brief GetMemoryGpuUsage
     * @return Gpu memory usage estimation in bytes
     */
    size_t TextureSlot::Cache::GetMemoryGpuUsage() const
    {
        if (m_texture == nullptr)
            return 0;
        m_texture->GetMemoryUsage();
    }

    TextureSlot::TextureSlot(Material* owner)
        : m_owner(owner)
        , m_gpu_cache(*this)
        , m_is_diffuse_map_slot(false)
        , m_is_specular_intensity_map_slot(false)
        , m_is_normal_map_slot(false)
    {}

    void TextureSlot::SetScale(const Math::vec3& value)
    {
        m_scale = value;
    }

    const Math::vec3& TextureSlot::GetScale() const
    {
        return m_scale;
    }

    void TextureSlot::SetFilename(const System::string& value)
    {
        m_image_filename = value;
    }

    const System::string& TextureSlot::GetFilename() const
    {
        return m_image_filename;
    }

    void TextureSlot::SetDiffuseFactor(float value)
    {
        m_diffuse_factor = value;
    }

    float TextureSlot::GetDiffuseFactor() const
    {
        return m_diffuse_factor;
    }

    void TextureSlot::SetNormalFactor(float value)
    {
        m_normal_factor = value;
    }

    float TextureSlot::GetNormalFactor() const
    {
        return m_normal_factor;
    }

    void TextureSlot::SetSpecularIntensityFactor(float value)
    {
        m_specular_intensity_factor = value;
    }

    float TextureSlot::GetSpecularIntensityFactor() const
    {
        return m_specular_intensity_factor;
    }

    TextureSlot::Cache& TextureSlot::GetGpuCache()
    {
        return m_gpu_cache;
    }

    bool TextureSlot::IsDiffuseMapSlot() const
    {
        return m_is_diffuse_map_slot;
    }

    bool TextureSlot::IsNormalMapSlot() const
    {
        return m_is_normal_map_slot;
    }

    bool TextureSlot::IsSpecularIntensityMapSlot() const
    {
        return m_is_specular_intensity_map_slot;
    }

    void TextureSlot::MarkAsDiffuseMapSlot(bool value)
    {
        m_is_diffuse_map_slot = value;
    }

    void TextureSlot::MarkAsNormalMapSlot(bool value)
    {
        m_is_normal_map_slot = value;
    }

    void TextureSlot::MarkAsSpecularIntensityMapSlot(bool value)
    {
        m_is_specular_intensity_map_slot = value;
    }

}
