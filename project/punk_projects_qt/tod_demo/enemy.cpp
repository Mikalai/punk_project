#include "enemy.h"

namespace Demo
{
    PUNK_OBJECT_REG(Enemy, "Demo.Enemy", TOD_ENENEMY, &System::Object::Info.Type);

    Enemy::Enemy()
        : m_path(nullptr)
        , m_visible_data(nullptr)
    {
        m_transform = new Virtual::Transform;
        m_transform_node = new Scene::Node;
        m_transform_node->SetData(m_transform);

        m_node = m_transform_node;
        //m_transform_node->Add(m_mesh_node);//m_material_node);
        //m_material_node->Add();

        m_skill = rand() % 100 / 100.0f;

        m_speed = 0.05 + m_skill*0.1;
        m_t = 0;
        m_state = State::READY;

        Info.Add(this);
    }

    Enemy::~Enemy()
    {
        Info.Remove(this);
    }

    void Enemy::Update(float dt)
    {
        if (m_state == State::RUNNING)
        {
            if (!m_path)
                return;
            float l = m_path->GetTotalLength();
            m_t += m_speed * dt;
            float t = m_t / l;
            if (t >= 1)
            {
                m_t = 0;
                t = 0;
                m_state = State::READY;
                m_on_reached((System::Event*)this);
            }

            if (m_armature_node)
            {
                auto mixer = As<Virtual::ArmatureAnimationMixer*>(m_armature_node->GetData());
                mixer->SetTrackTime(mixer->GetTrackTime() + dt*(150.0f * m_speed /  0.05));
            }

            auto p = m_path->At(t);
            Math::vec3 p1;
            float next_t = t+0.01;
            if (next_t >= 1)
            {
                p1 = p;
                p = m_path->At(t-0.01);
            }
            else
            {
                p1 = m_path->At(next_t);
            }

            auto dir = (p1-p).Normalized();
            float angle = acos(Math::vec3(1, 0, 0).Dot(dir));
            m_transform->Set(Math::mat4::CreateTranslate(p)*Math::mat4::CreateRotation(0, 0, 1, angle));
        }
    }

    void Enemy::SetPath(AI::CurvePath *value)
    {
        Scene::Node* node = As<Scene::Node*>(value->GetOwner());
        if (!node)
            return;
        m_path = value;
        System::Bind(node, m_node);
    }

    void Enemy::SetVisibleData(Scene::Node *node)
    {
        if (node == nullptr)
        {
            if (m_visible_data != nullptr)
            {
                m_transform_node->Remove(m_visible_data);
                delete m_visible_data;
                m_visible_data = nullptr;
            }
        }
        else
        {
            m_visible_data = node;
            m_transform_node->Add(node);
            m_armature_node = m_visible_data->Find(L"male_armature_2.armature", true);
        }
    }

    void Enemy::Kill()
    {
        m_transform_node->Remove(m_visible_data, true);
        m_state = State::READY;
        m_on_killed((System::Event*)this);
    }

    void Enemy::Activate()
    {
        if (m_state == State::READY)
        {
            m_state = State::RUNNING;
            m_on_activate((System::Event*)this);
        }
    }

    void Enemy::OnKilled(System::Handler value)
    {
        m_on_killed = value;
    }

    void Enemy::OnReached(System::Handler value)
    {
        m_on_reached = value;
    }

    void Enemy::OnActivate(System::Handler value)
    {
        m_on_activate = value;
    }
}
