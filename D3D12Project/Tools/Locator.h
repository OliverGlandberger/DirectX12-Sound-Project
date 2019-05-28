#pragma once

#include "../D3D12/D3D12Renderer.h"
#include "Benchmark.h"
#include <d3dcompiler.h>
#include "../D3D12/D3D12Camera.h"

#include <dxgi1_6.h>


#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif



inline void ThrowIfFailed(HRESULT hr) {
	if (FAILED(hr)) {
		// Char buffer
		char stringBuffer[64] = {};
		// Append data to buffer
		sprintf_s(stringBuffer, "HRESULT of 0x%08X", static_cast<UINT>(hr));
		// Throw!
		throw std::runtime_error(std::string(stringBuffer));
	}
}

class Locator {
private:
	static ID3D12RootSignature** gRootSignature;
	static ID3D12Device3** gDevice;
	static IDXGISwapChain4** gSwapChain;
	static ID3D12GraphicsCommandList2** gCommandList;
	static ID3D12CommandAllocator** gCommandAllocator;
	static ID3D12CommandQueue** gCommandQueue;
	static Benchmark** m_benchmark;
	static D3D12Camera** m_camera;
	static DirectX::XMMATRIX** m_worldMatrices;

public:
	Locator() {}
	~Locator() {}

	// PROVIDE
	static void provide(ID3D12RootSignature** rootSignature) {
		gRootSignature = rootSignature;
	}
	static void provide(ID3D12Device3** device) {
		gDevice = device;
	}
	static void provide(IDXGISwapChain4** swapChain) {
		gSwapChain = swapChain;
	}
	static void provide(ID3D12GraphicsCommandList2** commandList) {
		gCommandList = commandList;
	}
	static void provide(ID3D12CommandAllocator** commandAllocator) {
		gCommandAllocator = commandAllocator;
	}
	static void provide(ID3D12CommandQueue** commandQueue) {
		gCommandQueue = commandQueue;
	}

	static void provide(Benchmark** benchmark) {
		m_benchmark = benchmark;
	}

	static void provide(D3D12Camera** camera) {
		m_camera = camera;
	}

	static void provide(DirectX::XMMATRIX** worldMatrices) {
		m_worldMatrices = worldMatrices;
	}

	// GET
	static ID3D12RootSignature* getRootSignature() {
		return *gRootSignature;
	}
	static ID3D12Device3* getDevice() {
		return *gDevice;
	}
	static IDXGISwapChain4* getSwapChain() {
		return *gSwapChain;
	}
	static ID3D12GraphicsCommandList2* getCommandList() {
		return *gCommandList;
	}
	static ID3D12CommandAllocator* getCommandAllocator() {
		return *gCommandAllocator;
	}
	static ID3D12CommandQueue* getCommandQueue() {
		return *gCommandQueue;
	}
	static Benchmark* getBenchmark() {
		return *m_benchmark;
	}
	static D3D12Camera* getCamera() {
		return *m_camera;
	}
	static DirectX::XMMATRIX* getWorldMatrices() {
		return *m_worldMatrices;
	}
};