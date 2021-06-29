#pragma once
#include <vector>
#include "Node.h"
#include "LayerType.h"
#include <unordered_map>
class Layer
{
public:
	__declspec(dllexport) Layer(int nbNodes, LayerType type, Layer* precedentLayer = nullptr);
	__declspec(dllexport) ~Layer();
	__declspec(dllexport) std::vector<Node*>& getNodes();
	__declspec(dllexport) void setNodesOfNextLayer(Layer* layer);
	__declspec(dllexport) LayerType getType();
	__declspec(dllexport) void backpropagate();
	
private:
	LayerType _type;
	Layer* _precedent=nullptr;
	std::vector<Node*> _nodes;
	std::vector<Node*>* _nodesOfNextLayer=nullptr;
	std::unordered_map<Node*, Matrix<float>*> _linkWithPrecedentLayer;
};

