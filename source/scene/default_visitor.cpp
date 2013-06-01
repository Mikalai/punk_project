#include <string>
#include <iostream>
#include "scene_graph.h"
#include "../virtual/module.h"

namespace Scene
{
	DefaultVisitor::DefaultVisitor() : m_level(0) {}

	bool DefaultVisitor::Visit(CameraNode* node)
	{
		std::cout << std::string(m_level, ' ') << "CameraNode " << std::endl;
		m_level++;
		for (auto o : *node)
		{
			Node* child = As<Node*>(o);
			if (child)
				child->Apply(this);
		}
		m_level--;
		return true;
	}

	bool DefaultVisitor::Visit(StaticMeshNode* node)
	{
		std::cout << std::string(m_level, ' ') << "StaticMeshNode" << std::endl;
		m_level++;
		for (auto o : *node)
		{
			Node* child = As<Node*>(o);
			if (child)
				child->Apply(this);
		}
		m_level--;
		return true;
	}

	bool DefaultVisitor::Visit(SkinMeshNode* node)
	{
		std::cout << std::string(m_level, ' ') << "SkinMeshNode" << std::endl;
		m_level++;
		for (auto o : *node)
		{
			Node* child = As<Node*>(o);
			if (child)
				child->Apply(this);
		}
		m_level--;
		return true;
	}

	bool DefaultVisitor::Visit(BoneNode* node)
	{
		std::cout << std::string(m_level, ' ') << "BoneNode" << std::endl;
		m_level++;
		for (auto o : *node)
		{
			Node* child = As<Node*>(o);
			if (child)
				child->Apply(this);
		}
		m_level--;
		return true;
	}

	bool DefaultVisitor::Visit(ArmatureNode* node)
	{
		std::cout << std::string(m_level, ' ') << "ArmatureNode" << std::endl;
		Virtual::Armature* armature = Virtual::Armature::find(node->GetStorageName());
		for (int i = 0; i < armature->GetBonesCount(); ++i)
		{
			Virtual::Bone* bone = armature->GetBoneByIndex(i);
			out_message() << bone->GetName() << ": " << std::endl << bone->GetAnimatedGlobalMatrix().ToString() << std::endl;
		}

		m_level++;
		for (auto o : *node)
		{
			Node* child = As<Node*>(o);
			if (child)
				child->Apply(this);
		}
		m_level--;
		return true;
	}

	bool DefaultVisitor::Visit(LightNode* node)
	{
		std::cout << std::string(m_level, ' ') << "LightNode" << std::endl;
		m_level++;
		for (auto o : *node)
		{
			Node* child = As<Node*>(o);
			if (child)
				child->Apply(this);
		}
		m_level--;
		return true;
	}

	bool DefaultVisitor::Visit(MaterialNode* node)
	{
		std::cout << std::string(m_level, ' ') << "MaterialNode" << std::endl;
		m_level++;
		for (auto o : *node)
		{
			Node* child = As<Node*>(o);
			if (child)
				child->Apply(this);
		}
		m_level--;
		return true;
	}

	bool DefaultVisitor::Visit(Node* node)
	{
		std::cout << std::string(m_level, ' ') << "Node" << std::endl;
		m_level++;
		for (auto o : *node)
		{
			Node* child = As<Node*>(o);
			if (child)
				child->Apply(this);
		}
		m_level--;
		return true;
	}

	bool DefaultVisitor::Visit(TransformNode* node)
	{
		std::cout << std::string(m_level, ' ') << "TransformNode" << std::endl;
		m_level++;
		for (auto o : *node)
		{
			Node* child = As<Node*>(o);
			if (child)
				child->Apply(this);
		}
		m_level--;
		return true;
	}

	bool DefaultVisitor::Visit(LocationIndoorNode* node)
	{
		std::cout << std::string(m_level, ' ') << "LocationIndoorNode" << std::endl;
		m_level++;
		for (auto o : *node)
		{
			Node* child = As<Node*>(o);
			if (child)
				child->Apply(this);
		}
		m_level--;
		return true;
	}

	bool DefaultVisitor::Visit(PortalNode* node)
	{
		std::cout << std::string(m_level, ' ') << "PortalNode" << std::endl;
		m_level++;
		for (auto o : *node)
		{
			Node* child = As<Node*>(o);
			if (child)
				child->Apply(this);
		}
		m_level--;
		return true;
	}
}
