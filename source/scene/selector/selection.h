#ifndef PUNK_SCENE_SELECTION_H
#define PUNK_SCENE_SELECTION_H

#include "../../config.h"
#include "../../math/vec3.h"

namespace System { class Object; }

namespace Scene
{
    enum class SelectionType { BoundingBox, BoundingSphere, Geometry };

    class PUNK_ENGINE_API Selection final
    {
    public:

        Selection();

        void SetPoints(const std::vector<Math::vec3>& value);
        void SetObject(System::Object* value);

        const std::vector<Math::vec3>& GetPoints() const;
        System::Object* GetObject() const;

        void SetFaces(const std::vector<size_t>& value);
        const std::vector<size_t>& GetFaces() const;

        void SetType(SelectionType value);
        SelectionType GetType() const;

    private:        
        SelectionType m_type;
        System::Object* m_object;
        std::vector<Math::vec3> m_points;
        std::vector<size_t> m_faces;
    };
}

#endif // SELECTION_H
