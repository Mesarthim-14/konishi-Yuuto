#ifndef _MESSAGE_H_
#define _MESSAGE_H_

//=============================================================================
//
// ���b�Z�[�W�w�b�_�[	[message.h]
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
#define MESSAGE_SIZE_X			(50.0f)		// �T�C�Y
#define MESSAGE_SIZE_Y			(50.0f)		// �T�C�Y
#define MAX_MESSAGE_TEXTURE		(1)			// �e�N�X�`����

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;

//=============================================================================
// ���b�Z�[�W�N���X
//=============================================================================
class CMessage : public CScene2D
{
public:
	CMessage();				// �R���X�g���N�^
	~CMessage();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);				// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �X�V����
	void Draw(void);														// �`�揈��

	static CMessage * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// �|���S������
	static HRESULT Load(void);												// �e�N�X�`�����[�h
	static void UnLoad(void);												// �e�N�X�`���A�����[�h

	void ScaleUp(void);														// �g��̏���
	void ScaleDown(void);													// �k���̏���
	bool GetEndMessage(void);												// ���b�Z�[�W�̏I���t���O���
private:
	D3DXVECTOR3 m_Pos;												// ���W
	D3DXVECTOR3 m_move;												// �ړ���
	D3DXVECTOR3 m_size;												// �T�C�Y
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_MESSAGE_TEXTURE];		// �e�N�X�`�����̃|�C���^
	float m_fScale;													// �k���p�ϐ�
	float m_fScaleNum;												// �k����
	int m_nMessageCounter;											// ���b�Z�[�W�̎���
	bool m_bEndMessage;												// ���b�Z�[�W�̏I���t���O
};

#endif