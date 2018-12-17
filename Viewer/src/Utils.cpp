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
glm::mat4 Utils::TranslationMatrix(glm::vec3 translate) {
	return glm::mat4(1, 0, 0,0 ,
		0, 1, 0, 0,
		0, 0, 1,0 ,
		translate.x, translate.y, translate.z, 1);

}
glm::mat4 Utils::ScaleMatrix(glm::vec3 Scale) {
	return glm::mat4(Scale.x, 0, 0, 0,
		0, Scale.y, 0, 0,
		0, 0, Scale.z, 0,
		0, 0, 0, 1);

}
glm::vec3 Utils::MatrixMulti(const glm::vec4 src, glm::mat4 mat)
{
	float a, b, c, w;
	glm::vec3 newVec;

	
	a= src.x *  mat[0][0] + src.y * mat[1][0] + src.z * mat[2][0] + src.w * mat[3][0];
	b = src.x * mat[0][1] + src.y * mat[1][1] + src.z * mat[2][1] + src.w * mat[3][1];
	c = src.x * mat[0][2] + src.y * mat[1][2] + src.z * mat[2][2] + src.w * mat[3][2];
	w = src.x * mat[0][3] + src.y * mat[1][3] + src.z * mat[2][3] + src.w * mat[3][3];

	if (w != 1) {
		newVec.x = a / w;
		newVec.y = b / w;
		newVec.z = c / w;
	}
	else {
		newVec.x = a;
		newVec.y = b;
		newVec.z = c;
	}
	return newVec;
}
glm::mat4 Utils::PerspectiveMatrix(
	const float &b, const float &t, const float &l, const float &r,
	const float &n, const float &f
	)
{
	glm::mat4 M;
	M[0][0] = 2 * n / (r - l);
	M[0][1] = 0;
	M[0][2] = 0;
	M[0][3] = 0;

	M[1][0] = 0;
	M[1][1] = 2 * n / (t - b);
	M[1][2] = 0;
	M[1][3] = 0;

	M[2][0] = (r + l) / (r - l);
	M[2][1] = (t + b) / (t - b);
	M[2][2] = -(f + n) / (f - n);
	M[2][3] = -1;

	M[3][0] = 0;
	M[3][1] = 0;
	M[3][2] = -2 * f * n / (f - n);
	M[3][3] = 0;
	return M;
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