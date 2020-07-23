#pragma once
#include "gameobject.h"
class CPlayer:public CGameObject {
private:
	CModel* m_Model;
	D3DXVECTOR3 m_MoveWay;
	MATERIAL m_Material;
	D3DXQUATERNION m_Quaternion;
protected:
public:
	CPlayer() {}
	~CPlayer() {}
	void Init();
	void Uninit();
	void Update();
	void Draw();
	float GetAlpha() { return m_Material.Diffuse.a; }
	void SetAlpha(float alpha) { m_Material.Ambient = alpha; }
	void AddAlpha(float alpha) { m_Material.Diffuse.a += alpha; }
	D3DXVECTOR3 GetMoveWay();
};
