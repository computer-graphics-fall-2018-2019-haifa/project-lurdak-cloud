	#define _USE_MATH_DEFINES

#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Utils.h"
#include <nfd.h>
nfdchar_t *outPath = "Data//camera.obj";

Camera::Camera(const glm::vec4& eye, const glm::vec4& at, const glm::vec4& up) :
	zoom(1.0),
	cameraModel(Utils::LoadMeshModel(outPath))
	
 
{
	SetCameraLookAt(eye, at, up);
	//SetPerspectiveProjection(90, 100, 100, 500);
}

Camera::~Camera()
{
}

void Camera::SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up)
{

	glm::vec3 zaxis = glm::normalize(eye - at);    
	glm::vec3 xaxis = glm::normalize(cross(up, zaxis));
	glm::vec3 yaxis = glm::normalize(cross(zaxis, xaxis));

	glm::mat4 translationOrientation = {
	   glm::vec4(xaxis.x, yaxis.x, zaxis.x, 0),
	   glm::vec4(xaxis.y, yaxis.y, zaxis.y, 0),
	   glm::vec4(xaxis.z, yaxis.z, zaxis.z, 0),
	   glm::vec4(glm::dot(xaxis,-eye)  ,glm::dot(yaxis,-eye),glm::dot(zaxis,-eye) , 1)
	};//matrix for orientation Camera and translation Camera


	 
 
	this->viewTransformation = translationOrientation;


}
glm::mat4x4 Camera::GetCamViewTrans() {
	return this->viewTransformation;
}
glm::mat4x4 Camera::GetCamProjTrans() {
	return this->projectionTransformation;
}
float Camera::GetCamZoom() {
	return this->zoom;
}

void Camera::SetOrthographicProjection(
	const float height,
	const float aspectRatio,
	const float near,
	const float far)
{
	this->projectionTransformation = Utils::OrthographicProjectionMatrix(height, aspectRatio, near, far);

}

void Camera::SetPerspectiveProjection(
	const float fovy,
	const float aspectRatio,
	const float near,
	const float far)
{
	this->projectionTransformation = Utils::PerspectiveProjectionMatrix(fovy, aspectRatio, near, far);

}

void Camera::SetZoom(const float zoom)
{
	this->zoom = zoom;
}