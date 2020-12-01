#ifndef _ENEMY_H_
#define _ENEMY_H_
//=============================================================================
//
// �G�l�~�[�N���X�w�b�_�[ [enemy.h]
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
#define MAX_ENEMY				(256)			// �G�̍ő吔
#define ENEMY_SIZE_X			(50)			// �G�l�~�[�̃T�C�Y
#define ENEMY_SIZE_Y			(50)			// �G�l�~�[�̃T�C�Y
#define ENEMY_NORMAL_SIZE_X		(60)			// �G�̉���
#define ENEMY_NORMAL_SIZE_Y		(60)			// �G�̏c��
#define ENEMY_CURRENT_SIZE_X	(70)			// ���@�擾�e��łG�̑傫��
#define ENEMY_CURRENT_SIZE_Y	(70)			// ���@�擾�e��łG�̑傫��
#define ENEMY_SNAKE_SIZE_X		(40)			// �W�O�U�O�G
#define ENEMY_SNAKE_SIZE_Y		(40)			// �W�O�U�O�G
#define ENEMY_THROUGH_SIZE_X	(70)			// �^�������e��łG�̃T�C�Y
#define ENEMY_THROUGH_SIZE_Y	(70)			// �^�������e��łG�̃T�C�Y
#define ENEMY_DIRECTION_SIZE_X	(50)			// �����]������G�̃T�C�Y
#define ENEMY_DIRECTION_SIZE_Y	(50)			// �����]������G�̃T�C�Y
#define ENEMY_FOLLOW_SIZE_X		(50)			// �^�������e��łG�̃T�C�Y
#define ENEMY_FOLLOW_SIZE_Y		(50)			// �^�������e��łG�̃T�C�Y

#define MAX_ENEMY_TEXTURE		(4)				// �G�l�~�[�̃e�N�X�`��

#define INSIDE_ROTATION_RADIUS	(400)			// ���G�̊O���̔��a
#define OUTSIDE_ROTATION_RADIUS	(325)			// ���G�̓����̔��a

#define CIRCLE_ENEMY_NUM		(5)				// �T�[�N���z�u�̓G�̐�
#define CIRCLE_ANGLE			(-45.0f)		// �T�[�N���z�u�̓G�̊p�x
#define CIRCLE_MAX_ANGLE		(150)			// �G�̏o���̃T�[�N���̊p�x
#define CIRCLE_DISTANCE			(210.0f)		// �T�[�N���̋���
#define CIRCLE_INITIAL_Y		(-125.0f)		// �����̍��W

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;
class CLight;

//=============================================================================
// �G�l�~�[�N���X
//=============================================================================
class CEnemy : public CScene2D
{
public:
	// �G�̐F
	typedef enum
	{
		COLOR_TYPE_NONE = 0,	// �����l
		COLOR_TYPE_WHITE,		// �����G
		COLOR_TYPE_BLACK,		// �Ԃ��G
		COLOR_TYPE_MAX
	}COLOR_TYPE;

	// �G�̎��
	typedef enum
	{
		ENEMY_TYPE_NONE = 0,		// �����l
		ENEMY_TYPE_NORMAL,			// �ʏ�G
		ENEMY_TYPE_CURRENT,			// ���@�擾�e��łG
		ENEMY_TYPE_SNAKE,			// �W�O�U�O�ړ�
		ENEMY_TYPE_THROUGH,			// �^�������e��łG
		ENEMY_TYPE_ROTATION,		// ����Ă���G
		ENEMY_TYPE_CIRCLE,			// �T�[�N���z�u�̓G
		ENEMY_TYPE_DIRECTION,		// �����]������G
		ENEMY_TYPE_FOLLOW,			// �Ǐ]����G
		ENEMY_TYPE_MAX
	}ENEMY_TYPE;

	// �G�̏��
	typedef enum
	{
		ENEMY_STATE_NORMAL = 0,		// �ʏ���
		ENEMY_STATE_DAMAGE,			// �_���[�W���󂯂Ă�����
		ENEMY_STATE_MAX				// �ő�
	}ENEMY_STATE;

