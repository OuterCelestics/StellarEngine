#include "layer_stack.h"

LayerStack::~LayerStack()
{
	for (Layer* layer : m_Layers)
	{
		PopLayer(layer);
	}
}

void LayerStack::PushLayer(Layer* layer)
{
	m_Layers.push_back(layer);
}

void LayerStack::PopLayer(Layer* layer)
{
	if (!m_Layers.empty())
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}
}
