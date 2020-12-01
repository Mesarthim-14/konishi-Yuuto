#ifndef _BG_H_
#define _BG_H_
//=============================================================================
//
// BG�N���X�w�b�_�[ [bg.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene.h"
#include "scene2d.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_BG (256)			// �w�i�̍ő吔
#define BG_SIZE_X (600)			// �w�i�̉���
#define BG_SIZE_Y (400)			// �w�i�̏c��
#define MAX_BG_TEXTURE (3)		// �e�N�X�`���̍ő吔

//=============================================================================
// �O���錾
//=============================================================================
class CScene;
class CScene2D;

//=============================================================================
// BG�N���X
//=============================================================================
class CBackground : public CScene
{
public:
	CBackground();				// �R���X�g���N�^
	~CBackground();				// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);		// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

	static HRESULT Load(void);										// �e�N�X�`�����[�h
	static void UnLoad(void);										// �e�N�X�`���A�����[�h
	static CBackground * Create(
		D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);				// �C���X�^���X����

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG_TEXTURE];		// �e�N�X�`�����̃|�C���^
	CScene2D *m_apScene2D[MAX_POLYGON];							// scene2D���̃|�C���^
};

#endif