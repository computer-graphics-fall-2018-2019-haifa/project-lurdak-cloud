#pragma once
#include <glm/glm.hpp>
#include <string>
#include "MeshModel.h"

/*
 * Utils class.
 * This class is consisted of static helper methods that can have many clients across the code.
 */
class Utils
{
public:
	static glm::vec3 Vec3fFromStream(std::istream& issLine);
	static glm::vec2 Vec2fFromStream(std::istream& issLine);
	static MeshModel LoadMeshModel(const std::string& filePath);
	static glm::mat4 TranslationMatrix(glm::vec3 translate);
	static glm::vec3 MatrixMulti(const glm::vec4 src, glm::mat4 mat);
	static glm::mat4 Utils::ScaleMatrix(glm::vec3 Scale);
	static glm::mat4 PerspectiveMatrix(
		const float &b, const float &t, const float &l, const float &r,
		const float &n, const float &f
	);

	// Add here more static utility functions...
	// For example:
	//	1. function that gets an angle, and returns a rotation matrix around a certian axis
	//	2. function that gets a vector, and returns a translation matrix
	//	3. anything else that may be useful in global scope

private:
	static std::string GetFileName(const std::string& filePath);
};
