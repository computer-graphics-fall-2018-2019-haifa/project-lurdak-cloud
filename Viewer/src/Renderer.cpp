#define _USE_MATH_DEFINES

#include "Renderer.h"
#include "InitShader.h"
#include "MeshModel.h"
#include "Utils.h"
#include <imgui/imgui.h>
#include <vector>
#include <cmath>

#define INDEX(width,x,y,c) ((x)+(y)*(width))*3+(c)

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
	//glm::vec3 camViewv1 = Utils::matrixMulti(v1, (selectedCam.GetCamViewTrans()*selectedCam.GetCamProjTrans()));
	//glm::vec3 camViewv2 = Utils::matrixMulti(v2, (selectedCam.GetCamViewTrans()*selectedCam.GetCamProjTrans()));
	//glm::vec3 camViewv3 = Utils::matrixMulti(v3, (selectedCam.GetCamViewTrans()*selectedCam.GetCamProjTrans()));

	int  x0 =  v1.x ;
	int y0 =  v1.y ;
	int x1 =  v2.x ;
	int y1 =  v2.y ;
	int x2 =  v3.x ;
	int y2 =  v3.y ;

	DrawBrenLineAlg(x0, y0, x1, y1,color);
	DrawBrenLineAlg(x1, y1, x2, y2, color);
	DrawBrenLineAlg(x2, y2, x0, y0, color);
	 

	
}
void Renderer::DrawBox(std::vector<glm::vec3> box, const glm::vec3 color) {
	for (int i = 0; i < 3; i++) {
		DrawBrenLineAlg(box[i].x, box[i].y, box[i + 1].x, box[i + 1].y,color);
	}
	DrawBrenLineAlg(box[3].x, box[3].y, box[0].x, box[0].y,color);
	for (int i = 4; i < 7; i++) {
		DrawBrenLineAlg(box[i].x, box[i].y, box[i + 1].x, box[i + 1].y, color);
	}
	DrawBrenLineAlg(box[4].x, box[4].y, box[7].x, box[7].y, color);
	DrawBrenLineAlg(box[4].x, box[4].y, box[0].x, box[0].y, color);
	DrawBrenLineAlg(box[3].x, box[3].y, box[7].x, box[7].y, color);
	DrawBrenLineAlg(box[5].x, box[5].y, box[1].x, box[1].y, color);
	DrawBrenLineAlg(box[6].x, box[6].y, box[2].x, box[2].y, color);
}
/*void Renderer::DrawAxesInCenter(MeshModel model, const glm::vec3 color) {
	for (int i = 0; i < 2; i++) {
		DrawBrenLineAlg(model.getBox()[i].x, model.getBox()[i].y, model.getBox()[i + 1].x, model.getBox()[i + 1].y, color);
	}
	DrawBrenLineAlg(model.getBox()[3].x, model.getBox()[3].y, model.getBox()[0].x, model.getBox()[0].y, color);
	for (int i = 4; i < 6; i++) {
		DrawBrenLineAlg(model.getBox()[i].x, model.getBox()[i].y, model.getBox()[i + 1].x, model.getBox()[i + 1].y, color);
	}
	DrawBrenLineAlg(model.getBox()[4].x, model.getBox()[4].y, model.getBox()[7].x, model.getBox()[7].y, color);
	DrawBrenLineAlg(model.getBox()[4].x, model.getBox()[4].y, model.getBox()[0].x, model.getBox()[0].y, color);
	DrawBrenLineAlg(model.getBox()[3].x, model.getBox()[3].y, model.getBox()[7].x, model.getBox()[7].y, color);
	DrawBrenLineAlg(model.getBox()[5].x, model.getBox()[5].y, model.getBox()[1].x, model.getBox()[1].y, color);
	DrawBrenLineAlg(model.getBox()[6].x, model.getBox()[6].y, model.getBox()[2].x, model.getBox()[2].y, color);
}
*/
void Renderer::ScaledAndTransformedModels(const Scene& scene) {
 
	if (scene.GetModelCount() > 0) {
		Camera cam = *scene.GetCamera(0);

		for (int i = 0; i < scene.GetModelCount(); i++) {
			MeshModel model = *scene.GetModel(i);
			
			std::vector<glm::vec3> vertices = model.GetVertices( );
	 
	
			
			//model.lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
			glm::mat4 tMat = model.GetWorldTransformation();
		
			tMat = cam.GetCamProjTrans()*cam.GetCamViewTrans()*tMat;
			for(int j=0;j<vertices.size();j++){
				vertices[j] = Utils::matrixMulti(vertices[j], tMat);
			 
			 
			}
			std::vector<glm::vec3> box = model.getBox();
			

			
			if (model.isShowBox()) {
				for (int j = 0; j < box.size(); j++) {
					box[j] = Utils::matrixMulti(box[j], tMat);
				}
				DrawBox(box, glm::vec3(1, 0, 0));
			}
			for (auto face : model.GetFaces())
			{

				glm::vec3 v0 = vertices[face.GetVertexIndex(0) - 1];
				glm::vec3 v1 = vertices[face.GetVertexIndex(1) - 1];
				glm::vec3 v2 = vertices[face.GetVertexIndex(2) - 1];
				 
				DrawFaceLines(v0, v1, v2, glm::vec3(0, 1, 0));


			}
			

		}



	}
}
void Renderer::ScaledAndTransformedCams(const Scene& scene) {

	if (scene.GetCameraCount() > 0) {
		

		for (int i = 0; i < scene.GetCameraCount(); i++) {
			MeshModel model = scene.GetCamera(i)->GetCameraModel();

			std::vector<glm::vec3> vertices = model.GetVertices();



			//model.lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
			glm::mat4 tMat =( model.GetWorldTransformation());
	
			//tMat = cam.GetCamProjTrans()*cam.GetCamViewTrans()*tMat;
			for (int j = 0; j < vertices.size(); j++) {
				vertices[j] = Utils::matrixMulti(vertices[j], tMat);


			}
			std::vector<glm::vec3> box = model.getBox();



			if (model.isShowBox()) {
				for (int j = 0; j < box.size(); j++) {
					box[j] = Utils::matrixMulti(box[j], tMat);
				}
				DrawBox(box, glm::vec3(1, 0, 0));
			}
			for (auto face : model.GetFaces())
			{

				glm::vec3 v0 = vertices[face.GetVertexIndex(0) - 1];
				glm::vec3 v1 = vertices[face.GetVertexIndex(1) - 1];
				glm::vec3 v2 = vertices[face.GetVertexIndex(2) - 1];

				DrawFaceLines(v0, v1, v2, glm::vec3(0, 1, 0));


			}


		}



	}
}

