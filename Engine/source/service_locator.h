#pragma once

#include "engine/core.h"
#include "engine/components/input/input.h"

namespace Engine {
	class ENGINE_API ServiceLocator {
	public:
		static inline Input::InputEvent* GetInput() { return _input.get(); }

	public:
		static inline void Provide(Input::InputEvent* input)
		{
			if(input != nullptr)
				_input.reset(input);
		}

		static inline void Shutdown()
		{
			_input.reset();
			_input = nullptr;
		}
	private:
		static inline std::unique_ptr<Input::InputEvent> _input;

	};
}