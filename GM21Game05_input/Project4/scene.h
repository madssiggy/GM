#pragma once
#include <list>
#include "main.h"
#include "gameobject.h"
#include "camera.h"
#include "field.h"
#include "model.h"
#include "player.h"
#include "polygon.h"
CPlayer* tmpP;
CCamera* tmpC;
const int FIELD_X = 2;//X������ɂ�����
const int FIELD_Z = 2;//Z����ɒu����
CField* tmpF[FIELD_Z][FIELD_X];
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
		D3DXVECTOR3 Center(tmp_x,Height, tmp_z);
		for (int z = 0;z < FIELD_Z;z++) {
			for (int x = 0;x < FIELD_X;x++) {
				tmpF[z][x]=AddGameObject<CField>();
				tmpF[z][x]->Init(Center, Size, Height);
				tmp_x += Size;//���u�����玟�̗�ւ��炷
				Center.x = tmp_x;
			}
			tmp_z += Size;//���u�����玟�̗�ւ��炷
			Center.z = tmp_z;//��s�u�����玟�̍s�ւ��炷
		}
//===========================================

		tmpP=AddGameObject<CPlayer>();
		AddGameObject<CPolygon>();
		AddGameObject<CCamera>()->Init(	tmpP->GetPos(),
							D3DXVECTOR3(0.0f, 400.0f, -30.0f),
							D3DXVECTOR3(30.0f,0.0f,0.0f));
	}
	virtual void Uninit() {
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