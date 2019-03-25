#include "pch.h"
#include "Locator.h"

Locator::Map Locator::_map;
Locator::Storage Locator::_storage;

void Locator::Close()
{
	_map.clear();
	_storage.clear();
}

void Locator::Init()
{
}
