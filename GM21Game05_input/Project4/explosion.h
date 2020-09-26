#pragma once
#include "gameobject.h"

class CExplosion :public CGameObject {


	static ID3D11Buffer*								m_VertexBuffer;//���_�t�@�C��
	static ID3D11ShaderResourceView*	m_Texture;//�摜
	int m_count=0;

public:
	CExplosion(){};
	static void Load();
	static void Unload();
	void Init();
	void Init(D3DXVECTOR3 Center, float Size, float Height);
	void Uninit();
	void Update();
	void Draw();

};