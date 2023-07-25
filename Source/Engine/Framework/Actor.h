#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include <memory>

namespace Enginuity 
{
	class Actor
	{
	public:
		Actor() = default;
		Actor(const Enginuity::Transform& transform, std::shared_ptr<Model> model)
			: m_transform(transform), m_model(model) {}

		virtual void Update(float dt);
		virtual void Draw(Renderer& renderer);

		float GetRadius() { return m_model->GetRadius() * m_transform.scale; }
		virtual void OnCollision(Actor* other) {};

		class Scene* m_scene = nullptr;
		Enginuity::Transform m_transform;
		std::string m_tag;
		friend class Scene;
		class Game* m_game = nullptr;
	protected:

		std::shared_ptr<Model> m_model;

		float m_lifespan = -1.0f;
		bool m_destroyed = false;
	};

}