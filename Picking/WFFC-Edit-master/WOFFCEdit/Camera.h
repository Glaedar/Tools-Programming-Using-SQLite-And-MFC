#pragma once
#include "pch.h"
#include "SceneObject.h"
#include <vector>

struct InputCommands;

class Camera
{

	using Vector3 = DirectX::SimpleMath::Vector3;
	using Matrix = DirectX::SimpleMath::Matrix;
	//InputCommands						m_InputCommands;


public:
	Camera();
	~Camera();

	void Update(const InputCommands& inputCommands);
	
	Vector3 GetPosition() const;
	Matrix GetViewMatrix() const;
	Matrix FocusObject(const InputCommands & inputCommands, Vector3 obj);

private:

	DirectX::SimpleMath::Vector3		m_camPosition{ 0.f, 3.7f, -3.5f };
	DirectX::SimpleMath::Vector3		m_camOrientation{ 90, 0, 0 };
	DirectX::SimpleMath::Vector3		m_camLookAt{ 0, 0, 0 };
	DirectX::SimpleMath::Vector3		m_camLookDirection;
	DirectX::SimpleMath::Vector3		m_camRight;

	float m_movespeed = 0.3f;
	float m_camRotRate = 3.0f;

	Vector3 objectPosition;
};

