#define _USE_MATH_DEFINES
#include "Utils.h"
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


glm::vec3 Utils::Vec3fFromStream(std::istream& issLine)
{
	float x, y, z;
	issLine >> x >> std::ws >> y >> std::ws >> z;
	return glm::vec3(x, y, z);
}

glm::vec2 Utils::Vec2fFromStream(std::istream& issLine)
{
	float x, y;
	issLine >> x >> std::ws >> y;
	return glm::vec2(x, y);
}

MeshModel Utils::LoadMeshModel(const std::string& filePath)
{
	std::vector<Face> faces;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::ifstream ifile(filePath.c_str());

	// while not end of file
	while (!ifile.eof())
	{
		// get line
		std::string curLine;
		std::getline(ifile, curLine);

		// read the type of the line
		std::istringstream issLine(curLine);
		std::string lineType;

		issLine >> std::ws >> lineType;

		// based on the type parse data
		if (lineType == "v")
		{
			vertices.push_back(Utils::Vec3fFromStream(issLine));
		}
		else if (lineType == "vn")
		{
			// Add the required code here...
		}
		else if (lineType == "vt")
		{
			// Texture coordinates
		}
		else if (lineType == "f")
		{
			faces.push_back(Face(issLine));
		}
		else if (lineType == "#" || lineType == "")
		{
			// comment / empty line
		}
		else
		{
			std::cout << "Found unknown line Type \"" << lineType << "\"";
		}
	}

	return MeshModel(faces, vertices, normals, Utils::GetFileName(filePath));
}
//uti help in matrix multi , get a vertic and matrix and return the new vertic
glm::vec3 Utils::matrixMulti(const glm::vec3 vertic, const glm::mat4x4 mat) 
{	
	float x = mat[0][0]*vertic.x+mat[0][1]*vertic.y+mat[0][2]*vertic.z+mat[0][3]*1 ;
	float y = mat[1][0] * vertic.x + mat[1][1] * vertic.y + mat[1][2] * vertic.z + mat[1][3] * 1;
	float z = mat[2][0] * vertic.x + mat[2][1] * vertic.y + mat[2][2] * vertic.z + mat[2][3] * 1;
	float w = mat[3][0] * vertic.x + mat[3][1] * vertic.y + mat[3][2] * vertic.z + mat[3][3] * 1;

	return glm::vec3(x/w, y / w, z / w);
}
glm::vec2 Utils::d2vd3(const glm::vec3 vertic)
{
 

	return glm::vec2(vertic.x / vertic.z, vertic.y/ vertic.z);
}
//get angel and return rotation matrix
glm::mat4x4  Utils::RotateZMatrix(float angel) {
	float angelInRad = (angel*M_PI) / 180;
 
	return glm::mat4x4(cos(angelInRad),-sin(angelInRad), 0, 0
		, sin(angelInRad), cos(angelInRad), 0, 0
		, 0, 0, 1, 0
		, 0, 0, 0, 1);
}
glm::mat4x4  Utils::RotateMatrix(glm::vec3 rotate) {
	glm::mat4x4 help = RotateXMatrix(rotate.x)*RotateYMatrix(rotate.y)*RotateZMatrix(rotate.z);
	return  help;
}


glm::mat4x4  Utils::RotateXMatrix(float angel) {
	float angelInRad = (angel*M_PI) / 180;

	return glm::mat4x4(1,0,0,0,
		0,cos(angelInRad), -sin(angelInRad), 0
		,0, sin(angelInRad), cos(angelInRad),0
	 
		, 0, 0, 0, 1);
}
glm::mat4x4  Utils::RotateYMatrix(float angel) {
	float angelInRad = (angel*M_PI) / 180;

	return glm::mat4x4(cos(angelInRad),0, -sin(angelInRad),0,
		0,1,0,0,
		sin(angelInRad),0, cos(angelInRad),0 ,
		0,0,0,1
		);
}
glm::mat4x4  Utils::ScaleMatrix(const glm::vec3 scale) {
	return glm::mat4x4(scale.x, 0, 0, 0
		, 0, scale.y, 0, 0
		, 0, 0, scale.z, 0
		, 0, 0, 0, 1);
}

glm::mat4x4  Utils::TranslateMatrix(const glm::vec3 translate) {
	return glm::mat4x4(1, 0, 0, translate.x
		, 0, 1, 0, translate.y
		, 0, 0, 1, translate.z
		, 0, 0, 0, 1);


}
std::string Utils::GetFileName(const std::string& filePath)
{
	if (filePath.empty()) {
		return {};
	}

	auto len = filePath.length();
	auto index = filePath.find_last_of("/\\");

	if (index == std::string::npos) {
		return filePath;
	}

	if (index + 1 >= len) {

		len--;
		index = filePath.substr(0, len).find_last_of("/\\");

		if (len == 0) {
			return filePath;
		}

		if (index == 0) {
			return filePath.substr(1, len - 1);
		}

		if (index == std::string::npos) {
			return filePath.substr(0, len);
		}

		return filePath.substr(index + 1, len - index - 1);
	}

	return filePath.substr(index + 1, len - index);
}