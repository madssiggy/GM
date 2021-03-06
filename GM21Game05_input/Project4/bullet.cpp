#include "main.h"


#include "manager.h"
#include "renderer.h"
#include "model.h"

#include "gameobject.h"

#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include"scene.h"
#define MAX_BULLET_NUM (10)
#define BULLET_WIDTH (30)
CEnemy enemyList[ENEMY_INDEX];
CModel* CBullet::m_Model;

 void CBullet::Load() {
	m_Model = new CModel();
	m_Model->Load("asset\\model\\torus.obj");
	

}

void CBullet::UnLoad() {
	m_Model->Unload();
	delete m_Model;

}
void CBullet::Init() {
//	m_Model = new CModel();
	//m_Model->Load("asset\\model\\torus.obj");



	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	moveWay = D3DXVECTOR3(0, 0, 0);// MOVEWAY[NEUTRAL];
	canUse = false;
	Movecount = 0;
}

void CBullet::Uninit() {
	//m_Model->Unload();
	//delete m_Model;

}

void CBullet::Update() {

	m_Position += moveWay;
	Movecount++;

	if (Movecount >= MaxDistance) {
		SetDestroy();
	}

	//親がエネミーの場合（＝プレイヤーを対象に取っている場合
	if (m_Parent == 1) {

		CScene* scene = CManager::GetScene();
		std::vector<CPlayer*>playerList = scene->GetGameObjects<CPlayer>(1);
		for (CPlayer* player : playerList) {
			D3DXVECTOR3 enemyPosition = player->GetPosition();
			D3DXVECTOR3 direction = m_Position - enemyPosition;
			float length = D3DXVec3Length(&direction);
			if (length < 2.0f) {
				scene->AddGameObject<CExplosion>(1)->SetPosition(m_Position);
				//	player->AddAlpha(-0.25f);
					//	enemy->Destroy();
					//	enemy->SetCanUse(false);
				SetDestroy();
				return;
			}
		}
	}
	if (m_Parent == 0) {
		CScene* scene = CManager::GetScene();
		std::vector<CEnemy*>enemyList = scene->GetGameObjects<CEnemy>(1);
		for (CEnemy* enemy : enemyList) {
			D3DXVECTOR3 enemyPosition = enemy->GetPosition();
			D3DXVECTOR3 direction = m_Position - enemyPosition;
			float length = D3DXVec3Length(&direction);
			if (length < 2.0f) {
				//SE_explosion.Play();
				scene->AddGameObject<CExplosion>(1)->SetPosition(m_Position);
				enemy->AddHP(-1);
		
				if (enemy->GetHP() <= 0) {
					enemy->SetDestroy();
		
					SetDestroy();
				}
				return;
			}
		}
	}

}
void CBullet::EnemyUpdate() {

	m_Position += moveWay;
	Movecount++;
	if (Movecount >= MaxDistance) {
		SetDestroy();
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

void CBullet::Create(D3DXVECTOR3 playerPos,D3DXVECTOR3 Way,int parent) {
	m_Position = playerPos;
	moveWay = Way;
	canUse = true;
	Movecount = 0;
	m_Parent = parent;
}

bool CBullet::GetCanUse() {
	return canUse;
}

