#pragma once
#define _USE_MATH_DEFINES

#include "ImguiMenus.h"
#include "MeshModel.h"
#include "Utils.h"
 
#include <cmath>
#include <memory>
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <nfd.h>
#include <random>

bool showDemoWindow = false;
bool showAnotherWindow = false;
glm::vec3 scale=glm::vec3(10);
glm::vec3 location= glm::vec3(0);
glm::vec3 rotate=glm::vec3(0);
glm::vec3 worldRotate = glm::vec3(0);
glm::vec3 deltaScale= glm::vec3(10);
glm::vec3 deltaLocation= glm::vec3(0);
glm::vec3 deltaWorldRotate= glm::vec3(0);
glm::vec3 deltaRotate = glm::vec3(0);
bool check = false;
bool showNorm = false;

glm::vec4 clearColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);

const glm::vec4& GetClearColor()
{
	return clearColor;
}

void DrawImguiMenus(ImGuiIO& io, Scene& scene)
{
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (showDemoWindow)
	{
		ImGui::ShowDemoWindow(&showDemoWindow);
		//ImGui::show
	}

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;



		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &showDemoWindow);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &showAnotherWindow);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clearColor); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);
		ImGui::PushItemWidth(50);
		deltaScale = scale;
		deltaLocation = location;
		deltaRotate = rotate;
		deltaWorldRotate = worldRotate;
		ImGui::InputFloat("Scale X", &scale.x,0,0,2); ImGui::SameLine(120);
		 ImGui::InputFloat("Scale Y", &scale.y,0,0,2 ); ImGui::SameLine(240);
		 ImGui::InputFloat("Scale Z", &scale.z ,0,0,2);   
		//scaleX
		 
		 if (scale.x <= 0) {
			 scale.x = 0.01;
		 }
		//scale y
 
		 if (scale.y <= 0) {
			 scale.y = 0.01;

		 }
		//scalez
		 
		 if (scale.z <= 0) {
			 scale.z = 0.01;
		 }
		//location
		ImGui::InputFloat("LGlobal X", &location.x, 0, 0, 2); ImGui::SameLine(140);
		ImGui::InputFloat("LGlobal Y", &location.y, 0, 0, 2); ImGui::SameLine(280);
		ImGui::InputFloat("LGlobal z", &location.z, 0, 0, 2);

		ImGui::InputFloat("Rotate Self X", &rotate.x, 0, 0, 2); ImGui::SameLine(220);
		ImGui::InputFloat("Rotate Self Y", &rotate.y, 0, 0, 2); ImGui::SameLine(440);
		ImGui::InputFloat("Rotate Self Z", &rotate.z, 0, 0, 2);
	
		ImGui::InputFloat("Rotate World X", &worldRotate.x, 0, 0, 2); ImGui::SameLine(220);
		ImGui::InputFloat("Rotate World Y", &worldRotate.y, 0, 0, 2); ImGui::SameLine(440);
		ImGui::InputFloat("Rotate World Z", &worldRotate.z, 0, 0, 2);
		ImGui::Checkbox("box", &check);
		//ImGui::Checkbox("box", &showNorm);
			
		if (scene.GetModelCount() > 0) {
			scene.GetModel(scene.GetActiveModelIndex())->ChangeShowBox(check);
			//scene.GetModel(scene.GetActiveModelIndex())->ChangeShowBox(check);
			if (scale != deltaScale || rotate != deltaRotate || location !=deltaLocation || worldRotate!=deltaWorldRotate) {
				scene.GetModel(scene.GetActiveModelIndex())->changeScale(scale);
				scene.GetModel(scene.GetActiveModelIndex())->setSelfRotate(rotate);
				scene.GetModel(scene.GetActiveModelIndex())->setWorldLocation(location);
				scene.GetModel(scene.GetActiveModelIndex())->setWorldRotation(worldRotate);
			}
		
		}
		

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (showAnotherWindow)
	{
		ImGui::Begin("Another Window", &showAnotherWindow);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
		{
			showAnotherWindow = false;
		}
		ImGui::End();
	}

	// 4. Demonstrate creating a fullscreen menu bar and populating it.
	{
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoFocusOnAppearing;
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Load Model...", "CTRL+O"))
				{
					nfdchar_t *outPath = NULL;
					nfdresult_t result = NFD_OpenDialog("obj;png,jpg", NULL, &outPath);
					if (result == NFD_OKAY) {
						scene.AddModel(std::make_shared<MeshModel>(Utils::LoadMeshModel(outPath)));
						free(outPath);
					}
					else if (result == NFD_CANCEL) {
					}
					else {
					}

				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}
}