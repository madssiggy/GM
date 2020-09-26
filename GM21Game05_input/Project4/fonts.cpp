#include "main.h"

#include "renderer.h"
#include "fonts.h"
float TexCoords[10][4][2]{
	{ {0.9f,0.0f},{1.0f,0.0f},{0.9f,0.25f},{1.0f,0.25f}},//0
	{{0.0f,0.0f},{0.1f,0.0f},{0.0f,0.25f},{0.1f,0.25f}},//1
	{{0.1f,0.0f},{0.2f,0.0f},{0.1f,0.25f},{0.2f,0.25f}},//2
	{{0.2f,0.0f},{0.3f,0.0f},{0.2f,0.25f},{0.3f,0.25f}},//3
	{{0.3f,0.0f},{0.4f,0.0f},{0.3f,0.25f},{0.4f,0.25f}},//4
	{{0.4f,0.0f},{0.5f,0.0f},{0.4f,0.25f},{0.5f,0.25f}},//5
	{{0.5f,0.0f},{0.6f,0.0f},{0.5f,0.25f},{0.6f,0.25f}},//6
	{{0.6f,0.0f},{0.7f,0.0f},{0.6f,0.25f},{0.7f,0.25f}},//7
	{{0.7f,0.0f},{0.8f,0.0f},{0.7f,0.25f},{0.8f,0.25f}},//8
	{{0.8f,0.0f},{0.9f,0.0f},{0.8f,0.25f},{0.9f,0.25f}}//9

};

void CFonts::Init() {

	VERTEX_3D vertex[4];


	vertex[0].Position = D3DXVECTOR3(-100.0f+(float)SCREEN_WIDTH/2, -100.0f+(float)SCREEN_HEIGHT/2, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(100.0f + (float)SCREEN_WIDTH/2, -100.0f + (float)SCREEN_HEIGHT/2, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-100.0f + (float)SCREEN_WIDTH/2, 100.0f + (float)SCREEN_HEIGHT/2, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(100.0f + (float)SCREEN_WIDTH/2, 100.0f + (float)SCREEN_HEIGHT/2, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
		"asset/texture/fonts.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);
}

void CFonts::Uninit() {
	m_VertexBuffer->Release();
	m_Texture->Release();

}

void CFonts::Update() {
	if (m_oldScore != m_Score) {
		D3DXVECTOR2 tmpPos = pos;
		for (int i = 0, keta = 10, Score = tmpScore;i < 5;i++, keta *= 10) {


			Score %= 10;

			fonts[i]->SetVertex(Score, tmpPos);
			Score = tmpScore / keta;
			tmpPos.x -= 20.0f;

		}
	}
	m_oldScore = m_Score;
}

void CFonts::Draw() {
	LIGHT light;
	light.Enable = false;
	CRenderer::SetLight(light);
	//�}�g���N�X�ݒ�
	CRenderer::SetWorldViewProjection2D();

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

void CFonts::SetVertex(int value,D3DXVECTOR2 pos, D3DXVECTOR2 size) {
	float x = size.x/2;
	float y = size.y/2;

	VERTEX_3D vertex[4];


	vertex[0].Position = D3DXVECTOR3(-x+pos.x, -y + pos.y, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(TexCoords[value][0][0], TexCoords[value][0][1]);

	vertex[1].Position = D3DXVECTOR3(x+pos.x, -y + pos.y, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(TexCoords[value][1][0], TexCoords[value][1][1]);

	vertex[2].Position = D3DXVECTOR3(-x + pos.x, y + pos.y, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(TexCoords[value][2][0], TexCoords[value][2][1]);

	vertex[3].Position = D3DXVECTOR3(x +  pos.x, y  + pos.y, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(TexCoords[value][3][0], TexCoords[value][3][1]);
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
}