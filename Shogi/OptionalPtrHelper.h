#pragma once
#include <optional>

struct OptionalPtrHelper
{
	template<class T>
	static const T* GetOrNull(const std::optional<T>& value)
	{
		if (!value)
			return nullptr;
		return &*value;
	}

	template<class T>
	static T* GetOrNull(std::optional<T>& value)
	{
		if (!value)
			return nullptr;
		return &*value;
	}
};
