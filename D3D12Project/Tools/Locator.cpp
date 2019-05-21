#include "Locator.h"

ID3D12RootSignature** Locator::gRootSignature = nullptr;
ID3D12Device3** Locator::gDevice = nullptr;
IDXGISwapChain4** Locator::gSwapChain = nullptr;
ID3D12GraphicsCommandList2** Locator::gCommandList = nullptr;
ID3D12CommandAllocator** Locator::gCommandAllocator = nullptr;
ID3D12CommandQueue** Locator::gCommandQueue = nullptr;
Benchmark** Locator::m_benchmark = nullptr;
SoundManager** Locator::m_soundManager = nullptr;
D3D12Camera** Locator::m_camera = nullptr;