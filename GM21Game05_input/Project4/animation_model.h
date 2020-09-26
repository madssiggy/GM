#pragma once
#include <map>
#include <vector>
//�W�����C�u��������ɏ����Ă����B
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"
#pragma comment (lib,"assimp.lib")
struct DEFORM_VERTEX {
	aiVector3D Position;
	aiVector3D Normal;

	int BoneNum;
	std::string BoneName[4];
	float BoneWeight[4];
};

//�{�[���\��
struct BONE{
	aiMatrix4x4 Matrix;
	aiMatrix4x4 AnimationMatrix;
	aiMatrix4x4 OffsetMatrix;
};

class CAnimationModel {
private:

	const aiScene* m_Scene = NULL;//��ʑJ�ڂ̂��̂Ƃ͈Ⴄ�Aassimp�̃f�[�^�̎�
	std::map<std::string, const aiScene*> m_Animation;
	ID3D11Buffer** m_VertexBuffer;//**�̓|�C���^�̔z��B
	ID3D11Buffer** m_IndexBuffer;

	std::map<std::string, ID3D11ShaderResourceView*>m_Texture;

	std::vector<DEFORM_VERTEX>* m_DeformVertex;//�ό`��̒��_�f�[�^
	std::map<const std::string, BONE> m_Bone; //�{�[���f�[�^<���O�ŎQ��>

	void CreateBone(aiNode* node);
	void UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix);


public:
	void Load(const char *FileName);

	void LoadAnimation(const char* FileName, const char* Name);
	void UnLoad();
	void Update();
	void Draw();
	void Update(int frame);
	void Update(const char* AnimationName, int frame);
	void Update(const char* AnimationName1, const char* AnimationName2, float rate, int frame);
};