void Renderer::Render(const Scene& scene)
{
	//#############################################
	//## You should override this implementation ##
	//## Here you should render the scene.       ##
	//#############################################

	// Draw a chess board in the middle of the screen
	/*Camera cam = scene.GetCamera(0);
	if (scene.CameraModels.size() > 0) {
		MeshModel m=* scene.CameraModels[0];
		m.changeScale(glm::vec3(100, 100, 100));
		 
		m.setWorldLocation(cam.eye);
		
		//m.setSelfRotate(cam.orientation);
		std::vector<glm::vec3> vertices = m.GetFixedVertices();
		std::vector<glm::vec3> box = m.getBox();




		if (m.isShowBox()) {
			DrawBox(box, glm::vec3(1, 0, 0));
		}
		for (auto face : m.GetFaces())
		{

			glm::vec3 v0 = vertices[face.GetVertexIndex(0) - 1];
			glm::vec3 v1 = vertices[face.GetVertexIndex(1) - 1];
			glm::vec3 v2 = vertices[face.GetVertexIndex(2) - 1];
			v0 = Utils::matrixMulti(v0, cam.GetCamProjTrans());
			v1 = Utils::matrixMulti(v1, cam.GetCamProjTrans());
			v2 = Utils::matrixMulti(v2, cam.GetCamProjTrans());/*
			v0 = glm::vec3(v0.x / v0.z, v0.y / v0.z, 1);
			v1 = glm::vec3(v1.x / v1.z, v1.y / v1.z, 1);
			v2 = glm::vec3(v2.x / v2.z, v2.y / v2.z, 1);
			DrawFaceLines(v0, v1, v2, glm::vec3(0, 1, 0));


		}


	}*/
	ScaledAndTransformedModels(scene);
	ScaledAndTransformedCams(scene);
	std::vector<glm::vec3> vertices;
	vertices.push_back( glm::vec3(0, 0, 0));
	vertices.push_back(glm::vec3(100, 0, 0));
	vertices.push_back(glm::vec3(0, 100, 0));
	vertices.push_back(glm::vec3(0, 0, 100));
	 

	glm::mat4 tMat = scene.GetCamera(scene.GetActiveCameraIndex())->GetCamProjTrans() *scene.GetCamera(scene.GetActiveCameraIndex())->GetCamViewTrans();
	for (int j = 0; j < vertices.size(); j++) {
		vertices[j] = Utils::matrixMulti(vertices[j], tMat);
	}
	DrawBrenLineAlg(vertices[0].x, vertices[0].y, vertices[1].x, vertices[1].y, glm::vec3(1,0,0));
	DrawBrenLineAlg(vertices[0].x, vertices[0].y, vertices[2].x, vertices[2].y, glm::vec3(0, 1, 0));
	DrawBrenLineAlg(vertices[0].x, vertices[0].y, vertices[3].x, vertices[3].y, glm::vec3(0, 0, 1));

	}
	
	
 
	
	
 
	
		
	
	
	
	/*for (int i = 0; i < 10; i++) {
		DrawBrenLineAlg(100 + i * 50, 100, 100 + i * 50, 600, glm::vec3(0, 1, 0));
		DrawBrenLineAlg(100 , 100+50*i, 600, 100 + 50 * i, glm::vec3(0, 1, 0));
	}*/

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