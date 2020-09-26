#pragma once
#include "gameobject.h"
class CVegetable :public CGameObject {
private:

protected:
	CScene* m_scene;
	CModel* m_Model;
	D3DXVECTOR3 m_playerPos;
	int m_Price;
	float m_Size;
	float m_MaxSize;
	int m_GrowTime;
	int m_Ticks;//¬’·‚ª‹N‚«‚éŠÔ
public:
	CVegetable() :m_Price(100),m_Size(1.0f),m_GrowTime(0) ,m_Ticks(90),m_MaxSize(6.0f){};
	void Init();
	void Uninit();
	void Update();
	void Draw();
};