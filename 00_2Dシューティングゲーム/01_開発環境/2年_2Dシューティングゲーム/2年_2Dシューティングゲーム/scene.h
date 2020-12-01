#ifndef _SCENE_H_
#define _SCENE_H_
//=============================================================================
//
// �V�[���w�b�_�[ [scene.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_OBJECT		(2048)
#define NUM_VERTEX		(4)		// ���_�̐�
#define NUM_POLYGON		(2)		

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;

//=============================================================================
// �I�u�W�F�N�g�N���X
//=============================================================================
class CScene
{
public:

	//=========================================
	// �|���S���̃^�C�v
	//=========================================
	typedef enum
	{
		TYPE_NONE = 0,			// �����l
		TYPE_BG,				// �w�i
		TYPE_SHIELD,			// �V�[���h
		TYPE_LIGHT,				// ���C�g
		TYPE_ENEMY,				// �G�l�~�[
		TYPE_LASER,				// ���[�U�[
		TYPE_EFFECT,			// �G�t�F�N�g
		TYPE_PLAYER,			// �v���C���[
		TYPE_BULLET,			// �e
		TYPE_BOSS,				// �{�X
		TYPE_SURROUNDINGS,		// �{�X�̎�芪��
		TYPE_EXPLOSION,			// ����
		TYPE_UI,				// ��ʂ̎d�؂�
		TYPE_SCORE,				// �X�R�A
		TYPE_WARNING,			// �x��
		TYPE_FADE,				// �t�F�[�h�̗D��
		TYPE_MAX
	}TYPE;

	CScene();				// �R���X�g���N�^
	virtual ~CScene();		// �f�X�g���N�^

	// �����o�֐�
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type) = 0;	// ����������
	virtual void Uninit(void) = 0;											// �I������
	virtual void Update(void) = 0;											// �X�V����
	virtual void Draw(void) = 0;											// �`�揈��

	static void UpdateAll(void);			// �S�ẴI�u�W�F�N�g���X�V
	static void DrawAll(void);				// �S�ẴI�u�W�F�N�g��`��
	static void ReleaseAll(void);			// �S�ẴI�u�W�F�N�g���J������
	CScene *GetScene(int nCount);			// �V�[���̏��󂯎��
	void SetType(TYPE type);				// �V�[���̏��ݒ�
	TYPE GetType(void);						// �V�[������Ԃ�
	static int GetEnemyNum(void);			// �G�̐��̏��
	static void CountEnemy(void);			// �G�̃J�E���g
	
protected:
	void Release(void);						// �I�u�W�F�N�g���J��

private:
	static CScene *m_apScene[MAX_OBJECT];	// �V�[���I�u�W�F�N�g�̏��
	static int m_nNumEnemy;					// �G�l�~�[�̐�
	static int m_nNumAll;					// �g�p���Ă鐔
	TYPE m_type;							// �I�u�W�F�N�g�̃^�C�v
	int m_nID;								// �I�u�W�F�N�g�̔ԍ�
};

#endif