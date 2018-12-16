#pragma once
#include "Scene.h"
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>

/*
 * Renderer class.
 */
class Renderer
{
private:
	float *colorBuffer;
	float *zBuffer;
	int viewportWidth;
	int viewportHeight;
	int viewportX;
	int viewportY;

	void putPixel(int x, int y, const glm::vec3& color);
	void createBuffers(int viewportWidth, int viewportHeight);
	void plotLineLow(int x0, int y0, int x1, int y1, const glm::vec3& color);
	void plotLineHight(int x0, int y0, int x1, int y1, const glm::vec3& color);
	GLuint glScreenTex;
	GLuint glScreenVtc;

	void createOpenGLBuffer();
	void initOpenGLRendering();

public:
	Renderer(int viewportWidth, int viewportHeight, int viewportX = 0, int viewportY = 0);
	~Renderer();
	void DrawLine(const glm::vec3 a, const glm::vec3 b, const glm::vec4& color, const float zoom);
	void Render(const Scene& scene);
	void SwapBuffers();
	void ClearColorBuffer(const glm::vec3& color);
	void SetViewport(int viewportWidth, int viewportHeight, int viewportX = 0, int viewportY = 0);
	void DrawBrenLineAlg(int x0, int y0, int x1, int y1, const glm::vec3& color);
	void DrawFaceLines(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, const glm::vec3 color );
	void DrawBox(std::vector<glm::vec3> box, const glm::vec3 color);
	void  ScaledAndTransformedModels(const Scene& scene);
	void ScaledAndTransformedCams(const Scene& scene);
	void  TransformedCamera(const Scene& scene);
	 
	// Add more methods/functionality as needed...
};
