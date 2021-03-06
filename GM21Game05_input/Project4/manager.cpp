
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene.h"
#include "title.h"
//#include "game.h"
//#include "result.h"
#include "debug_scene.h"


CScene* CManager::m_Scene=NULL;

void CManager::Init()
{

	CRenderer::Init();
	CInput::Init();
	m_Scene = new CDebugScene;

	m_Scene->Init();
	//SetScene<CDebugScene >();
}

void CManager::Uninit()
{

	m_Scene->Uninit();

	CInput::Uninit();
	CRenderer::Uninit();
}

void CManager::Update()
{
	//
	CInput::Update();
	m_Scene->Update();

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
	light.Diffuse = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
	CRenderer::SetLight(light);

	m_Scene->Draw();

	light.Enable = false;
	CRenderer::SetLight(light);



	CRenderer::End();

}
