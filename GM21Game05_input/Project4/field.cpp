#include"main.h"

#include "camera.h"
#include "polygon.h"
#include "renderer.h"
#include "field.h"
#include "input.h"
VERTEX_3D SetVertex(int index, D3DXVECTOR3 Center, float Size, float Height);

void CField::Init() {

	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);//3D��
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f,1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(10.0f, 0.0f, -10.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"asset/texture/field.jpg",
		NULL,
		NULL,
		&m_Texture,
		NULL);
	assert(m_Texture);//�����[�X���ɂ͏o�Ă��Ȃ��A�G���[���ɏo�Ă��Ă���邷�������
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}
void CField::Init(D3DXVECTOR3 Center, float Size,float Height) {

	VERTEX_3D vertex[4];

	for (int i = 0;i < 4;i++) {
		vertex[i] = SetVertex(i, Center, Size, Height);
	}
	//vertex[0].Position = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);//3D��
	//vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	//vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	//vertex[1].Position = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
	//vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	//vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	//vertex[2].Position = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
	//vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	//vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	//vertex[3].Position = D3DXVECTOR3(10.0f, 0.0f, -10.0f);
	//vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	//vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"asset/texture/field.jpg",
		NULL,
		NULL,
		&m_Texture,
		NULL);
	assert(m_Texture);//�����[�X���ɂ͏o�Ă��Ȃ��A�G���[���ɏo�Ă��Ă���邷�������
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}
void CField::Uninit() {
	m_VertexBuffer->Release();
	m_Texture->Release();

}

void CField::Update() {
	//if (Keyboard_IsPress(DIK_UPARROW)) {
	//	m_Position.z += 1.0f;
	//}
	//else if (Keyboard_IsPress(DIK_DOWNARROW)) {
	//	m_Position.z -= 1.0f;
	//}
	//else if (Keyboard_IsPress(DIK_LEFTARROW)) {
	//	m_Position.x -= 1.0f;
	//}
	//else if (Keyboard_IsPress(DIK_RIGHTARROW)) {
	//	m_Position.x += 1.0f;
	//}
}

void CField::Draw() {
	//�}�g���N�X�ݒ�
	
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot*trans;
	CRenderer::SetWorldMatrix(&world);

	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//�}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	CRenderer::SetMaterial(material);
	
	//�e�N�X�`���ݒ�
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//�v���~�e�B�u�g�|���W�ݒ�
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
	);

	//�|���S���`��
	CRenderer::GetDeviceContext()->Draw(4, 0);

}

VERTEX_3D SetVertex(int index,D3DXVECTOR3 Center, float Size,float Height) {
	//�Ԃ��l�p����,tmp
	VERTEX_3D tmp;
	//������
	float SetNum = Size / 2.0f;//Size�͈�ӂ̒����Ƃ��Ă���B
	tmp.Position =D3DXVECTOR3(SetNum, Height, SetNum);//3D��
	tmp.Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	tmp.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	tmp.TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR3 mag(1.0f, 1.0f, 1.0f);
		switch (index) {
		case 0:
			mag = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
			tmp.TexCoord = D3DXVECTOR2(0.0f, 0.0f);
				break;
		case 1:
			mag = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			tmp.TexCoord = D3DXVECTOR2(1.0f, 0.0f);
			break;
		case 2:
			mag = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
			tmp.TexCoord = D3DXVECTOR2(0.0f, 1.0f);
			break;
		case 3:
			mag = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
			tmp.TexCoord = D3DXVECTOR2(1.0f, 1.0f);
			break;

		default:
			break;
		}
		tmp.Position.x*=mag.x;
		tmp.Position.y *= mag.y;
		tmp.Position.z *= mag.z;
		return tmp;

}