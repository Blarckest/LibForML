#pragma once
#include <vector>
#include "Node.h"
#include "LayerType.h"
#include <unordered_map>
class Layer
{
public:
	Layer(int nbNodes, LayerType type, Layer* precedentLayer = nullptr);
	~Layer();
	__declspec(dllexport) LayerType getType();
	__declspec(dllexport) void backpropagate();
	
private:
	LayerType _type;
	Layer* _precedent=nullptr;
	std::vector<Node*> _nodes;
	std::unordered_map<Node*, std::vector<std::pair<Node*,int>*>*> _linkWithPrecedentLayer;
};

