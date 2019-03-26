#pragma once
#include "..\Actor.h"
#include "ComponentsInformation.h"

template <class T>
inline T* component_cast(IComponent* component)
{
	return dynamic_cast<T*>(component);
}

template <class T>
T* CreateComponent(const Actor* par)
{
	T* component = new T(par);
	par->m_components.push_back(component);
	return component;
}