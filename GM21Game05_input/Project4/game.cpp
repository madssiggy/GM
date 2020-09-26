#include "game.h"

#include "camera.h"
#include "field.h"
#include "model.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "polygon.h"
#include "explosion.h"
void CGame::Init() {
	CScene::AddGameObject<CPlayer>(1);
}

void CGame::Uninit() {

}
void CGame::Update() {

}

