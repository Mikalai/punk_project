#ifndef ENEMY_H
#define ENEMY_H

#include "game_objects.h"
#include "../../../source/punk_engine.h"

namespace Demo
{
    class Enemy : public System::Object
    {
    public:

        enum class State { KILLED, RUNNING, READY };

        Enemy();
        Enemy(const Enemy&) = delete;
        Enemy& operator = (const Enemy&) = delete;
        virtual ~Enemy();

        void SetPath(AI::CurvePath* value);
        AI::CurvePath* GetPath() const;

        Scene::Node* GetNode();

        virtual void Update(float dt);

        void SetVisibleData(Scene::Node* node);

        void Kill();
        void Activate();
        State GetState() const;

        void OnKilled(System::Handler value);
        void OnReached(System::Handler value);
        void OnActivate(System::Handler value);

    private:
        State m_state;
        float m_skill;
        float m_speed;
        float m_t;
        Scene::Node* m_node;
        Scene::Node* m_visible_data;
        Scene::Node* m_armature_node;
        AI::CurvePath* m_path;

        Scene::Node* m_transform_node;

        System::Handler m_on_reached;
        System::Handler m_on_killed;
        System::Handler m_on_activate;

        Virtual::Transform* m_transform;

        PUNK_OBJECT(Enemy)
    };
}

#endif // ENEMY_H
