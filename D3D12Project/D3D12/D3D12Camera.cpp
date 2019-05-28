#include "D3D12Camera.h"
#include <iostream>
#include "../Tools/Locator.h"

D3D12Camera::D3D12Camera() {

	//View
	m_cameraPos = {1.0f, 0.0f, -1.0f};
	m_cameraUp = {0.0f, 1.0f, 0.0f};
	this->cameraDirection = { 0, 0, 1 };
	m_viewMatrix = XMMatrixLookToLH(m_cameraPos, cameraDirection, m_cameraUp);

	//Projection
	m_fov = 75.0f;
	m_aspectRatio = 800.0f / 600.0f;
	m_nearPlane = 0.01f;
	m_farPlane = 10000.0f;
	m_projectionMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);

	m_viewProjectionMatrix = m_viewMatrix * m_projectionMatrix;

	m_trigAngle = 0.0f;

}

D3D12Camera::~D3D12Camera() {

}

void D3D12Camera::UpdateCamera(
	TCHAR					CharacterMessage,
	POINT					MouseCoordinates
)
{
	bool NeedsToUpdate = false;

	// CAMERA MOVEMENT
	if (CharacterMessage == 'w') {
		NeedsToUpdate = true;
		this->MoveCameraForward();
	}
	else if (CharacterMessage == 'a') {
		NeedsToUpdate = true;
		this->MoveCameraLeft();
	}
	else if (CharacterMessage == 's') {
		NeedsToUpdate = true;
		this->MoveCameraBackward();
	}
	else if (CharacterMessage == 'd') {
		NeedsToUpdate = true;
		this->MoveCameraRight();
	}
	else if (CharacterMessage == 32) {
		NeedsToUpdate = true;
		this->MoveCameraUp();
	}


	// CAMERA ROTATION
	if (MouseCoordinates.y != 0) {
		NeedsToUpdate = true;
		this->RotateCameraVertically(MouseCoordinates);
	}
	if (MouseCoordinates.x != 0) {
		NeedsToUpdate = true;
		this->RotateCameraHorizontally(MouseCoordinates);
	}


	// MISC COMMANDS - Needs to be called after movement and rotation.
	if (CharacterMessage == 'r') {
		NeedsToUpdate = true;
		//this->ResetCamera();
	}


	// IF DATA HAS BEEN UPDATED
	if (NeedsToUpdate) {
		// Creates the new viewMatrix
		DirectX::XMMATRIX UnformattedViewMatrix = DirectX::XMMatrixLookToLH(
			m_cameraPos,
			this->cameraDirection,
			m_cameraUp
		);
		m_viewProjectionMatrix = UnformattedViewMatrix * m_projectionMatrix;

		// Update Listener
		XMFLOAT3 camposOutput;
		XMFLOAT3 camupOutput;		
		XMFLOAT3 camdirOutput;
		XMStoreFloat3(&camposOutput, m_cameraPos);
		XMStoreFloat3(&camupOutput, m_cameraUp);
		XMStoreFloat3(&camdirOutput, cameraDirection);

		// maybe update pointer to soundmanagers variable here, based on cameras position/direction
	}
}

void D3D12Camera::setFocusPoint(XMVECTOR focusPoint) {
	//m_focusPoint = focusPoint;
}

void D3D12Camera::update(float dt) {
	
	/// OUTDATED, see other update function
	//m_cameraPos = XMVECTOR{ cos(m_trigAngle) * 7.0f, 2.0f, sin(m_trigAngle) * 7.0f };

//	m_trigAngle = fmod(m_trigAngle + dt, 6.28f);

	//m_viewMatrix = XMMatrixLookAtLH(m_cameraPos, m_focusPoint, m_cameraUp);
	//m_viewProjectionMatrix = m_viewMatrix * m_projectionMatrix;
}

XMMATRIX D3D12Camera::getViewProjection() {
	return m_viewProjectionMatrix;
}

