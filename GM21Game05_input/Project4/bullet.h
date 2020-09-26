#pragma once
#include "gameobject.h"



class CBullet :public CGameObject {
private:
	static class CModel* m_Model;
protected:
	D3DXVECTOR3 moveWay;
	bool canUse;//trueのみ描画
	int Movecount;
	int m_Parent=0;
	 int MaxDistance;
public:
	CBullet():MaxDistance(40) {};
	virtual ~CBullet() {};
	static void Load();
	
	static void UnLoad();
	void Init();
	void Uninit();
	void Update();
	void EnemyUpdate();
	void Draw();
	void Create(D3DXVECTOR3 playerPos, D3DXVECTOR3 Way,int parent=0);
	bool GetCanUse();
	//void SetParent(int parent=0) { m_Parent = parent;//0がプレイヤー、１がエネミー }
};

//class CBullet :public CGameObject {
//private:
//	static class CModel* m_Model;
//protected:
//	D3DXVECTOR3 moveWay;
//	bool canUse;//trueのみ描画
//	int Movecount;
//	int m_Parent = 0;
//	int MaxDistance;
//public:
//	CBullet() :MaxDistance(40) {};
//	virtual ~CBullet() {};
//	static void Load();
//
//	static void UnLoad();
//	void Init();
//	void Uninit();
//	void Update();
//	void EnemyUpdate();
//	void Draw();
//	void Create(D3DXVECTOR3 playerPos, D3DXVECTOR3 Way, int parent = 0);
//	bool GetCanUse();
//	//void SetParent(int parent=0) { m_Parent = parent;//0がプレイヤー、１がエネミー }
//};