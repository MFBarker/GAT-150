#pragma once
#include "Resource.h"
#include <map>
#include <string>
#include <memory>
#include <cstdarg> 

namespace neu
{
	class ResourceManager
	{
	public:
		ResourceManager() = default;

		void Initialize();
		void Shutdown();

		template<typename T, typename ... TArgs>
		std::shared_ptr<T> Get(const std::string& name, TArgs... args);

	private:
		std::map<std::string, std::shared_ptr<Resource>> m_resources;
		// map <key,data>	 //[key] -> data


	};

	template<typename T, typename ... TArgs>
	inline std::shared_ptr<T> ResourceManager::Get(const std::string& name, TArgs... args)
	{
		if (ResourceManager::m_resources.find(name) != ResourceManager::m_resources.end())
		{
			//found
			return std::dynamic_pointer_cast<T>(ResourceManager::m_resources[name]);
		}
		else
		{
			//not found
			std::shared_ptr<T> resource = std::make_shared<T>();
			resource -> Create(name, args...);
			ResourceManager::m_resources[name] = resource;

			return resource;
		}
	}

}