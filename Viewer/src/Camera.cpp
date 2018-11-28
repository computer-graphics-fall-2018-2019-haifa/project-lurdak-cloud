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
	this->eye = eye;
	SetCameraLookAt(eye, at, up);
	projectCamera(20, 20, 200, 100);
}

Camera::~Camera()
{
}

void Camera::SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up)
{
	
	glm::vec3 zaxis = glm::normalize(eye - at);    
	glm::vec3 xaxis = glm::normalize(cross(up, zaxis));
	glm::vec3 yaxis = glm::normalize(cross(zaxis, xaxis));
	this->eye = -at;
	this->viewTransformation  = {
	   glm::vec4(xaxis.x  , yaxis.x  , zaxis.x  , 0),
	   glm::vec4(xaxis.y  , yaxis.y , zaxis.y  , 0),
	   glm::vec4(xaxis.z  , yaxis.z  , zaxis.z , 0),
	   glm::vec4(-xaxis.x * eye.x - xaxis.y * eye.y - xaxis.z * eye.z,       -yaxis.x * eye.x - yaxis.y * eye.y - yaxis.z * eye.z,       -zaxis.x * eye.x - zaxis.y * eye.y - zaxis.z * eye.z,     1)
	};

}
void Camera::moveCame(const glm::vec3& transfor)
{
	this->eye = -transfor;
	this->viewTransformation = Utils::TranslateMatrix(-transfor)*this->viewTransformation;
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

 

 

MeshModel Camera::GetCameraModel(
 )
{
	return this->cameraModel;

}

void Camera::SetZoom(const float zoom)
{
	this->zoom = zoom;
}
void Camera::projectCamera(int width, int hight, int far, int near)
{

	float left = this->eye.x - (width / 2);
	float right = this->eye.x + (width / 2);
	float bot = this->eye.y - (hight / 2);
	float top = this->eye.y + (hight / 2);



	if (this->isOrth)
		this->projectionTransformation = Utils::OrthographicProjectionMatrix(right, left, top, bot, far, near);
	else
		this->projectionTransformation = Utils::PerspectiveProjectionMatrix(right, left, top, bot, far, near);
}
glm::vec3 Camera::getEye() {
	return this->eye;
}