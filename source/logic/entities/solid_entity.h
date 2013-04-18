//#ifndef _H_SOLID_ENTITY
//#define _H_SOLID_ENTITY
//
//#include "../config.h"
//#include "abstract_entity.h"
//#include "../../math/vec3.h"
//
//namespace Logic
//{
//	class PUNK_LOGIC_MODULE SolidEntity : public AbstractEntity
//	{
//		Math::vec3 m_position;		//	in parent space
//		Math::vec3 m_orientation;	//	in parent space
//
//	public:
//
//		SolidEntity();
//		SolidEntity(const SolidEntity& e);
//		SolidEntity& operator = (const SolidEntity& e);
//
//		virtual bool Visit(Visitor* v);
//		virtual AbstractEntity* Clone() const { return new SolidEntity(*this); }
//
//	public:
//
//		//
//		//	Specific stuff goes here
//		//
//		void SetPosition(const Math::vec3& position);
//		Math::vec3& GetPosition();
//		const Math::vec3& GetPosition() const;
//
//		void SetOrientation(const Math::vec3& orientation);
//		Math::vec3& GetOrientation();
//		const Math::vec3& GetOrientation() const;
//
//	};
//}
//
//#endif
