#pragma once
#include <list>
#include "main.h"
#include "gameobject.h"
#include "camera.h"
#include "field.h"
#include "model.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "polygon.h"
#include "scene.h"
CPlayer* tmpP;
CBullet* tmpBullet[MAX_BULLET_NUM];
CCamera* tmpC;
CEnemy* tmpE[ENEMY_INDEX];
const int FIELD_X = 5;//X������ɂ�����
const int FIELD_Z = 5;//Z����ɒu����
CField* tmpF[FIELD_Z][FIELD_X];
CCollision* tmpCol;
class CScene {
protected:
	std::list<CGameObject*>m_GameObject;

public:
	CScene(){}
	virtual ~CScene() {}
	virtual void Init(){
		tmpC=AddGameObject<CCamera>();
//�t�B�[���h�Â���=============================
		float Height = -30.0f;//�u������
		float Size=30.0f;//��ӂ̃T�C�Y
		float tmp_x, tmp_z;//���S�ʒu�����߂邽�߂�tmp�ϐ�
		tmp_x = (float)FIELD_X*(Size/2.0f)*-1.0f;
		tmp_z = (float)FIELD_Z*(Size / 2.0f)*-1.0f;
		D3DXVECTOR3 Center(tmp_x, Height, tmp_z);
		for (int z = 0;z < FIELD_Z;z++) {
			for (int x = 0;x < FIELD_X;x++) {
				D3DXVECTOR3 Center(tmp_x, Height, tmp_z);
				tmpF[z][x]=AddGameObject<CField>();
				tmpF[z][x]->Init(Center, Size, Height);
				tmp_x += Size;//���u�����玟�̗�ւ��炷
				Center.x = tmp_x;
			}
			tmp_x -= Size * FIELD_X;
			tmp_z += Size;//���u�����玟�̗�ւ��炷
			Center.z = tmp_z;//��s�u�����玟�̍s�ւ��炷
		}
//===========================================
		float posX = -20.0f;
		for (int i = 0;i < ENEMY_INDEX;i++) {
			D3DXVECTOR3 pos(posX, 0, 30.0f);
			tmpE[i] = AddGameObject<CEnemy>();
			tmpE[i]->Init(pos);
			posX += 20.0f;
		}
		tmpP=AddGameObject<CPlayer>();
		for (int i = 0;i < MAX_BULLET_NUM;i++) {
			tmpBullet[i] = AddGameObject<CBullet>();
		}
		AddGameObject<CPolygon>();
		AddGameObject<CCamera>()->Init(	tmpP->GetPos(),
							D3DXVECTOR3(0.0f, 400.0f, -30.0f),
							D3DXVECTOR3(30.0f,0.0f,0.0f));
		tmpCol->Init();
	}

	virtual void Uninit() {
		tmpCol->Uninit();
		for (CGameObject* object : m_GameObject) {
			object->Uninit();
			delete object;
		}
		m_GameObject.clear();
	}
	
	virtual void Update() {
		for (CGameObject* object : m_GameObject) {
			object->Update();
		}
		for (int i = 0;i < ENEMY_INDEX;i++) {
			tmpE[i]->GetPlayerPos(tmpP->GetPos());
			tmpE[i]->Update();
		}

		if (CInput::GetKeyTrigger(VK_SPACE)) {
			for (int i = 0;i < MAX_BULLET_NUM;i++) {
				if (tmpBullet[i]->GetCanUse() == false) {
					tmpBullet[i]->Create(tmpP->GetPos(),tmpP->GetMoveWay());
				}
			}
		}
		for (int i = 0;i < MAX_BULLET_NUM;i++) {
			if (tmpBullet[i]->GetCanUse() == true) {
				tmpBullet[i]->Update();
			}
		}
		tmpC->Update(tmpP->GetPos());
	
	}

	virtual void Draw() {
		for (CGameObject* object : m_GameObject) {
			object->Draw();

		}
		tmpC->Draw(tmpP->GetPos());

	}
	
	template <typename T>
	T* AddGameObject() {
		T* gameObject = new T();
		m_GameObject.push_back(gameObject);
		gameObject->Init();

		return gameObject;
	}
};