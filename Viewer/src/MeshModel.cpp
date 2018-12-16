#include "MeshModel.h"
#include "Utils.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


MeshModel::MeshModel(const std::vector<Face>& faces, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::string& modelName) :
	modelName(modelName),
 
	worldTransform(1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1),
	selfTransform(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1),
	vertices(vertices),
	faces(faces),
	normals(normals)
	

{
	
	
	float maxX = vertices[0].x;
	float maxY = vertices[0].y;
	float maxZ = vertices[0].z;
	float minX = vertices[0].x;
	float minY = vertices[0].y;
	float minZ = vertices[0].z;
	 
	 
	for (int i = 1; i < vertices.size(); i++) {
		if (vertices[i].x  > maxX) {
			maxX = vertices[i].x;
		}
		if (vertices[i].x < minX) {
			minX = vertices[i].x;
		}
		if (vertices[i].y  > maxY) {
			maxY = vertices[i].y;
		}
		if (vertices[i].y  < minY) {
			minY = vertices[i].y;
		}
		
		if (vertices[i].z  > maxZ) {
			maxZ = vertices[i].z;
		}
		if (vertices[i].z  < minZ) {
			minZ = vertices[i].z;
		}

		
	}

	this->center =    glm::vec3((maxX + minX) / 2, (maxY + minY) / 2, (maxZ + minZ) / 2);
	
	this->modelSelfRotate = (glm::vec3(0, 0, 0));
	changeScale(glm::vec3(10, 10, 10));
	this->boxPoints.push_back(glm::vec3(maxX , maxY, minZ));
	this->boxPoints.push_back(glm::vec3(maxX, minY, minZ));
	this->boxPoints.push_back(glm::vec3(minX, minY, minZ));
	this->boxPoints.push_back(glm::vec3(minX, maxY, minZ));
	this->boxPoints.push_back(glm::vec3(maxX, maxY, maxZ));
	this->boxPoints.push_back(glm::vec3(maxX, minY, maxZ));
	this->boxPoints.push_back(glm::vec3(minX, minY, maxZ));
	this->boxPoints.push_back(glm::vec3(minX, maxY, maxZ));
	this->boxPoints2 = this->boxPoints;
	showBox = false;
	if (center.x != 0 || center.y != 0 || center.z !=0) {
		centerTheModel();
		center.x = 0;
		center.y = 0;
		center.z = 0;
	}
	this->axes.push_back(glm::vec3(200, 0, 0));
	this->axes.push_back(glm::vec3(0, 200, 0));
	this->axes.push_back(glm::vec3(0, 0, 200));
	
}

MeshModel::~MeshModel()
{

}


void MeshModel::SetWorldTransformation(const glm::mat4x4& worldTransform)
{
	this->worldTransform = worldTransform;
}
void MeshModel::SetWorldTransformation(const glm::vec3 location,const glm::vec3 rotate)
{
<<<<<<< HEAD
<<<<<<< HEAD
 this->worldTransform = Utils::TranslateMatrix(location)*Utils::RotateMatrix(rotate);
=======
	this->worldTransform = Utils::RotateMatrix(rotate)*Utils::TranslateMatrix(location);
>>>>>>> parent of 8ad3f73... greatWork
=======
	this->worldTransform = Utils::RotateMatrix(rotate)*Utils::TranslateMatrix(location);
>>>>>>> parent of 8ad3f73... greatWork
}
void MeshModel::applyScaleAndRotate() {
	this->scaledAndRotatedvertices = this->vertices;
	this->scaledAndRotatenormals = this->normals;
	for (int j = 0; j < this->scaledAndRotatedvertices.size(); j++) {
		this->scaledAndRotatedvertices[j] = Utils::matrixMulti(this->scaledAndRotatedvertices[j], this->selfTransform);
		 
	}
	for (int j = 0; j < this->scaledAndRotatenormals.size(); j++) {
		this->scaledAndRotatenormals[j] = Utils::matrixMulti(this->scaledAndRotatenormals[j], this->selfTransform);

	}
	this->boxPoints2 = this->boxPoints;
	for (int j = 0; j < this->boxPoints2.size(); j++) {
		this->boxPoints2[j] = Utils::matrixMulti(this->boxPoints2[j], this->selfTransform);
	 
	}
	for (int j = 0; j < this->axes.size(); j++) {
		this->axes[j] = Utils::matrixMulti(this->axes[j], this->selfTransform);

	}
	 
		this->center = Utils::matrixMulti(this->center, this->selfTransform);

	 
	

}

