#pragma once
#include "gameobject.h"
#include "collision.h"
class CEnemy:public CGameObject{
protected:
	CModel* m_Model;
	D3DXVECTOR3 m_playerPos;
	CCollision m_Col;
public:
	CEnemy() {}
	~CEnemy() {}
	void Init();
	void Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();
	void GetPlayerPos(D3DXVECTOR3 Ppos);
	CCollision GetCollision() { return m_Col; }
};