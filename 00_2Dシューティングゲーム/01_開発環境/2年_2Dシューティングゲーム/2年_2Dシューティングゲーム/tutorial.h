#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//=============================================================================
//
// �`���[�g���A���N���X�w�b�_�[
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
#define MAX_TUTORIAL_TEXTURE		(1)			// �e�N�X�`���̐�
#define TUTORIAL_SIZE_X			(300.0f)		// �T�C�Y
#define TUTORIAL_SIZE_Y			(400.0f)		// �T�C�Y

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;

//=============================================================================
// �^�C�g��Bg�N���X
//=============================================================================
class CTutorial : public CScene2D
{
public:
	CTutorial();			// �R���X�g���N�^
	~CTutorial();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

	static CTutorial * Create(									// �|���S���̐���
		D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);
	static HRESULT Load(void);									// �e�N�X�`�����[�h
	static void UnLoad(void);									// �e�N�X�`���A�����[�h

private:
	D3DXVECTOR3 m_Pos;												// ���W
	D3DXVECTOR3 m_move;												// �ړ���
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TUTORIAL_TEXTURE];	// �e�N�X�`�����̃|�C���^
};

#endif