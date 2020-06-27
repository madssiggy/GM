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
class CScene {
protected:
	std::list<CGameObject*>m_GameObject;

public:
	CScene(){}
	virtual ~CScene() {}
	virtual void Init(){
	
		tmpC=AddGameObject<CCamera>();
		AddGameObject<CField>();
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