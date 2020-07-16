#pragma once
#include "gameobject.h"

class CExplosion :public CGameObject {


	ID3D11Buffer*								m_VertexBuffer = nullptr;//���_�t�@�C��
	ID3D11ShaderResourceView*	m_Texture = NULL;//�摜
	int m_count=0;
public:
	void Load();
	void Unload();
	void Init();
	void Init(D3DXVECTOR3 Center, float Size, float Height);
	void Uninit();
	void Update();
	void Draw();

};