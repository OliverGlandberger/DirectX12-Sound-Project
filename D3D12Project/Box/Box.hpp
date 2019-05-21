#pragma once

#include "../GlobalDefines.h"
#include <d3d12.h>
#include "../D3D12/D3D12VertexBuffer.h"
#include "../D3D12/D3D12Mesh.h"

class Box {
private:
	// Rectangle
	
	float4 posRect[4]{
		{ -0.5f, 0.5f, 0.0f, 1.0f },	// TopLeft
		{ 0.5f, 0.5f, 0.0f, 1.0f },		// TopRight
		{ 0.5f, -0.5f, 0.0f, 1.0f },	// BotRight
		{ -0.5f, -0.5f, 0.0f, 1.0f }	// BotLeft
	};
	size_t sides = 1;

	
	


public:
	Box();
	~Box();
	D3D12Mesh* mesh = nullptr;
	D3D12VertexBuffer* vertexBuffer = nullptr;
	int vertices = 3;

	void initialize();
	void cleanUp();
};