#define _USE_MATH_DEFINES

#include "Renderer.h"
#include "InitShader.h"
#include "MeshModel.h"
#include <imgui/imgui.h>
#include <vector>
#include <cmath>

#define INDEX(width,x,y,c) ((x)+(y)*(width))*3+(c)
#define SIZE 50;

Renderer::Renderer(int viewportWidth, int viewportHeight, int viewportX, int viewportY) :
	colorBuffer(nullptr),
	zBuffer(nullptr)
{
	initOpenGLRendering();
	SetViewport(viewportWidth, viewportHeight, viewportX, viewportY);
}

Renderer::~Renderer()
{
	if (colorBuffer)
	{
		delete[] colorBuffer;
	}
}

void Renderer::putPixel(int i, int j, const glm::vec3& color)
{
	if (i < 0) return; if (i >= viewportWidth) return;
	if (j < 0) return; if (j >= viewportHeight) return;
	colorBuffer[INDEX(viewportWidth, i, j, 0)] = color.x;
	colorBuffer[INDEX(viewportWidth, i, j, 1)] = color.y;
	colorBuffer[INDEX(viewportWidth, i, j, 2)] = color.z;
}

void Renderer::createBuffers(int viewportWidth, int viewportHeight)
{
	if (colorBuffer)
	{
		delete[] colorBuffer;
	}

	colorBuffer = new float[3* viewportWidth * viewportHeight];
	for (int x = 0; x < viewportWidth; x++)
	{
		for (int y = 0; y < viewportHeight; y++)
		{
			putPixel(x, y, glm::vec3(0.0f, 0.0f, 0.0f));
		}
	}
}

void Renderer::ClearColorBuffer(const glm::vec3& color)
{
	for (int i = 0; i < viewportWidth; i++)
	{
		for (int j = 0; j < viewportHeight; j++)
		{
			putPixel(i, j, color);
		}
	}
}

void Renderer::SetViewport(int viewportWidth, int viewportHeight, int viewportX, int viewportY)
{
	this->viewportX = viewportX;
	this->viewportY = viewportY;
	this->viewportWidth = viewportWidth;
	this->viewportHeight = viewportHeight;
	createBuffers(viewportWidth, viewportHeight);
	createOpenGLBuffer();
}
void Renderer::plotLineLow(int x0, int y0,int x1,int y1, const glm::vec3& color)
{
	float deltax = x1 - x0;
	float deltay = y1 - y0;
	float yi = 1;
	float slopError = 0;
	int y = 0;
	int x = 0;
	if (deltay < 0) {
		yi = -1;
		deltay = -deltay;
	}
	slopError = 2 * deltay - deltax;
	y = y0;
	for (x = x0; x < x1; x++) {
		putPixel(x, y, color);
		if (slopError > 0) {
			y += yi;
			slopError -= 2 * deltax;
		}
		slopError += 2 * deltay;
	}
}
void Renderer::plotLineHight(int x0, int y0, int x1, int y1, const glm::vec3& color)
{
	float deltax = x1 - x0;
	float deltay = y1 - y0;
	float xi = 1;
	float slopError  ;
	int y = 0;
	int x = 0;
	if (deltax < 0) {
		xi = -1;
		deltax = -deltax;
	}
	slopError = 2 * deltax - deltay;
	x = x0;
	for (y = y0; y < y1; y++) {
		putPixel(x, y, color);
		if (slopError > 0) {
			x += xi;
			slopError -= 2 * deltay;
		}
		slopError += 2 * deltax;
	}
}
void Renderer::DrawBrenLineAlg(int x0, int y0, int x1, int y1, const glm::vec3& color) {
	float deltax = abs(x1- x0);
	float deltay = abs(y1 - y0);
	if (deltax > deltay) {
		if (x0 > x1) {
			plotLineLow(x1, y1, x0, y0,color);
		}
		else {
			plotLineLow(x0, y0, x1, y1, color);	
		}	
	}
	else {
		if (y0 > y1) {
			plotLineHight(x1, y1, x0, y0, color);
			
		}
		else {
			plotLineHight(x0, y0, x1, y1, color);
			
		}
	}
	


}
void Renderer::DrawFaceLines(const glm::vec3 v1, const glm::vec3 v2, const glm::vec3 v3,const glm::vec3 color) {
	int  x0 = v1.x*SIZE;
	int y0 = v1.y*SIZE;
	int x1 = v2.x*SIZE;
	int y1 = v2.y*SIZE;
	int x2 = v3.x*SIZE;
	int y2 = v3.y*SIZE;

	DrawBrenLineAlg(x0, y0, x1, y1,color);
	DrawBrenLineAlg(x1, y1, x2, y2, color);
	DrawBrenLineAlg(x2, y2, x0, y0, color);
	 

	
}
void Renderer::Render(const Scene& scene)
{
	//#############################################
	//## You should override this implementation ##
	//## Here you should render the scene.       ##
	//#############################################

	// Draw a chess board in the middle of the screen
	auto flag = true;
	if (scene.GetModelCount() > 0 ) {

		for (int i = 0; i < scene.GetModelCount(); i++) {

			auto model = scene.GetModel(i);
			auto facesInModel = model.GetFaces();
			for (auto face : facesInModel)
			{

				glm::vec3 v0 = model.GetVertices()[face.GetVertexIndex(0)-1];
				glm::vec3 v1 = model.GetVertices()[face.GetVertexIndex(1)-1];
				glm::vec3 v2 = model.GetVertices()[face.GetVertexIndex(2)-1];
				DrawFaceLines(v0, v1, v2, glm::vec3(0, 1, 0));


			}
		}
		
	
	}
	
	/*for (int i = 0; i < 10; i++) {
		DrawBrenLineAlg(100 + i * 50, 100, 100 + i * 50, 600, glm::vec3(0, 1, 0));
		DrawBrenLineAlg(100 , 100+50*i, 600, 100 + 50 * i, glm::vec3(0, 1, 0));
	}*/
	
}

