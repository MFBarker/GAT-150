#pragma once
#include "RenderComponent.h"
#include "Math/Rect.h"

namespace neu
{
	class Renderer;
	class Texture;

	class SprAnimComponent : public RenderComponent
	{
	public:
		//void Initialize() override;

		// Inherited via RenderComponent
		virtual void Update() override;
		virtual void Draw(Renderer& renderer) override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		float fps = 0;
		int num_columns = 0;
		int num_row = 0;

		int start_frame = 0;
		int end_frame = 0;

		int frame = 0;
		float frameTimer = 0;

		Rect source;
		std::shared_ptr<Texture> m_texture;
	};
}