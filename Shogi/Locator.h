#pragma once
#include <memory>
#include <unordered_map>
#include <forward_list>
#include <string_view>

class Locator
{
public:
	template<class Instance>
	static void RegisterInstance(const std::shared_ptr<Instance>& instance, const std::string& name = {})
	{
		auto notfound = _map.cend();
		auto instanceId = typeid(Instance).name() + name;
		auto finded = _map.find(instanceId);
		if (finded != notfound)
			throw std::logic_error("Already registered '" + instanceId + "' in Locator");
		_map.emplace(instanceId, _storage.insert_after(_storage.cbefore_begin(), instance));
	}

	template<class Instance>
	static std::shared_ptr<Instance> Resolve(const std::string& name = {})
	{
		auto instanceId = typeid(Instance).name() + name;
		if(_map.empty())
			throw std::logic_error("Empty Locator while finding '" + instanceId + "'");
		auto notfound = _map.cend();
		auto finded = _map.find(instanceId);
		if (finded == notfound)
			throw std::logic_error("Not found '" + instanceId + "' in Locator");
		auto sharedPointerToInstance = *(finded->second);
		auto result = std::dynamic_pointer_cast<Instance>(sharedPointerToInstance);
		if (!result)
			throw std::logic_error("Mismatch type for '" + instanceId + "'. Locator logic error");
		return result;
	}

	static void Close();
	static void Init();

private:
	using Storage = std::forward_list<std::shared_ptr<void>>;
	using Map = std::unordered_map<std::string, Storage::const_iterator>;
	static Map _map;
	static Storage _storage;
};

