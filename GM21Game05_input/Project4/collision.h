#pragma once
typedef struct {
	D3DXVECTOR3 Center;
	float r;
}pos;
class CCollision {
protected:
	pos m_Circle;
public:
	void Init();
	void Init(D3DXVECTOR3 c,float r);
	void Uninit();
	void Update();
	void Update(D3DXVECTOR3 p);

	pos GetCircle() {
		return m_Circle;
	}
	
};
void EnemyVSBullet(CCollision target, CCollision bullet);

bool OnCollisionEnter(CCollision target, CCollision bullet);