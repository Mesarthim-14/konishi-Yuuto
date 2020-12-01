#ifndef _SHIELD_H_
#define _SHIELD_H_

//=============================================================================
//
// �V�[���h�N���X�w�b�_�[	[shield.h]
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
#define SHIELD_SIZE_X			(94)	// �T�C�Y
#define SHIELD_SIZE_Y			(94)	// �T�C�Y
#define SHIELD_ANIM_SPEED		(5)		// �A�j���[�V�����̑��x
#define SHIELD_ANIM_PATTERN		(8)		// �A�j���[�V�����̃p�^�[��
#define MAX_SHILD_TEXTURE		(2)		// �e�N�X�`���̐�

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;

//=============================================================================
// BG�N���X
//=============================================================================
class CShield : public CScene2D
{
public:
	typedef enum
	{
		SHIELD_TYPE_NONE = 0,	// �����l
		SHIELD_TYPE_WHITE,		// �����V�[���h
		SHIELD_TYPE_BLACK,		// �Ԃ��V�[���h
		SHIELD_TYPE_MAX
	}SHIELD_TYPE;

	CShield();			// �R���X�g���N�^
	~CShield();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

	static CShield * Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,	// �|���S������
		D3DXVECTOR3 size, TYPE type, SHIELD_TYPE Stype);

	void SetMove(D3DXVECTOR3 move);								// �ړ��ʐݒ�
	bool GetbScale(void);										// �o���A�̑傫�����
	static HRESULT Load(void);									// �e�N�X�`�����[�h
	static void UnLoad(void);									// �e�N�X�`���A�����[�h
private:
	D3DXVECTOR3 m_Pos;											// ���W
	D3DXVECTOR3 m_move;											// �ړ���
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_SHILD_TEXTURE];	// �e�N�X�`�����̃|�C���^
	bool m_bScaleUp;											// �g��I���t���O
};

#endif