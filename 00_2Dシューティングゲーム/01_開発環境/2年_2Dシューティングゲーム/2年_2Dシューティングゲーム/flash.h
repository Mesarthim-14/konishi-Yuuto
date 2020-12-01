#ifndef _FLASH_H_
#define _FLASH_H_

//=============================================================================
//
// �t���b�V���N���X�w�b�_�[ [flash.h]
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
#define FLASH_SIZE_X			(27)			// �T�C�Y
#define FLASH_SIZE_Y			(27)			// �T�C�Y
#define MAX_FLASH_TEXTURE		(1)				// �e�N�X�`���̐�
#define FLASH_LIFE				(5)				// ���C�t
#define FLASH_NUM				(30)			// ��

//=============================================================================
// �O���錾
//=============================================================================
class CEffect;

//=============================================================================
// �t���b�V���N���X
//=============================================================================
class CFlash : public CEffect
{
public:
	typedef enum
	{
		FLASH_TYPE_NONE = 0,	// �����l
		FLASH_TYPE_TOP,			// ����
		FLASH_TYPE_SHOT,		// �Ԃ�
		FLASH_TYPE_MAX
	}FLASH_TYPE;

	typedef enum
	{
		FLASH_COLOR_NONE = 0,	// �����l
		FLASH_COLOR_WHITE,		// �����V�[���h
		FLASH_COLOR_BLACK,		// �Ԃ��V�[���h
		FLASH_COLOR_MAX
	}FLASH_COLOR;

	CFlash();			// �R���X�g���N�^
	~CFlash();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

	static CFlash * Create(										// �|���S������
		D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type, 
		FLASH_COLOR Ctype,  FLASH_TYPE Ftype , int nLife);

	void SetMove(D3DXVECTOR3 move);								// �ړ��ʐݒ�
	static HRESULT Load(void);									// �e�N�X�`�����[�h
	static void UnLoad(void);									// �e�N�X�`���A�����[�h
	void SetColor(FLASH_COLOR Ctype);							// �F�̐ݒ�
	void InitColor(void);										// �F�̏�����
	void GetPlayerPos(void);									// �v���C���[���̎擾
	void GetLaserTop(void);										// ���[�U�[�̏��
	void SetFType(FLASH_TYPE Ftype);							// ���[�U�[�̃^�C�v��ݒ�

private:
	D3DXVECTOR3 m_Pos;											// ���W
	D3DXVECTOR3 m_move;											// �ړ���
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							// ���_�o�b�t�@�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_FLASH_TEXTURE];	// �e�N�X�`�����̃|�C���^
	FLASH_COLOR m_Ctype;										// �J���[�^�C�v
	FLASH_TYPE m_Ftype;											// �G�t�F�N�g�^�C�v
	int m_nLife;												// ���C�t
	D3DXVECTOR3 m_TargetOld;									// �W�I�̌Â����W
};

#endif