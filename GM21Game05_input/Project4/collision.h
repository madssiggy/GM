#pragma once
typedef struct {
	D3DXVECTOR3 Center;
	float r;
}CIRCLE;
class CCollision {
protected:
public:
	void Init();
	void Uninit();
	void Update();
	void Update(const CIRCLE* player, const CIRCLE* enemy, const CIRCLE* bullet );
	
};
//void EnemyVSBullet(const CEnemy* target, const CBullet* bullet);

bool OnCollisionEnter(const CIRCLE* target, const CIRCLE* bullet);