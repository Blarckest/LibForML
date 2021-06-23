#include "pch.h"
#include "Model.h"

Model::Model(std::vector<int> nodesByLayers)
{
	for (unsigned int i = 0; i < nodesByLayers.size(); i++)
	{
		_layers.push_back(new Layer(nodesByLayers.at(i), i == 0 ? LayerType::Input : i == nodesByLayers.size() - 1 ? LayerType::Output : LayerType::Hidden, i > 0 ? _layers.back():nullptr));
	}
}

void Model::start(int maxBackpropagation)
{
	startBackpropagationFrom(*(_layers.back()), maxBackpropagation);
}

void Model::startBackpropagationFrom(Layer layer, unsigned int nbBackpropagation)
{
	for (unsigned i = 0; i < nbBackpropagation; i++)
	{
		layer.backpropagate();
	}
}
