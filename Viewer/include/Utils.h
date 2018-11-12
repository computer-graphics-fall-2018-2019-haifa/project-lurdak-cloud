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
	static glm::mat4x4 RotateZMatrix(float angel);
	static glm::mat4x4 RotateXMatrix(float angel);
	static glm::mat4x4 RotateYMatrix(float angel);
	static glm::mat4x4 TranslateMatrix(const glm::vec3 vertic);
	static glm::mat4x4 ScaleMatrix(const glm::vec3 vertic);


	static glm::vec3 matrixMulti(const glm::vec3 vertic, const glm::mat4x4 mat);
	// Add here more static utility functions...
	// For example:
	//	1. function that gets an angle, and returns a rotation matrix around a certian axis
	//	2. function that gets a vector, and returns a translation matrix
	//	3. anything else that may be useful in global scope

private:
	static std::string GetFileName(const std::string& filePath);
};
