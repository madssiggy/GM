#include "main.h"


#include "manager.h"
#include "renderer.h"
#include "model.h"


#include "enemy.h"
D3DXVECTOR3 mag(0.1f, 0.1f, 0.1f);
#define ENEMY_WIDTH (32)
void CEnemy::Init(D3DXVECTOR3 pos) {
	m_Model = new CModel();
	m_Model->Load("asset\\model\\torus.obj");


	m_Position = pos;

	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_playerPos= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Col.Center = m_Position;
	m_Col.r = (float)ENEMY_WIDTH*0.8f;
}

void CEnemy::Init() {
	m_Model = new CModel();
	m_Model->Load("asset\\model\\torus.obj");


	m_Position = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_playerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Col.Center = m_Position;
	m_Col.r = (float)ENEMY_WIDTH*0.8f;
}
void CEnemy::Uninit() {

	m_Model->Unload();
	delete m_Model;
}
void CEnemy::Update() {
	D3DXVECTOR3 moveWay = m_playerPos - m_Position;
	D3DXVec3Normalize(&moveWay, &moveWay);
	moveWay.x *= mag.x;
	moveWay.y *= mag.y;
	moveWay.z *= mag.z;
	m_Position += moveWay;
	m_Col.Center = m_Position;
}
void CEnemy::Draw() {//マトリクス設定

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot*trans;
	CRenderer::SetWorldMatrix(&world);



	m_Model->Draw();
}

void CEnemy::GetPlayerPos(D3DXVECTOR3 Ppos) {
	m_playerPos = Ppos;
}