#ifndef _H_PUNK_RENDER_BATCH
#define _H_PUNK_RENDER_BATCH

#include <list>
#include "../../system/poolable.h"

namespace GPU
{

class CoreState;
class Renderable;

class Batch: public System::Poolable<Batch>
{
public:
    ~Batch();
    CoreState* m_state;
    Renderable* m_renderable;
	bool m_destroy;
};

}

#endif	//	_H_PUNK_RENDER_BATCH
