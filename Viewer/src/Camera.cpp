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
	this->eye = glm::vec3(eye.x, eye.y, eye.z);
	cameraModel.setWorldLocation(this->eye);
	cameraModel.changeScale(glm::vec3(10, 10, 10));
  
	SetCameraLookAt(this->eye, glm::vec3(at.x,at.y,at.z), glm::vec3(up.x,up.y,up.z));
	//isOrth = false;
	projectCamera(20, 20, 20, 1);
}

Camera::~Camera()
{
}

void Camera::SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up)
{
	
	glm::vec3 zaxis = glm::normalize(eye - at);    
	glm::vec3 xaxis = glm::normalize(cross(up, zaxis));
	glm::vec3 yaxis = glm::normalize(cross(zaxis, xaxis));
	
	/*this->eye = eye;
	cameraModel.setWorldLocation(this->eye);
	 
	glm::mat4 orint= {
	   glm::vec4(xaxis.x  , yaxis.x  , zaxis.x  , 0),
	   glm::vec4(xaxis.y  , yaxis.y , zaxis.y  , 0),
	   glm::vec4(xaxis.z  , yaxis.z  , zaxis.z , 0),
	   glm::vec4(0,0,0,    1)
	};
	
	//this->cameraModel.SetWorldTransformation(Utils::TranslateMatrix(glm::vec3(glm::dot(xaxis, eye), glm::dot(yaxis, eye),glm::dot(zaxis, eye)))*orint);
	 
	/*this->cameraModel.setSelfRotate(glm::vec3 (0, -180, 0));
	/*this->viewTransformation = -this->cameraModel.GetWorldTransformation()*orint;
		
	this->cameraModel.SetWorldTransformation(glm::mat4{
	   glm::vec4(xaxis.x  , yaxis.x  , zaxis.x  , -eye.x),
	   glm::vec4(xaxis.y  , yaxis.y , zaxis.y  , -eye.y),
	   glm::vec4(xaxis.z  , yaxis.z  , zaxis.z , -eye.z),
	   glm::vec4(0,0,0,     1)
	});
<<<<<<< HEAD
 */
	this->cameraModel.SetWorldTransformation(Utils::matrixMulti(glm::vec3(0,0,0), glm::mat4{
	   glm::vec4(xaxis.x  , yaxis.x  , zaxis.x  ,0),
	   glm::vec4(xaxis.y  , yaxis.y , zaxis.y  , 0 ),
	   glm::vec4(xaxis.z  , yaxis.z  , zaxis.z ,0),
	   glm::vec4(glm::dot(xaxis, eye),glm::dot(yaxis, eye), glm::dot(zaxis, eye),     1)
		});

=======
>>>>>>> parent of 8ad3f73... greatWork
	this->viewTransformation = glm::inverse(this->cameraModel.GetWorldTransformation());
	

}
void Camera::moveCame(const glm::vec3& transfor)
{

	this->viewTransformation = this->viewTransformation*Utils::TranslateMatrix(transfor);
	 
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

 

 

MeshModel  Camera::GetCameraModel(
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
		this->projectionTransformation = Utils::PerspectiveProjectionMatrix(right, left, top, bot, far, near);
		else
			this->projectionTransformation = Utils::OrthographicProjectionMatrix(right, left, top, bot, far, near);
}
glm::vec3 Camera::getEye() {
	return this->eye;
}