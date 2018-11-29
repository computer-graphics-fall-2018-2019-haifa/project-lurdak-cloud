#include "Scene.h"
#include "MeshModel.h"
#include <string>
#include "Utils.h"

Scene::Scene() :
	activeCameraIndex(0),
	activeModelIndex(0)
{
 
	AddCamera(std::make_shared<Camera>(glm::vec4(500, 600, 500, 0), glm::vec4(0, 0, 0, 0), glm::vec4(0, 1, 0, 0)));


}

void Scene::AddModel(const std::shared_ptr<MeshModel>& model)
{
	models.push_back(model);
}
 MeshModel * Scene::GetModel(int index)const
{
	return  &*models[index];
}
 Camera  * Scene::GetCamera(int index)const
 {
	 return    &*  cameras[index];
 }

const int Scene::GetModelCount() const
{
	return models.size();
}

void Scene::AddCamera(const std::shared_ptr<Camera>& camera)
{

	cameras.push_back(camera);
}

const int Scene::GetCameraCount() const
{
	return cameras.size();
}

void Scene::SetActiveCameraIndex(int index)
{
	// implementation suggestion...
	if (index >= 0 && index < cameras.size())
	{
		activeCameraIndex = index;
	}
}

const int Scene::GetActiveCameraIndex() const
{
	return activeCameraIndex;
}

void Scene::SetActiveModelIndex(int index)
{
	// implementation suggestion...
	if (index >= 0 && index < models.size())
	{
		activeModelIndex = index;
	}
}

const int Scene::GetActiveModelIndex() const
{
	return activeModelIndex;
}