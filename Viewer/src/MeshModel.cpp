#include "MeshModel.h"
#include "Utils.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

MeshModel::MeshModel(const std::vector<Face>& faces, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::string& modelName) :
	modelName(modelName),
	worldTransform(glm::mat4x4(1)),
	vertices(vertices),
	faces(faces),
	normals(normals)
	

{
	
	changeScale(glm::vec3(100, 100, 100));
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
	setLocation(glm::vec3(maxX*this->modelScale.x, maxY*this->modelScale.x, 0));

	this->boxPoints.push_back(glm::vec3(maxX , maxY, minZ));
	this->boxPoints.push_back(glm::vec3(maxX, minY, minZ));
	this->boxPoints.push_back(glm::vec3(minX, minY, minZ));
	this->boxPoints.push_back(glm::vec3(minX, maxY, minZ));
	this->boxPoints.push_back(glm::vec3(maxX, maxY, maxZ));
	this->boxPoints.push_back(glm::vec3(maxX, minY, maxZ));
	this->boxPoints.push_back(glm::vec3(minX, minY, maxZ));
	this->boxPoints.push_back(glm::vec3(minX, maxY, maxZ));
	showBox = false;



}

MeshModel::~MeshModel()
{

}

void MeshModel::SetWorldTransformation(const glm::mat4x4& worldTransform)
{
	this->worldTransform = worldTransform;
}

const glm::mat4x4& MeshModel::GetWorldTransformation() const
{
	return worldTransform;
}

void MeshModel::SetColor(const glm::vec4& color)
{
	this->color = color;
}
void MeshModel::changeScale(const glm::vec3 scale) {
	this->modelScale = glm::vec3(scale.x,  scale.y, scale.z);

}
const glm::vec3  MeshModel::getScale() {
	return this->modelScale;
}
const glm::vec3  MeshModel::getSelfRotate() {
	return this->modelSelfRotate;
}
const glm::vec3  MeshModel::getLocation() {
	return this->modelLocationGlobal;
}
void  MeshModel::setLocation(const glm::vec3 location) {
	 this->modelLocationGlobal=(location);
}
void  MeshModel::setSelfRotate(const glm::vec3 rotate) {
	this->modelSelfRotate = (rotate);
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
const std::vector<glm::vec3> MeshModel::GetVertices()
{
	return this->vertices;
}
const std::vector<Face> MeshModel::GetFaces()
{
	return this->faces;
}
const std::vector<glm::vec3> MeshModel::getBox() {
	return  this->boxPoints;
}
void MeshModel::ChangeShowBox() {
	this->showBox = !this->showBox;
}
const bool MeshModel::isShowBox() {
	return this->showBox;
}
const glm::vec3 MeshModel::getCenter() {
	return  this->center;
}