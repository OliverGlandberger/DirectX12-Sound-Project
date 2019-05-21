#include "Box.hpp"

Box::Box()
{

}

Box::~Box()
{
}

void Box::initialize()
{
	// Allocate Vertex Buffer & Mesh
	this->vertexBuffer = new D3D12VertexBuffer(sides * sizeof(posRect));
	this->mesh = new D3D12Mesh();

	// Per Side of the box...
	for (size_t i = 0; i < sides; i++)	{
		size_t offset = i * sizeof(posRect);

		// ... Add it to the Vertex Buffer
		this->vertexBuffer->setData(posRect, sizeof(posRect), offset);

		// ... Add it to the Mesh
		mesh->addIAVertexBufferBinding(
			this->vertexBuffer,
			offset,
			sides,	// CODEDIFF 'std::extent<decltype(posRect)>::value;'
			sizeof(float4),
			POSITION	// ERRORPOS index needs to correlate properly to input assembly
		);
	}

	// Constant Buffers for TRANSLATION & VIEWPROJ


}

void Box::cleanUp()
{
	delete this->vertexBuffer;
	delete this->mesh;
}
