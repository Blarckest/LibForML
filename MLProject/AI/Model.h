#pragma once
#include "Layer.h"
class Model
{
public:
	__declspec(dllexport) Model(std::vector<int> nodesByLayers);
	__declspec(dllexport) void start(int maxBackpropagation);
private:
	void startBackpropagationFrom(Layer layer, unsigned int nbBackpropagation);
	std::vector<Layer*> _layers;
};

