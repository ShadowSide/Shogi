#pragma once
#include <Memory>

template <class T>
using Handle = std::shared_ptr<T>;