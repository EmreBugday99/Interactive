#pragma once

class Entity;
class Component
{
public:
	Entity* Owner;
	
	Component();
	virtual ~Component();

	virtual void Update();
	virtual void Render();
};
