#ifndef _CROW_H_
#define _CROW_H_

//=============================================================================
//
// �J���X�w�b�_�[	[crow.h]
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
#define CROW_POS_X			(-100.0f)	// �o�����W
#define CROW_POS_Y			(300.0f)	// �o�����W
#define CROW_MOVE_X			(5.0f)		// �ړ���
#define CROW_MOVE_Y			(0.0f)		// �ړ���
#define CROW_SIZE_X			(40.0f)		// �T�C�Y
#define CROW_SIZE_Y			(40.0f)		// �T�C�Y
#define MAX_CROW_TEXTURE	(1)			// �e�N�X�`��

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;

//=============================================================================
// �^�C�g��Bg�N���X
//=============================================================================
class CCrow : public CScene2D
{
public:
	CCrow();				// �R���X�g���N�^
	~CCrow();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);					// ����������
	void Uninit(void);															// �I������
	void Update(void);															// �X�V����
	void Draw(void);															// �`�揈��

	static CCrow * Create(
		D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, TYPE type);		// �|���S������
	static HRESULT Load(void);													// �e�N�X�`�����[�h
	static void UnLoad(void);													// �e�N�X�`���A�����[�h

private:
	D3DXVECTOR3 m_Pos;												// ���W
	D3DXVECTOR3 m_move;												// �ړ���
	D3DXVECTOR3 m_size;												// �T�C�Y
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_CROW_TEXTURE];		// �e�N�X�`�����̃|�C���^
	int m_nCounter;													// �o���J�E���^�[
};

#endif