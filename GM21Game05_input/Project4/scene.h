#pragma once
#include <list>
#include "main.h"
#include "gameobject.h"
#include "camera.h"
#include "field.h"
#include "model.h"
#include "player.h"
#include "polygon.h"

class CScene {
protected:
	std::list<CGameObject*>m_GameObject;

public:
	CScene(){}
	virtual ~CScene() {}
	virtual void Init(){
	//	CCamera* camera = new CCamera();
	//	camera->Init();
	//	m_GameObject.push_back(camera);
	//	CField* field = new CField();
	//	field->Init();
	//	m_GameObject.push_back(field);
	//	CPlayer* player = new CPlayer();
	//	player->Init();
	//	m_GameObject.push_back(player);
	//////これいこうに３Ｄオブジェクトを設定する
	//	CPolygon* polygon = new CPolygon();
	//	polygon->Init();
	//	m_GameObject.push_back(polygon);
		AddGameObject<CCamera>();
		AddGameObject<CField>();
		AddGameObject<CPlayer>();
		AddGameObject<CPolygon>();
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
	}
	virtual void Draw() {
		for (CGameObject* object : m_GameObject) {
			object->Draw();
		}
	}
	template <typename T>
	T* AddGameObject() {
		T* gameObject = new T();
		m_GameObject.push_back(gameObject);
		gameObject->Init();

		return gameObject;
	}
};