#ifndef _GAGE_H_
#define _GAGE_H_
//=============================================================================
//
// �Q�[�W�N���X�w�b�_�[		[gage.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene2d.h"
#include "ui.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define GAGE_SIZE_X			(10)			// �Q�[�W�̃T�C�Y
#define GAGE_SIZE_Y			(300)			// �Q�[�W�̃T�C�Y
#define MAX_GAGE_TEXTURE	(3)				// �e�N�X�`���̐�

//=============================================================================
// �O���錾
//=============================================================================
class CUi;

//=============================================================================
// BG�N���X
//=============================================================================
class CGage : public CUi
{
public:
	typedef enum
	{
		GAGE_TYPE_NONE = 0,		// �����l
		GAGE_TYPE_BLUE,			// ���Q�[�W
		GAGE_TYPE_FLAME,		// �g
		GAGE_TYPE_MAX
	}GAGE_TYPE;

	typedef enum
	{
		GAGE_COLOR_NONE = 0,	// �����l
		GAGE_COLOR_WHITE,		// ��
		GAGE_COLOR_BLACK,		// ��
		GAGE_COLOR_MAX
	}GAGE_COLOR;

	CGage();			// �R���X�g���N�^
	~CGage();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

	static CGage * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type, GAGE_TYPE Gtype);
	static HRESULT Load(void);
	static void UnLoad(void);

	void SetInfo(D3DXVECTOR3 pos, D3DXVECTOR3 size, GAGE_TYPE Gtype);	// �Q�[�W�̏��ݒ�
	void AddGage(int nNumber);											// �Q�[�W�ʉ��Z
	void SubtractGame(int nNumber);										// �Q�[�W���Z
	int GetLaserNum(void);												// ���[�U�[�̗�
	void GetPlayerColor(void);											// �v���C���[�̐F���擾

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_GAGE_TEXTURE];	// �e�N�X�`�����̃|�C���^
	D3DXVECTOR3 m_Pos;											// ���W
	D3DXVECTOR3 m_Move;											// �ړ���
	D3DXVECTOR3 m_Size;											// �T�C�Y
	GAGE_TYPE m_Gtype;											// �Q�[�W�^�C�v
	GAGE_COLOR m_Ctype;											// �Q�[�W�̃J���[
	int m_nLaserNum;											// ���[�U�[�̗�
	int m_nMaxLaserNum;											// ���[�U�[�Q�[�W�̃}�b�N�X
	int m_nFlashFlame;											// �t���[��
};

#endif