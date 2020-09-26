#include "debug_scene.h"

#include "renderer.h"
#include "model.h"
#include "camera.h"
#include "field.h"

#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "polygon.h"
#include "explosion.h"
#include "vegetable.h"
#include "hexagon.h"
//#include "fonts.h"
CEnemy* tmpE[ENEMY_INDEX];
const int FIELD_X = 5;//Xâ°é≤è„Ç…Ç®Ç≠å¬êî
const int FIELD_Z = 5;//Zé≤è„Ç…íuÇ≠å¬êî
CHexagon* tmpHex[7];


void CDebugScene::Init(){
	CAudioClip::Init();
	CAudioClip::SetMasterVolume(0.5f);
	CBullet::Load();
	CExplosion::Load();
	AddGameObject<CCamera>(0);
	AddGameObject<CPlayer>(1);
	
	SetHexagon(15);

	float posX = -20.0f;
	for (int i = 0;i < ENEMY_INDEX;i++) {
		D3DXVECTOR3 pos(posX, 0, 30.0f);
		tmpE[i] = AddGameObject<CEnemy>(1);
		tmpE[i]->Init(pos);
		posX += 20.0f;
	}

	AddGameObject<CBullet>(1)->Load();
	AddGameObject<CPolygon>(2);
	//AddGameObject<CFonts>(2);

	AddGameObject<CCamera>(0)->Init();
	AddGameObject<CVegetable>(1)->Init();
	audio.Load("asset//sound/SE//decide.wav");
	SE_explosion.Load("asset//sound/SE//hit.wav");
}

void CDebugScene::Uninit() {
	CAudioClip::Uninit();
	CScene::Uninit();
	 CBullet::UnLoad();
	 CExplosion::Unload();
}
void CDebugScene::Update() {
	CScene::Update();
}
void CDebugScene::PlaySE() {
	SE_explosion.Play();
}