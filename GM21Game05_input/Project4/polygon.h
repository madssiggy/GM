#pragma once

class CPolygon {
private:
	ID3D11Buffer* m_VertexBuffer = NULL;//頂点ファイル
	ID3D11ShaderResourceView* m_Texture = NULL;//画像
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};