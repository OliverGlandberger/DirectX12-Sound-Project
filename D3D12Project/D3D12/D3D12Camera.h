#pragma once

#include <DirectXMath.h>

#include "D3D12ConstantBuffer.h"
#include "../Tools/SoundManager.hpp"

using namespace DirectX;

class D3D12Camera {
private:
	//View
	XMVECTOR m_cameraPos;
	XMVECTOR cameraDirection;
	XMVECTOR m_cameraUp;
	XMMATRIX m_viewMatrix;
	// SOUNDMOD | Do not deallocate here!
	SoundStruct* pListener = nullptr;

	

	//Projection
	float m_fov;
	float m_aspectRatio;
	float m_nearPlane;
	float m_farPlane;
	XMMATRIX m_projectionMatrix;

	//View-Proj
	XMMATRIX m_viewProjectionMatrix;

	//Update
	float m_trigAngle;

	// Movement
	float CameraMovementSpeed = 0.1f;
	float CameraRotationSpeed = 0.02f;


public:
	D3D12Camera();
	~D3D12Camera();

	void MoveCameraLeft();
	void MoveCameraRight();
	void MoveCameraForward();
	void MoveCameraBackward();
	void MoveCameraUp();
	void RotateCameraVertically(POINT MouseMovement);
	void RotateCameraHorizontally(POINT mouseMovement);

	// Moves on input
	void UpdateCamera(
		TCHAR					CharacterMessage,
		POINT					MouseCoordinates
	);
	// Moves statically
	void update(float dt);

	void setFocusPoint(XMVECTOR focusPoint);
	
	XMMATRIX getViewProjection();

};