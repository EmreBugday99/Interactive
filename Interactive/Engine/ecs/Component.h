#pragma once

class Entity;
class Component
{
public:
	Entity* Owner;
	
	Component();
	virtual ~Component();

	virtual void Update(float deltaTime);
	virtual void Render();
};
