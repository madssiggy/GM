
#include "main.h"
#include "manager.h"
#include "renderer.h"


#include "polygon.h"

#include "gameobject.h"
#include "camera.h"
#include "field.h"


#include "model.h"
#include "player.h"
#include "input.h"
#define OBJECT_COUNT 3


CPolygon* g_Polygon;
CGameObject* g_GameObject[OBJECT_COUNT];

void CManager::Init()
{

	CRenderer::Init();
	CInput::Init();
	g_GameObject[0] = new CCamera();
	g_GameObject[0]->Init();

	
	g_GameObject[1] = new CField();
	g_GameObject[1]->Init();

	g_GameObject[2] = new CPlayer();
	g_GameObject[2]->Init();
	//これいこうに３Ｄオブジェクトを設定する
	g_Polygon = new CPolygon();
	g_Polygon->Init();

}

void CManager::Uninit()
{

	g_Polygon->Uninit();
	delete g_Polygon;
	for (int i = OBJECT_COUNT - 1;i >= 0;i--) {
		g_GameObject[i]->Uninit();
		delete g_GameObject[i];
	}
	

	//g_Field->Uninit();
	//delete g_Field;

	//g_Camera->Uninit();
	//delete g_Camera;

	CInput::Uninit();
	CRenderer::Uninit();
}

void CManager::Update()
{
	//
	CInput::Update();
	g_Polygon->Update();
	g_GameObject[0]->Update();

	for (int i = 1;i <OBJECT_COUNT ;i++) {

		g_GameObject[i]->Update();

	}
	CCamera* test = (CCamera*)g_GameObject[0];
	CPlayer* tmp = (CPlayer*)g_GameObject[2];
	test->SetPos(tmp->GetPos());
	//g_Field->Update();
	//g_Camera->Update();
	//g_Player->Update();


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
	for (int i = 0;i < OBJECT_COUNT;i++) {
		g_GameObject[i]->Draw();

	}
	
	//g_Field->Draw();
	//g_Player->Draw();
	light.Enable = false;
	CRenderer::SetLight(light);
	g_Polygon->Draw();



	CRenderer::End();

}
