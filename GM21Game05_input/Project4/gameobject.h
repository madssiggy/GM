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
enum WAY {
	up=0,
	down,
	front,
	back,
	left,
	right,

	NEUTRAL,
	WAY_MAX
};
const D3DXVECTOR3 MOVEWAY[WAY_MAX]{
	{0,1,0},{0,-1,0},{0,0,-1},{0,0,1},{-1,0,0},{1,0,0},{0,0,0}
};//�㉺�O�㍶�E�̏��Ԃ�0~�T