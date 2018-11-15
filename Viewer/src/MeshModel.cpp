#include "MeshModel.h"
#include "Utils.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

MeshModel::MeshModel(const std::vector<Face>& faces, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::string& modelName) :
	modelName(modelName),
	worldTransform(Utils::TranslateMatrix(glm::vec3(400, 400, 400))),
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
	setWorldLocation(glm::vec3(400,400, 400));
	this->modelWorldRotate=(glm::vec3(0, 0, 0));
	this->modelSelfRotate = (glm::vec3(0, 0, 0));
	

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
	FixVert();



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
void MeshModel::FixVert() {
	this->FixedVer = this->vertices;
	this->boxPoints = this->boxPoints2;
	glm::mat4 myModelMatrix = Utils::TranslateMatrix(this->center) *Utils::RotateMatrix(this->modelSelfRotate) * Utils::ScaleMatrix(this->modelScale);
	glm::mat4 myGlobalMatrix = Utils::TranslateMatrix(this->modelWorldLocation)* Utils::RotateMatrix(this->modelWorldRotate);
	for (int i = 0; i < this->FixedVer.size(); i++) {
			this->FixedVer[i] = Utils::matrixMulti(FixedVer[i], myModelMatrix);
			this->FixedVer[i] = Utils::matrixMulti(FixedVer[i], myGlobalMatrix);

 
	}
	for (int i = 0; i < this->boxPoints.size(); i++) {
		this->boxPoints[i] = Utils::matrixMulti(boxPoints[i], myModelMatrix);
		this->boxPoints[i] = Utils::matrixMulti(boxPoints[i], myGlobalMatrix);

 
	}
}



const glm::vec3  MeshModel::getScale() {
	return this->modelScale;
}
const glm::vec3  MeshModel::getSelfRotate() {
	return this->modelSelfRotate;
}
const glm::vec3  MeshModel::getWorldLocation() {
	return this->modelWorldLocation;
}
void  MeshModel::setWorldLocation(const glm::vec3 location) {
	 this->modelWorldLocation =(location);
	 FixVert();
}
void  MeshModel::setWorldRotation(const glm::vec3 rotate) {
	this->modelWorldRotate = (rotate);
	FixVert();
}
void  MeshModel::setSelfRotate(const glm::vec3 rotate) {
	this->modelSelfRotate = (rotate);
	FixVert();
}
void MeshModel::changeScale(const glm::vec3 scale) {
	this->modelScale = glm::vec3(scale.x, scale.y, scale.z);
	FixVert();
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
const std::vector<glm::vec3> MeshModel::GetFixedVertices()
{
	return this->FixedVer;
}


const std::vector<Face> MeshModel::GetFaces()
{
	return this->faces;
}
const std::vector<glm::vec3> MeshModel::getBox() {
	return  this->boxPoints;
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