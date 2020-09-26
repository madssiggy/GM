#pragma once
#include "gameobject.h"
class CPlayer:public CGameObject {
private:
	CModel* m_Model;
	D3DXVECTOR3 m_MoveWay;
	float m_SpeedMag;
	float m_SpeedMagMax;
//	MATERIAL m_PlayerMaterial;
	D3DXQUATERNION m_Quaternion;
	const int m_cCoolTime;
	int m_CoolTime;
	bool m_CanShot;
	float m_JumpVector;
	int m_JumpCount;
	int m_JumpCountMax;
	bool m_TriggerMoveKey;
protected:
public:
	CPlayer():m_cCoolTime(10),m_CoolTime(0),m_CanShot(true),m_JumpVector(0.0f),m_JumpCount(0), m_JumpCountMax(1) ,m_SpeedMag(0.0f),m_SpeedMagMax(1.0f),
	m_TriggerMoveKey(false){}
	~CPlayer() {}
	void Init();
	void Uninit();
	void Update();
	void Draw();

	//float GetAlpha();
	//void SetAlpha(float alpha);
	//void AddAlpha(float alpha);
	D3DXVECTOR3 GetMoveWay();
	void CollisionField();
};
