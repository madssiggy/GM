#pragma once
#include "gameobject.h"
class CPlayer:public CGameObject {
private:
	CModel* m_Model;
	D3DXVECTOR3 m_MoveWay;
	MATERIAL m_Material;
protected:
public:
	CPlayer() {}
	~CPlayer() {}
	void Init();
	void Uninit();
	void Update();
	void Draw();
	D3DXVECTOR3 GetMoveWay();
};
