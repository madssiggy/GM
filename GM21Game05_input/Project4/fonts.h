#pragma once
#include "gameobject.h"
class CFonts :public CGameObject {
private:
	ID3D11Buffer* m_VertexBuffer = NULL;//頂点ファイル
	ID3D11ShaderResourceView* m_Texture = NULL;//画像
	int m_Score;
	int m_oldScore;
public:
	CFonts() :m_Score(11111),m_oldScore(m_Score) {};
	void Init();
	void Uninit();
	void Update();
	void Draw();
	int GetScore() { return m_Score; }
	void SetScore(int value) { m_Score = value; }
	void SetVertex(int value,D3DXVECTOR2 pos=D3DXVECTOR2(0.0f,0.0f), D3DXVECTOR2 size = D3DXVECTOR2(20.0f, 20.0f));
};
class CScore :public CGameObject {

};