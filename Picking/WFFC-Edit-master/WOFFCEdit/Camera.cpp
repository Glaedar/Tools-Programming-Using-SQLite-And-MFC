#include "Camera.h"
#include "InputCommands.h"

using namespace DirectX;

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::Update(const InputCommands & inputCommands)
{
	//Vector3 planarMotionVector = m_camLookDirection;
	//planarMotionVector.y = 0.0;

	if (inputCommands.rotRight)
	{
		m_camOrientation.y -= m_camRotRate;
	}
	if (inputCommands.rotLeft)
	{
		m_camOrientation.y += m_camRotRate;
	}
	if (inputCommands.rotUp)
	{
		m_camOrientation.x += m_camRotRate;
	}
	if (inputCommands.rotDown)
	{
		m_camOrientation.x -= m_camRotRate;
	}


	//m_camOrientation.y += inputCommands.mouse_X;
	//m_camOrientation.x += inputCommands.mouse_Y;

	//stops camera going crazy
	m_camOrientation.x = std::min(m_camOrientation.x, +89.f);
	m_camOrientation.x = std::max(m_camOrientation.x, -89.f);

	//create look direction from Euler angles in m_camOrientation	

	m_camLookDirection.z = cos((m_camOrientation.y)*3.1415 / 180) * sin((m_camOrientation.x)*3.1415 / 180);
	m_camLookDirection.x = sin((m_camOrientation.y)*3.1415 / 180) * sin((m_camOrientation.x)*3.1415 / 180);
	m_camLookDirection.y = cos((m_camOrientation.x)*3.1415 / 180);
	m_camLookDirection.Normalize();

	m_camLookDirection.Cross(Vector3::UnitY, m_camRight);

	//process input and update stuff
	if (inputCommands.forward)
	{
		m_camPosition += m_camLookDirection * m_movespeed;
	}
	if (inputCommands.back)
	{
		m_camPosition -= m_camLookDirection * m_movespeed;
	}
	if (inputCommands.right)
	{
		m_camPosition += m_camRight * m_movespeed;
	}
	if (inputCommands.left)
	{
		m_camPosition -= m_camRight * m_movespeed;
	}

	//float cosY = cosf(XMConvertToRadians(m_rotation.y));
	//float cosP = cosf(XMConvertToRadians(m_rotation.x));

	//float sinY = sinf(XMConvertToRadians(m_rotation.y));
	//float sinP = sinf(XMConvertToRadians(m_rotation.x));

	//m_forward.x = sinY * cosP;
	//m_forward.y = sinP;
	//m_forward.z = cosP * cosY;
	//m_forward.Normalize();

	//create right vector from look Direction
	//Vector3 right;
	//m_forward.Cross(Vector3::UnitY, right);
	//right.Normalize();

	m_camLookAt = m_camPosition + m_camLookDirection;
}

DirectX::SimpleMath::Vector3 Camera::GetPosition() const
{
	return m_camPosition;
}

DirectX::SimpleMath::Matrix Camera::GetViewMatrix() const
{
	return Matrix::CreateLookAt(m_camPosition, m_camLookAt, Vector3::UnitY);
}

DirectX::SimpleMath::Matrix Camera::FocusObject(const InputCommands & inputCommands, Vector3 objPos)
{
	//m_camOrientation.x = std::min(m_camOrientation.x, +89.f);
	//m_camOrientation.x = std::max(m_camOrientation.x, -89.f);

	//create look direction from Euler angles in m_camOrientation	

	m_camLookDirection.z = cos((m_camOrientation.y)*3.1415 / 180) * sin((m_camOrientation.x)*3.1415 / 180);
	m_camLookDirection.x = sin((m_camOrientation.y)*3.1415 / 180) * sin((m_camOrientation.x)*3.1415 / 180);
	m_camLookDirection.y = cos((m_camOrientation.x)*3.1415 / 180);
	m_camLookDirection.Normalize();

	//m_camLookDirection.Cross(Vector3::UnitY, m_camRight);

	objectPosition = Vector3(objPos.x, objPos.y, objPos.z);

	//return Matrix::CreateLookAt(objectPosition - (m_camLookDirection * 15), objectPosition, Vector3(0, 1, 0));
	return Matrix::CreateLookAt(m_camPosition, objectPosition, Vector3(0, 1, 0));
}
