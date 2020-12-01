#ifndef _SPARK_H_
#define _SPARK_H_

//=============================================================================
//
// �ΉԃN���X�w�b�_�[ [spark.h]
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
#define SPARK_SIZE_X			(5)			// ���T�C�Y
#define SPARK_SIZE_Y			(5)			// �c�T�C�Y
#define MAX_SPARK_TEXTURE		(1)			// �e�N�X�`����

#define SPARK_LIFE				(30)		// �X�p�[�N�̗̑�
#define SPARK_BASE_ANGLE		(90)		// �ΉԂ̌���
#define SPARK_NUM				(50)		// �X�p�[�N�̐�
#define SPARK_SPPED				(3)			// �X�s�[�h
#define SPARK_DISTANCE			(5)			// ��������
#define SPARK_ANGLE				(360)		// �p�x

#define SPARK_BOSS_NUM			(2)			// �X�p�[�N�̐�
#define SPARK_BASE_BOSS_ANGLE	(-90)		// �ΉԂ̌���
#define SPARK_BOSS_SPPED		(3)			// �X�s�[�h
#define SPARK_BOSS_DISTANCE		(5)			// ��������
#define SPARK_BOSS_ANGLE		(60)		// �p�x

#define SPARK_CHANGE_LIFE		(17)		// �X�p�[�N�̗̑�
#define SPARK_CHANGE_NUM		(2)			// �X�p�[�N�̐�
#define SPARK_CHANGE_SPPED		(5)			// �X�s�[�h
#define SPARK_CHANGE_DISTANCE	(20)		// ��������
#define SPARK_CHANGE_ANGLE		(20)		// �p�x

//=============================================================================
// �O���錾
//=============================================================================
class CEffect;

//=============================================================================
// BG�N���X
//=============================================================================
class CSpark : public CEffect
{
public:
	CSpark();			// �R���X�g���N�^
	~CSpark();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

	static CSpark * Create(										// �|���S������
		D3DXVECTOR3 pos, D3DXVECTOR3 size,
		TYPE type, int nAngle,  int nBaseAngle, int nDistance, int nLife);
	static HRESULT Load(void);									// �e�N�X�`�����[�h
	static void UnLoad(void);									// �e�N�X�`���A�����[�h

	void InitColor(void);										// �G�t�F�N�g�̃J���[��ݒ�
	void SetMove(D3DXVECTOR3 move);								// �ړ��̐ݒ�

private:
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_move;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_SPARK_TEXTURE];		// �e�N�X�`�����̃|�C���^
	int m_nLife;							// �̗�
	D3DXVECTOR3 m_TargetOld;				// �W�I�̌Â����W
};

#endif