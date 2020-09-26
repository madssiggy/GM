#pragma once
#include "gameobject.h"
#include "collision.h"
#define ENEMY_INDEX (3)
class CEnemy:public CGameObject{
protected:
	
	CScene* m_scene;
	CModel* m_Model;
	D3DXVECTOR3 m_playerPos;
	CIRCLE m_Col;
	bool canUse=true;
	bool isMove=false;
	int m_shotTime;
	int m_coolTime;
	int m_HP;
	int m_MoneyDrop;
public:
	CEnemy() :m_HP(5){}
	~CEnemy() {}
	void Init();
	void Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();
	
	int GetHP() { return m_HP; }
	void SetHP(int health) { m_HP = health; }
	void AddHP(int addHP) { m_HP += addHP; }
	int GetMoney() { return m_MoneyDrop; }
	void SetMoney(int money) { m_MoneyDrop = money; }
	void GetPlayerPos(D3DXVECTOR3 Ppos);
	const CIRCLE* GetCollision() { return &m_Col; }
	//void Destroy() { canUse = false; }
	void SetCanUse(bool set) { canUse = set; }
};