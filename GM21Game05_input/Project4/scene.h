#pragma once
#include <list>
#include <typeinfo>
#include <vector>
#include "input.h"
#include "main.h"

#include "audio_clip.h"
#include "resource.h"

#include "gameobject.h"





static CAudioClip audio;
static CAudioClip SE_explosion;

class CScene {
protected:
	std::list<CGameObject*>m_GameObject[3];//‚ ‚Æ‚©‚ç’¼’l‚ð’è’l‚É‚©‚¦‚æ‚¤

	
public:
	CScene(){}
	virtual ~CScene() {
		CAudioClip::Init();
		CAudioClip::SetMasterVolume(0.3f);

	}
	virtual void Init() = 0;

	virtual void Uninit() {

		for (int i = 0;i < 3;i++) {
			for (CGameObject* object : m_GameObject[i]) {
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear();
		}
	//	CBullet::UnLoad();
	}
	
	virtual void Update() {
		for (int i = 0;i < 3;i++) {
			for (CGameObject* object : m_GameObject[i]) {
				object->Update();
			}
			m_GameObject[i].remove_if([](CGameObject* object) {return object->Destroy();});
		}
	


	}

 void Draw() {
		for (int i = 0;i < 3;i++) {
			for (CGameObject* object : m_GameObject[i]) {
				object->Draw();

			}
		
		}

	}
	
	template <typename T>
	T* AddGameObject(int Layer) {
		T* gameObject = new T();
		m_GameObject[Layer].push_back(gameObject);
		gameObject->Init();

		return gameObject;
	}
	template <typename T>
	T* GetGameObject(int Layer) {
		for (CGameObject* object : m_GameObject[Layer]) {
			if (typeid(*object) == typeid(T) ) {
				return (T*)object;
			}
		}
		return NULL;
	}
	template <typename T>
	std::vector<T*> GetGameObjects(int Layer) 
	{
		std::vector<T*>objects;//STL
		for (CGameObject* object : m_GameObject[Layer]) {
			if (typeid(*object) == typeid(T)) {
				objects.push_back((T*)object);
			}
		}
		return objects;
	}
};

