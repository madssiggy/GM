#pragma once
#include <list>
#include "main.h"
#include "gameobject.h"
#include "camera.h"
#include "field.h"
#include "model.h"
#include "player.h"
#include "enemy.h"
#include "polygon.h"
#include <iostream>
#include <iterator> // std::next()ŠÖ”‚ªŠ‘®‚·‚éƒwƒbƒ_
class CScene {
protected:
	std::list<CGameObject*>m_GameObject;

public:
	CScene(){}
	virtual ~CScene() {}
	virtual void Init(){
	
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
		AddGameObject<CPlayer>()->Update();


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
	template <typename T>
	T* AddGameObject(D3DXVECTOR3 pos) {
		T* gameObject = new T();
		m_GameObject.push_back(gameObject);
		gameObject->Init(pos);

		return gameObject;
	}
};