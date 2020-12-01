#ifndef _UI_H_
#define _UI_H_

//=============================================================================
//
// UI�N���X�w�b�_�[
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
#define WALL_SIZE_X (350)		// �ǂ̃T�C�Y
#define WALL_SIZE_Y (720)		// �ǂ̃T�C�Y
#define WAKU_SIZE_X	(30)		// ���N�̃T�C�Y
#define WAKU_SIZE_Y	(720)		// ���N�̃T�C�Y
#define SHIP_SIZE_X (60)		// ���@��UI�T�C�Y
#define SHIP_SIZE_Y (40)		// ���@��UI�T�C�Y
#define MAX_UI_TEXTURE (3)		// �e�N�X�`���̐�

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;

//=============================================================================
// BG�N���X
//=============================================================================
class CUi : public CScene2D
{
public:
	typedef enum
	{
		UI_TYPE_NONE = 0,	// �����l
		UI_TYPE_WALL,		// ��
		UI_TYPE_WAKU,		// �g
		UI_TYPE_REMAIN,		// �q�b�g�|�C���g
		UI_TYPE_MAX
	}UI_TYPE;

	CUi();			// �R���X�g���N�^
	~CUi();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

	static CUi * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,		// �|���S������
		TYPE type, UI_TYPE Utype);
	static HRESULT Load(void);									// �e�N�X�`�����[�h
	static void UnLoad(void);									// �e�N�X�`���A�����[�h

	void SetType(UI_TYPE Utype);								// Ui�^�C�v�̐ݒ�

private:
	D3DXVECTOR3 m_Pos;											// ���W
	D3DXVECTOR3 m_move;											// �ړ���
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_UI_TEXTURE];		// �e�N�X�`�����̃|�C���^
	UI_TYPE m_Utype;											// Ui�̎��
};

#endif