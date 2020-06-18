#pragma once
class CGameObject {
protected:
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotation;
	D3DXVECTOR3 m_Scale;

public:
	CGameObject() {}
	virtual ~CGameObject() {}
	virtual void Init()=0;
	virtual void Uninit()=0;
	virtual void Update()=0;
	virtual void Draw()=0;
};