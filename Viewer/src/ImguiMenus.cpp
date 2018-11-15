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
		static float scaleX = 100;
		static float scaleY = 100;
		static float scaleZ = 100;
		static float LX = 100;
		static float LY = 100;
		static float LZ = 100;
		static float RZ = 0;

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
		
		ImGui::InputFloat("Scale X", &scaleX,0,0,2); ImGui::SameLine(120);
		 ImGui::InputFloat("Scale Y", &scaleY,0,0,2 ); ImGui::SameLine(240);
		 ImGui::InputFloat("Scale Z", &scaleZ ,0,0,2);   
		//scaleX
		 
		if (scaleX <= 0)scaleX = 0.01;
		//scale y
 
		if (scaleY <= 0)scaleY = 0.01;
		//scalez
		 
		if (scaleZ <= 0)scaleZ = 0.01;
		//location
		ImGui::InputFloat("LGlobal X", &LX, 0, 0, 2); ImGui::SameLine(120);
		ImGui::InputFloat("LGlobal Y", &LY, 0, 0, 2); ImGui::SameLine(240);
		ImGui::InputFloat("LGlobal z", &LZ, 0, 0, 2);

		ImGui::InputFloat("Rotate Self z", &RZ, 0, 0, 2);

		if (scene.GetModelCount() > 0) {
		scene.GetModel(scene.GetActiveModelIndex())->changeScale(glm::vec3(scaleX, scaleY, scaleZ));
		scene.GetModel(scene.GetActiveModelIndex())->setLocation(glm::vec3(LX, LY, LZ));
		scene.GetModel(scene.GetActiveModelIndex())->setSelfRotate(glm::vec3(0, 0, RZ));
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