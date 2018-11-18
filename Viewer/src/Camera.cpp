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
	cameraModel.setWorldLocation(eye);
	SetCameraLookAt(eye, at, up);
	

	SetPerspectiveProjection(90, 100, 100, 500);
}

Camera::~Camera()
{
}

void Camera::SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up)
{

	glm::vec3 zaxis = glm::normalize(eye - at);    
	glm::vec3 xaxis = glm::normalize(cross(up, zaxis));
	glm::vec3 yaxis = glm::normalize(cross(zaxis, xaxis));

	glm::mat4 orientation = {
	   glm::vec4(xaxis.x * 180 / M_PI, yaxis.x * 180 / M_PI, zaxis.x * 180 / M_PI, 0),
	   glm::vec4(xaxis.y * 180 / M_PI, yaxis.y * 180 / M_PI, zaxis.y * 180 / M_PI, 0),
	   glm::vec4(xaxis.z * 180 / M_PI, yaxis.z * 180 / M_PI, zaxis.z * 180 / M_PI, 0),
	   glm::vec4(0,       0,       0,     1)
	};//matrix for orientation Camera
	cameraModel.setSelfRotate(Utils::matrixMulti(cameraModel.getCenter(), orientation ));
	 
	glm::mat4 translation = {
		glm::vec4(1,      0,      0,   0),
		glm::vec4(0,      1,      0,   0),
		glm::vec4(0,      0,      1,   0),
		glm::vec4(-eye.x, -eye.y, -eye.z, 1)
	};//matrix for translation Camera

	this->viewTransformation = translation * orientation;


}
glm::mat4x4 Camera::GetCamViewTrans() {
	return this->viewTransformation;
}
glm::mat4x4 Camera::GetCamProjTrans() {
	return this->projectionTransformation;
}
MeshModel Camera::getCamModel() {
	return this->cameraModel;
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