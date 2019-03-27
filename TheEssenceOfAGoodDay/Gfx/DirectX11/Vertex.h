#pragma once
#include "dx11.h"

struct SimpleVertexType
{
	DirectX::XMFLOAT3 position;
};

struct ScreenVertexType
{
	DirectX::XMFLOAT2 position;
};

struct SpriteVertexType
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT2 uv;
};

struct TextureVertexType
{
	DirectX::XMFLOAT2 position;
	DirectX::XMFLOAT2 uv;
};

struct ColorVertexType
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 color;
};