#include "main.h"


#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "input.h"

#include "player.h"


#include "bullet.h"
#include "scene.h"

#include "ballenemy.h"

void CBallEnemy::Init() {
	m_scene = CManager::GetScene();
	m_Model = new CModel();
	m_Model->Load("asset\\model\\sphere.obj");


	m_Position = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
	m_Rotation = D3DXVECTOR3(30.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_playerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_shotTime = 60;
	m_coolTime = 0;
}