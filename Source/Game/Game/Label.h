#pragma once
#include "Framework/Actor.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"

class Label : public Enginuity::Text, public Enginuity::Actor
{
	class Renderer;

public:
	Label() = default;
	Label(const Enginuity::Transform& transform, std::shared_ptr<Enginuity::Font> font) 
		: Actor{ transform }, Text{ font } {}

	void Draw(Enginuity::Renderer& renderer);
};