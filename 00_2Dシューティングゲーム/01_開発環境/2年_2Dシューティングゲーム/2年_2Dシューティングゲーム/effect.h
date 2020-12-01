#ifndef _EFFECT_H_
#define _EFFECT_H_

//=============================================================================
//
// �G�t�F�N�g�N���X�w�b�_�[
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene2d.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define EFFECT_SIZE_X			(30)	// �T�C�Y
#define EFFECT_SIZE_Y			(30)	// �T�C�Y
#define EFFECT_ANIM_SPEED		(5)		// �A�j���[�V�����̃X�s�[�h
#define EFFECT_ANIM_PATTERN		(8)		// �A�j���[�V�����̃p�^�[��
#define MAX_EFFECT_TEXTURE		(1)		// �e�N�X�`����

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;

//=============================================================================
// BG�N���X
//=============================================================================
class CEffect : public CScene2D
{
public:
	typedef enum
	{
		EFFECT_TYPE_NONE = 0,	// �����l
		EFFECT_TYPE_BULLET,		// �e
		EFFECT_TYPE_ENEMY,		// �G
		EFFECT_TYPE_MAX
	}EFFECT_TYPE;

	typedef enum
	{
		EFFECT_COLOR_NONE = 0,	// �����l
		EFFECT_COLOR_WHITE,		// �����V�[���h
		EFFECT_COLOR_BLACK,		// �Ԃ��V�[���h
		EFFECT_COLOR_MAX
	}EFFECT_COLOR;

	CEffect();			// �R���X�g���N�^
	~CEffect();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);		// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

	static CEffect * Create(										// �|���S������
		D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, 
		TYPE type, EFFECT_COLOR Ctype);

	void SetMove(D3DXVECTOR3 move);									// �ړ��ʐݒ�
	static HRESULT Load(void);										// �e�N�X�`�����[�h
	static void UnLoad(void);										// �e�N�X�`���A�����[�h
	void SetColor(EFFECT_COLOR Ctype);								// �F�̐ݒ�
	void InitColor(void);											// �F�̏�����

private:
	D3DXVECTOR3 m_Pos;												// ���W
	D3DXVECTOR3 m_move;												// �ړ���
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;								// ���_�o�b�t�@�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_EFFECT_TEXTURE];		// �e�N�X�`�����̃|�C���^
	EFFECT_COLOR m_Ctype;											// �J���[�^�C�v
	EFFECT_TYPE m_Etype;											// �G�t�F�N�g�^�C�v
	bool m_bScaleDown;												// �g��I���t���O
};

#endif