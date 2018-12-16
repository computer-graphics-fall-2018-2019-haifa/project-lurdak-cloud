#pragma once
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include "Face.h"
 
/*
 * MeshModel class.
 * This class represents a mesh model (with faces and normals informations).
 * You can use Utils::LoadMeshModel to create instances of this class from .obj files.
 */
class MeshModel
{
private:
	std::vector<Face> faces;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	glm::mat4x4 worldTransform;
	glm::mat4x4 selfTransform;
	std::vector<glm::vec3> scaledAndRotatenormals;
	bool showBox;
 
	
	glm::vec4 color;
	std::string modelName;
	std::vector<glm::vec3> boxPoints;
	std::vector<glm::vec3> axes;

	std::vector<glm::vec3> scaledAndRotatedvertices;
	std::vector<glm::vec3> boxPoints2;
	
 
	glm::vec3 center;
	glm::vec3 modelSelfRotate;
	glm::vec3 modelScale;

	 



public:
	MeshModel(const std::vector<Face>& faces, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::string& modelName = "");
	virtual ~MeshModel();

	void SetWorldTransformation(const glm::mat4x4& worldTransform);
	const glm::mat4x4& GetWorldTransformation() const;
	const glm::mat4x4& GetSelfTransformation() const;
	const bool isShowBox();
	const glm::vec4& GetColor() const;
	void SetColor(const glm::vec4& color);
	const std::vector<glm::vec3>  getAxes();
	const std::string& GetModelName();
	void SetModelName(const std::string name);
	const std::vector<glm::vec3>  GetVertices();
	const glm::vec3 getSelfRotate();
	const std::vector<Face>  GetFaces();
	const std::vector<glm::vec3> getBox();
	const glm::vec3 getCenter();
	void changeScale(const glm::vec3 scale);
	const glm::vec3  getScale(); 
	void SetWorldTransformation(const glm::vec3 location, const glm::vec3 rotate);
 
	void setWorldLocation(const glm::vec3 location);
	void setWorldRotation(const glm::vec3 rotate);
	void setSelfRotate(const glm::vec3 rotate);
	void  centerTheModel();
	void ChangeShowBox(bool check);
	void applyScaleAndRotate();
	const std::vector<glm::vec3> GetOriginalVertices();
	const std::vector<glm::vec3> MeshModel::GetNomal();
	//void  lookAt(const glm::vec3& at, const glm::vec3& up);
	// Add more methods/functionality as needed...
};
