#pragma once
#include "gameobject.h"
class CHexagon :public CGameObject {
private:

protected:
	CScene* m_scene;
	CModel* m_Model;
	float m_Size;
public:
	CHexagon() : m_Size(10.0f) {};
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

void SetHexagon(int Mag);