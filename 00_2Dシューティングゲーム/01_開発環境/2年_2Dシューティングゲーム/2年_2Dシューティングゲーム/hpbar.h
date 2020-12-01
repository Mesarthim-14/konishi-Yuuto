#ifndef _HPBAR_H_
#define _HPBAR_H_
//=========================================================
//
// �̗̓o�[�N���X�w�b�_�[	[hpbar.h]
// Author : Konishi Yuuto
//
//=========================================================

//=========================================================
// �C���N���[�h
//=========================================================
#include "scene2d.h"

//=========================================================
// �}�N����`
//=========================================================
#define MAX_HPBAR_TEXTURE	(1)			// �e�N�X�`��
#define BAR_SIZE_X			(500)		// �T�C�Y
#define BAR_SIZE_Y			(20)		// �T�C�Y

//=========================================================
// �O���錾
//=========================================================
class CScene2D;

//=========================================================
// �{���N���X
//=========================================================
class CHpbar : public CScene2D
{
public:
	CHpbar();			// �R���X�g���N�^
	~CHpbar();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);				// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �X�V����
	void Draw(void);														// �`�揈��

	static HRESULT Load(void);												// �e�N�X�`�����[�h
	static void UnLoad(void);												// �e�N�X�`���A�����[�h
	static CHpbar *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, 
		TYPE type, int nLife);												// �|���S������

	void AddDamage(int nNumber);											// �_���[�W����
	void SetHp(int nNumber);												// �̗͂̉�
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							// �o�b�t�@�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_HPBAR_TEXTURE];	// �e�N�X�`���̃|�C���^
	D3DXVECTOR3 m_Pos;											// ���W
	int m_nMaxLife;												// �̗�
	int m_nLife;												// �̗�
};
#endif