//##############################
//##OpenGL stuff. Don't touch.##
//##############################

// Basic tutorial on how opengl works:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
// don't linger here for now, we will have a few tutorials about opengl later.
void Renderer::initOpenGLRendering()
{
	// Creates a unique identifier for an opengl texture.
	glGenTextures(1, &glScreenTex);

	// Same for vertex array object (VAO). VAO is a set of buffers that describe a renderable object.
	glGenVertexArrays(1, &glScreenVtc);

	GLuint buffer;

	// Makes this VAO the current one.
	glBindVertexArray(glScreenVtc);

	// Creates a unique identifier for a buffer.
	glGenBuffers(1, &buffer);

	// (-1, 1)____(1, 1)
	//	     |\  |
	//	     | \ | <--- The exture is drawn over two triangles that stretch over the screen.
	//	     |__\|
	// (-1,-1)    (1,-1)
	const GLfloat vtc[]={
		-1, -1,
		 1, -1,
		-1,  1,
		-1,  1,
		 1, -1,
		 1,  1
	};

	const GLfloat tex[]={
		0,0,
		1,0,
		0,1,
		0,1,
		1,0,
		1,1};

	// Makes this buffer the current one.
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// This is the opengl way for doing malloc on the gpu. 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtc)+sizeof(tex), NULL, GL_STATIC_DRAW);

	// memcopy vtc to buffer[0,sizeof(vtc)-1]
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vtc), vtc);

	// memcopy tex to buffer[sizeof(vtc),sizeof(vtc)+sizeof(tex)]
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vtc), sizeof(tex), tex);

	// Loads and compiles a sheder.
	GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );

	// Make this program the current one.
	glUseProgram(program);

	// Tells the shader where to look for the vertex position data, and the data dimensions.
	GLint  vPosition = glGetAttribLocation( program, "vPosition" );
	glEnableVertexAttribArray( vPosition );
	glVertexAttribPointer( vPosition,2,GL_FLOAT,GL_FALSE,0,0 );

	// Same for texture coordinates data.
	GLint  vTexCoord = glGetAttribLocation( program, "vTexCoord" );
	glEnableVertexAttribArray( vTexCoord );
	glVertexAttribPointer( vTexCoord,2,GL_FLOAT,GL_FALSE,0,(GLvoid *)sizeof(vtc) );

	//glProgramUniform1i( program, glGetUniformLocation(program, "texture"), 0 );

	// Tells the shader to use GL_TEXTURE0 as the texture id.
	glUniform1i(glGetUniformLocation(program, "texture"),0);
}

void Renderer::createOpenGLBuffer()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, glScreenTex);

	// malloc for a texture on the gpu.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, viewportWidth, viewportHeight, 0, GL_RGB, GL_FLOAT, NULL);
	glViewport(0, 0, viewportWidth, viewportHeight);
}

void Renderer::SwapBuffers()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, glScreenTex);

	// memcopy's colorBuffer into the gpu.
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, viewportWidth, viewportHeight, GL_RGB, GL_FLOAT, colorBuffer);

	// Tells opengl to use mipmapping
	glGenerateMipmap(GL_TEXTURE_2D);

	// Make glScreenVtc current VAO
	glBindVertexArray(glScreenVtc);

	// Finally renders the data.
	glDrawArrays(GL_TRIANGLES, 0, 6);
}