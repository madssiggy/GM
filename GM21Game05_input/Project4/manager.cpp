
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene.h"



CScene* g_Scene;

void CManager::Init()
{

	CRenderer::Init();
	CInput::Init();
	g_Scene = new CScene;
	g_Scene->Init();

}

void CManager::Uninit()
{

	g_Scene->Uninit();

	CInput::Uninit();
	CRenderer::Uninit();
}

void CManager::Update()
{
	//
	CInput::Update();
	g_Scene->Update();

}

void CManager::Draw()
{

	CRenderer::Begin();


	//cameraUdate
	LIGHT light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	CRenderer::SetLight(light);
	g_Scene->Update();
	
	//g_Field->Draw();
	//g_Player->Draw();
	light.Enable = false;
	CRenderer::SetLight(light);



	CRenderer::End();

}
