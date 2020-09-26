#pragma once


class CManager
{
protected:
	static class CScene* m_Scene;
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
	static class CScene* GetScene() { return m_Scene; }
	template<typename T>
	static void SetScene() {
		if (m_Scene != NULL) {
			m_Scene->Uninit();
			delete m_Scene;

	}
		T* scne = new T();
		m_Scene = scne;
		scne->Init();
	}
};