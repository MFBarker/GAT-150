#include "AudioComponents.h"
#include "Engine.h"

namespace neu
{
	void AudioComponent::Initialize()
	{
	}
	void AudioComponent::Update()
	{
		//g_audioSystem
	}

	void AudioComponent::Play()
	{
	}

	void AudioComponent::Stop()
	{
	}

	bool AudioComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}
	bool AudioComponent::Read(const rapidjson::Value& value)
	{
		if (!value.HasMember("actors") || !value["actors"].IsArray())
		{
			return false;
		}

		for (auto& actorValue : value["actors"].GetArray())
		{
			std::string type;
			READ_DATA(actorValue, type);

			auto actor = Factory::Instance().Create<Actor>(type);
			if (actor)
			{
				//read actor
				actor->Read(actorValue);
			}
			return true;
		}
		return true;
	}
}
