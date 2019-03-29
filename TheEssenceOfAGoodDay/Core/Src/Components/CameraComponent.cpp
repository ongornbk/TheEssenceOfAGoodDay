#include "Actor.h"

Components::CameraComponent::CameraComponent(Actor* par) : IComponent(par)
{

}

void Components::CameraComponent::Initialize()
{
	IComponent* transform = (IComponent*)parent->GetComponent(ComponentType::TRANSFORM_COMPONENT_TYPE);
	if (transform)
	{
		position = &(component_cast<TransformComponent>(transform))->position;
		rotation = &(component_cast<TransformComponent>(transform))->rotation;
	}
	else throw(exception("Exception at Components::CollisionComponent::Initialize -> No TransformComponent!"));
}

ComponentType Components::CameraComponent::GetType() const noexcept
{
	return ComponentType::CAMERA_COMPONENT_TYPE;
}

void Components::CameraComponent::InitializeOrthoMatrix(const int32 screenwidth, const int32 screenheight, const float screennear, const float screenfar)
{
	DirectX::XMStoreFloat4x4(&ortho, DirectX::XMMatrixOrthographicLH((float)screenwidth, (float)screenheight, screennear, screenfar));
}

void Components::CameraComponent::InitializeProjectionMatrix(const float fow, const float screenaspect, const float screennear, const float screenfar)
{
	DirectX::XMStoreFloat4x4(&projection, DirectX::XMMatrixPerspectiveFovLH(fow, screenaspect, screennear, screenfar));
}

void Components::CameraComponent::Update()
{

	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw((*rotation).x, (*rotation).y, (*rotation).z);

	DirectX::XMVECTOR lookat = XMVector3TransformCoord(DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), rotationMatrix);
	DirectX::XMVECTOR up = XMVector3TransformCoord(DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), rotationMatrix);

	float f[4] = { position->x,position->y,position->z,position->w };
	__m128 pos = _mm_load_ps(f);
	lookat = _mm_add_ps(lookat, pos);
	DirectX::XMStoreFloat4x4(&view, DirectX::XMMatrixLookAtLH(pos, lookat, up));
}

void Components::CameraComponent::Release()
{
	delete (this);
}