void MeshModel::centerTheModel()
{
	for (int j = 0; j < this->vertices.size(); j++) {
		this->vertices[j] = Utils::matrixMulti(this->vertices[j], Utils::TranslateMatrix(-this->center));
		//vertices[j] = Utils::matrixMulti(vertices[j], worldToCamera);
	}
	for (int j = 0; j < this->normals.size(); j++) {
		this->normals[j] = Utils::matrixMulti(this->normals[j], Utils::TranslateMatrix(-this->center));
		//vertices[j] = Utils::matrixMulti(vertices[j], worldToCamera);
	}
	for (int j = 0; j < this->boxPoints.size(); j++) {
		this->boxPoints[j] = Utils::matrixMulti(this->boxPoints[j], Utils::TranslateMatrix(-this->center));
		//vertices[j] = Utils::matrixMulti(vertices[j], worldToCamera);
	}
}
const glm::mat4x4& MeshModel::GetWorldTransformation() const
{
	return this->worldTransform;
}
const glm::mat4x4& MeshModel::GetSelfTransformation() const
{
	return this->selfTransform;
}

void MeshModel::SetColor(const glm::vec4& color)
{
	this->color = color;
}
 



const glm::vec3  MeshModel::getScale() {
	return this->modelScale;
}
const glm::vec3  MeshModel::getSelfRotate() {
	return this->modelSelfRotate;
}
 
void  MeshModel::setWorldLocation(const glm::vec3 location) {
	this->worldTransform[0][3] = location.x;
	this->worldTransform[1][3] = location.y;
	this->worldTransform[2][3] = location.z;
	 
 
}
void  MeshModel::setWorldRotation(const glm::vec3 rotate) {
	 
	this->worldTransform = this->worldTransform*Utils::RotateMatrix(rotate) ;
 
	 
}
void  MeshModel::setSelfRotate(const glm::vec3 rotate) {
	this->modelSelfRotate = (rotate);
	this->selfTransform= Utils::ScaleMatrix(this->modelScale)*Utils::RotateMatrix(this->modelSelfRotate)    ;
	applyScaleAndRotate();
 
}
void MeshModel::changeScale(const glm::vec3 scale) {
	this->modelScale = glm::vec3(scale.x, scale.y, scale.z);
	this->selfTransform = Utils::ScaleMatrix(this->modelScale)* Utils::RotateMatrix(this->modelSelfRotate)   ;
	applyScaleAndRotate();
}
const glm::vec4& MeshModel::GetColor() const
{
	return color;
}

const std::string& MeshModel::GetModelName()
{
	return modelName;
}
void MeshModel::SetModelName(const std::string name)
{
	this->modelName = name;
} 
const std::vector<glm::vec3> MeshModel::GetOriginalVertices()
{
	return this->vertices;
}
const std::vector<glm::vec3> MeshModel::GetVertices()
{
	return this->scaledAndRotatedvertices;
}
const std::vector<glm::vec3> MeshModel::GetNomal()
{
	return this->scaledAndRotatenormals;
}

 


const std::vector<Face> MeshModel::GetFaces()
{
	return this->faces;
}
const std::vector<glm::vec3> MeshModel::getBox() {
	return  this->boxPoints2;
}
void MeshModel::ChangeShowBox(bool check) {
	this->showBox = check;
}
const bool MeshModel::isShowBox() {
	return this->showBox;
}
const glm::vec3 MeshModel::getCenter() {
	return  this->center;
} 
const std::vector<glm::vec3> MeshModel::getAxes() {
	return  this->axes;
}