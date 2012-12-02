#include <string>
#include <iostream>
#include "scene_graph.h"

namespace Scene
{
	DefaultVisitor::DefaultVisitor() : m_level(0) {}

	bool DefaultVisitor::Visit(CameraNode* node)
	{
		std::cout << std::string(m_level, ' ') << "CameraNode" << std::endl;			
		m_level++;
		for each (System::Proxy<Node> child in *node)
			child->Apply(this);
		m_level--;
		return true;
	}

	bool DefaultVisitor::Visit(GeometryNode* node)
	{
		std::cout << std::string(m_level, ' ') << "GeometryNode" << std::endl;			
		m_level++;
		for each (System::Proxy<Node> child in *node)
			child->Apply(this);
		m_level--;
		return true;
	}
		
	bool DefaultVisitor::Visit(LightNode* node)
	{
		std::cout << std::string(m_level, ' ') << "LightNode" << std::endl;			
		m_level++;
		for each (System::Proxy<Node> child in *node)
			child->Apply(this);
		m_level--;
		return true;
	}
	
	bool DefaultVisitor::Visit(MaterialNode* node)
	{
		std::cout << std::string(m_level, ' ') << "MaterialNode" << std::endl;	
		m_level++;
		for each (System::Proxy<Node> child in *node)
			child->Apply(this);
		m_level--;
		return true;
	}
	
	bool DefaultVisitor::Visit(Node* node)
	{
		std::cout << std::string(m_level, ' ') << "Node" << std::endl;		
		m_level++;
		for each (System::Proxy<Node> child in *node)
			child->Apply(this);
		m_level--;
		return true;
	}
	
	bool DefaultVisitor::Visit(TransformNode* node)
	{
		std::cout << std::string(m_level, ' ') << "TransformNode" << std::endl;			
		m_level++;
		for each (System::Proxy<Node> child in *node)
			child->Apply(this);
		m_level--;
		return true;
	}
	
	bool DefaultVisitor::Visit(LocationIndoorNode* node)
	{
		std::cout << std::string(m_level, ' ') << "LocationIndoorNode" << std::endl;			
		m_level++;
		for each (System::Proxy<Node> child in *node)
			child->Apply(this);
		m_level--;
		return true;
	}
	
	bool DefaultVisitor::Visit(PortalNode* node)
	{
		std::cout << std::string(m_level, ' ') << "PortalNode" << std::endl;			
		m_level++;
		for each (System::Proxy<Node> child in *node)
			child->Apply(this);
		m_level--;
		return true;
	}
}