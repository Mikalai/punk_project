#ifndef _H_PUNK_VIRTUAL_TEXTURE_SLOT
#define _H_PUNK_VIRTUAL_TEXTURE_SLOT

#include "../../config.h"
#include "../../math/vec3.h"
#include "../../string/string.h"
#include "../../gpu/common/texture/module.h"

namespace Virtual
{
    class Material;

    class PUNK_ENGINE_API TextureSlot
    {
    public:

        struct Cache
        {
            Cache(TextureSlot& slot);
            ~Cache();
            Gpu::Texture2D* GetTexture();

            /**
             * @brief Drop - removes data from Gpu
             */
            void Drop();

            /**
             * @brief Update - sends data to Gpu throug the specified driver
             */
            void Update(Gpu::VideoDriver* driver);

            /**
             * @brief IsOnGpu
             * @return true if data is on gpu, false otherwise
             */
            bool IsOnGpu() const;

            /**
             * @brief GetMemoryGpuUsage
             * @return Gpu memory usage estimation in bytes
             */
            size_t GetMemoryGpuUsage() const;

        private:
            Gpu::Texture2D* m_texture;
            TextureSlot& m_slot;
        };

    public:

        /**
         * @brief TextureSlot Create texture slot as part of the specified material
         * @param owner Material that owns this slot. Material is responsible for deleting the texture slot.
         */
        TextureSlot(Material* owner);

        void SetScale(const Math::vec3& value);
        const Math::vec3& GetScale() const;
        void SetFilename(const System::string& value);
        const System::string& GetFilename() const;
        void SetDiffuseFactor(float value);
        float GetDiffuseFactor() const;
        void SetNormalFactor(float value);
        float GetNormalFactor() const;
        void SetSpecularIntensityFactor(float value);
        float GetSpecularIntensityFactor() const;

        bool IsDiffuseMapSlot() const;
        bool IsNormalMapSlot() const;
        bool IsSpecularIntensityMapSlot() const;

        void MarkAsDiffuseMapSlot(bool value);
        void MarkAsNormalMapSlot(bool value);
        void MarkAsSpecularIntensityMapSlot(bool value);

        Cache& GetGpuCache();

    private:
        Material* m_owner;
        Math::vec3 m_scale;
        System::string m_image_filename;
        float m_diffuse_factor;
        float m_normal_factor;
        float m_specular_intensity_factor;

        bool m_is_diffuse_map_slot;
        bool m_is_specular_intensity_map_slot;
        bool m_is_normal_map_slot;

        Cache m_gpu_cache;
    };
}

#endif // TEXTURE_SLOT_H
