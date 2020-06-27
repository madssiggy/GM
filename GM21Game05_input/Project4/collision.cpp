#include "main.h"

#include "collision.h"

void CCollision::Init() {
	m_Circle.Center=D3DXVECTOR3(0,0,0);
	m_Circle.r = 0.0f;
}
void CCollision::Init(D3DXVECTOR3 c, float r) {
	m_Circle.Center = c;
	m_Circle.r = r;
}
void CCollision::Uninit() {}
void CCollision::Update(){

}

void CCollision::Update(D3DXVECTOR3 p) {
	m_Circle.Center = p;
}

bool OnCollisionEnter(CCollision target, CCollision bullet) {
	D3DXVECTOR3 dst = target.GetCircle().Center - bullet.GetCircle().Center;
	float length = D3DXVec3Length(&dst);

	float size = target.GetCircle().r + bullet.GetCircle().r;
	if (length < size) {
		return true;
	}
	//ƒqƒbƒg‚µ‚Ä‚¢‚È‚©‚Á‚½
	return false;
}