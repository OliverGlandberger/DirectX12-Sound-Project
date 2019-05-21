#include "Box.hpp"
#include "../IA.h"
#include "../D3D12/D3D12ConstantBuffer.h"

Box::Box()
{
}

Box::~Box()
{
}

void Box::initialize()
{
	float4 triPos[3] = {
		{ 0.0f,  0.05f, 0.0f, 1.0f },
		{ 0.05f, -0.05f, 0.0f, 1.0f },
		{ -0.05f, -0.05f, 0.0f, 1.0f } 
	};
	float4 posRect[3]{
		{ -0.5f, 0.5f, 0.0f, 1.0f },	// TopLeft
		{ 0.5f, 0.5f, 0.0f, 1.0f },		// TopRight
		{ 0.5f, -0.5f, 0.0f, 1.0f }	// BotRight
	};
	float4 tempNormal[3]{
		{ -0.5f, 0.5f, 0.0f, 1.0f },	// TopLeft
		{ 0.5f, 0.5f, 0.0f, 1.0f },		// TopRight
		{ 0.5f, -0.5f, 0.0f, 1.0f }	// BotRight
	};
	float2 tempUV[4]{
		{0.5f, 0.6f},
		{0.7f, 0.8f}
	};

	// Allocate Vertex Buffer & Mesh
	this->vertexBuffer = new D3D12VertexBuffer(sides * sizeof(posRect));
	D3D12VertexBuffer* normalVertexBuffer = new D3D12VertexBuffer(sides * sizeof(tempNormal));
	D3D12VertexBuffer* uvVertexBuffer = new D3D12VertexBuffer(sides * sizeof(tempUV));

	this->mesh = new D3D12Mesh();

	// Per Side of the box...
	for (size_t i = 0; i < sides; i++)	{
		size_t offset = 0;// i * sizeof(posRect);

		// ... Add it to the Vertex Buffer
		this->vertexBuffer->setData(posRect, sizeof(posRect), offset);

		// ... Add it to the Mesh | POS
		mesh->addIAVertexBufferBinding(
			this->vertexBuffer,
			offset,
			std::extent<decltype(posRect)>::value,	// CODEDIFF 'std::extent<decltype(posRect)>::value;'
			sizeof(float4),
			POSITION	// ERRORPOS index needs to correlate properly to input assembly
		);

		// ... Add it to the Mesh | NORMAL
		mesh->addIAVertexBufferBinding(
			normalVertexBuffer,
			offset,
			std::extent<decltype(tempNormal)>::value,	// CODEDIFF 'std::extent<decltype(posRect)>::value;'
			sizeof(float4),
			NORMAL	// ERRORPOS index needs to correlate properly to input assembly
		);


		// ... Add it to the Mesh | TEXTOORD
		mesh->addIAVertexBufferBinding(
			uvVertexBuffer,
			offset,
			std::extent<decltype(tempUV)>::value,	// CODEDIFF 'std::extent<decltype(triPos)>::value;'
			sizeof(float2),
			TEXTCOORD	// ERRORPOS index needs to correlate properly to input assembly
		);

		mesh->txBuffer = new D3D12ConstantBuffer(std::string(TRANSLATION_NAME), PIPELINEINPUT::CB::TRANSLATION_MATRIX);
	}

	// Constant Buffers for TRANSLATION & VIEWPROJ


}

void Box::cleanUp()
{
	delete this->vertexBuffer;
	delete this->mesh;
}
