#include "Scene.h"
#include "GameObject.h"

using namespace aze;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	object->SetParent(nullptr);
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update(float elapsedSec)
{
	for(auto& object : m_objects)
	{
		object->Update(elapsedSec);
	}
	for (auto& object : m_objects)
	{
		if (object->IsMarkedForDestroy())
		{
			Remove(object);
		}
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

