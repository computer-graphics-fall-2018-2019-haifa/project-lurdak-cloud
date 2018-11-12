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
	float maxX = vertices[0].x;
	float maxY = vertices[0].y;
	float maxZ = vertices[0].z;
	float minX = vertices[0].x;
	float minY = vertices[0].y;
	float minZ = vertices[0].z;
	 
	 
	for (int i = 0; i < vertices.size(); i++) {
		if (vertices[i].x > maxX) {
			maxX = vertices[i].x;
		}
		if (vertices[i].y > maxY) {
			maxX = vertices[i].x;
		}
		if (vertices[i].y < minY) {
			minY = vertices[i].y;
		}
		if (vertices[i].x < minX) {
			minX = vertices[i].x;
		}
		if (vertices[i].z > maxZ) {
			maxZ = vertices[i].z;
		}
		if (vertices[i].z < minZ) {
			minZ = vertices[i].z;
		}

		
	}
	this->center =    glm::vec3((maxX + minX) / 2, (maxY + minY) / 2, (maxZ + minZ) / 2);

	this->boxPoints[0]= glm::vec3(maxX , maxY, minZ);
	this->boxPoints[1] = glm::vec3(maxX, minY, minZ);
	this->boxPoints[2] = glm::vec3(minX, minY, minZ);
	this->boxPoints[3] = glm::vec3(minX, maxY, minZ);
	this->boxPoints[4] = glm::vec3(maxX, maxY, maxZ);
	this->boxPoints[5] = glm::vec3(maxX, minY, maxZ);
	this->boxPoints[6] = glm::vec3(minX, minY, maxZ);
	this->boxPoints[7] = glm::vec3(minX, maxY, maxZ);



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