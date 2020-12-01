#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
//=============================================================================
//
// �����N���X�w�b�_�[ [explosion.h]
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
#define MAX_EXPLOSION								(256)		// �����̍ő吔
#define EXPLOSION_SIZE_X							(70)		// �����̉���
#define EXPLOSION_SIZE_Y							(70)		// �����̏c��
#define EXPLOSION_ANIM_SPEED						(5)			// �����̑���
#define EXPLOSION_ANIM_PATTERN						(8)			// �����e�N�X�`���̃p�^�[����
#define MAX_EXPLOSION_TEXTURE						(3)			// �e�N�X�`���̍ő吔

#define BOSS_EXPLOSION_SIZE_X						(150.0f)	// �����̉���
#define BOSS_EXPLOSION_SIZE_Y						(150.0f)	// �����̏c��
#define BOSS_EXPLOSION_ANIM_SPEED					(2)			// �{�X�̔����̑���
#define BOSS_EXPLOSION_ANIM_PATTERN					(15)		// �{�X�̔����e�N�X�`���̃p�^�[����

#define SURROUNDINGS_EXPLOSION_SIZE_X				(50.0f)		// ��芪���̔���
#define SURROUNDINGS_EXPLOSION_SIZE_Y				(50.0f)		// ��芪���̔���

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;

//=============================================================================
// �����N���X
//=============================================================================
class CExplosion : public CScene2D
{
public:
	typedef enum
	{
		COLOR_TYPE_NONE = 0,		// �����l
		COLOR_TYPE_WHITE,			// ��
		COLOR_TYPE_BLACK,			// ��
		COLOR_TYPE_BOSS,			// �{�X
		COLOR_TYPE_MAX
	}COLOR_TYPE;

	CExplosion();			// �R���X�g���N�^
	~CExplosion();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);				// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �X�V����
	void Draw(void);														// �`�揈��

	static CExplosion * Create(D3DXVECTOR3 pos,  D3DXVECTOR3 move,	
		D3DXVECTOR3 size, TYPE type, COLOR_TYPE Ctype);						// �|���S������

	void SetExplosion(D3DXVECTOR3 move, COLOR_TYPE Ctype);					// �ړ��ʐݒ�
	static HRESULT Load(void);												// �e�N�X�`�����[�h
	static void UnLoad(void);												// �e�N�X�`���A�����[�h

private:
	D3DXVECTOR3 m_Pos;													// ���W
	D3DXVECTOR3 m_move;													// �ړ�
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_EXPLOSION_TEXTURE];		// �e�N�X�`�����̃|�C���^
	COLOR_TYPE m_Ctype;													// �J���[�^�C�v
};

#endif