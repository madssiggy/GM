#pragma once
#include "gameobject.h"
class CPolygon:public CGameObject{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;//���_�t�@�C��
	ID3D11ShaderResourceView* m_Texture = NULL;//�摜
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};