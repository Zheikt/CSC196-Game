#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"

class Actor
{
public:
	Actor(const Enginuity::Transform& transform, const Enginuity::Model& model)
		: m_transform(transform), m_model(model) {}

	virtual void Update(float dt) = 0; //Forces this to be defined in inheritors
	virtual void Draw(Enginuity::Renderer& renderer);
protected:
	Enginuity::Transform m_transform;
	Enginuity::Model m_model;
};