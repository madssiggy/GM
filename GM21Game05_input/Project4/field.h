#pragma once
#include "gameobject.h"
class CField :public CGameObject{
private:


	ID3D11Buffer*								m_VertexBuffer = nullptr;//���_�t�@�C��
	ID3D11ShaderResourceView*	m_Texture = NULL;//�摜
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};