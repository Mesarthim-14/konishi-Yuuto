#ifndef _BOMB_UI_H_
#define _BOMB_UI_H_
//=============================================================================
//
// �{����UI�N���X�w�b�_�[	[bomb_ui.h]
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
#define MAX_BOMB_UI_TEXTURE		(1)
#define BOMB_UI_SIZE_X			(25.0f)
#define BOMB_UI_SIZE_Y			(45.0f)

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;

//=============================================================================
// �^�C�g��Bg�N���X
//=============================================================================
class CBombUi : public CScene2D
{
public:
	CBombUi();			// �R���X�g���N�^
	~CBombUi();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

	static CBombUi * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);
	static HRESULT Load(void);
	static void UnLoad(void);

private:
	D3DXVECTOR3 m_move;
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BOMB_UI_TEXTURE];		// �e�N�X�`�����̃|�C���^
	D3DXVECTOR3 m_Pos;
};

#endif