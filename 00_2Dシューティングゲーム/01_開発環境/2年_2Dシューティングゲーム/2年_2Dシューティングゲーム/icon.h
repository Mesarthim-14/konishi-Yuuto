#ifndef _ICON_H_
#define _ICON_H_

//=============================================================================
//
// �A�C�R���w�b�_�[	[icon.h]
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
#define ICON_SIZE_X			(50.0f)			// �T�C�Y
#define ICON_SIZE_Y			(50.0f)			// �T�C�Y
#define MAX_ICON_TEXTURE	(1)				// �e�N�X�`���̐�

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;

//=============================================================================
// �A�C�R���N���X
//=============================================================================
class CIcon : public CScene2D
{
public:
	CIcon();				// �R���X�g���N�^
	~CIcon();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);				// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �X�V����
	void Draw(void);														// �`�揈��

	static CIcon * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// �|���S������
	static HRESULT Load(void);												// �e�N�X�`�����[�h
	static void UnLoad(void);												// �e�N�X�`���A�����[�h
	void ScaleUp(void);														// �g��̏���
	void ScaleDown(void);													// �k���̏���
	void FlashPolygon(void);												// �|���S���̓_��
	bool GetEndIcon(void);													// �A�C�R���̏I���t���O���
private:
	D3DXVECTOR3 m_Pos;												// ���W
	D3DXVECTOR3 m_move;												// �ړ���
	D3DXVECTOR3 m_size;												// �T�C�Y
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_ICON_TEXTURE];		// �e�N�X�`�����̃|�C���^
	float m_fScale;													// �k���p�ϐ�
	float m_fScaleNum;												// �k����
	int m_nFlashFlame;												// �_�ł̃t���[��
	int m_nSubNumber;												// �J���[���Z
	int m_nSubNum;													// �J���[�̌��Z��
	int m_nIconCounter;												// �A�C�R���̎���
	bool m_bEndIcon;												// �A�C�R���̏I���t���O
};

#endif