#include "pch.h"
#include "Layer.h"

Layer::Layer(int nbNodes, LayerType type, Layer* precedentLayer)
{
	_type = type;
	for (int i = 0; i < nbNodes; i++)
	{
		Node* node = new Node(1, precedentLayer == nullptr ? nullptr : &precedentLayer->_nodes);
		_nodes.push_back(node);
		if ((_type == LayerType::Hidden || _type==LayerType::Output) && precedentLayer != nullptr) [[likely]]
		{
			_precedent = precedentLayer;
			auto* vectTemp = new std::vector<std::pair<Node*, int >*>();
			for (unsigned int j = 0; j < _precedent->_nodes.size(); j++)
			{
				vectTemp->push_back(new std::pair<Node*, int>(_precedent->_nodes.at(j), 1));
			}
			_linkWithPrecedentLayer.insert(std::pair<Node* , std::vector<std::pair<Node*, int>*>*>(node, vectTemp));
		}		
	}
}

Layer::~Layer()
{
	
}

LayerType Layer::getType()
{
	return _type;
}

void Layer::backpropagate()
{
}
