#pragma once

#include "../GlobalDefines.h"
#include <d3d12.h>
#include "../D3D12/D3D12VertexBuffer.h"
#include "../D3D12/D3D12Mesh.h"

#define POSITION 4

class Box {
private:
	// Rectangle
	float4 posRect[4]{
		{ -0.5f, 0.5f, 0.0f, 1.0f },	// TopLeft
		{ 0.5f, 0.5f, 0.0f, 1.0f },		// TopRight
		{ 0.5f, -0.5f, 0.0f, 1.0f },	// BotRight
		{ -0.5f, -0.5f, 0.0f, 1.0f }	// BotLeft
	};
	size_t sides = 6;

	D3D12VertexBuffer* vertexBuffer = nullptr;
	D3D12Mesh* mesh = nullptr;


public:
	Box();
	~Box();

	void initialize();
	void cleanUp();
};