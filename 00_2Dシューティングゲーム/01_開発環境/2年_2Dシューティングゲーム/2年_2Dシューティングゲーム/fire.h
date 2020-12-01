#ifndef _FIRE_H_
#define _FIRE_H_
//=============================================================================
//
// �ԉ΂̍ŏ��̃N���X�w�b�_�[ [fire.h]
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
#define MAX_FIRE (256)					// �e�̍ő吔
#define FIRE_SIZE_X (25)				// �e�̉���
#define FIRE_SIZE_Y (25)				// �e�̏c��
#define MAX_FIRE_TEXTURE (1)			// �e�N�X�`���̍ő吔

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;

//=============================================================================
// �o���b�g�N���X
//=============================================================================
class CFire : public CScene2D
{
public:
	typedef enum
	{
		FIRE_COLOR_NONE = 0,	// �����l
		FIRE_COLOR_WHITE,		// �����e
		FIRE_COLOR_BLACK,		// �����e
		FIRE_COLOR_MAX
	}FIRE_COLOR;

	CFire();			// �R���X�g���N�^
	~CFire();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);			// ����������
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��

	static CFire * Create(
		D3DXVECTOR3 pos, D3DXVECTOR3 size,
		TYPE type, FIRE_COLOR Ctype,
		int nLife);														// �|���S������

	void SetFire(int nLife, D3DXVECTOR3 size);							// �e�̏���ݒ�
	void SetType(FIRE_COLOR Ctype);										// �^�C�v�ݒ�
	static HRESULT Load(void);											// �e�N�X�`�����[�h
	static void UnLoad(void);											// �e�N�X�`���A�����[�h
	FIRE_COLOR GetCtype(void);											// �F�̏��
	void InitMove(void);												// �ړ���
private:
	D3DXVECTOR3 m_Pos;												// �ʒu
	D3DXVECTOR3 m_move;												// �ړ�
	D3DXVECTOR3 m_Size;												// �T�C�Y
	int m_nLife;													// ��������
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_FIRE_TEXTURE];		// �e�N�X�`�����̃|�C���^
	FIRE_COLOR m_Ctype;												// �ΉԃJ���[
};

#endif