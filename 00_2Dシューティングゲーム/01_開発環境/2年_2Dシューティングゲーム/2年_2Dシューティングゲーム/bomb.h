#ifndef _BOMB_H_
#define _BOMB_H_

//=============================================================================
//
// �{���N���X�w�b�_�[ [bomb.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "effect.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define BOMB_SIZE_X				(50)		// ���T�C�Y
#define BOMB_SIZE_Y				(50)		// �c�T�C�Y
#define BOMB_SPARK_SIZE_X		(8)			// ���T�C�Y
#define BOMB_SPARK_SIZE_Y		(8)			// �c�T�C�Y
#define MAX_BOMB_TEXTURE		(1)			// �e�N�X�`����

#define BOMB_LIFE				(25)		// �{���̗̑�
#define BOMB_BASE_ANGLE			(90)		// �ΉԂ̌���
#define BOMB_NUM				(60)		// �X�p�[�N�̐�
#define BOMB_SPPED				(5)			// �X�s�[�h
#define BOMB_DISTANCE			(200)		// ��������
#define BOMB_ANGLE				(380)		// �p�x

#define BOMB_SPARK_LIFE			(40)		// �{���̗̑�
#define BOMB_SPARK_BASE_ANGLE	(90)		// �ΉԂ̌���
#define BOMB_SPARK_NUM			(70)		// �X�p�[�N�̐�
#define BOMB_SPARK_SPPED		(10)		// �X�s�[�h
#define BOMB_SPARK_DISTANCE		(100)		// ��������
#define BOMB_SPARK_ANGLE		(361)		// �p�x

//=============================================================================
// �O���錾
//=============================================================================
class CEffect;

//=============================================================================
// BG�N���X
//=============================================================================
class CBomb : public CEffect
{
public:
	typedef enum
	{
		BOMB_TYPE_NONE = 0,		// �����l
		BOMB_TYPE_SHOCK,		// �Ռ��h
		BOMB_TYPE_SPARK,		// �Ή�
		BOMB_TYPE_CENTER,		// ���S
		BOMB_TYPE_MAX			// �ő�l
	}BOMB_TYPE;

	typedef enum
	{
		BOMB_COLOR_NONE = 0,		// �����l
		BOMB_COLOR_WHITE,		// �Ռ��h
		BOMB_COLOR_BLACK,		// �Ή�
		BOMB_COLOR_MAX			// �ő�l
	}BOMB_COLOR;

	CBomb();			// �R���X�g���N�^
	~CBomb();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

	static CBomb * Create(										// �|���S������
		D3DXVECTOR3 pos, D3DXVECTOR3 size,
		TYPE type, BOMB_TYPE Btype, BOMB_COLOR BColor,
		int nAngle, int nBaseAngle, int nDistance, int nLife);

	static HRESULT Load(void);									// �e�N�X�`�����[�h
	static void UnLoad(void);									// �e�N�X�`���A�����[�h

	void InitColor(void);										// �G�t�F�N�g�̃J���[��ݒ�
private:
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_move;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							// ���_�o�b�t�@�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BOMB_TEXTURE];	// �e�N�X�`�����̃|�C���^
	int m_nLife;												// �̗�
	D3DXVECTOR3 m_TargetOld;									// �W�I�̌Â����W
	BOMB_COLOR m_BColor;
};

#endif