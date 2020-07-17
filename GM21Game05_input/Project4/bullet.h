#pragma once
#include "gameobject.h"


#define MAX_BULLET_NUM (10)
class CBullet :public CGameObject {
private:
	static class CModel* m_Model;
	D3DXVECTOR3 moveWay;
	bool canUse;//true‚Ì‚Ý•`‰æ
	int Movecount;

public:
	CBullet() {};
	virtual ~CBullet() {};
	static void Load();
	
	static void UnLoad();
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Create(D3DXVECTOR3 playerPos, D3DXVECTOR3 Way);
	bool GetCanUse();

};
const int MaxDistance = 40;