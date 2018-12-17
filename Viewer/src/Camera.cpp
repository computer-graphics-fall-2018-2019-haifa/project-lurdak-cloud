#define _USE_MATH_DEFINES

#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Utils.h"

Camera::Camera(const glm::vec4& eye, const glm::vec4& at, const glm::vec4& up) :
	zoom(1.0)
{
	SetCameraLookAt(eye, at, up);
	
}

Camera::~Camera()
{
}

void Camera::SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up)
{
	 
		glm::vec3 forward = glm::normalize(eye - at);
		glm::vec3 right = glm::cross(glm::normalize(up), forward);
		glm::vec3 up2 = glm::cross(forward, right);

		glm::mat4 camToWorld;

		camToWorld[0][0] = right.x;
		camToWorld[0][1] = right.y;
		camToWorld[0][2] = right.z;
		camToWorld[1][0] = up.x;
		camToWorld[1][1] = up.y;
		camToWorld[1][2] = up.z;
		camToWorld[2][0] = forward.x;
		camToWorld[2][1] = forward.y;
		camToWorld[2][2] = forward.z;
		camToWorld[3][0] = eye.x;
		camToWorld[3][1] = eye.y;
		camToWorld[3][2] = eye.z;
		this->viewTransformation = camToWorld;
	 
	}




void Camera::SetOrthographicProjection(
	const float height,
	const float aspectRatio,
	const float near,
	const float far)
{

}

void Camera::SetPerspectiveProjection(
	const float fovy,
	const float aspectRatio,
	const float near,
	const float far)
{
	
	
	float b,t,  l,  r;
	
		float scale = tan(fovy * 0.5 * M_PI / 180) * near;
		r = aspectRatio * scale, l = -r;
		t = scale, b = -t;
		this->projectionTransformation = Utils::PerspectiveMatrix(b, t, l, r, near, far);
	}
glm::mat4 Camera::getProjection()
{
	return this->projectionTransformation;
}
glm::mat4 Camera::getView()
{
	return this->viewTransformation;
}




void Camera::SetZoom(const float zoom)
{

}