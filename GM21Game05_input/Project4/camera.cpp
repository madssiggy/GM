#include "main.h"

#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "input.h"
#include "model.h"
#include "player.h"
D3DXVECTOR3 CameraPos;
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
	m_Position = m_Target+CameraPos;
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void CCamera::Uninit() {

}

void CCamera::Update() {
	//if (CInput::GetKeyTrigger('I') &&m_Position.z>0.0f) {
	//	m_Position.z
	//}
	
}

void CCamera::Update(D3DXVECTOR3 playerPos) {
	m_Target=playerPos;
	m_Position =m_Target  + CameraPos;
}



void CCamera::Draw() {
	D3DXMATRIX viewMatrix;
	D3DXMatrixLookAtLH(&viewMatrix, &m_Position, &m_Target,
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	CRenderer::SetViewMatrix(&viewMatrix);


	//�v�������񂭂����}�g���N�X�ݒ�

	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f,//���W�A���ŉ�p��\�����Ă���
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);//nearclip,perclip�B�`�拗���̍ŏ��ƍő�������Ă���B�L���Ƃ肷����Ƃ��`��̃��x����������

	CRenderer::SetProjectionMatrix(&projectionMatrix);

}
void CCamera::Draw(const D3DXVECTOR3& pPos) {
	D3DXMATRIX viewMatrix;
	D3DXMatrixLookAtLH(&viewMatrix, &m_Position, &m_Target,
		&m_Target);

	CRenderer::SetViewMatrix(&viewMatrix);


	//�v�������񂭂����}�g���N�X�ݒ�

	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f,//���W�A���ŉ�p��\�����Ă���
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);//nearclip,perclip�B�`�拗���̍ŏ��ƍő�������Ă���B�L���Ƃ肷����Ƃ��`��̃��x����������

	CRenderer::SetProjectionMatrix(&projectionMatrix);

}

D3DXVECTOR3 CCamera::GetPos() {
	return m_Position;
}
void CCamera::SetPos(D3DXVECTOR3 playerPos) {
	m_Target = playerPos;
}