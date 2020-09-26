#pragma once
#include "scene.h"
class CTitle :public CScene {
private:
	int m_SoundTime;
	bool m_GoSign;
public:
	CTitle() :m_GoSign(false), m_SoundTime(150) {};
	void Init();
	void Uninit();
	void Update();

};
