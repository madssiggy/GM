#include "main.h"


#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "input.h"

#include "player.h"
#include "vegetable.h"

#include "bullet.h"
#include "scene.h"



void CVegetable::Init() {
	m_scene = CManager::GetScene();
	m_Model = new CModel();
	//	m_Model->Load("asset\\model\\human.obj");
	m_Model->Load("asset\\model\\pumpkin.obj");

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(30.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_playerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	
}
void CVegetable::Uninit() {

	m_Model->Unload();
	delete m_Model;
}
void CVegetable::Update() {
	//成長
	if(m_Size<=m_MaxSize)
	m_GrowTime++;
	if (m_GrowTime >= m_Ticks) {
		m_Ticks += 10;
		m_Size+=0.25f;
		m_Price += 50;
		m_GrowTime = 0;
	}
	//プレイヤーとの当たり判定

}
void CVegetable::Draw() {//マトリクス設定

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x*m_Size, m_Scale.y*m_Size, m_Scale.z*m_Size);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot*trans;
	CRenderer::SetWorldMatrix(&world);



	m_Model->Draw();

}