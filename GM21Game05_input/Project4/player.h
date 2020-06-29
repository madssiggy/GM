#pragma once
#include "gameobject.h"
#include "collision.h"
class CPlayer:public CGameObject {
private:
	CModel* m_Model;
	D3DXVECTOR3 m_MoveWay;
	CIRCLE m_Col;
protected:
public:
	CPlayer() {}
	~CPlayer() {}
	void Init();
	void Uninit();
	void Update();
	void Draw();
	D3DXVECTOR3 GetPos();
	D3DXVECTOR3 GetMoveWay();
	const CIRCLE* GetCollision() { return &m_Col; }
};
