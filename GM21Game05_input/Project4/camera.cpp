#include "main.h"

#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "input.h"
#include "model.h"
#include "player.h"
#include "input.h"


D3DXVECTOR3 CameraPos;
static D3DXVECTOR3 oldCameraPos;
bool isOnePerson;
void CCamera::Init() {
	CameraPos= D3DXVECTOR3(0.0f, 4.0f, -30.0f);
	m_Position = CameraPos;
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
void CCamera::Init(	D3DXVECTOR3 pPos ,
								D3DXVECTOR3 mPos,
								D3DXVECTOR3 mRot ) {
	m_Target = pPos;
	m_Position = mPos;
	m_Rotation = mRot;
	CameraPos =D3DXVECTOR3(0.0f, 30.0f, -30.0f);
	oldCameraPos=CameraPos;
	m_Position = m_Target+CameraPos;
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	isOnePerson = false;
}

void CCamera::Uninit() {

}

void CCamera::Update() {
	//if (CInput::GetKeyTrigger('I') &&m_Position.z>0.0f) {
	//	m_Position.z
	//}
	
}

void CCamera::Update(D3DXVECTOR3 playerPos) {
	if (CInput::GetKeyPress(VK_UP) && CameraPos.y < 40.0f) {
		CameraPos.y += 1;
	}
	if (CInput::GetKeyPress(VK_DOWN) && CameraPos.y>0.0f) {
		CameraPos.y -= 1;
	}
	if (CInput::GetKeyPress(VK_LSHIFT)&&isOnePerson==false) {
		oldCameraPos.y = CameraPos.y;
		oldCameraPos.z = CameraPos.z;
		CameraPos.y = 20;
		CameraPos.z = -30;
		isOnePerson = true;
	}
	if (CInput::GetKeyPress(VK_RSHIFT) && isOnePerson == true) {
		 CameraPos.y = oldCameraPos.y;
			 CameraPos.z = oldCameraPos.z;
			 isOnePerson = false;
	}
	m_Target=playerPos;
	m_Position =m_Target  + CameraPos;
}



void CCamera::Draw() {
	D3DXMATRIX viewMatrix;
	D3DXMatrixLookAtLH(&viewMatrix, &m_Position, &m_Target,
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	CRenderer::SetViewMatrix(&viewMatrix);


	//プロじぇんくしょんマトリクス設定

	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f,//ラジアンで画角を表示じている
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);//nearclip,perclip。描画距離の最小と最大を示している。広くとりすぎるとｚ描画のレベルが下がる

	CRenderer::SetProjectionMatrix(&projectionMatrix);

}
void CCamera::Draw(const D3DXVECTOR3& pPos) {
	D3DXMATRIX viewMatrix;
	D3DXMatrixLookAtLH(&viewMatrix, &m_Position, &m_Target,
		&m_Target);

	CRenderer::SetViewMatrix(&viewMatrix);


	//プロじぇんくしょんマトリクス設定

	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f,//ラジアンで画角を表示じている
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);//nearclip,perclip。描画距離の最小と最大を示している。広くとりすぎるとｚ描画のレベルが下がる

	CRenderer::SetProjectionMatrix(&projectionMatrix);

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