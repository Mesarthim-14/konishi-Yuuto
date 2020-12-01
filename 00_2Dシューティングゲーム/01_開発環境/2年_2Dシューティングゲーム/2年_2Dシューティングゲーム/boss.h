#ifndef _BOSS_H_
#define _BOSS_H_
//=============================================================================
//
// �{�X�N���X�w�b�_�[	[boss.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "enemy.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define BOSS_SIZE_X			(150)			// �{�X�̃T�C�Y
#define BOSS_SIZE_Y			(150)			// �{�X�̃T�C�Y
#define MAX_BOSS_TEXTURE	(1)				// �e�N�X�`���̐�

//=============================================================================
// �O���錾
//=============================================================================
class CEnemy;
class CHpbar;

//=============================================================================
// �{�X�N���X
//=============================================================================
class CBoss : public CEnemy
{
public:
	typedef enum
	{
		BOSS_PHASE_NONE = 0,	// �����l
		BOSS_PHASE_FIRST,		// ���t�F�C�Y
		BOSS_PHASE_CHANGE_01,	// ����
		BOSS_PHASE_SECOND,		// ���t�F�C�Y
		BOSS_PHASE_CHANGE_02,	// ����
		BOSS_PHASE_THIRD,		// ��O�t�F�C�Y
		BOSS_PHASE_EXPLOSION,	// �����t�F�[�Y
		BOSS_PHASE_MAX
	}BOSS_PHASE;

	CBoss();			// �R���X�g���N�^
	~CBoss();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);				// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �X�V����
	void Draw(void);														// �`�揈��
	static CBoss * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// �|���S������
	static HRESULT Load(void);												// �e�N�X�`�����[�h
	static void UnLoad(void);												// �e�N�X�`���A�����[�h

	void AppearanceMove(void);												// �o�ꎞ�̈ړ���
	void FirstUpdateMove(void);												// �G�l�~�[�̈ړ�
	void FirstBulletShot(void);												// �e�̔���
	void FirstPhases(void);													// ���t�F�[�Y
	void ChangePhases(void);												// �`�F���W�t�F�[�Y
	void ChangeUpdateMove(void);											// �`�F���W�̍X�V
	void ChangeFlash(void);													// �_��
	void InitSecondPhase(void);												// ���t�F�C�Y������
	void SecondUpdateMove(void);											// �G�l�~�[�̈ړ�
	void SecondBulletShot(void);											// �e�̔���
	void SecondPhases(void);												// ���t�F�[�Y
	void ThirdPhase(void);													// ��O�t�F�[�Y
	void InitThirdPhase(void);												// ��O�t�F�[�Y�{�X��񏉊���
	void ThirdUpdateMove(void);												// ��O�t�F�[�Y�̓���
	void ThirdBulletShot(void);												// ��O�t�F�[�Y�̒e�̏���
	void HitBossDamage(int nNumber);										// �{�X�̗̑͂����炷
	void FhaseUpdate(void);													// �{�X�̃t�F�C�Y�X�V
	void Retire(void);														// �P�ނ̊֐�
	void ExplosionPhase(void);												// �{�X�̔����t�F�[�Y
	int GetLife(void);														// �{�X�̗̑͂̏��
	bool GetColor(void);													// �e�̃J���[�̏��
	bool GetExplosion(void);												// �{�X�̔������̏��

private:
	D3DXVECTOR3 m_Pos;												// ���W
	D3DXVECTOR3 m_Move;												// �ړ�
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BOSS_TEXTURE];		// �e�N�X�`�����̃|�C���^
	ENEMY_STATE m_State;											// �G�l�~�[�̏��
	BOSS_PHASE m_Fhase;												// �t�F�[�Y
	int m_nLife;													// ���C�t
	int m_nStateCnt;												// �G�l�~�[�̏�ԃJ�E���^�[
	int m_nBulletFlame;												// �t���[���̃J�E���g
	int m_nBulletCnt;												// �e���o����
	int m_nBossPhases;												// �{�X�̃t�F�C�Y
	int m_nFlashFlame;												// �_�ł̃t���[��
	int m_nSubNumber;												// �J���[���Z
	int m_nSubNum;													// �J���[�̌��Z��
	int m_nPhaseFlame;												// �t�F�[�Y�̃t���[��
	int m_nRetireCount;												// �P�ނ̃J�E���g
	int m_nExplosionFlame;											// �������Ă���J�E���g
	int m_nExplosionCount;											// �����̃J�E���g
	int m_nEndCount;												// �I���t���[��
	bool m_bColorFlag;												// �e�̐F�̃t���O
	bool m_bExplosion;												// �{�X�̔���
	bool m_bBossEnd;												// �{�X�̏I������
	CHpbar *pHpbar;													// HP�o�[
};

#endif