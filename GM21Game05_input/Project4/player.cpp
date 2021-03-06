#include <math.h>
#include "main.h"


#include "manager.h"
#include "renderer.h"
#include "model.h"

#include "camera.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "scene.h"
#include "field.h"


//#include "enemy.h"

//#define ENEMY_INDEX (3)

const float addSpeedMag = 0.01f;
const float maxSpeedMag = 1.0f;
const float minSpeedMag = 0.0f;
const float moveSpeed=1.0f;
//CEnemy g_Enemy[ENEMY_INDEX];
#define PLAYER_WIDTH (100)
CScene* scene;

void CPlayer::Init() {
	scene = CManager::GetScene();
	m_Model = new CModel();
	m_Model->Load("asset\\model\\player.obj");
	//m_PlayerMaterial = m_Model->GetMaterial();

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_SpeedMag = 0.5f;
	m_MoveWay = D3DXVECTOR3(0, 0, 0);// MOVEWAY[NEUTRAL];
	D3DXQuaternionIdentity(&m_Quaternion);

}

void CPlayer::Uninit() {


	m_Model->Unload();
	delete m_Model;

}

void CPlayer::Update() {
	D3DXVECTOR3 Forward = GetForward();
	scene = CManager::GetScene();
	m_TriggerMoveKey = false;
/*	//一定の角度まで回転させる
	//rotの範囲は0~4(0~360度)
	//範囲は０〜４のプラスで一周、０〜−４のマイナス一周をみる感じかね
			//正の正面負の正面（Ｗなら０と４、Ｓなら２とー２、Ａなら１と
	//めんどくっせ！角度事にしていする方向の回転設定しておこう
	//そもなんでこれ必要なんだっけ？あ、回転の方向か
	//%4すればよいのでは？
	float nowRot=fmodf(m_Rotation.y,4);
	if (CInput::GetKeyPress('W')) {


		if (nowRot == 0.0) {
			m_Rotation.y;
		}
		else if (nowRot!=0.0f) {
		//向いていない場合は角度事に異なる回転方向を指定して向かせる
			//マイナスの時は４．０ｆ足して正の値としてみる。
			if ((m_Rotation.y > 0.0f) && (m_Rotation.y < 2.0f)) {
				m_Rotation.y -= 0.05f;
			}
			else if ((m_Rotation.y >= 2.0f) && (m_Rotation.y < 4.0f)) {
				m_Rotation.y += 0.05f;
			}
		}

	//front の方向に移動する==回転角度からfrontを取得してm_posに加算していく
		Forward = GetForward();
		m_MoveWay = Forward;
		D3DXVec3Normalize(&m_MoveWay, &m_MoveWay);
		m_Position += m_MoveWay * speedMag;
	}
	if (CInput::GetKeyPress('A')) {
		//一定の角度まで回転させる
		//W以外は
	//rot.yが方向の位置（＋４．０ｆ）を向いている場合
		if (m_Rotation.y == 2.0f || m_Rotation.y == 6.0f) {
			m_Rotation.y = 2.0f;
		}
		else if (m_Rotation.y != 0.0f || m_Rotation.y != 4.0f) {
			//向いていない場合は角度事に異なる回転方向を指定して向かせる
				//180度（＋２．０ｆ）未満と１８０以上の場合でパターンを用意する
			if ((m_Rotation.y > 0.0f) && (m_Rotation.y < 2.0f)) {
				m_Rotation.y -= 0.05f;
			}
			else if ((m_Rotation.y >= 2.0f) && (m_Rotation.y < 4.0f)) {
				m_Rotation.y += 0.05f;
			}
		}

		//front の方向に移動する==回転角度からfrontを取得してm_posに加算していく
		Forward = GetForward();
		m_MoveWay = Forward;
		D3DXVec3Normalize(&m_MoveWay, &m_MoveWay);
		m_Position += m_MoveWay * speedMag;
	}
	if (CInput::GetKeyPress('S')) {
	
	}
	if (CInput::GetKeyPress('D')) {
	}*/

	//if (CInput::GetKeyPress('W')) {
	//	m_MoveWay = MOVEWAY[back];
	//	m_Position += Forward * 0.1f;
	//	if (CInput::GetKeyPress('A')) 
	//		m_MoveWay += MOVEWAY[left];
	//	if (CInput::GetKeyPress('D')) 
	//		m_MoveWay += MOVEWAY[right];
	//	
	//	D3DXVec3Normalize(&m_MoveWay, &m_MoveWay);
	//	m_Position += m_MoveWay * speedMag;
	//}
	//else if (CInput::GetKeyPress('S')) {
	//	m_MoveWay = MOVEWAY[front];
	//	m_Position -= Forward * 0.1f;
	//	if (CInput::GetKeyPress('A'))
	//		m_MoveWay += MOVEWAY[left];
	//	if (CInput::GetKeyPress('D'))
	//		m_MoveWay += MOVEWAY[right];
	//	D3DXVec3Normalize(&m_MoveWay, &m_MoveWay);
	//	m_Position += m_MoveWay * speedMag;
	//}
	//else if (CInput::GetKeyPress('A')) {
	//	m_Position += MOVEWAY[left] *speedMag;
	//	m_MoveWay = MOVEWAY[left];
	//}
	//else if (CInput::GetKeyPress('D')) {
	//	m_Position += MOVEWAY[right] *speedMag;
	//	m_MoveWay = MOVEWAY[right];
	//}


	if (CInput::GetKeyPress(VK_UP)) {
		//if (CInput::GetKeyPress('A'))
		//	m_Rotation.y -= 0.05f;
		//if (CInput::GetKeyPress('D'))
		//	m_Rotation.y += 0.05f;
		Forward = GetForward();
		m_MoveWay = Forward;
	D3DXVec3Normalize(&m_MoveWay, &m_MoveWay);
	m_Position += m_MoveWay * m_SpeedMag;
	m_TriggerMoveKey=true;

	}
	if (CInput::GetKeyPress(VK_DOWN)) {
		//if (CInput::GetKeyPress('A'))
		//	m_Rotation.y -= 0.05f;
		//if (CInput::GetKeyPress('D'))
		//	m_Rotation.y += 0.05f;
		Forward = GetForward();
		m_MoveWay = Forward;
		D3DXVec3Normalize(&m_MoveWay, &m_MoveWay);
		m_Position -= m_MoveWay * m_SpeedMag;
		m_TriggerMoveKey = true;
	}

	if (CInput::GetKeyPress(VK_RIGHT)) {
		m_Rotation.y += 0.05f;
		//m_TriggerMoveKey = true;
	}
	if (CInput::GetKeyPress(VK_LEFT)) {
		m_Rotation.y -= 0.05f;
		//m_TriggerMoveKey = true;
	}

	if (CInput::GetKeyTrigger(VK_LSHIFT)) {
		m_SpeedMagMax = 5.0f;
	}
	if (CInput::GetKeyTrigger(VK_RSHIFT)) {
		m_SpeedMagMax = 1.0f;
	}

	if (m_TriggerMoveKey&&m_SpeedMag<=m_SpeedMagMax) {

		m_SpeedMag += 0.1f;
	}
	else if (!m_TriggerMoveKey&&m_SpeedMag > 0.0f) {
		m_SpeedMag = 0;
	}

	//if (CInput::GetKeyPress('A')) {
	//	m_Position.x -= 0.1f;
	//	D3DXQUATERNION quat;
	//	D3DXQuaternionRotationAxis(&quat,
	//		&D3DXVECTOR3(0.0f, 0.0f, 1.0f), 0.1f);
	//	m_Quaternion *= quat;
	//}

	//if (CInput::GetKeyPress('W')) {
	//	m_Position.z += 0.1f;
	//	D3DXQUATERNION quat;
	//	D3DXQuaternionRotationAxis( &quat,
	//	&D3DXVECTOR3(1.0f,0.0f,0.0f),-0.1f );
	//	m_Quaternion *= quat;
	//}

	//if (CInput::GetKeyPress('S')) {
	//	m_Position.z -= 0.1f;
	//	D3DXQUATERNION quat;
	//	D3DXQuaternionRotationAxis(&quat,
	//		&D3DXVECTOR3(1.0f, 0.0f, 0.0f), 0.1f);
	//	m_Quaternion *= quat;
	//}

	//if (CInput::GetKeyPress('D')) {
	//	m_Position.x += 0.1f;
	//	D3DXQUATERNION quat;
	//	D3DXQuaternionRotationAxis(&quat,
	//		&D3DXVECTOR3(0.0f, 0.0f, 1.0f), -0.1f);
	//	m_Quaternion *= quat;
	//}

	if (!m_CanShot) {
		
		m_CoolTime++;
		if (m_CoolTime >= m_cCoolTime) {
			m_CoolTime = 0;
			m_CanShot = true;
		}
	}
	if (CInput::GetKeyPress('W')) {
		D3DXVECTOR3 tmpFWD = GetForward();
		tmpFWD.x *= 1.3f;
		tmpFWD.z *= 1.3f;
		tmpFWD.z *= 1.3f;
		if (m_CanShot) {

			scene->AddGameObject<CBullet>(1)->Create(m_Position, tmpFWD);
			m_CanShot = false;
		}
	}
	//if (CInput::GetKeyPress(VK_LSHIFT)) {
	//	m_Rotation.y -= 0.01f;
	//}
	//if (CInput::GetKeyPress(VK_RSHIFT)) {
	//	m_Rotation.y += 0.01f;
	//}
	if (CInput::GetKeyTrigger(VK_SPACE)) {
		m_JumpCountMax++;
	}
	if (m_JumpCountMax != 0) {

	}

	//色変更デバグ
	/*if (CInput::GetKeyPress('R')) {
		m_PlayerMaterial.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		m_Model->SetMaterial(m_PlayerMaterial);
	}
	if (CInput::GetKeyPress('G')) {
		m_PlayerMaterial.Diffuse= D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		m_Model->SetMaterial(m_PlayerMaterial);
	}
	if (CInput::GetKeyPress('B')) {
		m_PlayerMaterial.Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		m_Model->SetMaterial(m_PlayerMaterial);
	}
	if (CInput::GetKeyPress('Z')) {
		m_PlayerMaterial.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f);
		m_Model->SetMaterial(m_PlayerMaterial);
	}*/
	scene->GetGameObject<CCamera>(0)->Update(m_Position);
	if (m_JumpCount != 0) {
	
	}
}

void CPlayer::Draw() {
	//マトリクス設定

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.z, m_Rotation.x);
	
//	D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot*trans;
	CRenderer::SetWorldMatrix(&world);



	m_Model->Draw();

}
//float CPlayer::GetAlpha() { return m_PlayerMaterial.Diffuse.a; }
//void CPlayer::SetAlpha(float alpha) { m_PlayerMaterial.Ambient = alpha; }
//void CPlayer::AddAlpha(float alpha) { m_PlayerMaterial.Diffuse.a += alpha; }

D3DXVECTOR3 CPlayer::GetMoveWay() { return m_MoveWay; }

void CPlayer::CollisionField() {
	std::vector<CField*>enemyList = scene->GetGameObjects<CField>(1);
	for (CField* enemy : enemyList) {
		D3DXVECTOR3 enemyPosition = enemy->GetPosition();
		D3DXVECTOR3 direction = m_Position - enemyPosition;
		float length = D3DXVec3Length(&direction);
		//浮いてるとき
		if (length > 0.2f) {
			m_Position.y -= 0.2f;


		
			return;
		}
	
	}
}