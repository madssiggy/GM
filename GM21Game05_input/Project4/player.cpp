#include "main.h"


#include "manager.h"
#include "renderer.h"
#include "model.h"

#include "player.h"
#include "input.h"
#include "bullet.h"
#include "scene.h"
//#include "enemy.h"

//#define ENEMY_INDEX (3)
float speedMag;
const float addSpeedMag = 0.01f;
const float maxSpeedMag = 1.0f;
const float minSpeedMag = 0.0f;

//CEnemy g_Enemy[ENEMY_INDEX];
#define PLAYER_WIDTH (100)

void CPlayer::Init() {

	m_Model = new CModel();
	m_Model->Load("asset\\model\\human.obj");
	

	m_Position = D3DXVECTOR3(0.0f, 15.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	speedMag = 0.5f;
	m_MoveWay = MOVEWAY[NEUTRAL];


	m_Col.Center = m_Position;
	m_Col.r = (float)PLAYER_WIDTH * 0.8f;
}

void CPlayer::Uninit() {
	//for (int i = 0;i < ENEMY_INDEX;i++) {
	//	g_Enemy[i].Uninit();
	//}

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
		if (CInput::GetKeyPress('D')) 
			m_MoveWay += MOVEWAY[right];
		
		D3DXVec3Normalize(&m_MoveWay, &m_MoveWay);
		m_Position += m_MoveWay * speedMag;
	}
	else if (CInput::GetKeyPress('S')) {
		m_MoveWay = MOVEWAY[front];

		if (CInput::GetKeyPress('A'))
			m_MoveWay += MOVEWAY[left];
		if (CInput::GetKeyPress('D'))
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
		CScene* scene = CManager::GetScene();
		scene->AddGameObject<CBullet>(1)->Create(m_Position,m_MoveWay);
		/*for (int i = 0;i < MAX_BULLET_NUM;i++) {
			if (tmpBullet[i]->GetCanUse() == false) {
				tmpBullet[i]->Create(tmpP->GetPosition(), tmpP->GetMoveWay());

			}
		}*/
	}

	m_Col.Center = m_Position;
}

void CPlayer::Draw() {
	//マトリクス設定

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.z, m_Rotation.x);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot*trans;
	CRenderer::SetWorldMatrix(&world);



	m_Model->Draw();

}



D3DXVECTOR3 CPlayer::GetMoveWay() { return m_MoveWay; }

//bool CollisionVsEnemAndBul() {
//	for (int i = 0;i < MAX_BULLET_NUM;i++) {
//		if (myBullet[i].GetCanUse()) {
//			continue;
//		}
//		for (int EnemyCount = 0;EnemyCount < ENEMY_INDEX;EnemyCount++) {
//			if (OnCollisionEnter(g_Enemy[i].GetCollision(), myBullet[i].GetCollision())) 
//				return true;
//		}
//	}
//	return false;
//}