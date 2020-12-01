#ifndef _MUZZLE_FLASH_H_
#define _MUZZLE_FLASH_H_

//=============================================================================
//
// �}�Y���t���b�V���N���X�w�b�_�[ [muzzle_flash.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "effect.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MUZZLE_FLASH_SIZE_X				(18)		// �T�C�Y
#define MUZZLE_FLASH_SIZE_Y				(18)		// �T�C�Y
#define MAX_MUZZLE_FLASH_TEXTURE		(1)			// �e�N�X�`����
#define MUZZLE_FLASH_LIFE				(8)			// ���C�t
#define MUZZLE_FLASH_NUM				(30)		// ��

//=============================================================================
// �O���錾
//=============================================================================
class CEffect;

//=============================================================================
// BG�N���X
//=============================================================================
class CMuzzleFlash : public CEffect
{
public:
	typedef enum
	{
		MUZZLE_FLASH_TYPE_NONE = 0,		// �����l
		MUZZLE_FLASH_TYPE_BULLET,		// �e
		MUZZLE_FLASH_TYPE_ENEMY,		// �G
		MUZZLE_FLASH_TYPE_MAX
	}EFFECT_TYPE;

	typedef enum
	{
		MUZZLE_FLASH_COLOR_NONE = 0,	// �����l
		MUZZLE_FLASH_COLOR_WHITE,		// �����V�[���h
		MUZZLE_FLASH_COLOR_BLACK,		// �Ԃ��V�[���h
		MUZZLE_FLASH_COLOR_MAX
	}EFFECT_COLOR;

	CMuzzleFlash();				// �R���X�g���N�^
	~CMuzzleFlash();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

	static CMuzzleFlash * Create(								// �|���S������
		D3DXVECTOR3 pos, D3DXVECTOR3 size,
		TYPE type, EFFECT_COLOR Ctype, int nLife);

	void SetMove(D3DXVECTOR3 move);								// �ړ��ʐݒ�
	static HRESULT Load(void);									// �e�N�X�`�����[�h
	static void UnLoad(void);									// �e�N�X�`���A�����[�h
	void SetColor(EFFECT_COLOR Ctype);							// �J���[�ݒ�
	void InitColor(void);										// �J���[����������
	void GetPlayerPos(void);									// �v���C���[���W�擾
private:
	D3DXVECTOR3 m_Pos;													// ���W
	D3DXVECTOR3 m_move;													// �ړ���
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;									// ���_�o�b�t�@�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_MUZZLE_FLASH_TEXTURE];	// �e�N�X�`�����̃|�C���^
	EFFECT_COLOR m_Ctype;												// �J���[�^�C�v
	EFFECT_TYPE m_Etype;												// �G�t�F�N�g�^�C�v
	int m_nLife;														// �̗́@
	D3DXVECTOR3 m_TargetOld;											// �W�I�̌Â����W
};

#endif