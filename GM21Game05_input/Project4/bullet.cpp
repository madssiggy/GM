#include "main.h"


#include "manager.h"
#include "renderer.h"
#include "model.h"

#include "bullet.h"
#include "input.h"


void CBullet::Init() {

	m_Model = new CModel();
	m_Model->Load("asset\\model\\torus.obj");


	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);


	moveWay = MOVEWAY[NEUTRAL];
	canUse = false;
	Movecount = 0;
}

void CBullet::Uninit() {
	
	m_Model->Unload();
	delete m_Model;

}

void CBullet::Update() {
	if (canUse == true) {
		m_Position += moveWay;
		Movecount++;
	}
	if (Movecount >= MaxDistance) {
		Destroy();
	}
}

void CBullet::Draw() {
	//マトリクス設定

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot*trans;
	CRenderer::SetWorldMatrix(&world);



	m_Model->Draw();

}

void CBullet::Create(D3DXVECTOR3 playerPos,D3DXVECTOR3 Way) {
	m_Position = playerPos;
	moveWay = Way;
	canUse = true;
	Movecount = 0;
}
void CBullet::Destroy() {
	//エフェクト発生させたら素敵だね
	canUse = false;
}
bool CBullet::GetCanUse() {
	return canUse;
}