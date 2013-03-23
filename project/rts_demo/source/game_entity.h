#include "../../../source/punk_engine.h"

class GameEntity : public Scene::Node
{
public:
	bool CanBeDeleted() { return m_can_be_deleted; }
	bool MarkToDelete() { m_can_be_deleted = false; }
private:
	bool m_can_be_deleted;
};