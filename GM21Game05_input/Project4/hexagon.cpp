#include "main.h"


#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "input.h"

#include "player.h"
#include "hexagon.h"

#include "bullet.h"
#include "scene.h"



void CHexagon::Init() {
	m_scene = CManager::GetScene();
	m_Model = new CModel();
	//	m_Model->Load("asset\\model\\human.obj");
	m_Model->Load("asset\\model\\hexagon.obj");

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);


}
void CHexagon::Uninit() {

	m_Model->Unload();
	delete m_Model;
}
void CHexagon::Update() {


}
void CHexagon::Draw() {//マトリクス設定

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot*trans;
	CRenderer::SetWorldMatrix(&world);



	m_Model->Draw();

}
int HexagonMatrix[9][2]={
	//中心
	{0,0},
	//右から記載。つまり最初の周回の最初に取り扱う行列が（１，１）、最期が（２、０）、
	{1,1},
	{0,2},
	{-1,1},
	{-2,0},
	{-1,-1},
	{0,-2},
	{1,-1},
	{2,0}
};
void SetHexagon(int Mag) {
	CScene* scene = CManager::GetScene();
	D3DXVECTOR3 pos = D3DXVECTOR3(1.0f, 0.0f, 1.5f);
//	scene->AddGameObject<CHexagon>(1)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CHexagon* tmp;
		for (int i = 0;i < 9;i++) {
			tmp = scene->AddGameObject<CHexagon>(1);
			tmp->SetScale(D3DXVECTOR3((float)Mag, 1.0f, (float)Mag));
			tmp->SetPosition(D3DXVECTOR3(pos.x*(float)HexagonMatrix[i][0] * (float)Mag, 0.0f, pos.z*(float)HexagonMatrix[i][1] * (float)Mag));
		
		}
		for (int i = 0;i < 9;i++) {
			tmp = scene->AddGameObject<CHexagon>(1);
			tmp->SetScale(D3DXVECTOR3((float)Mag, 1.0f, (float)Mag));
			tmp->SetPosition(D3DXVECTOR3(pos.x*((float)HexagonMatrix[i][0] + 4.0f) * (float)Mag, 0.0f, (pos.z*(float)HexagonMatrix[i][1] + 3.0f) * (float)Mag));
		}

		for (int i = 0;i < 9;i++) {
			tmp = scene->AddGameObject<CHexagon>(1);
			tmp->SetScale(D3DXVECTOR3((float)Mag, 1.0f, (float)Mag));
			tmp->SetPosition(D3DXVECTOR3(pos.x*((float)HexagonMatrix[i][0] + 4.0f) * (float)Mag, 0.0f, (pos.z*(float)HexagonMatrix[i][1] - 3.0f) * (float)Mag));
		}

		for (int i = 0;i < 9;i++) {
			tmp = scene->AddGameObject<CHexagon>(1);
			tmp->SetScale(D3DXVECTOR3((float)Mag, 1.0f, (float)Mag));
			tmp->SetPosition(D3DXVECTOR3(pos.x*((float)HexagonMatrix[i][0] - 4.0f) * (float)Mag, 0.0f, (pos.z*(float)HexagonMatrix[i][1] + 3.0f) * (float)Mag));
		}

		for (int i = 0;i < 9;i++) {
			tmp = scene->AddGameObject<CHexagon>(1);
			tmp->SetScale(D3DXVECTOR3((float)Mag, 1.0f, (float)Mag));
			tmp->SetPosition(D3DXVECTOR3(pos.x*((float)HexagonMatrix[i][0] -4.0f) * (float)Mag, 0.0f, (pos.z*(float)HexagonMatrix[i][1] -3.0f) * (float)Mag));
		}
		/*scene->AddGameObject<CHexagon>(1)->SetPosition(D3DXVECTOR3(1.0f, 0.0f, 1.5f));
	scene->AddGameObject<CHexagon>(1)->SetPosition(D3DXVECTOR3(-1.0f, 0.0f, -1.5f));
	scene->AddGameObject<CHexagon>(1)->SetPosition(D3DXVECTOR3(1.0f, 0.0f, -1.5f));*/
}