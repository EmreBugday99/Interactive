#pragma once
#include "../../components/PrimitiveSprite2D.h"

class InteractiveEngine;
class BaseRenderer
{
public:
	BaseRenderer();
	virtual ~BaseRenderer();

public:
	InteractiveEngine* Engine;

	virtual void InsertIntoRenderQueue(PrimitiveSprite2D* sprite);
	virtual void Render();
};
