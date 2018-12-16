#define _USE_MATH_DEFINES

#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Utils.h"

Camera::Camera(const glm::vec4& eye, const glm::vec4& at, const glm::vec4& up) :
	zoom(1.0), cameraModel(Utils::LoadMeshModel("c:/"))
{
	SetCameraLookAt(eye, at, up);
	
}

Camera::~Camera()
{
}

void Camera::SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up)
{
 
	glm::vec3 cameraDirection = glm::normalize(eye - at);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

		glm::mat4 camToWorld;

		camToWorld[0][0] = cameraRight.x;
		camToWorld[0][1] = cameraRight.y;
		camToWorld[0][2] = cameraRight.z;
		camToWorld[1][0] = cameraUp.x;
		camToWorld[1][1] = cameraUp.y;
		camToWorld[1][2] = cameraUp.z;
		camToWorld[2][0] = cameraDirection.x;
		camToWorld[2][1] = cameraDirection.y;
		camToWorld[2][2] = cameraDirection.z;
		camToWorld[3][3] = 1;
		this->viewTransformation = camToWorld*Utils::TranslateMatrix(-eye);
		camToWorld=glm::lookAt(eye, at, up);

 


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

}

void Camera::SetZoom(const float zoom)
{

}