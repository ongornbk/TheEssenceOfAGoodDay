#include "Actor.h"

Components::CameraComponent::CameraComponent(Actor* par) : IComponent(par)
{

}

void Components::CameraComponent::Initialize()
{
	IComponent* transform = (IComponent*)parent->GetComponent(ComponentType::TRANSFORM_COMPONENT_TYPE);
	if (transform)
	{
		transform_pos = &(component_cast<TransformComponent>(transform))->position;
		transform_rot = &(component_cast<TransformComponent>(transform))->rotation;
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

	position = _mm_set_ps(transform_pos->x, transform_pos->y, transform_pos->z, transform_pos->w);
	rotation = _mm_set_ps(transform_rot->x, transform_rot->y, transform_rot->z, transform_rot->w);
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(rotation.m128_f32[0], rotation.m128_f32[1], rotation.m128_f32[2]);

	DirectX::XMVECTOR lookat = XMVector3TransformCoord(DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), rotationMatrix);
	DirectX::XMVECTOR up = XMVector3TransformCoord(DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), rotationMatrix);

	lookat = DirectX::XMVectorAdd(lookat,position);
	DirectX::XMStoreFloat4x4(&view, DirectX::XMMatrixLookAtLH(position, lookat, up));
}

void Components::CameraComponent::Release()
{
	delete (this);
}