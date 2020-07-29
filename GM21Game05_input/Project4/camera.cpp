#include "main.h"

#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "input.h"
#include "model.h"
#include "player.h"
#include "input.h"
#include "scene.h"

D3DXVECTOR3 CameraPos;
static D3DXVECTOR3 oldCameraPos;
bool isOnePerson;
D3DXVECTOR3 p_cameraPos(0.0f, 25.0f, 00.0f);
void CCamera::Init() {
	CameraPos = p_cameraPos;
	m_Position = CameraPos;
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//D3DXMatrixLookAtLH(&m_Matrix, &m_Position, &m_Target,
	//	&m_Target);
}
void CCamera::Init(	D3DXVECTOR3 pPos ,
								D3DXVECTOR3 mPos,
								D3DXVECTOR3 mRot ) {
	m_Target = pPos;
	m_Position = mPos;
	m_Rotation = mRot;
	CameraPos = p_cameraPos;
	oldCameraPos=CameraPos;
	m_Position = m_Target+CameraPos;
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	isOnePerson = false;
}

void CCamera::Uninit() {

}

void CCamera::Update() {
//	CScene* scene = CManager::GetScene();
	CPlayer* player = CManager::GetScene()->GetGameObject<CPlayer>(1);
	
	m_Target = player->GetPosition();//プレイヤーを定点で観測する
	D3DXVECTOR3 Forward = player->GetForward();
	m_Position = m_Target - (Forward * 5.0f) + CameraPos;
}

void CCamera::Update(D3DXVECTOR3 playerPos) {
	//if (CInput::GetKeyPress(VK_LEFT)) {
	//	CPlayer* player = CManager::GetScene()->GetGameObject<CPlayer>(1);
	//	player->SetRotation(player->GetRotation() - D3DXVECTOR3(0.0f,0.01f,0.0f));

	//}
	//if (CInput::GetKeyPress(VK_RIGHT) && CameraPos.y>0.0f) {
	//	CPlayer* player = CManager::GetScene()->GetGameObject<CPlayer>(1);

	//	player->SetRotation(player->GetRotation() + D3DXVECTOR3(0.0f, 0.01f, 0.0f));
	//}

	m_Target=playerPos;
	m_Position =m_Target  + CameraPos;
	CPlayer* player = CManager::GetScene()->GetGameObject<CPlayer>(1);

	m_Target = player->GetPosition();//プレイヤーを定点で観測する
	D3DXVECTOR3 Forward = player->GetForward();
	m_Position = m_Target - Forward * 5.0f + CameraPos;
}

void CCamera::Draw() {
	D3DXMATRIX viewMatrix;
	D3DXMatrixLookAtLH(&viewMatrix, &m_Position, &m_Target,
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	CRenderer::SetViewMatrix(&viewMatrix);
	m_viewMatrix = viewMatrix;

	//プロじぇんくしょんマトリクス設定

	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f,//ラジアンで画角を表示じている
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);//nearclip,perclip。描画距離の最小と最大を示している。広くとりすぎるとｚ描画のレベルが下がる

	CRenderer::SetProjectionMatrix(&projectionMatrix);

}
void CCamera::Draw(const D3DXVECTOR3& pPos) {
	D3DXMatrixLookAtLH(&m_viewMatrix, &m_Position, &m_Target,
		&m_Target);
	CRenderer::SetViewMatrix(&m_viewMatrix);

	//プロじぇんくしょんマトリクス設定

	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f,//ラジアンで画角を表示じている
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);//nearclip,perclip。描画距離の最小と最大を示している。広くとりすぎるとｚ描画のレベルが下がる

	CRenderer::SetProjectionMatrix(&projectionMatrix);
	//m_viewMatrix = viewMatrix;
}
//void CCamera::fixedDraw() {
//	D3DXMATRIX CamMat;
//	D3DXMatrixIdentity(&CamMat);
//	memcpy(CamMat.m[0], &D3DXVECTOR3(1, 0, 0), sizeof(D3DXVECTOR3));
//	memcpy(CamMat.m[1], &D3DXVECTOR3(0, 1, 0), sizeof(D3DXVECTOR3));
//	memcpy(CamMat.m[2], &D3DXVECTOR3(0, 0, 1), sizeof(D3DXVECTOR3));
//	
//	D3DXQUATERNION ZAxisQ;
//	D3DXQuaternionRotationAxis(&ZAxisQ, &m_Target, angle);
//	D3DXMATRIX ZAxisRotMat;
//	D3DXMatrixRotationQuaternion(&ZAxisRotMat, &ZAxisQ);
//
//	CamMat *= ZAxisRotMat;
//}
D3DXVECTOR3 CCamera::GetPos() {
	return m_Position;
}
void CCamera::SetPos(D3DXVECTOR3 playerPos) {
	m_Target = playerPos;
}

D3DXMATRIX CCamera::GetViewMatrix() {
	return m_viewMatrix;
}