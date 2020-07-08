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
#include <typeinfo>
#include <vector>
CPlayer* tmpP;
CBullet* tmpBullet[MAX_BULLET_NUM];
CCamera* tmpC;
CEnemy* tmpE[ENEMY_INDEX];
const int FIELD_X = 5;//X横軸上におく個数
const int FIELD_Z = 5;//Z軸上に置く個数
CField* tmpF[FIELD_Z][FIELD_X];
CCollision* tmpCol;
class CScene {
protected:
	std::list<CGameObject*>m_GameObject[3];//あとから直値を定値にかえよう

public:
	CScene(){}
	virtual ~CScene() {}
	virtual void Init(){
		tmpC=AddGameObject<CCamera>(0);
//フィールドづくり=============================
		float Height = -30.0f;//置く高さ
		float Size=30.0f;//一辺のサイズ
		float tmp_x, tmp_z;//中心位置を決めるためのtmp変数
		tmp_x = (float)FIELD_X*(Size/2.0f)*-1.0f;
		tmp_z = (float)FIELD_Z*(Size / 2.0f)*-1.0f;
		D3DXVECTOR3 Center(tmp_x, Height, tmp_z);
		for (int z = 0;z < FIELD_Z;z++) {
			for (int x = 0;x < FIELD_X;x++) {
				D3DXVECTOR3 Center(tmp_x, Height, tmp_z);
				tmpF[z][x]=AddGameObject<CField>(1);
				tmpF[z][x]->Init(Center, Size, Height);
				tmp_x += Size;//一列置いたら次の列へずらす
				Center.x = tmp_x;
			}
			tmp_x -= Size * FIELD_X;
			tmp_z += Size;//一列置いたら次の列へずらす
			Center.z = tmp_z;//一行置いたら次の行へずらす
		}
//===========================================
		float posX = -20.0f;
		for (int i = 0;i < ENEMY_INDEX;i++) {
			D3DXVECTOR3 pos(posX, 0, 30.0f);
			tmpE[i] = AddGameObject<CEnemy>(1);
			tmpE[i]->Init(pos);
			posX += 20.0f;
		}
		tmpP=AddGameObject<CPlayer>(1);
		for (int i = 0;i < MAX_BULLET_NUM;i++) {
			tmpBullet[i] = AddGameObject<CBullet>(1);
		}
		AddGameObject<CPolygon>(2);
		AddGameObject<CCamera>(0)->Init(	tmpP->GetPosition(),
																	D3DXVECTOR3(0.0f, 400.0f, -30.0f),
																	D3DXVECTOR3(30.0f,0.0f,0.0f));
		tmpCol->Init();
	}

	virtual void Uninit() {
		tmpCol->Uninit();
		for (int i = 0;i < 3;i++) {
			for (CGameObject* object : m_GameObject[i]) {
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear();
		}
		
	}
	
	virtual void Update() {
		for (int i = 0;i < 3;i++) {
			for (CGameObject* object : m_GameObject[i]) {
				object->Update();
			}
			/*m_GameObject[i].remove_if([](CGameObject* object){return object->Destroy();})*/
		}
	
		for (int i = 0;i < ENEMY_INDEX;i++) {
			tmpE[i]->GetPlayerPos(tmpP->GetPosition());
			tmpE[i]->Update();
		}

		if (CInput::GetKeyTrigger(VK_SPACE)) {
			for (int i = 0;i < MAX_BULLET_NUM;i++) {
				if (tmpBullet[i]->GetCanUse() == false) {
					tmpBullet[i]->Create(tmpP->GetPosition(),tmpP->GetMoveWay());
				}
			}
		}
		for (int i = 0;i < MAX_BULLET_NUM;i++) {
			if (tmpBullet[i]->GetCanUse() == true) {
				tmpBullet[i]->Update();
			}
		}
		tmpC->Update(tmpP->GetPosition());

		for (int i = 0;i < ENEMY_INDEX;i++) {
			for (int n = 0;n < MAX_BULLET_NUM;n++) {
				if (OnCollisionEnter(tmpE[i]->GetCollision(), tmpBullet[n]->GetCollision())) {
					tmpE[i]->Destroy();
					tmpBullet[n]->Destroy();
				}
			}
		}

	}

	virtual void Draw() {
		for (int i = 0;i < 3;i++) {
			for (CGameObject* object : m_GameObject[i]) {
				object->Draw();

			}
		
		}
		tmpC->Draw(tmpP->GetPosition());

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