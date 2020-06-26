#include "main.h"


#include "manager.h"
#include "renderer.h"
#include "model.h"

#include "player.h"
#include "input.h"
#include "bullet.h"
#include "enemy.h"
#define MAX_BULLET_NUM (10)
#define ENEMY_INDEX (3)
float speedMag;
const float addSpeedMag = 0.01f;
const float maxSpeedMag = 1.0f;
const float minSpeedMag = 0.0f;
CBullet myBullet[MAX_BULLET_NUM];
CEnemy g_Enemy[ENEMY_INDEX];
void CPlayer::Init() {

	m_Model = new CModel();
	m_Model->Load("asset\\model\\torus.obj");
	

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	speedMag = 0.5f;
	m_MoveWay = MOVEWAY[NEUTRAL];
	for (int i = 0;i < MAX_BULLET_NUM ;i++) {
		myBullet[i].Init();
	}
	float posX = -20.0f;

	for (int i = 0;i < ENEMY_INDEX;i++) {
		D3DXVECTOR3 pos(posX, 0, 30.0f);
		g_Enemy[i].Init(pos);
		posX += 20.0f;
	}
}

void CPlayer::Uninit() {
	for (int i = 0;i < ENEMY_INDEX;i++) {
		g_Enemy[i].Uninit();
	}
	for (int i = 0;i < MAX_BULLET_NUM;i++) {
		myBullet[i].Uninit();
	}
	m_Model->Unload();
	delete m_Model;

}

void CPlayer::Update() {
	if (CInput::GetKeyTrigger('H')&&speedMag+addSpeedMag<maxSpeedMag) {
		speedMag += addSpeedMag;
	}
	if (CInput::GetKeyTrigger('L')&&speedMag-addSpeedMag>minSpeedMag) {
		
		speedMag -= addSpeedMag;
	}

	if (CInput::GetKeyPress('W')) {
		m_MoveWay = MOVEWAY[back];

		if (CInput::GetKeyPress('A')) 
			m_MoveWay += MOVEWAY[left];
		else if (CInput::GetKeyPress('D')) 
			m_MoveWay += MOVEWAY[right];
		
		D3DXVec3Normalize(&m_MoveWay, &m_MoveWay);
		m_Position += m_MoveWay * speedMag;
	}
	else if (CInput::GetKeyPress('S')) {
		m_MoveWay = MOVEWAY[front];

		if (CInput::GetKeyPress('A'))
			m_MoveWay += MOVEWAY[left];
		else if (CInput::GetKeyPress('D'))
			m_MoveWay += MOVEWAY[right];

		D3DXVec3Normalize(&m_MoveWay, &m_MoveWay);
		m_Position += m_MoveWay * speedMag;
	}
	else if (CInput::GetKeyPress('A')) {
		m_Position += MOVEWAY[left] *speedMag;
		m_MoveWay = MOVEWAY[left];
	}
	else if (CInput::GetKeyPress('D')) {
		m_Position += MOVEWAY[right] *speedMag;
		m_MoveWay = MOVEWAY[right];
	}

	if (CInput::GetKeyTrigger(VK_SPACE)) {
		for (int i = 0;i < MAX_BULLET_NUM;i++) {
			if (myBullet[i].GetCanUse() == false) {
				myBullet[i].Create(m_Position, m_MoveWay);
			}
		}
	}
	for (int i = 0;i < MAX_BULLET_NUM;i++) {
		if (myBullet[i].GetCanUse() == true) {
			myBullet[i].Update();
		}
	}
	for (int i = 0;i < ENEMY_INDEX;i++) {
		g_Enemy[i].GetPlayerPos(m_Position);
		g_Enemy[i].Update();
}
}

void CPlayer::Draw() {
	//マトリクス設定

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot*trans;
	CRenderer::SetWorldMatrix(&world);



	m_Model->Draw();
	for (int i = 0;i < MAX_BULLET_NUM;i++) {
		if (myBullet[i].GetCanUse() ==true) {
			myBullet[i].Draw();
		}
	}
	for (int i = 0;i < ENEMY_INDEX;i++) {
		g_Enemy[i].Draw();
	}
}

D3DXVECTOR3 CPlayer::GetPos() {
	return m_Position;
}

