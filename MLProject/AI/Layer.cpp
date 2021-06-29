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
			auto* matrix = new Matrix<float>(1, _precedent->_nodes.size());
			++*matrix;
			_linkWithPrecedentLayer.insert(std::pair<Node* , Matrix<float>*>(node, matrix));
		}		
	}
}

Layer::~Layer()
{
	
}

std::vector<Node*>& Layer::getNodes()
{
	return _nodes;
}

void Layer::setNodesOfNextLayer(Layer* layer)
{
	_nodesOfNextLayer = &layer->_nodes;
}

LayerType Layer::getType()
{
	return _type;
}

void Layer::backpropagate()
{
}
