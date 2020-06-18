#include "main.h"

#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "input.h"
#include "model.h"
#include "player.h"
D3DXVECTOR3 CameraPos;
void CCamera::Init() {
	CameraPos= D3DXVECTOR3(0.0f, 2.0f, -10.0f);
	m_Position = CameraPos;
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void CCamera::Uninit() {

}

void CCamera::Update() {
	//if (CInput::GetKeyTrigger('I') &&m_Position.z>0.0f) {
	//	m_Position.z
	//}
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

D3DXVECTOR3 CCamera::GetPos() {
	return m_Position;
}
