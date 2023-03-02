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
#include "Scene.h"

void load()
{
	auto& scene = aze::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<aze::GameObject>();
	go->AddComponent<aze::TextureObject>("background.tga");
	scene.Add(go);

	go = std::make_shared<aze::GameObject>();
	go->AddComponent<aze::TextureObject>("logo.tga").lock()->SetPosition(216,180);
	scene.Add(go);

	auto font = aze::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<aze::GameObject>();
	auto toc = to->AddComponent<aze::TextObject>("Programming 4 Assignment",font);
	toc.lock()->SetPosition(80, 20);
	scene.Add(to);

	auto fpsFont = aze::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	auto fpsGO = std::make_shared<aze::GameObject>();
	auto fpsText = fpsGO->AddComponent<aze::TextObject>("FPS",fpsFont);
	fpsText.lock()->SetPosition(10, 10).SetColor(SDL_Color{ 255,255,0 });
	auto fps = fpsGO->AddComponent<aze::FPS>(fpsText);
	fps.lock()->SetUpdateInterval(1.f);
	scene.Add(fpsGO);
}

int main(int, char*[]) {
	aze::Azeban engine("../Data/");
	engine.Run(load);
    return 0;
}