#pragma once
#include "gameobject.h"
class CEnemy:public CGameObject{
protected:
	CModel* m_Model;
	D3DXVECTOR3 m_playerPos;
public:
	CEnemy() {}
	~CEnemy() {}
	void Init();
	void Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();
	void GetPlayerPos(D3DXVECTOR3 Ppos);
};