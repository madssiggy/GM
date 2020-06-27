#pragma once
#include "gameobject.h"
#include "collision.h"
class CPlayer:public CGameObject {
private:
	CModel* m_Model;
	D3DXVECTOR3 m_MoveWay;
	CCollision m_Col;
protected:
public:
	CPlayer() {}
	~CPlayer() {}
	void Init();
	void Uninit();
	void Update();
	void Draw();
	D3DXVECTOR3 GetPos();
	CCollision GetCollision() { return m_Col; }
};
