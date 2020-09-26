#include"main.h"

#include "scene.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "camera.h"
#include "polygon.h"

#include "field.h"

#include "camera.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "scene.h"
#include <math.h>

VERTEX_3D SetVertex(int index, D3DXVECTOR3 Center, float Size, float Height);
VERTEX_3D SetVertexAsHexagon(int index, D3DXVECTOR3 Center, float Size, float Height);
D3DXCOLOR gaming;
bool colorChange = false;
D3DXCOLOR changeColor;
int nowColor;
int nextColor;
CPlayer* m_Player;
D3DXVECTOR3 playerPos;
D3DXVECTOR3 fieldPos;
enum ColorIndex {
	none=0,
	red,
	green,
	blue,
};


void CField::Init() {

	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);//3D化
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

	//頂点バッファ生成
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

	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"asset/texture/hexagon3.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);
	assert(m_Texture);//リリース時には出てこない、エラー時に出てきてくれるすぐれもの
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	gaming = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	colorChange = false;
	changeColor = D3DXCOLOR(0.1f, 0.0f, -0.1f, 1.0f);

	nowColor = blue;
	nextColor = red;
	CScene* scene = CManager::GetScene();
	m_Player= scene->GetGameObject<CPlayer>(1);
	playerPos = m_Player->GetPosition();

	fieldPos = m_Position + playerPos;

}
void CField::Init(D3DXVECTOR3 Center, float Size,float Height) {

	VERTEX_3D vertex[6];

	for (int i = 0;i < 6;i++) {
		vertex[i] = SetVertexAsHexagon(i, Center, Size, Height);
	}


	//頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 6;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"asset/texture/hexagon.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);
	assert(m_Texture);//リリース時には出てこない、エラー時に出てきてくれるすぐれもの
	m_Position = Center;
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}
void CField::Uninit() {
	m_VertexBuffer->Release();
	m_Texture->Release();

}

float addRed = 0.05f;
void CField::Update() {
	CScene* scene = CManager::GetScene();
	m_Player = scene->GetGameObject<CPlayer>(1);
	playerPos = m_Player->GetPosition();

	fieldPos = m_Position + playerPos;
	D3DXVec3Normalize(&fieldPos, &fieldPos);
//	fieldPos = m_Position;
//	m_Position += m_Player->GetPosition();
	//gaming.r += addRed;
	//if (gaming.r == 1.0f||gaming.r==-0.05f)
	//	addRed*=-1.0f;
}

void CField::Draw() {
	//マトリクス設定
	
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	D3DXMatrixTranslation(&trans, fieldPos.x, fieldPos.y, fieldPos.z);
	world = scale * rot*trans;
	CRenderer::SetWorldMatrix(&world);

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//マテリアル設定
	MATERIAL material;

	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	/*material.Diffuse.g = gaming.g;
	material.Diffuse.b = gaming.b;*/

	CRenderer::SetMaterial(material);
	
	//テクスチャ設定
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//プリミティブトポロジ設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
	);

	//ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(6, 0);

}

VERTEX_3D SetVertex(int index, D3DXVECTOR3 Center, float Size, float Height) {
	//返し値用数列,tmp
	VERTEX_3D tmp;
	//初期化
	float SetNum = Size / 2.0f;//Sizeは一辺の長さとしている。
	tmp.Position = D3DXVECTOR3(SetNum, Height, SetNum);//3D化
	tmp.Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	tmp.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	tmp.TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR3 mag(1.0f, 1.0f, 1.0f);
	switch (index) {
	case 0:
		mag = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
		tmp.TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		//vertex[0].Position = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);//3D化
		//vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		break;
	case 1:
		mag = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		tmp.TexCoord = D3DXVECTOR2(1.0f, 0.0f);
		//vertex[1].Position = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
		//vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
		break;
	case 2:
		mag = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
		tmp.TexCoord = D3DXVECTOR2(0.0f, 1.0f);
		//vertex[2].Position = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
		//vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
		break;
	case 3:
		mag = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
		tmp.TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		//vertex[3].Position = D3DXVECTOR3(10.0f, 0.0f, -10.0f);
		//vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		break;
	default:
		break;
	}
	tmp.Position.x *= mag.x;
	tmp.Position.y *= mag.y;
	tmp.Position.z *= mag.z;
	return tmp;

}

VERTEX_3D SetVertexAsHexagon(int index, D3DXVECTOR3 Center, float Size, float Height) {
	//返し値用数列,tmp
	VERTEX_3D tmp;
	//初期化
	float SetNum = Size / 2.0f;//Sizeは一辺の長さとしている。
	tmp.Position = D3DXVECTOR3(SetNum, Height, SetNum);//3D化
	tmp.Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	tmp.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	tmp.TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR3 mag(1.0f, 1.0f, 1.0f);
	switch (index) {
	case 0:
		mag = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
		tmp.TexCoord = D3DXVECTOR2(0.25f, 0.0f);
		//vertex[0].Position = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);//3D化
		//vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		break;
	case 1:
		mag = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		tmp.TexCoord = D3DXVECTOR2(0.75f, 0.0f);
		//vertex[1].Position = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
		//vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
		break;
	case 2:
		mag = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
		tmp.TexCoord = D3DXVECTOR2(0.0f, 0.5f);
		//vertex[2].Position = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
		//vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
		break;
	case 3:
		mag = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
		tmp.TexCoord = D3DXVECTOR2(1.0f, 0.5f);
		//vertex[3].Position = D3DXVECTOR3(10.0f, 0.0f, -10.0f);
		//vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		break;
	case 4:
		mag = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
		tmp.TexCoord = D3DXVECTOR2(0.25f, 1.0f);
		//vertex[3].Position = D3DXVECTOR3(10.0f, 0.0f, -10.0f);
		//vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		break;
	case 5:
		mag = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
		tmp.TexCoord = D3DXVECTOR2(0.75f, 1.0f);
		//vertex[3].Position = D3DXVECTOR3(10.0f, 0.0f, -10.0f);
		//vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		break;
	default:
		break;
	}
	tmp.Position.x *= mag.x;
	tmp.Position.y *= mag.y;
	tmp.Position.z *= mag.z;
	return tmp;

}