	CEnemy();			// �R���X�g���N�^
	~CEnemy();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);		// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
	static HRESULT Load(void);										// �e�N�X�`�����[�h
	static void UnLoad(void);										// �e�N�X�`���A�����[�h

	D3DXVECTOR3 GetPos(void) { return m_Pos; }						// ����Ԃ�
	void SetPos(D3DXVECTOR3 pos);									// ���W�ݒ�
	void SetSize(D3DXVECTOR3 size);									// �T�C�Y�ݒ�
	void SetEnemyType(COLOR_TYPE Ctype, ENEMY_TYPE Etype);			// ���Z�b�g
	void SetLife(void);												// ���C�t�̐ݒ�
	void SetMove(void);												// �ړ��ݒ�
	void SetCounter(void);											// �J�E���^�[�o���b�g�̐ݒ�
	void SetFirstBulletTime(int nTime);								// ���e�̔����t���[���ݒ�
	void SetRotation(float fRadius, float fTheta);					// �p�x�̐ݒ�
	bool Collision(void);											// �����蔻��
	void InitThrough(D3DXVECTOR3 pos);								// �����ʒu�擾
	D3DXVECTOR3 GetSize(void);										// �T�C�Y�̏��
	void TransparentInit(void);										// �����̏�����

	void ObliqueUpdate(void);										// �΂߈ړ��̍X�V
	void CurrentUpdate(void);										// ���@�擾�e��łG�̓���
	void SnakeUpdate(void);											// ���ړ��X�V
	void ThroughUpdate(void);										// �^�������e��łG�̍X�V
	void RotationUpdate(void);										// ���[�e�[�V�����̓G�̍X�V
	void CircleUpdate(void);										// �T�[�N���z�u�̓G�̍X�V
	void DirectionUpdate(void);										// �����]���̓G
	void FollowUpdate(void);										// �Ǐ]���Ă���G

	void HitDamage(int nCount);										// �G�l�~�[�̃q�b�g��

	void NormalBullet(void);										// �ʏ�e
	void CurrentBullet(int nBulletNum);								// ���@�擾�e
	void ContinuousBullet(int nBulletNum);							// �A���e
	void ScaleUp(void);												// �g��
	void Appearance(void);											// ��������o��

	static CEnemy * Create(
		D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, 
		TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype);									// �G�l�~�[����

	static CEnemy * Current(
		D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
		TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype, int nTime);						// �Ǐ]�̓G����

	static CEnemy * Rotation(
		D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
		TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype, float fRadius, float fTheta);	// ���G�l�~�[����

	static CEnemy * Circle(
		D3DXVECTOR3 pos, D3DXVECTOR3 size,
		TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype, float fRadius, float fTheta);	// �T�[�N���̓G

	static CEnemy * Direction(
		D3DXVECTOR3 pos, D3DXVECTOR3 size,
		TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype, int nNumber);					// �����]���̓G

	static CEnemy*Follow(D3DXVECTOR3 pos, D3DXVECTOR3 size,								// �Ǐ]���Ă���G
		TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_ENEMY_TEXTURE];		// �e�N�X�`�����̃|�C���^
	D3DXVECTOR3 m_Pos;						// �ʒu
	D3DXVECTOR3 m_Move;						// �ړ�
	D3DXVECTOR3 m_Size;						// �T�C�Y
	int m_nLife;							// �̗�
	CLight *m_pLight;						// ���C�g�̃|�C���^
	D3DXVECTOR3 m_center;					// �Z���^�[
	COLOR_TYPE m_Ctype;						// �J���[�̎��
	ENEMY_TYPE m_Etype;						// �G�l�~�[�̎��
	ENEMY_STATE m_State;					// �G�l�~�[�̏��
	float m_fBulletFlame;					// �o���b�g�Ԋu�̃J�E���^�[
	int m_nEnemyCounter;					// �G�l�~�[����̃J�E���^�[
	int m_nStateCnt;						// �G�l�~�[�̏�ԃJ�E���^�[
	int m_nCountinueInter;					// �A���e�̊Ԋu
	int m_nContinueCnt;						// �A���e�̃J�E���g
	int m_nBulletNum;						// �e�̐�
	int m_nCounterBulletNum;				// �J�E���^�[�e�̐ݒ�
	int m_nFirstBulletFrame;				// ���e�̃t���[��
	int m_nThroughStopCnt;					// �~�܂��Ă���t���[��
	int m_nOutsideScreenCnt;				// �X�N���[���O�̃J�E���g
	int m_nDirection;						// �����]���̓G�̃i���o�[
	int m_nSubNumber;						// �e�N�X�`���̓����x�ύX�ϐ�
	int m_nSubNum;							// �����x�̐��l
	float m_fScale;							// �k���p�ϐ�
	float m_fScaleNum;						// �k����
	float m_fThroughBulletCnt;				// �^��������΂��G�̃o���b�g�J�E���g
	float m_fRadius;						// ���a
	float m_fAddRadius;						// ���a���Z��
	float m_fTheta;							// �p�x
	float m_fOmega;							// �p�x���Z��
	float m_fRadiusNum;						// ���a�̒l
	bool m_bSnakeSwitch;					// �W�O�U�O�ړ��̃t���O
	bool m_bTwo_Sides;						// �^�������e��łG�̃t���O
	bool m_bRotationScale;					// ���[�e�[�V�����̊g��t���O
	bool m_bFlashFlag;						// �t���b�V���̃t���O
	bool m_bFollowFlag;						// �Ǐ]�̓G�̃t���O
};

#endif