#pragma once
#include "gameobject.h"
class CPlayer:public CGameObject {
private:
	CModel* m_Model;
protected:
public:
	CPlayer() {}
	~CPlayer() {}
	void Init();
	void Uninit();
	void Update();
	void Draw();
};