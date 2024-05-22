#pragma once
class Layer
{
public:
	virtual void OnAttach() = 0;
	virtual void OnInput() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnRender() = 0;
	virtual void OnDetach() = 0;
};

