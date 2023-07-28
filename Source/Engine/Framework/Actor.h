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
		Actor(const Enginuity::Transform& transform)
			: m_transform(transform) {}

		virtual void Update(float dt);
		virtual void Draw(Renderer& renderer);

		float GetRadius() { return (m_model) ? m_model->GetRadius() * m_transform.scale : 0; }
		virtual void OnCollision(Actor* other) {};

		bool ProcessCollision() const { return !m_destroyed; }

		void AddForce(const vec2& force) { m_velocity += force; }
		void SetDamping(float damping) { m_damping = damping; }

		class Scene* m_scene = nullptr;
		friend class Scene;
		
		class Game* m_game = nullptr;
		
		std::string m_tag;
		Enginuity::Transform m_transform;
		float m_lifespan = -1.0f;

	protected:

		std::shared_ptr<Model> m_model;
		bool m_destroyed = false;

		vec2 m_velocity;
		float m_damping = 0;
	};

}