#pragma once

enum ComponentType
{
	TRANSFORM_COMPONENT_TYPE,
	COLLISION_COMPONENT_TYPE
};

class IComponent
{
public:

	

	virtual void Initialize() = 0;

public:
	virtual ComponentType GetType() const noexcept = 0;

protected:
//	Actor*        parent;
};