// Moves the camera Upwards!
void D3D12Camera::MoveCameraUp()
{
	DirectX::XMVECTOR upVector = DirectX::XMVector3Normalize(this->m_cameraUp);
	upVector = DirectX::XMVectorScale(upVector, this->CameraMovementSpeed);
	this->m_cameraPos = DirectX::XMVectorAdd(this->m_cameraPos, upVector);
}

// Moves the m_cameraPos to the Left, based on the crossproduct of
// the current cameraDirection & m_cameraUp
void D3D12Camera::MoveCameraLeft() {
	DirectX::XMVECTOR MovementVector = DirectX::XMVector3Cross(this->cameraDirection, this->m_cameraUp);// Creates rightVector
	DirectX::XMVector3Normalize(MovementVector);
	MovementVector = DirectX::XMVectorScale(MovementVector, CameraMovementSpeed);		// The lower the scale, the slower the movement

	this->m_cameraPos = DirectX::XMVectorAdd(this->m_cameraPos, MovementVector);
}

// Moves the m_cameraPos to the Right, based on the crossproduct of
// the current m_cameraUp & cameraDirection
void D3D12Camera::MoveCameraRight() {
	DirectX::XMVECTOR MovementVector = DirectX::XMVector3Cross(this->m_cameraUp, this->cameraDirection);// Creates rightVector
	DirectX::XMVector3Normalize(MovementVector);
	MovementVector = DirectX::XMVectorScale(MovementVector, CameraMovementSpeed);		// The lower the scale, the slower the movement

	this->m_cameraPos = DirectX::XMVectorAdd(this->m_cameraPos, MovementVector);
}

// Moves Camera forward based on the current cameraDirection
void D3D12Camera::MoveCameraForward() {
	DirectX::XMVECTOR MovementVector = this->cameraDirection;
	DirectX::XMVector3Normalize(MovementVector);
	MovementVector = DirectX::XMVectorScale(MovementVector, CameraMovementSpeed);

	this->m_cameraPos = DirectX::XMVectorAdd(this->m_cameraPos, MovementVector);
}

// Moves Camera backward based on the current cameraDirection
void D3D12Camera::MoveCameraBackward() {
	DirectX::XMVECTOR MovementVector = DirectX::XMVectorScale(this->cameraDirection, -1);
	DirectX::XMVector3Normalize(MovementVector);
	MovementVector = DirectX::XMVectorScale(MovementVector, CameraMovementSpeed);

	this->m_cameraPos = DirectX::XMVectorAdd(this->m_cameraPos, MovementVector);
}

// Rotates the camera Vertically through Quaternions based
// on the MouseMovement.y
// AIRPLANE MOVEMENT IS TYPICALLY TURNED OFF.
void D3D12Camera::RotateCameraVertically(POINT MouseMovement) {
	DirectX::XMVECTOR RightAxis = DirectX::XMVector3Cross(this->m_cameraUp, this->cameraDirection);

	float RotationAngle = MouseMovement.y * CameraRotationSpeed;

	DirectX::XMVECTOR RotationQuaternion = DirectX::XMQuaternionRotationAxis(RightAxis, RotationAngle);

	// Camera-Plane movement is currently turned OFF. Un-comment the line below to turn it ON.
	//this->m_cameraUp = DirectX::XMVector3Rotate(this->m_cameraUp, RotationQuaternion);
	this->cameraDirection = DirectX::XMVector3Rotate(this->cameraDirection, RotationQuaternion);
}

// Rotates the camera Horiontally through Quaternions based
// on the MouseMovement.x
void D3D12Camera::RotateCameraHorizontally(POINT MouseMovement) {
	float RotationAngle = MouseMovement.x * CameraRotationSpeed;

	DirectX::XMVECTOR RotationQuaternion = DirectX::XMQuaternionRotationAxis(this->m_cameraUp, RotationAngle);

	this->cameraDirection = DirectX::XMVector3Rotate(this->cameraDirection, RotationQuaternion);
}