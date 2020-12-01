#ifndef _LASER_H_
#define _LASER_H_
//=============================================================================
//
// ���[�U�[�N���X�w�b�_�[	[laser.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene2d.h"
#include "flash.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define LASER_SIZE_X			(95)		// �T�C�Y
#define LASER_SIZE_Y			(10)		// �T�C�Y
#define LASER_ANIM_SPEED		(5)			// �A�j���[�V�����̑���
#define LASER_ANIM_PATTERN		(8)			// �A�j���[�V�����̃p�^�[��
#define MAX_LASER_TEXTURE		(1)			// �e�N�X�`����
#define MAX_FLASH_NUM			(64)		// ��
#define LASER_FLAME				(30)		// ���[�U�[�̃t���[��

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;
class CFlash;

//=============================================================================
// BG�N���X
//=============================================================================
class CLaser : public CScene2D
{
public:
	typedef enum
	{
		LASER_COLOR_NONE = 0,	// �����l
		LASER_COLOR_WHITE,		// ����
		LASER_COLOR_BLACK,		// �Ԃ�
		LASER_COLOR_MAX
	}LASER_COLOR;

	CLaser();			// �R���X�g���N�^
	~CLaser();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);		// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

	static CLaser * Create(											// �|���S������
		D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
		TYPE type, LASER_COLOR Ctype);

	void SetInfo(D3DXVECTOR3 move, D3DXVECTOR3 size);				// ���[�U�[�̏��ݒ�
	static HRESULT Load(void);										// �e�N�X�`�����[�h
	static void UnLoad(void);										// �e�N�X�`���A�����[�h
	void SetColor(LASER_COLOR Ctype);								// �ϐ��̑��
	void InitColor(void);											// �J���[�ݒ�
	void LaserUpdate(void);											// ���[�U�[�̏���
	void DisappearLaser(void);										// ���[�U�[�������鏈��
	bool Collision(void);											// ���[�U�[�����������Ƃ�
	void FlashCreate(D3DXVECTOR3 pos, CFlash::FLASH_TYPE Ftype);	// ���[�U�[�̃t���b�V��
	D3DXVECTOR3 GetSize(void);										// �T�C�Y���
	D3DXVECTOR3 GetTop(void);										// ��[���
private:
	D3DXVECTOR3 m_Pos;											// ���W
	D3DXVECTOR3 m_move;											// �ړ���
	D3DXVECTOR3 m_Size;											// �T�C�Y
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							// ���_�o�b�t�@�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_LASER_TEXTURE];	// �e�N�X�`�����̃|�C���^
	LASER_COLOR m_Ctype;										// �J���[�^�C�v
	bool m_bUse;												// ���[�U�[���g���Ă���
	D3DXVECTOR3 m_PolygonPos;									// �|���S���̍��W
	D3DXVECTOR3 m_PolygonSize;									// �|���S���̃T�C�Y
	D3DXVECTOR3 m_PolygonTop;									// �|���S���̐�[
};

#endif