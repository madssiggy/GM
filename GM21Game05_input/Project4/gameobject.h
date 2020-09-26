#pragma once
class CGameObject {
protected:
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotation;
	D3DXVECTOR3 m_Scale;
	bool canUse;
	bool m_Destroy = false;
public:
	CGameObject() {}
	virtual ~CGameObject() {}

	virtual void Init()=0;
	virtual void Uninit()=0;
	virtual void Update()=0;
	virtual void Draw()=0;
	virtual void Create() { canUse = true; }
//	virtual void Destroy() { canUse = false; }
	D3DXVECTOR3 GetPosition() { return m_Position; }
	D3DXVECTOR3 GetRotation() { return m_Rotation; }
	D3DXVECTOR3 GetScale() { return m_Scale; }

	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }
	void SetRotation(D3DXVECTOR3 Rotation) { m_Rotation = Rotation; }
	void SetScale(D3DXVECTOR3 Scale) { m_Scale = Scale; }
	


	void SetDestroy() { m_Destroy = true; }

	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}
	D3DXVECTOR3 GetForward(){
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot,
			m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;
		return forward;
	}
};
//enum WAY {
//	up=0,
//	down,
//	front,
//	back,
//	left,
//	right,
//
//	NEUTRAL,
//	WAY_MAX
//};
//const D3DXVECTOR3 MOVEWAY[WAY_MAX]{
//	{0,1,0},{0,-1,0},{0,0,-1},{0,0,1},{-1,0,0},{1,0,0},{0,0,0}
//};//�㉺�O�㍶�E�̏��Ԃ�0~�T