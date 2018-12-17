#define _USE_MATH_DEFINES

#include "Renderer.h"
#include "InitShader.h"
#include "MeshModel.h"
#include <imgui/imgui.h>
#include <vector>
#include <cmath>
#include "Utils.h"
 
#define INDEX(width,x,y,c) ((x)+(y)*(width))*3+(c)
 
template<class T>
const T& min(const T& a, const T& b)
{
	return (b < a) ? b : a;
}
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
void Renderer::DrawBrenLineAlg(int x0,int y0,int x1, int y1, const glm::vec3& color) {
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
void Renderer::Render(const Scene& scene)
{
	std::vector<glm::vec3> axes;
	Camera cam= Camera(glm::vec4(0,0,-50,1), glm::vec4(0, 0,0,1), glm::vec4(0, 1, 0,1));
	if (scene.GetCameraCount() > 0) {
		cam = scene.GetActiveCamera();

	}
	

	axes.push_back(glm::vec3(0, 0, 0));
	axes.push_back(glm::vec3(1, 0, 0));
	axes.push_back(glm::vec3(0, 1, 0));
	axes.push_back(glm::vec3(0,0, 1));
	cam.SetPerspectiveProjection(90, viewportWidth / (float)viewportHeight, 0.1, 100);
	glm::mat4 view=cam.getView();
 
	view = glm::inverse(view);
	for (int i = 0; i < axes.size(); i++) {
		
		axes[i] = Utils::MatrixMulti(glm::vec4(axes[i], 1), view);
		axes[i]=Utils::MatrixMulti(glm::vec4(axes[i], 1), cam.getProjection());
		axes[i].x =   (float)((axes[i].x + 1) * 0.5 * viewportWidth);
		axes[i].y =   (float)(( (axes[i].y + 1) * 0.5) * viewportHeight);



	}
	DrawBrenLineAlg(axes[0].x, axes[0].y, axes[1].x, axes[1].y, glm::vec3(1, 0, 0));
	DrawBrenLineAlg(axes[0].x, axes[0].y, axes[2].x, axes[2].y, glm::vec3(0, 1, 0));
	DrawBrenLineAlg(axes[0].x, axes[0].y, axes[3].x, axes[3].y, glm::vec3(0, 0, 1));
	 
	//#############################################
	//## You should override this implementation ##
	//## Here you should render the scene.       ##
	//#############################################

	// Draw a chess board in the middle of the screen
	 
	 
	/*for (int i = 100; i < viewportWidth - 100; i++)
	{
		for (int j = 100; j < viewportHeight - 100; j++)
		{
			int mod_i = i / 50;
			int mod_j = j / 50;

			int odd = (mod_i + mod_j) % 2;
			if (odd)
			{
				putPixel(i, j, glm::vec3(0, 1, 0));
			}
			else
			{
				putPixel(i, j, glm::vec3(1, 0, 0));
			}
		}
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