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
/*	//ˆê’è‚ÌŠp“x‚Ü‚Å‰ñ“]‚³‚¹‚é
	//rot‚Ì”ÍˆÍ‚Í0~4(0~360“x)
	//”ÍˆÍ‚Í‚O`‚S‚Ìƒvƒ‰ƒX‚ÅˆêŽüA‚O`|‚S‚Ìƒ}ƒCƒiƒXˆêŽü‚ð‚Ý‚éŠ´‚¶‚©‚Ë
			//³‚Ì³–Ê•‰‚Ì³–Êi‚v‚È‚ç‚O‚Æ‚SA‚r‚È‚ç‚Q‚Æ[‚QA‚`‚È‚ç‚P‚Æ
	//‚ß‚ñ‚Ç‚­‚Á‚¹IŠp“xŽ–‚É‚µ‚Ä‚¢‚·‚é•ûŒü‚Ì‰ñ“]Ý’è‚µ‚Ä‚¨‚±‚¤
	//‚»‚à‚È‚ñ‚Å‚±‚ê•K—v‚È‚ñ‚¾‚Á‚¯H‚ A‰ñ“]‚Ì•ûŒü‚©
	//%4‚·‚ê‚Î‚æ‚¢‚Ì‚Å‚ÍH
	float nowRot=fmodf(m_Rotation.y,4);
	if (CInput::GetKeyPress('W')) {


		if (nowRot == 0.0) {
			m_Rotation.y;
		}
		else if (nowRot!=0.0f) {
		//Œü‚¢‚Ä‚¢‚È‚¢ê‡‚ÍŠp“xŽ–‚ÉˆÙ‚È‚é‰ñ“]•ûŒü‚ðŽw’è‚µ‚ÄŒü‚©‚¹‚é
			//ƒ}ƒCƒiƒX‚ÌŽž‚Í‚SD‚O‚†‘«‚µ‚Ä³‚Ì’l‚Æ‚µ‚Ä‚Ý‚éB
			if ((m_Rotation.y > 0.0f) && (m_Rotation.y < 2.0f)) {
				m_Rotation.y -= 0.05f;
			}
			else if ((m_Rotation.y >= 2.0f) && (m_Rotation.y < 4.0f)) {
				m_Rotation.y += 0.05f;
			}
		}

	//front ‚Ì•ûŒü‚ÉˆÚ“®‚·‚é==‰ñ“]Šp“x‚©‚çfront‚ðŽæ“¾‚µ‚Äm_pos‚É‰ÁŽZ‚µ‚Ä‚¢‚­
		Forward = GetForward();
		m_MoveWay = Forward;
		D3DXVec3Normalize(&m_MoveWay, &m_MoveWay);
		m_Position += m_MoveWay * speedMag;
	}
	if (CInput::GetKeyPress('A')) {
		//ˆê’è‚ÌŠp“x‚Ü‚Å‰ñ“]‚³‚¹‚é
		//WˆÈŠO‚Í
	//rot.y‚ª•ûŒü‚ÌˆÊ’ui{‚SD‚O‚†j‚ðŒü‚¢‚Ä‚¢‚éê‡
		if (m_Rotation.y == 2.0f || m_Rotation.y == 6.0f) {
			m_Rotation.y = 2.0f;
		}
		else if (m_Rotation.y != 0.0f || m_Rotation.y != 4.0f) {
			//Œü‚¢‚Ä‚¢‚È‚¢ê‡‚ÍŠp“xŽ–‚ÉˆÙ‚È‚é‰ñ“]•ûŒü‚ðŽw’è‚µ‚ÄŒü‚©‚¹‚é
				//180“xi{‚QD‚O‚†j–¢–ž‚Æ‚P‚W‚OˆÈã‚Ìê‡‚Åƒpƒ^[ƒ“‚ð—pˆÓ‚·‚é
			if ((m_Rotation.y > 0.0f) && (m_Rotation.y < 2.0f)) {
				m_Rotation.y -= 0.05f;
			}
			else if ((m_Rotation.y >= 2.0f) && (m_Rotation.y < 4.0f)) {
				m_Rotation.y += 0.05f;
			}
		}

		//front ‚Ì•ûŒü‚ÉˆÚ“®‚·‚é==‰ñ“]Šp“x‚©‚çfront‚ðŽæ“¾‚µ‚Äm_pos‚É‰ÁŽZ‚µ‚Ä‚¢‚­
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

	//F•ÏXƒfƒoƒO
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
	//ƒ}ƒgƒŠƒNƒXÝ’è

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
		//•‚‚¢‚Ä‚é‚Æ‚«
		if (length > 0.2f) {
			m_Position.y -= 0.2f;


		
			return;
		}
	
	}
}