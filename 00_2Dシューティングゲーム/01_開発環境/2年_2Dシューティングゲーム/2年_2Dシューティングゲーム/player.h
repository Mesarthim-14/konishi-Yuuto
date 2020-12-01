#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// �v���C���[�N���X�w�b�_�[ [player.h]
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
#define DECISION_PLAYER_SIZE_X	(15)		// �����蔻��
#define DECISION_PLAYER_SIZE_Y	(15)		// �����蔻��
#define PLAYER_REMAIN_NUM		(2)			// �c�@
#define PLAYER_SHOT_POS_X		(11.0f)		// �e�̏o���ʒu
#define PLAYER_SHOT_POS_Y		(30.0f)		// �e�̏o���ʒu

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;
class CShield;
class CGage;
class CLaser;
class CBombUi;

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer : public CScene2D
{
public:
	typedef enum
	{
		// �v���C���[�̏��
		PLAYER_STATE_NONE = 0,		// �����l
		PLAYER_STATE_NORMAL,		// �ʏ���
		PLAYER_STATE_REVIVE,		// ������
		PLAYER_STATE_LASER,			// ���[�U�[���ˎ�
		PLAYER_STATE_MAX
	}PLAYER_STATE;

	CPlayer();			// �R���X�g���N�^
	~CPlayer();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);				// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �X�V����
	void Draw(void);														// �`�揈��

	static HRESULT Load(void);												// �e�N�X�`���̃��[�h
	static void UnLoad(void);												// �e�N�X�`���̃A�����[�h
	static CPlayer * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// �|���S������

	void HitDamage(int nCount);												// �_���[�W����
	void PlayerControl(void);												// �v���C���[����
	void Resurrection(void);												// ����
	void UpdateState(void);													// �v���C���[��ԍX�V
	bool BombCollision(void);												// �{���̓����蔻��
	bool GetUseLaser(void);													// ���[�U�[�̏��
	bool GetShildInfo(void);												// �V�[���h�̏��
	CGage *GetGage(void);													// ���[�U�[�Q�[�W
	CLaser *GetLaser(void);													// ���[�U�[�̏��

private:
	D3DXVECTOR3 m_Pos;						// ���W
	D3DXVECTOR3 m_Move;						// �ړ���
	PLAYER_STATE m_State;					// �v���C���[�̏��
	int m_StateCount;						// �v���C���[�̏�ԃJ�E���^�[
	int m_BulletState;						// �o���b�g�Ԋu�̃J�E���^�[
	static LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`���̃|�C���^
	int m_nLife;							// ���@�̗̑�
	int m_nStock;							// �X�g�b�N
	int m_nResurrectionCnt;					// �����t���[��
	int m_nLaserFlame;						// ���[�U�[�̃J�E���g
	int m_nLaserCounter;					// ���[�U�[�̐؂�ւ��J�E���^�[
	int m_nBombFlame;						// �{���̓����蔻��t���[��
	int m_nBombNum;							// �{���ɓ��������G�̃i���o�[
	int m_nBombCount;						// �{���̐�
	bool m_bShildInfo;						// �V�[���h�̏��
	bool m_bShildScaleInfo;					// �V�[���h�̊g���
	bool m_bPlayerDraw;						// �v���C���[�̕\��
	bool m_bUseLaser;						// ���[�U�[���g���Ă��邩
	bool m_bPressInfo;						// �������Ƃ��̏��
	bool m_bBombUse;						// �{�����g�����Ƃ�
	CShield *m_pShield;						// �V�[���h�̃|�C���^
	CGage *m_pGage;							// �Q�[�W�̃|�C���^
	CLaser *m_pLaser;						// ���[�U�[�̃|�C���^
	CBombUi *m_pBombUi;						// �{����UI
	TYPE m_BombType;						// �{���^�C�v
};

#endif