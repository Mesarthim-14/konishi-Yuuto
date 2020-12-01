#ifndef _LIGHT_H_
#define _LIGHT_H_

//=============================================================================
//
// ���C�g�N���X�w�b�_�[		[light.h]
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
#define LIGHT_SIZE_X			(80)		// �T�C�Y
#define LIGHT_SIZE_Y			(80)		// �T�C�Y
#define LIGHT_ANIM_SPEED		(5)			// �A�j���[�V�����̃X�s�[�h
#define LIGHT_ANIM_PATTERN		(8)			// �A�j���[�V�����̃p�^�[��
#define MAX_LIGHT_TEXTURE		(1)			// �e�N�X�`���̐�

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;

//=============================================================================
// BG�N���X
//=============================================================================
class CLight : public CScene2D
{
public:
	typedef enum
	{
		LIGHT_TYPE_NONE = 0,	// �����l
		LIGHT_TYPE_WHITE,		// �����V�[���h
		LIGHT_TYPE_BLACK,		// �Ԃ��V�[���h
		LIGHT_TYPE_MAX
	}LIGHT_TYPE;

	CLight();					// �R���X�g���N�^
	~CLight();					// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

	static CLight * Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,	// �|���S���̃T�C�Y
		D3DXVECTOR3 size, TYPE type, LIGHT_TYPE Ltype);

	void SetMove(D3DXVECTOR3 move);								// �ړ��ʐݒ�
	static HRESULT Load(void);									// �e�N�X�`�����[�h
	static void UnLoad(void);									// �e�N�X�`���A�����[�h
	void SetColor(LIGHT_TYPE Ctype);							// �J���[�̐ݒ�
	void InitColor(void);										// �J���[�̏�����

private:
	D3DXVECTOR3 m_Pos;											// ���W
	D3DXVECTOR3 m_move;											// �ړ���
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_LIGHT_TEXTURE];	// �e�N�X�`�����̃|�C���^
	LIGHT_TYPE m_Ltype;											// ���C�g�̎��
	bool m_bScaleUp;											// �g��I���t���O
};

#endif