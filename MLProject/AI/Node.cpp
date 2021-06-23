#include "pch.h"
#include "Node.h"

Node::Node(int value, std::vector<Node*>* parents):_value(value),_parents(parents)
{
}

Node::~Node()
{
	delete _parents;
}

int Node::getValue()
{
    return _value;
}

void Node::setValue(int value)
{
	if (value>=0)
	{
		_value = value;
	}
}

std::vector<Node*>* Node::getParents()
{
	return _parents;
}

void Node::setParents(std::vector<Node*>* parents)
{
	_parents = parents;
}

