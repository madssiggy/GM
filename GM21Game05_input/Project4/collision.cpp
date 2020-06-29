#include "main.h"
#include "collision.h"

void CCollision::Init() {

}

void CCollision::Uninit() {}
void CCollision::Update(){

}

void EnemyVSBullet(const CIRCLE* target, const CIRCLE* bullet) {
	OnCollisionEnter(target,bullet);
}



bool OnCollisionEnter(const CIRCLE* target, const CIRCLE* bullet) {
	D3DXVECTOR3 dst = target->Center - bullet->Center;
	float length = D3DXVec3Length(&dst);

	float size = target->r + bullet->r;
	if (length < size) {
		return true;
	}
	//ƒqƒbƒg‚µ‚Ä‚¢‚È‚©‚Á‚½
	return false;
}