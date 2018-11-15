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
	glm::mat4x4 worldRotate;
	bool showBox;
 
	
	glm::vec4 color;
	std::string modelName;
	std::vector<glm::vec3> boxPoints;
	glm::vec3 modelLocationGlobal;
	glm::vec3 center;
	glm::vec3 modelSelfRotate;
	glm::vec3 modelTranslate;
	glm::vec3 modelScale;
	std::vector<glm::vec3>  FixedVer;//save the vertices after multi with transfor matrixes
	void FixVert();



public:
	MeshModel(const std::vector<Face>& faces, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::string& modelName = "");
	virtual ~MeshModel();

	void SetWorldTransformation(const glm::mat4x4& worldTransform);
	const glm::mat4x4& GetWorldTransformation() const;
	const bool isShowBox();
	const glm::vec4& GetColor() const;
	void SetColor(const glm::vec4& color);
	void ChangeShowBox();
	const std::vector<glm::vec3> GetFixedVertices();
	const std::string& GetModelName();
	void SetModelName(const std::string name);
	const std::vector<glm::vec3>  GetVertices();
	const glm::vec3 getSelfRotate();
	const std::vector<Face>  GetFaces();
	const std::vector<glm::vec3> getBox();
	const glm::vec3 getCenter();
	void changeScale(const glm::vec3 scale);
	const glm::vec3  getScale();
	const glm::vec3   getLocation();
	void setLocation(const glm::vec3 location);
	void 	setSelfRotate(const glm::vec3 rotate);

	// Add more methods/functionality as needed...
};
