#ifndef _H_PUNK_SCENE_NODE
#define _H_PUNK_SCENE_NODE

#include <vector>

#include "../system/object.h"
#include "../system/hresource.h"
#include "../string/string.h"

namespace Virtual { class Entity; }

namespace Scene
{
	class Node;

	class PUNK_ENGINE NodeVisitor
	{
	public:
		virtual void PreEnter() = 0;
		virtual bool operator () (Node* value) = 0;
		virtual void PostEnter() = 0;
	};

	class PUNK_ENGINE Node : System::Object
	{
	public:
		typedef std::vector<Node*> Collection;

	public:
		Node();

		void SetParent(Node* obj) { m_parent_name = (m_parent = obj) == nullptr ? L"" : m_parent->GetName(); }

		Node* GetParent() { return m_parent; }
		const Node* GetParent() const { return m_parent; }

		void SetParentName(const System::string& name) { m_parent_name = name; }
		const System::string& GetParentName() const { return m_parent_name; }
		System::string& GetParentName() { return m_parent_name; }

		Collection& GetChildren() { return m_children; }
		const Collection& GetChildren() const { return m_children; }

		Node* GetChild(int index) { return m_children[index]; }
		const Node* GetChild(int index) const { return m_children[index]; }
		Node* GetChild(const System::string& name, bool deep_search = true);
		const Node* GetChild(const System::string& name, bool deep_search = true) const;
		int GetChildIndex(const System::string& name);

		const System::string& GetName() const { return m_name; }
		void SetName(const System::string& name) { m_name = name; }

		void AddChild(Node* child) { m_children.push_back(child); }

		virtual bool Save(std::ostream& stream);
		virtual bool Load(std::istream& stream);

		virtual ~Node();

		bool Apply(NodeVisitor* value);

		void SetData(System::Object* value) { m_data = value; }
		System::Object* GetData() const { return m_data; }

	private:
		Node(const Node&);
		Node& operator = (const Node&);

		void Init();
		void Clear();

	private:
		Node* m_parent;
		System::string m_name;		
		System::string m_parent_name;
		System::Object* m_data;		
		std::vector<Node*> m_children;
	};
}

#endif	//	H_PUNK_SCENE_NODE