#ifndef SUNNODE_H
#define SUNNODE_H

#include "../config.h"
#include "node.h"

namespace Virtual
{
    class Sun;
}

namespace Scene
{
    class PUNK_ENGINE_API SunNode : public Node
    {
    public:
        SunNode();
        virtual ~SunNode();
        virtual bool Apply(AbstractVisitor* visitor) override;
        void SetSun(Virtual::Sun* value);
        Virtual::Sun* GetSun() const;

        virtual Node* Clone() const override;
    private:
        Virtual::Sun* m_sun;
    };

}

#endif // SUNNODE_H
