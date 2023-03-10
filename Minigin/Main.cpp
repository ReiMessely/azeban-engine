#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Azeban.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "TextureObject.h"
#include "GameObject.h"
#include "FPS.h"
#include "RevolutionComponent.h"
#include "RenderComponent.h"
#include "Scene.h"

void load()
{
	auto& scene = aze::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<aze::GameObject>();
	go->AddComponent<aze::RenderComponent>();
	go->AddComponent<aze::TextureObject>("background.tga");
	scene.Add(go);

	go = std::make_shared<aze::GameObject>();
	go->AddComponent<aze::RenderComponent>();
	go->AddComponent<aze::TextureObject>("logo.tga")/*.lock()->SetPosition(216, 180)*/;
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = aze::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<aze::GameObject>();
	to->AddComponent<aze::RenderComponent>();
	auto toc = to->AddComponent<aze::TextObject>("Programming 4 Assignment",font);
	//toc.lock()->SetPosition(80, 20);
	to->SetPosition(80, 20);
	scene.Add(to);

	auto fpsFont = aze::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	auto fpsGO = std::make_shared<aze::GameObject>();
	fpsGO->AddComponent<aze::RenderComponent>();
	auto fpsText = fpsGO->AddComponent<aze::TextObject>("FPS",fpsFont);
	fpsText.lock()->/*SetPosition(10, 10).*/SetColor(SDL_Color{255,255,0});
	fpsGO->SetPosition(10, 10);
	auto fps = fpsGO->AddComponent<aze::FPS>(fpsText);
	fps.lock()->SetUpdateInterval(1.f);
	scene.Add(fpsGO);

	auto emptyGameObject = std::make_shared<aze::GameObject>();
	emptyGameObject->SetPosition(300, 300);
	auto go_bub = std::make_shared<aze::GameObject>();
	go_bub->AddComponent<aze::RenderComponent>();
	go_bub->AddComponent<aze::TextureObject>("Bub.png");
	go_bub->AddComponent<aze::RevolutionComponent>().lock()->SetRadius(15.f).SetSpeed(5.f);
	go_bub->SetParent(emptyGameObject);
	auto go_bob = std::make_shared<aze::GameObject>();
	go_bob->AddComponent<aze::RenderComponent>();
	go_bob->AddComponent<aze::TextureObject>("Bob.png");
	go_bob->AddComponent<aze::RevolutionComponent>().lock()->SetRadius(30.f).SetSpeed(-5.f);
	go_bob->SetParent(go_bub);
	scene.Add(emptyGameObject);
	scene.Add(go_bub);
	scene.Add(go_bob);
	//aze::GameObject::Destroy(go_bob.get());
}

int main(int, char*[]) {
	aze::Azeban engine("../Data/");
	engine.Run(load);
    return 0;
}