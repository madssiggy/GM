#include "title.h"
#include "manager.h"

#include "polygon.h"
//#include "fonts.h"
//#include "game.h"
#include "debug_scene.h"
#include "title.h"
CPolygon* title;
//CFonts* fonts[5];
int tmpScore=13579;
D3DXVECTOR2 pos = D3DXVECTOR2((float)SCREEN_WIDTH - 20.0f, 20.0f);
void CTitle::Init() {
	CAudioClip::Init();
	CAudioClip::SetMasterVolume(0.5f);
	//CScene::Init();
	title=AddGameObject<CPolygon>(2);
	D3DXVECTOR2 tmpPos = pos;
	//for (int i = 0,keta=10,Score=tmpScore;i < 5;i++,keta*=10) {
	//	//fonts[i] = AddGameObject<CFonts>(2);

	//	Score %=10;
	//	
	////	//fonts[i]->SetVertex(Score,tmpPos);
	//	Score = tmpScore / keta;
	//	tmpPos.x -= 20.0f;
	//	
	//}
	title->ReadTexture((char*)"asset/texture/title.png",
		D3DXVECTOR2(400.0f,400.0f),D3DXVECTOR3((float)SCREEN_WIDTH/2,-50.0f+(float)SCREEN_HEIGHT/2,0.0f) );

//	title->SetPosition(D3DXVECTOR3((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT/2, 0.0f));
	audio.Load("asset//sound/SE//decide.wav");
	SE_explosion.Load("asset//sound/SE//hit.wav");

}

void CTitle::Uninit() {
	CAudioClip::Uninit();
	CScene::Uninit();
}
void CTitle::Update() {
CScene::Update();

if (CInput::GetKeyPress('W')) {
	tmpScore += 1;
	//D3DXVECTOR2 tmpPos = pos;
	//for (int i = 0, keta = 10, Score = tmpScore;i < 5;i++, keta *= 10) {


	//	Score %= 10;

	//	fonts[i]->SetVertex(Score, tmpPos);
	//	Score = tmpScore / keta;
	//	tmpPos.x -= 20.0f;

	//}
	//}
if (CInput::GetKeyPress('S')) {
	tmpScore -= 1;
	/*D3DXVECTOR2 tmpPos = pos;
	for (int i = 0, keta = 10, Score = tmpScore;i < 5;i++, keta *= 10) {


		Score %= 10;

		fonts[i]->SetVertex(Score, tmpPos);
		Score = tmpScore / keta;
		tmpPos.x -= 20.0f;*/

	}
}
if (CInput::GetKeyPress(VK_SPACE))
SE_explosion.Play();
if (CInput::GetKeyPress(VK_RETURN)) {
	m_GoSign = true;
	audio.Play(false);
}
if (m_GoSign&&m_SoundTime>0) {
	m_SoundTime--;
	if(m_SoundTime<=0)
	CManager::SetScene<CDebugScene>();
}
}

