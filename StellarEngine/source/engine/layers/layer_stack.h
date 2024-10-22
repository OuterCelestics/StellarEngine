#pragma once

#include <vector>
#include "layer.h"

class LayerStack
{
public:
	~LayerStack();
	void PushLayer(Layer* layer);
	void PopLayer(Layer* layer);
	std::vector<Layer*> m_Layers;
};

