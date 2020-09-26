#pragma once
#include "scene.h"


class CDebugScene :public CScene {

public:
	void Init();
	void Uninit();
	void Update();
	static void PlaySE();
};