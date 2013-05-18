#ifndef _H_PUNK_IMAGE_MODULE_COMPONENT
#define _H_PUNK_IMAGE_MODULE_COMPONENT

namespace ImageModule
{
    enum class ComponentType { UnsignedByte, SignedByte, Float };

    inline size_t GetComponentSize(ComponentType type)
    {
        switch (type) {
        case ComponentType::UnsignedByte:
            return 1;
        case ComponentType::SignedByte:
            return 1;
        case ComponentType::Float:
            return 4;
        default:
            break;
        }
    }
}

#endif
