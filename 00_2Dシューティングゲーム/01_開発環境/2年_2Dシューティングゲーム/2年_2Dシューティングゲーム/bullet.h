#ifndef _BULLET_H_
#define _BULLET_H_
//=============================================================================
//
// �o���b�g�N���X�w�b�_�[ [bullet.h]
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
#define MAX_BULLET (512)				// �e�̍ő吔
#define BULLET_SIZE_X (25)				// �e�̉���
#define BULLET_SIZE_Y (25)				// �e�̏c��
#define COUNTER_BULLET_SIZE_X (20)		// �J�E���^�[���̒e
#define COUNTER_BULLET_SIZE_Y (20)		// �J�E���^�[���̒e
#define FIRE_WORKS_SIZE_X	(20)		// �ԉ΂̃T�C�Y
#define FIRE_WORKS_SIZE_Y	(20)		// �ԉ΂̃T�C�Y
#define MAX_BULLET_TEXTURE (4)			// �e�N�X�`���̍ő吔

#define FIRE_WORKS_NUM	(15)			// �o���b�g�̐�
#define FIRE_WORKS_LIFE	(120)			// �o���b�g�̗̑�

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;

//=============================================================================
// �o���b�g�N���X
//=============================================================================
class CBullet : public CScene2D
{
public:
	typedef enum
	{
		BULLET_TYPE_NONE = 0,	// �����l
		BULLET_TYPE_PLAYER,		// ���@�̒e
		BULLET_TYPE_ENEMY,		// �G�̒e
		BULLET_TYPE_BOSS,		// �{�X�̒e
		BULLET_TYPE_MAX			// �ő吔
	}BULLET_TYPE;

	typedef enum
	{
		BULLET_COLOR_NONE = 0,	// �����l
		BULLET_COLOR_WHITE,		// �����e
		BULLET_COLOR_BLACK,		// �����e
		BULLET_COLOR_MAX
	}BULLET_COLOR;

	typedef enum
	{
		BULLET_CATEGORY_NONE = 0,	// �����l
		BULLET_CATEGORY_NORMAL,		// �ʏ�
		BULLET_CATEGORY_CURRENT,	// �Ǐ]�e
		BULLET_CATEGORY_COUNTER,	// �J�E���^�[�e
		BULLET_CATEGORY_FIREWORKS,	// �ԉΒe
		BULLET_CATEGORY_MAX			// �ő吔
	}BULLET_CATEGORY;

	CBullet();			// �R���X�g���N�^
	~CBullet();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);						// ����������
	void Uninit(void);																// �I������
	void Update(void);																// �X�V����
	void Draw(void);																// �`�揈��
	void SetBullet(D3DXVECTOR3 move, int nLife, D3DXVECTOR3 size);							// �e�̏���ݒ�
	void SetType(BULLET_TYPE type, BULLET_COLOR Ctype);										// �^�C�v�ݒ�
	void SetCategory(BULLET_CATEGORY Bcate);												// �J�e�S���ݒ�
	static HRESULT Load(void);																// �e�N�X�`�����[�h
	static void UnLoad(void);																// �e�N�X�`���A�����[�h
	bool Collision(D3DXVECTOR3 pos, D3DXVECTOR3 size);										// �����蔻��
	BULLET_COLOR GetCtype(void);															// �F�̃^�C�v���
	void DecreaseLife(int nNumber);															// ���C�t�����炷
	void FlashPolygon(void);																// �|���S���̓_��	
	D3DXVECTOR3 GetSize(void);																// �T�C�Y�̏��
	void FireWorksUpdate(void);																// �ԉ΍X�V����

	static CBullet * Create(																// �|���S������
		D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
		TYPE type, BULLET_TYPE Btype, BULLET_COLOR Ctype,
		int nLife);	

	static CBullet *CounterAttack(D3DXVECTOR3 pos, D3DXVECTOR3 size,						// �J�E���^�[�e
		TYPE type, BULLET_TYPE Btype, BULLET_COLOR Ctype, BULLET_CATEGORY Bcate,
		int nLife, int nBulletNum);

	static CBullet *CurrentAttack(D3DXVECTOR3 pos, D3DXVECTOR3 Ppos, D3DXVECTOR3 size,		// �v���C���[�̌��ݒn�ɒe��ł�
		TYPE type, BULLET_TYPE Btype, BULLET_COLOR Ctype,
		int nLife);

	static CBullet *FireWorks(D3DXVECTOR3 pos, D3DXVECTOR3 size,							// �ԉΌ^�o���b�g
		TYPE type, BULLET_TYPE Btype, BULLET_COLOR Ctype, BULLET_CATEGORY Bcate, int nLife);

private:
	D3DXVECTOR3 m_Pos;												// �ʒu
	D3DXVECTOR3 m_move;												// �ړ�
	D3DXVECTOR3 m_Size;												// �T�C�Y
	int m_nLife;													// ��������
	D3DXVECTOR3 m_Target;											// �^�[�Q�b�g�̏ꏊ
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BULLET_TEXTURE];		// �e�N�X�`�����̃|�C���^
	BULLET_TYPE m_type;												// �o���b�g�^�C�v
	BULLET_COLOR m_Ctype;											// �o���b�g�J���[
	BULLET_CATEGORY m_Bcategory;									// �o���b�g�̎��
	int m_nSubColor;
	int m_nSubCol;
};

#endif