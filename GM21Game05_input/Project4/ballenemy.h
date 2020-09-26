#pragma once
#include "enemy.h"

class CBallEnemy :public CEnemy {
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};