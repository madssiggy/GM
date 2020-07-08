#pragma once
class CGameObject {
protected:
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotation;
	D3DXVECTOR3 m_Scale;
	bool canUse;
public:
	CGameObject() {}
	virtual ~CGameObject() {}
	virtual void Init()=0;
	virtual void Uninit()=0;
	virtual void Update()=0;
	virtual void Draw()=0;
	virtual void Create() { canUse = true; }
	virtual void Destroy() { canUse = false; }
	D3DXVECTOR3 GetPosition(){ return m_Position; }
	D3DXVECTOR3 SetPosition(D3DXVECTOR3 pos) { m_Position = pos; }

	void SetDestroy() {}
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
};//è„â∫ëOå„ç∂âEÇÃèáî‘Ç≈0~ÇT