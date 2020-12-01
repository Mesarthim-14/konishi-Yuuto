//=============================================================================
//
// �G�l�~�[�̏����@[enemy.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "enemy.h"
#include "renderer.h"
#include "manager.h"
#include "bullet.h"
#include "ui.h"
#include "explosion.h"
#include "light.h"
#include "player.h"
#include "effect.h"
#include "score.h"
#include "game.h"
#include "shock.h"
#include "spark.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ENEMY_NORMAL_LIFE			(4)					// �ʏ�̃G�l�~�[�̃��C�t
#define ENEMY_OUTSIDE_FLAME			(120)				// �G����ʊO�ɂ����t���[��
#define ENEMY_SCORE					(200)				// �G�l�~�[�̃X�R�A
#define ENEMY_STATE_COUNT			(1)					// �G�l�~�[�̓������t���[��

#define BULLET_INTERVAL				(35.0f)				// ���ˊԊu���
#define BULLET_RANDOM_INTERVAL		(50)				// ���ˊԊu�̃����_��
#define CONTINUOUS_INTERVAL			(7)					// ���@�擾�e�̊Ԋu
#define TARGET_POS_AMPLITUDE		(1)					// �W�I�̍��W�U�ꕝ

#define NORMAL_COUNTER_BULLET_NUM	(5)					// �G�̔����e

#define OBLIQUE_POS_Y				(30.0f)				// �����̃t���O�ʒu
#define OBLIQUE_MOVE_Y				(3.0f)				// �c�̑���
#define OBLIQUE_ACCELERATION_X		(0.04f)				// X���W�̉�����
#define OBLIQUE_ACCELERATION_Y		(0.003f)			// Y���W�̉�����
#define OBLIQUE_MOVE_LIMIT			(7.0f)				// �����̐���

#define CURRENT_ENEMY_LIFE			(8)					// ���@�擾�e��łG�̗̑�
#define CURRENT_NUM_BULLET			(9)					// ���@�擾�e�̐�
#define CURRENT_COUNTER_BULLET_NUM	(10)				// ���@�擾�e��łG�̃J�E���^�[�e�̐�
#define CURRENT_MOVE				(1.5f)				// ���@�擾�G�̑���
#define CURRENT_BULLET_AMPLITUDE_X	(5)					// ���@�擾�e�̉��̐U�ꕝ
#define CURRENT_BULLET_AMPLITUDE_Y	(5)					// ���@�擾�e�̏c�̐U�ꕝ
#define CURRENT_FLAG_POS_Y			(50.0f)				// �����t���O�ʒu
#define CURRENT_MOVE_Y				(7.0f)				// ���@�擾�e��łG�̈ړ���
#define CURRENT_ACCELERATION_SPEED	(0.4f)				// ���@�擾�e��łG�̉�����
#define CURRENT_DECELERATION_SPEED	(0.25f)				// ���@�擾�e��łG�̌�����
#define CURRENT_RETURN_FLAME		(200)				// ���@�擾�e��łG�̖߂��Ă����t���[��
#define CURRENT_LAPSE_FLAME	(CURRENT_RETURN_FLAME+50)	// ���@�擾�e��łG�̓G�̏��ł̃t���[��

#define SNAKE_LIFE						(3)				// �W�O�U�O�ړ��G�̗̑�
#define SNAKE_MOVE_X					(0.7f)			// �W�O�U�O�ړ���X�ړ���
#define SNAKE_MOVE_Y					(1.5f)			// �W�O�U�O�ړ���Y�ړ���
#define SNAKE_SWITCH_TIME				(100)			// X�ړ��؂�ւ��̎���

#define COUNTINUE_BULLET_INTERVAL		(5)				// �A���e�̊Ԋu
#define THROUGH_ENEMY_LIFE				(7)				// �^�������e��łG�̗̑�
#define THROUGH_BULLET_NUM				(30)			// �^�������e��łG�̒e��
#define THROUGH_MOVE_X					(0.0f)			// �^�������e��łG�̈ړ���
#define THROUGH_MOVE_Y					(2.0f)			// �^�������e��łG�̈ړ���
#define THROUGH_ACCELERATION_X			(0.05f)			// �^�������e��łG�̉�����
#define THROUGH_ACCELERATION_Y			(0.04f)			// �^�������e��łG�̉�����
#define THROUGH_DECELERATION_X			(0.05f)			// �^�������e��łG�̌�����
#define THROUGH_DECELERATION_Y			(0.04f)			// �^�������e��łG�̌�����
#define THROUGH_STOP_TIME				(70)			// �^�������e��łG�̐Î~����
#define THROUGH_BULLET_SPEED_Y			(8.0f)			// �^�������e��łG�̒e�̑���
#define THROUGH_COUNTER_BULLET_NUM		(5)				// �^�������e��łG�̃J�E���^�[�e�̐�

#define ROTATION_LIFE					(5)				// ���G�̗̑�
#define ROTATION_COUNTER_BULLET_NUM		(5)				// ���G�̃J�E���^�[�e�̐�
#define ROTATION_SCALE_UP				(0.04f)			// ���G�̊g��

#define CIRCLE_COUNTER_BULLET_NUM		(5)				// �T�[�N���z�u�̓G�̃J�E���^�[�o���b�g��
#define CIRCLE_MOVE_Y					(4.0f)			// �T�[�N���z�u�̓G��Y���̈ړ���
#define CIRCLE_LIFE						(3)				// �T�[�N���z�u�̓G�̗̑�
#define CIRCLE_FLAME					(60)			// �T�[�N���z�u�̓G�̈ړ��ύX�t���[��

#define DIRECTION_MOVE_X				(7.0f)			// �����]��������G�̈ړ���
#define DIRECTION_MOVE_Y				(8.0f)			// �����]��������G�̈ړ���
#define DIRECTION_LIFE					(1)				// �����]��������G�̗̑�
#define DIRECTION_COUNTER_BULLET_NUM	(5)				// �����]������G�̃J�E���^�[�e��

#define FOLLOW_MOVE_X					(4.0f)			// �Ǐ]����G�̈ړ���
#define FOLLOW_MOVE_Y					(4.0f)			// �Ǐ]����G�̈ړ���
#define FOLLOW_LIFE						(1)				// �Ǐ]����G�̗̑�
#define FOLLOW_COUNTER_BULLET_NUM		(5)				// �Ǐ]����G�̃J�E���^�[�e��
#define FOLLOW_MOVE_TIME				(50)			//  �Ǐ]����G��������

#define WARNING_COLOR_MAX				(255)			// �����x�ύX�l�̍ő吔
#define COLOR_NUM						(4)				// �����x

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture[MAX_ENEMY_TEXTURE] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_center = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_fBulletFlame = 0.0f;
	m_Ctype = COLOR_TYPE_NONE;
	m_Etype = ENEMY_TYPE_NONE;
	m_State = ENEMY_STATE_NORMAL;
	m_nCountinueInter = 0;
	m_nBulletNum = 0;
	m_nStateCnt = 0;
	m_nCounterBulletNum = 0;
	m_bSnakeSwitch = false;
	m_bTwo_Sides = false;
	m_nFirstBulletFrame = 0;
	m_nThroughStopCnt = 0;
	m_pLight = NULL;
	m_fRadius = 0.0f;
	m_fAddRadius = 0.7f;
	m_fTheta = 0.0f;
	m_fOmega = 0.2f;
	m_nOutsideScreenCnt = 0;
	m_fThroughBulletCnt = 0.0f;
	m_fScale = 0.0f;
	m_fScaleNum = 0.0f;
	m_bRotationScale = false;
	m_nDirection = 0;
	m_bFlashFlag = false;
	m_nSubNumber = 255;
	m_nSubNum = 0;
	m_bFollowFlag = false;
	m_nEnemyCounter = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, 
	TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype)
{
	// ����������
	CEnemy *pEnemy = new CEnemy;
	if (pEnemy != NULL)
	{
		// ����������
		pEnemy->Init(pos, size, type);			// ���������
		pEnemy->SetSize(size);					// �T�C�Y�ݒ�
		pEnemy->SetEnemyType(Ctype, Etype);		// �G�l�~�[�̎��
		pEnemy->SetMove();						// �ړ��ʐݒ�
		pEnemy->SetLife();						// ���C�t������
		pEnemy->SetCounter();					// �J�E���^�[�e�̐ݒ�
	}

	// �G�l�~�[�̎��
	switch (Etype)
	{
	case ENEMY_TYPE_NORMAL:
	case ENEMY_TYPE_CURRENT:
	case ENEMY_TYPE_SNAKE:
	case ENEMY_TYPE_ROTATION:

		// �e�N�X�`���U�蕪��
		switch (Ctype)
		{
			// �����Ƃ�
		case COLOR_TYPE_WHITE:

			// �e�N�X�`���̐ݒ�
			pEnemy->BindTexture(m_apTexture[0]);

			 // ���̐���
			pEnemy->m_pLight = CLight::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(LIGHT_SIZE_X, LIGHT_SIZE_Y, 0.0f),
				TYPE_LIGHT, CLight::LIGHT_TYPE_WHITE);
			break;

			// �����Ƃ�
		case COLOR_TYPE_BLACK:

			// �e�N�X�`���̐ݒ�
			pEnemy->BindTexture(m_apTexture[1]);

			// ���̐���
			pEnemy->m_pLight = CLight::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(LIGHT_SIZE_X, LIGHT_SIZE_Y, 0.0f),
				TYPE_LIGHT, CLight::LIGHT_TYPE_BLACK);
			break;

		}
		break;

		// �^�������e��ł��Ă���G
	case ENEMY_TYPE_THROUGH:

		// ����������
		pEnemy->InitThrough(pos);

		// �F�̎��
		switch (Ctype)
		{
			// �����Ƃ�
		case COLOR_TYPE_WHITE:

			// �e�N�X�`���̐ݒ�
			pEnemy->BindTexture(m_apTexture[2]);

			// ���̐���
			pEnemy->m_pLight = CLight::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(LIGHT_SIZE_X, LIGHT_SIZE_Y, 0.0f),
				TYPE_LIGHT, CLight::LIGHT_TYPE_WHITE);
			break;

			// �����Ƃ�
		case COLOR_TYPE_BLACK:

			// �e�N�X�`���̐ݒ�
			pEnemy->BindTexture(m_apTexture[3]);

			// ���̐���
			pEnemy->m_pLight = CLight::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(LIGHT_SIZE_X, LIGHT_SIZE_Y, 0.0f),
				TYPE_LIGHT, CLight::LIGHT_TYPE_BLACK);
			break;
		}

		break;

	default:
		break;
	}

	return pEnemy;
}

//=============================================================================
// ���@�Ǐ]�e��łG
//=============================================================================
CEnemy * CEnemy::Current(
	D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR3 size, 
	TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype, 
	int nTime)
{
	// ����������
		CEnemy *pEnemy = new CEnemy;

	if (pEnemy != NULL)
	{
		// ����������
		pEnemy->Init(pos, size, type);			// ���������
		pEnemy->SetSize(size);					// �T�C�Y�̐ݒ�
		pEnemy->SetEnemyType(Ctype, Etype);		// �G�l�~�[�̎�ސݒ�
		pEnemy->SetMove();						// �ړ��ʐݒ�
		pEnemy->SetLife();						// ���C�t������
		pEnemy->SetCounter();					// �J�E���^�[�e�ݒ�
		pEnemy->SetFirstBulletTime(nTime);		// �ŏ��̔��˂̐ݒ�
	}

	// �G�l�~�[�̎��
	switch (Etype)
	{
	case ENEMY_TYPE_NORMAL:
	case ENEMY_TYPE_CURRENT:
	case ENEMY_TYPE_SNAKE:

		// �^�������e��œG�̏���
	case ENEMY_TYPE_THROUGH:

		// �e�N�X�`���U�蕪��
		switch (Ctype)
		{
			// �����G
		case COLOR_TYPE_WHITE:

			// �e�N�X�`���̐ݒ�
			pEnemy->BindTexture(m_apTexture[2]);

			// ���̐���
			pEnemy->m_pLight = CLight::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(LIGHT_SIZE_X, LIGHT_SIZE_Y, 0.0f),
				TYPE_LIGHT, CLight::LIGHT_TYPE_WHITE);
			break;

			// �����Ƃ�
		case COLOR_TYPE_BLACK:

			// �e�N�X�`���̐ݒ�
			pEnemy->BindTexture(m_apTexture[3]);

			// ���̐���
			pEnemy->m_pLight = CLight::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(LIGHT_SIZE_X, LIGHT_SIZE_Y, 0.0f),
				TYPE_LIGHT, CLight::LIGHT_TYPE_BLACK);
			break;
		}

		break;
	}

	return pEnemy;
}

//=============================================================================
// ���G
//=============================================================================
CEnemy * CEnemy::Rotation(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, 
	TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype, 
	float fRadius, float fTheta)
{
	// ����������
	CEnemy *pEnemy = new CEnemy;
	if (pEnemy != NULL)
	{
		// ����������
		pEnemy->Init(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), type);	// ���������
		pEnemy->SetSize(size);									// �T�C�Y�̐ݒ�
		pEnemy->SetEnemyType(Ctype, Etype);						// �G�̎�ސݒ�
		pEnemy->SetMove();										// �ړ��ʐݒ�
		pEnemy->SetLife();										// �̗͂̐ݒ�
		pEnemy->SetCounter();									// �J�E���^�[�e�̐ݒ�
		pEnemy->SetRotation(fRadius, fTheta);					// ��]���
		pEnemy->m_fScaleNum = ROTATION_SCALE_UP;				// �傫���̒l�̐ݒ�

		// �F�̎��
		switch (Ctype)
		{
			// �����G�̎�
		case COLOR_TYPE_WHITE:

			// �e�N�X�`���̐ݒ�
			pEnemy->BindTexture(m_apTexture[0]);

			// ���̐���
			pEnemy->m_pLight = CLight::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(LIGHT_SIZE_X - 20.0f, LIGHT_SIZE_Y - 20.0f, 0.0f),
				TYPE_LIGHT, CLight::LIGHT_TYPE_WHITE);
			break;

			// �����Ƃ�
		case COLOR_TYPE_BLACK:

			// �e�N�X�`���̐ݒ�
			pEnemy->BindTexture(m_apTexture[1]);

			// ���̐���
			pEnemy->m_pLight = CLight::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(LIGHT_SIZE_X - 20.0f, LIGHT_SIZE_Y - 20.0f, 0.0f),
				TYPE_LIGHT, CLight::LIGHT_TYPE_BLACK);
			break;
		}
	}

	return pEnemy;
}

//=============================================================================
// �T�[�N���̔z�u�̓G
//=============================================================================
CEnemy * CEnemy::Circle(D3DXVECTOR3 pos, D3DXVECTOR3 size, 
	TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype, float fRadius, float fTheta)
{
	// �������m��
	CEnemy *pEnemy = new CEnemy;

	if (pEnemy != NULL)
	{
		// ����������
		pEnemy->Init(pos, size, type);			// ���������
		pEnemy->SetSize(size);					// �T�C�Y�̐ݒ�
		pEnemy->SetEnemyType(Ctype, Etype);		// �G�̎�ނ̏��
		pEnemy->SetMove();						// �ړ��ʂ̐ݒ�
		pEnemy->SetLife();						// ���C�t������
		pEnemy->SetCounter();					// �J�E���^�[�e�̐ݒ�
		pEnemy->SetRotation(fRadius, fTheta);	// ��]�̐ݒ�

		if (pos.x <= SCREEN_WIDTH / 2)
		{
			pEnemy->m_center = D3DXVECTOR3(WALL_SIZE_X, CIRCLE_INITIAL_Y, 0.0f);
		}
		else
		{
			pEnemy->m_center = D3DXVECTOR3(SCREEN_WIDTH - WALL_SIZE_X, CIRCLE_INITIAL_Y, 0.0f);
		}

		// �F�̐ݒ�
		switch (Ctype)
		{
			// �����Ƃ�
		case COLOR_TYPE_WHITE:

			// �e�N�X�`���̐ݒ�
			pEnemy->BindTexture(m_apTexture[0]);

			// ���̐���
			pEnemy->m_pLight = CLight::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(LIGHT_SIZE_X , LIGHT_SIZE_Y , 0.0f),
				TYPE_LIGHT, CLight::LIGHT_TYPE_WHITE);
			break;

			// �����Ƃ�
		case COLOR_TYPE_BLACK:

			// �e�N�X�`���̐ݒ�
			pEnemy->BindTexture(m_apTexture[1]);

			// ���̐���
			pEnemy->m_pLight = CLight::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(LIGHT_SIZE_X , LIGHT_SIZE_Y , 0.0f),
				TYPE_LIGHT, CLight::LIGHT_TYPE_BLACK);
			break;
		}
	}
	return pEnemy;
}

//=============================================================================
// �����]���̓G
//=============================================================================
CEnemy * CEnemy::Direction(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype, int nNumber)
{
	// ����������
	CEnemy *pEnemy = new CEnemy;

	if (pEnemy != NULL)
	{
		// �G�l�~�[�̏��ݒ�
		pEnemy->Init(pos, size, type);			// ���������
		pEnemy->SetSize(size);					// �T�C�Y�ݒ�
		pEnemy->SetEnemyType(Ctype, Etype);		// �G�l�~�[�̃^�C�v���
		pEnemy->SetMove();						// �ړ��ʐݒ�
		pEnemy->SetLife();						// ���C�t������
		pEnemy->SetCounter();					// �J�E���^�[�e�̐ݒ�
		pEnemy->m_nDirection = nNumber;			// �ԍ��̐ݒ�

		// �e�N�X�`���U�蕪��
		switch (Ctype)
		{
			// �����Ƃ�
		case COLOR_TYPE_WHITE:

			// �e�N�X�`���̐ݒ�
			pEnemy->BindTexture(m_apTexture[2]);

			// ���̐���
			pEnemy->m_pLight = CLight::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(LIGHT_SIZE_X, LIGHT_SIZE_Y, 0.0f),
				TYPE_LIGHT, CLight::LIGHT_TYPE_WHITE);
			break;

			// �����Ƃ�
		case COLOR_TYPE_BLACK:
			pEnemy->BindTexture(m_apTexture[3]);

			// ���̐���
			pEnemy->m_pLight = CLight::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(LIGHT_SIZE_X, LIGHT_SIZE_Y, 0.0f),
				TYPE_LIGHT, CLight::LIGHT_TYPE_BLACK);
			break;
		}
	}

	return pEnemy;
}

//=============================================================================
// �Ǐ]���Ă���G
//=============================================================================
CEnemy * CEnemy::Follow(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype)
{
	// �������m��
	CEnemy *pEnemy = new CEnemy;

	if (pEnemy != NULL)
	{
		// ����������
		pEnemy->Init(pos, size, type);			// ����������
		pEnemy->SetSize(size);					// �T�C�Y�ݒ�
		pEnemy->SetEnemyType(Ctype, Etype);		// �G�l�~�[�̎�ސݒ�
		pEnemy->m_nSubNum = COLOR_NUM;			// �J���[�ύX�̒l
		pEnemy->SetLife();						// ���C�t������
		pEnemy->SetCounter();					// �J�E���^�[�e�̐ݒ�
		pEnemy->TransparentInit();				// �����ɂ�����
	}
		// �F�̎��
		switch (Ctype)
		{
			// �����Ƃ�
		case COLOR_TYPE_WHITE:

			//�@�e�N�X�`���̐ݒ�
			pEnemy->BindTexture(m_apTexture[0]);

			// ���̐���
			pEnemy->m_pLight = CLight::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(LIGHT_SIZE_X, LIGHT_SIZE_Y, 0.0f),
				TYPE_LIGHT, CLight::LIGHT_TYPE_WHITE);
			break;

			// �����Ƃ�
		case COLOR_TYPE_BLACK:

			// �e�N�X�`���̐ݒ�
			pEnemy->BindTexture(m_apTexture[1]);

			// ���̐���
			pEnemy->m_pLight = CLight::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(LIGHT_SIZE_X, LIGHT_SIZE_Y, 0.0f),
				TYPE_LIGHT, CLight::LIGHT_TYPE_BLACK);
			break;
		}

	return pEnemy;
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CEnemy::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/enemy_q (1).png",
		&m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/enemy_q (3).png",
		&m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/BlueEnemy.png",
		&m_apTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/RedEnemy.png",
		&m_apTexture[3]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CEnemy::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_ENEMY_TEXTURE; nCount++)
	{
		// �e�N�X�`���̊J��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// �o���b�g�Ԋu������
	m_fBulletFlame = BULLET_INTERVAL + (float)(rand() % BULLET_RANDOM_INTERVAL);

	// ����������
	CScene2D::Init(pos, size, type);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemy::Uninit(void)
{
	// 2D�|���S���I������
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemy::Update(void)
{
	// �o���b�g�̃t���[��
	m_fBulletFlame--;

	// 2D�|���S���X�V����
	CScene2D::Update();

	// ���W�X�V
	m_Pos = GetPosition();

	// �ړ��̍X�V
	m_Pos += m_Move;
	
	if (m_pLight != NULL)
	{
		// ���C�g�̈ړ�
		m_pLight->SetPosition(m_Pos);
	}

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �G�l�~�[�̏��
	switch (m_State)
	{
		// �ʏ펞
	case ENEMY_STATE_NORMAL:
		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �������_�̐F	�����x255
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�����_�̐F	�����x255
		break;

		// �_���[�W��
	case ENEMY_STATE_DAMAGE:
		
		// ��ԃJ�E���^�[
		m_nStateCnt++;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);	// �������_�̐F	�����x255
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);	// �E�����_�̐F	�����x255

		// ���Œʏ��Ԃɖ߂�
		if (m_nStateCnt >= ENEMY_STATE_COUNT)
		{
			m_State = ENEMY_STATE_NORMAL;
			m_nStateCnt = 0;
		}
		break;
	}

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();

	// �G�l�~�[�̎��
	switch (m_Etype)
	{
		// �ʏ펞
	case ENEMY_TYPE_NORMAL:

		// �΂߈ړ�����
		ObliqueUpdate();
		break;

		// ���@�擾�e��łG
	case ENEMY_TYPE_CURRENT:

		// ���@�擾�̓G
		CurrentUpdate();

		// �e�̔���
		if (m_fBulletFlame <= 0.0f)
		{
			// �A���e����
			CurrentBullet(CURRENT_NUM_BULLET);
		}
		break;

		// �W�O�U�O�̓G
	case ENEMY_TYPE_SNAKE:
		// �W�O�U�O�ړ�
		SnakeUpdate();
		break;

		// �^�������ł��Ă���G
	case ENEMY_TYPE_THROUGH:
		// �X�V����
		ThroughUpdate();
		break;

		// ���G
	case ENEMY_TYPE_ROTATION:
		// �X�V����
		RotationUpdate();
		break;

		// �T�[�N���z�u�̓G
	case ENEMY_TYPE_CIRCLE:
		CircleUpdate();
		break;

		// �����]������G
	case ENEMY_TYPE_DIRECTION:
		DirectionUpdate();
		break;

		// �Ǐ]
	case ENEMY_TYPE_FOLLOW:
		FollowUpdate();
		break;
	}

	// ���W��n��
	SetPosition(m_Pos);

	// �v���C���[�Ƃ̓����蔻��
	Collision();

	// �G����ʊO�ɏo����
	if (m_Pos.x < 0.0f ||
		m_Pos.x > SCREEN_WIDTH - WALL_SIZE_X ||
		m_Pos.y < 0.0f ||
		m_Pos.y > SCREEN_HEIGHT)
	{
		// ��ʊO���Z
		m_nOutsideScreenCnt++;
	}

	// ��ʊO��100�t���[��������
	if (m_nOutsideScreenCnt >= ENEMY_OUTSIDE_FLAME)
	{
		m_nLife = 0;
	}

	// ���C�t��0��������
	if (m_nLife <= 0)
	{
		// ���C�g�폜
		m_pLight->Uninit();

		// �G�l�~�[�폜
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEnemy::Draw(void)
{
	// 2D�|���S���`�揈��
	CScene2D::Draw();
}

//=============================================================================
// �G�l�~�[�q�b�g��
//=============================================================================
void CEnemy::HitDamage(int nCount)
{
	// �G����ʊO�ɏo����
	if (m_Pos.x < 0.0f ||
		m_Pos.x > SCREEN_WIDTH - WALL_SIZE_X ||
		m_Pos.y < 0.0f ||
		m_Pos.y > SCREEN_HEIGHT)
	{
	}
	else
	{
		// �̗͌��Z
		m_nLife -= nCount;

		// ���C�t��0�ɂȂ�����
		if (m_nLife <= 0)
		{
			// �T�E���h�ݒ�
			CSound *pSound = NULL;
			pSound = CManager::GetSound();
			pSound->Play(CSound::SOUND_LABEL_EXPLOSION);

			// �F�̎��
			switch (m_Ctype)
			{
				// �����Ƃ�
			case COLOR_TYPE_WHITE:

				for (int nCount = 0; nCount < SPARK_NUM; nCount++)
				{
					// �ΉԂ̏���
					CSpark::Create(m_Pos,
						D3DXVECTOR3(SPARK_SIZE_X, SPARK_SIZE_Y, 0.0f),
						TYPE_EFFECT, SPARK_ANGLE, SPARK_BASE_ANGLE, SPARK_DISTANCE, SPARK_LIFE);
				}
				break;

				// �����Ƃ�
			case COLOR_TYPE_BLACK:

				for (int nCount = 0; nCount < SPARK_NUM; nCount++)
				{
					// �ΉԂ̏���
					CSpark::Create(m_Pos,
						D3DXVECTOR3(SPARK_SIZE_X, SPARK_SIZE_Y, 0.0f),
						TYPE_EFFECT, SPARK_ANGLE, SPARK_BASE_ANGLE, SPARK_DISTANCE, SPARK_LIFE);
				}
				break;

			default:
				break;
			}

			// �X�R�A�����Z
			CScore *pScore = CGame::GetScore();
			pScore->SetScore(ENEMY_SCORE);

			// �J�E���^�[�e�̏���
			for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
			{
				CScene *pScene = NULL;

				if (pScene == NULL)
				{
					// �������m��
					pScene = CScene::GetScene(nCount);

					// �������̃L���X�g
					CScene2D *pScene2D = (CScene2D*)pScene;

					if (pScene2D != NULL)
					{
						// �^�[�Q�b�g�̏��m��
						CScene::TYPE type = pScene2D->GetType();

						// �e��������
						if (type == TYPE_BULLET)
						{
							// �e�̐F�擾
							CBullet *pBullet = (CBullet*)pScene2D;
							CBullet::BULLET_COLOR Ctype = pBullet->GetCtype();

							// �F�̎��
							switch (Ctype)
							{
								// �����Ƃ�
							case CBullet::BULLET_COLOR_BLACK:

								// ����������������
								if (m_Ctype == COLOR_TYPE_BLACK)
								{
									// �J�E���^�[�e����
									CBullet::CounterAttack(
										m_Pos, D3DXVECTOR3(COUNTER_BULLET_SIZE_X, COUNTER_BULLET_SIZE_Y, 0.0f),
										TYPE_BULLET, CBullet::BULLET_TYPE_ENEMY,
										CBullet::BULLET_COLOR_BLACK, CBullet::BULLET_CATEGORY_COUNTER,
										1000, m_nCounterBulletNum);
								}
								break;

								// �����Ƃ�
							case CBullet::BULLET_COLOR_WHITE:

								// �������邾������
								if (m_Ctype == COLOR_TYPE_WHITE)
								{
									// �J�E���^�[�e����
									CBullet::CounterAttack(
										m_Pos, D3DXVECTOR3(COUNTER_BULLET_SIZE_X, COUNTER_BULLET_SIZE_Y, 0.0f),
										TYPE_BULLET, CBullet::BULLET_TYPE_ENEMY,
										CBullet::BULLET_COLOR_WHITE, CBullet::BULLET_CATEGORY_COUNTER,
										1000, m_nCounterBulletNum);
								}
								break;
							}
							break;
						}
					}
				}
			}
		}
		else
		{
			// �_���[�W��Ԃɂ���
			m_State = ENEMY_STATE_DAMAGE;
		}
	}
}

//=============================================================================
// ���W�ݒ�
//=============================================================================
void CEnemy::SetPos(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//=============================================================================
// �G�l�~�[�T�C�Y�ݒ�
//=============================================================================
void CEnemy::SetSize(D3DXVECTOR3 size)
{
	m_Size = size;
}

//=============================================================================
// ���e�̔����t���[���ݒ�
//=============================================================================
void CEnemy::SetFirstBulletTime(int nTime)
{
	m_nFirstBulletFrame = nTime;
}

//=============================================================================
// �p�x�̐ݒ�
//=============================================================================
void CEnemy::SetRotation(float fRadius, float fTheta)
{
	m_fTheta = fTheta;
	m_fRadius = fRadius;
	m_fRadiusNum = fRadius;
}

//=============================================================================
// �G�l�~�[�̃^�C�v�ݒ�
//=============================================================================
void CEnemy::SetEnemyType(COLOR_TYPE Ctype, ENEMY_TYPE Etype)
{
	m_Ctype = Ctype;
	m_Etype = Etype;
}

//=============================================================================
// �G�l�~�[�̃��C�t�ݒ�
//=============================================================================
void CEnemy::SetLife(void)
{
	switch (m_Etype)
	{
	case ENEMY_TYPE_NORMAL:
		m_nLife = ENEMY_NORMAL_LIFE;
		break;

	case ENEMY_TYPE_SNAKE:
		m_nLife = SNAKE_LIFE;
		break;

		// ���@�擾�e��łG
	case ENEMY_TYPE_CURRENT:
		m_nLife = CURRENT_ENEMY_LIFE;
		break;

	case ENEMY_TYPE_THROUGH:
		m_nLife = THROUGH_ENEMY_LIFE;
		break;

	case ENEMY_TYPE_ROTATION:
		m_nLife = ROTATION_LIFE;
		break;

	case ENEMY_TYPE_CIRCLE:
		m_nLife = CIRCLE_LIFE;
		break;

	case ENEMY_TYPE_DIRECTION:
		m_nLife = DIRECTION_LIFE;
		break;

	case ENEMY_TYPE_FOLLOW:
		m_nLife = FOLLOW_LIFE;
		break;
	default:
		break;
	}
}

//=============================================================================
// �΂߈ړ�����
//=============================================================================
void CEnemy::SetMove(void)
{
	// �ړ��ʏ����ݒ�
	switch (m_Etype)
	{
		// �ʏ�̓G
	case ENEMY_TYPE_NORMAL:
		m_Move = D3DXVECTOR3(0.0f, OBLIQUE_MOVE_Y, 0.0f);
		break;

		// ���@�擾�e��łG
	case ENEMY_TYPE_CURRENT:
		m_Move = D3DXVECTOR3(0.0f, CURRENT_MOVE_Y, 0.0f);
		break;

		// �W�O�U�N�̓G
	case ENEMY_TYPE_SNAKE:
		m_Move = D3DXVECTOR3(0.0f, SNAKE_MOVE_Y, 0.0f);
			break;

			// �e��łG
	case ENEMY_TYPE_THROUGH:
		m_Move = D3DXVECTOR3(-0.001f, THROUGH_MOVE_Y, 0.0f);
		break;

		// ����Ă���G
	case ENEMY_TYPE_ROTATION:
		m_fOmega = 2.0f;
		break;

		// �T�[�N���z�u�̓G
	case ENEMY_TYPE_CIRCLE:
		m_Move = D3DXVECTOR3(0.0f, CIRCLE_MOVE_Y, 0.0f);
		m_fOmega = 0.2f;
		break;

		// �����]������G
	case ENEMY_TYPE_DIRECTION:
		m_Move = D3DXVECTOR3(0.0f, DIRECTION_MOVE_Y, 0.0f);
		break;
	default:
		break;
	}
}

//=============================================================================
// �J�E���^�[�e�̐��̐ݒ�
//=============================================================================
void CEnemy::SetCounter(void)
{
	// �ړ��ʏ����ݒ�
	switch (m_Etype)
	{
		// �ʏ�̓G
	case ENEMY_TYPE_NORMAL:
	case ENEMY_TYPE_SNAKE:
		m_nCounterBulletNum = NORMAL_COUNTER_BULLET_NUM;
		break;

		// ���@�擾�e��łG
	case ENEMY_TYPE_CURRENT:
		m_nCounterBulletNum = CURRENT_COUNTER_BULLET_NUM;
		break;

	case ENEMY_TYPE_THROUGH:
		m_nCounterBulletNum = THROUGH_COUNTER_BULLET_NUM;
		break;

	case ENEMY_TYPE_ROTATION:
		m_nCounterBulletNum = ROTATION_COUNTER_BULLET_NUM;
		break;
	case ENEMY_TYPE_CIRCLE:
		m_nCounterBulletNum = CIRCLE_COUNTER_BULLET_NUM;
		break;

		// �����]������G
	case ENEMY_TYPE_DIRECTION:
		m_nCounterBulletNum = DIRECTION_COUNTER_BULLET_NUM;
		break;

		// �����]������G
	case ENEMY_TYPE_FOLLOW:
		m_nCounterBulletNum = FOLLOW_COUNTER_BULLET_NUM;
		break;
	}
}

//=============================================================================
// �΂߈ړ��G�X�V����
//=============================================================================
void CEnemy::ObliqueUpdate(void)
{
	switch (m_Ctype)
	{
		// �����Ƃ�
	case COLOR_TYPE_WHITE:

		// Y���W�����ȏ�ɍs������
		if (m_Pos.y > OBLIQUE_POS_Y)
		{
			// ����������
			m_Move.x += OBLIQUE_ACCELERATION_X;
			m_Move.y += OBLIQUE_ACCELERATION_Y;
		}
		break;

		// �����Ƃ�
	case COLOR_TYPE_BLACK:

		// Y���W�����ȏ�ɍs������
		if (m_Pos.y > OBLIQUE_POS_Y)
		{
			// ����������
			m_Move.x -= OBLIQUE_ACCELERATION_X;
			m_Move.y += OBLIQUE_ACCELERATION_Y;
		}
		break;
	}

	// ����ȏ�ړ��ʂ𑝂₳�Ȃ�
	if (m_Move.x >= OBLIQUE_MOVE_LIMIT)
	{
		m_Move.x = OBLIQUE_MOVE_LIMIT;
	}
	if (m_Move.y >= OBLIQUE_MOVE_LIMIT)
	{
		m_Move.y = OBLIQUE_MOVE_LIMIT;
	}
}

//=============================================================================
// ���@�擾�e��łG�̍X�V
//=============================================================================
void CEnemy::CurrentUpdate(void)
{
	// �t���[���J�E���g
	m_nEnemyCounter++;

	// Y���W�����ȏ�ɍs������
	if (m_nEnemyCounter >= 5)
	{
		// ����
		m_Move.y -= CURRENT_DECELERATION_SPEED;
	}

	// ���ʂɂȂ�����
	if (m_Move.y <= 0.0f && m_nEnemyCounter <= CURRENT_RETURN_FLAME)
	{
		m_Move.y = 0.0f;
	}

	if (m_nEnemyCounter >= CURRENT_RETURN_FLAME)
	{
		// ��ʊO�֖߂鏈��
		m_Move.y -= CURRENT_ACCELERATION_SPEED;
	}

	if (m_nEnemyCounter >= CURRENT_LAPSE_FLAME)
	{
		// ����
		m_nLife = 0;
	}
}

//=============================================================================
// �W�O�U�O�ړ��X�V
//=============================================================================
void CEnemy::SnakeUpdate(void)
{
	// Y���W�����ȏ�ɍs������
	if (m_Pos.y > OBLIQUE_POS_Y)
	{
		m_nEnemyCounter++;

		if (m_bSnakeSwitch == false)
		{
			m_Move = D3DXVECTOR3(SNAKE_MOVE_X, SNAKE_MOVE_Y, 0.0f);
			m_bSnakeSwitch = true;
		}
		if (m_nEnemyCounter % SNAKE_SWITCH_TIME == 0)
		{
			m_Move.x *= -1;
		}
	}
}

//=============================================================================
// ���i�̓G�̍X�V
//=============================================================================
void CEnemy::ThroughUpdate(void)
{
	m_fThroughBulletCnt--;

	// �����e�̔���
	if (m_fThroughBulletCnt <= 0)
	{
		ContinuousBullet(THROUGH_BULLET_NUM);
	}

	if (m_bTwo_Sides == false)
	{
		// �o��������
		if (m_Pos.x >= SCREEN_WIDTH / 2)
		{
			// ���̈ړ��𑝂₷
			m_Move.x -= THROUGH_ACCELERATION_X;
			m_Move.y += THROUGH_ACCELERATION_Y;
		}
		else
		{	// �������z������
			// �ړ������炷
			m_Move.x += THROUGH_DECELERATION_X;
			m_Move.y -= THROUGH_DECELERATION_Y;
		}
		if (m_Move.x >= 0.0f)
		{
			m_nThroughStopCnt++;
			m_Move.x = 0.0f;
		}

		if (m_Move.y <= 0.0f)
		{
			m_Move.y = 0.0f;
		}

		// �Î~���Ԃ��߂�����
		if (m_nThroughStopCnt >= THROUGH_STOP_TIME)
		{
			m_bTwo_Sides = true;
			m_nThroughStopCnt = 0;
		}
	}
	else
	{
		// �o��������
		if (m_Pos.x <= SCREEN_WIDTH / 2)
		{
			// ���̈ړ��𑝂₷
			m_Move.x += THROUGH_ACCELERATION_X;
			m_Move.y += THROUGH_DECELERATION_Y;
		}
		else
		{	// �������z������
			// �ړ������炷
			m_Move.x -= THROUGH_DECELERATION_X;
			m_Move.y -= THROUGH_DECELERATION_Y;
		}

		if (m_Move.x <= 0.0f)
		{
			m_nThroughStopCnt++;
			m_Move.x = 0.0f;
		}
		if (m_Move.y <= 0.0f)
		{
			m_Move.y = 0.0f;
		}

		// �Î~���Ԃ��߂�����
		if (m_nThroughStopCnt >= THROUGH_STOP_TIME)
		{
			m_bTwo_Sides = false;
			m_nThroughStopCnt = 0;
		}
	}

	// �w�肳�ꂽ�e���o���甭�˃t���[����ݒ�
	if (m_nContinueCnt >= THROUGH_BULLET_NUM)
	{
		m_fThroughBulletCnt = THROUGH_STOP_TIME;
		m_nContinueCnt = 0;
	}
}

//=============================================================================
// ��]����G
//=============================================================================
void CEnemy::RotationUpdate(void)
{
	// ���S��ݒ�
	D3DXVECTOR3 Center = D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f);
	
	// �g��
	ScaleUp();

	// ���a���Z
	m_fRadius -= m_fAddRadius;

	// �p�x���Z
	m_fTheta += m_fOmega;

	if (m_fRadius <= m_fRadiusNum - 190.0f)
	{
		m_fAddRadius *= -1.2f;
	}

	// ���W
	m_Pos = D3DXVECTOR3(Center.x + m_fRadius * cosf(D3DXToRadian(m_fTheta)), 
		Center.y + m_fRadius * sinf(D3DXToRadian(m_fTheta)), 0.0f);
}

//=============================================================================
// �T�[�N���z�u�̓G�̍X�V
//=============================================================================
void CEnemy::CircleUpdate(void)
{
	m_nEnemyCounter++;

	// ������荶��������
	if (m_center.x <= SCREEN_WIDTH / 2)
	{
		// ���]����^�C�~���O
		if (m_nEnemyCounter <= CIRCLE_FLAME)
		{
			if (m_Move.x <= 2.0f)
			{
				m_Move.x += 0.1f;
			}
			else
			{
				m_Move.x = 2.0f;
			}
		}
		else
		{
			if (m_Move.x >= -2.0f)
			{
				m_Move.x -= 0.05f;
			}
			else
			{
				m_Move.x = -2.0f;
			}
		}

		// ���S�̈ړ�
		m_center += m_Move;

		// �p�x���Z
		m_fTheta += m_fOmega;

		// ���W
		m_Pos = D3DXVECTOR3(m_center.x + m_fRadius * cosf(D3DXToRadian(m_fTheta)),
			m_center.y + m_fRadius * sinf(D3DXToRadian(m_fTheta)), 0.0f);
	}
	else
	{
		// ���]����^�C�~���O
		if (m_nEnemyCounter <= CIRCLE_FLAME)
		{
			if (m_Move.x >= -2.0f)
			{
				m_Move.x -= 0.1f;
			}
			else
			{
				m_Move.x = -2.0f;
			}
		}
		else
		{
			if (m_Move.x <= 2.0f)
			{
				m_Move.x += 0.05f;
			}
			else
			{
				m_Move.x = +2.0f;
			}
		}

		// ���S�̈ړ�
		m_center += m_Move;

		// �p�x���Z
		m_fTheta -= m_fOmega;

		// ���W
		m_Pos = D3DXVECTOR3(m_center.x + m_fRadius * cosf(D3DXToRadian(m_fTheta)),
			m_center.y + m_fRadius * sinf(D3DXToRadian(m_fTheta)), 0.0f);
	}
}

//=============================================================================
// �����]������G�̍X�V����
//=============================================================================
void CEnemy::DirectionUpdate(void)
{
	// �v���C���[�̏����擾
	CPlayer *pPlayer = CGame::GetPlayer();
	
	// ���W�擾
	D3DXVECTOR3 Target = pPlayer->GetPosition();

	// �v���C���[�Ɠ��������ɂȂ�����
	if (m_Pos.y >= Target.y)
	{
		// ��ʔ�����荶�ɂ�����
		if (m_Pos.x <= SCREEN_WIDTH /2)
		{
			// ���Ɉړ�����
			m_Move = D3DXVECTOR3(5.0f, 0.0f, 0.0f);
		}
		else
		{
			// ���Ɉړ�����
			m_Move = D3DXVECTOR3(-5.0f, 0.0f, 0.0f);
		}
	}

	if (m_nDirection == 0)
	{
		if (m_Pos.x >= SCREEN_WIDTH / 2)
		{
			// ����
			m_nLife = 0;
		}
	}
	else if (m_nDirection == 1)
	{
		if (m_Pos.x <= SCREEN_WIDTH / 2)
		{
			// ����
			m_nLife = 0;
		}
	}
}

//=============================================================================
// �Ǐ]���Ă���G
//=============================================================================
void CEnemy::FollowUpdate(void)
{
	if (m_bFlashFlag == false)
	{
		// �����x�̕ύX
		Appearance();
	}

	if (m_bFollowFlag == false)
	{
		m_nEnemyCounter++;

		if (m_nEnemyCounter >= 50)
		{
			m_bFollowFlag = true;

			// �v���C���[�����擾
			CPlayer *pPlayer = CGame::GetPlayer();
			D3DXVECTOR3 Ppos = pPlayer->GetPosition();

			//���@���擾����
			float fPposx = Ppos.x, fPposy = Ppos.y;		// ���@�̍��W
			float fEposx = m_Pos.x, fEposy = m_Pos.y;	// �G�̍��W
			float fAngle;								// �p�x

			//�p�x�����߂�
			fAngle = atan2f((fEposx - fPposx), (fEposy - fPposy));

			// �����ȓG�̈ړ�
			D3DXVECTOR3 FollowMove = D3DXVECTOR3(
				(sinf(fAngle)*-FOLLOW_MOVE_X),
				cosf(fAngle)*-FOLLOW_MOVE_Y, 0.0f);

			// �ړ��ʂ̐ݒ�
			m_Move = FollowMove;
		}
	}
}

//=============================================================================
// �ʏ�e����
//=============================================================================
void CEnemy::NormalBullet(void)
{
	// �F�̎��
	switch (m_Ctype)
	{
		// �����Ƃ�
	case COLOR_TYPE_WHITE:
		CBullet::Create(D3DXVECTOR3(m_Pos.x + 0.0f, m_Pos.y + 40.0f, 0.0f),
			D3DXVECTOR3(0.0f, 5.0f, 0.0f),
			D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f),
			TYPE_BULLET, CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_COLOR_WHITE,
			1000);
		m_fBulletFlame = BULLET_INTERVAL + (float)(rand() % BULLET_RANDOM_INTERVAL);
		break;

		// �����Ƃ�
	case COLOR_TYPE_BLACK:
		CBullet::Create(D3DXVECTOR3(m_Pos.x + 0.0f, m_Pos.y + 40.0f, 0.0f),
			D3DXVECTOR3(0.0f, 5.0f, 0.0f),
			D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f),
			TYPE_BULLET, CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_COLOR_BLACK,
			1000);

		// �e��łt���[��
		m_fBulletFlame = BULLET_INTERVAL + (float)(rand() % BULLET_RANDOM_INTERVAL);
		break;
	}
}

//=============================================================================
// ���@�擾����
//=============================================================================
void CEnemy::CurrentBullet(int nBulletNum)
{
	// ���˃t���[�����Z
	m_nCountinueInter++;

	// �ݒ肵�����e�t���[���ɒB������
	if (m_nCountinueInter >= m_nFirstBulletFrame)
	{
		// �J�E���^�[�̑���
		if (m_nCountinueInter % CONTINUOUS_INTERVAL == 0)
		{
			// �F�̎��7
			switch (m_Ctype)
			{
				// �����Ƃ�
				case COLOR_TYPE_WHITE:
				{
					// ���݂̈ʒu���擾
					CPlayer *pPlayer = CGame::GetPlayer();
					D3DXVECTOR3 Target = pPlayer->GetPosition();

					// ���@�擾�e�𔭎�
					CBullet::CurrentAttack(D3DXVECTOR3(
						m_Pos.x + (float)(rand() % CURRENT_BULLET_AMPLITUDE_X - rand() % CURRENT_BULLET_AMPLITUDE_X),
						m_Pos.y + 40.0f + (float)(rand() % CURRENT_BULLET_AMPLITUDE_Y - rand() % CURRENT_BULLET_AMPLITUDE_Y), 0.0f),
						D3DXVECTOR3(Target.x + (float)(rand() % TARGET_POS_AMPLITUDE - rand() % TARGET_POS_AMPLITUDE), Target.y, 0.0f),
						D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f),
						TYPE_BULLET, CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_COLOR_WHITE,
						1000);

					// �e�̃J�E���g
					m_nBulletNum++;
					break;
				}

				// �����e�̎�
				case COLOR_TYPE_BLACK:
				{
					// ���@�̍��W�擾
					CPlayer *pPlayer = CGame::GetPlayer();
					D3DXVECTOR3 Target = pPlayer->GetPosition();

					// ���@�擾�e�𔭎�
					CBullet::CurrentAttack(D3DXVECTOR3(
						m_Pos.x + (float)(rand() % CURRENT_BULLET_AMPLITUDE_X - rand() % CURRENT_BULLET_AMPLITUDE_X),
						m_Pos.y + 40.0f + (float)(rand() % CURRENT_BULLET_AMPLITUDE_Y - rand() % CURRENT_BULLET_AMPLITUDE_Y), 0.0f),
						D3DXVECTOR3(Target.x + (float)(rand() % TARGET_POS_AMPLITUDE - rand() % TARGET_POS_AMPLITUDE), Target.y, 0.0f),
						D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f),
						TYPE_BULLET, CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_COLOR_BLACK,
						1000);

					// �e�̃J�E���g
					m_nBulletNum++;
					break;
				}
			}
		}

		// ���ʒe���o������
		if (m_nBulletNum >= nBulletNum)
		{
			// �e�̔����t���[����߂�
			m_fBulletFlame = 50000.0f;
		}
	}
}

//=============================================================================
// �A���e����
//=============================================================================
void CEnemy::ContinuousBullet(int nBulletNum)
{
	// ���˃t���[�����Z
	m_nCountinueInter++;

	// �A���e�̔��ˊԊu
	if (m_nCountinueInter % COUNTINUE_BULLET_INTERVAL == 0)
	{
		// �F�̎��
		switch (m_Ctype)
		{
			// �����Ƃ�
		case COLOR_TYPE_WHITE:
			CBullet::Create(D3DXVECTOR3(m_Pos.x + 0.0f, m_Pos.y + 40.0f, 0.0f),
				D3DXVECTOR3((float)(rand() % 2 - rand() % 2), THROUGH_BULLET_SPEED_Y, 0.0f),
				D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f),
				TYPE_BULLET, CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_COLOR_WHITE,
				1000);
			break;

			// �����Ƃ�
		case COLOR_TYPE_BLACK:
			CBullet::Create(D3DXVECTOR3(m_Pos.x + 0.0f, m_Pos.y + 40.0f, 0.0f),
				D3DXVECTOR3((float)(rand() % 2 - rand() % 2), THROUGH_BULLET_SPEED_Y, 0.0f),
				D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f),
				TYPE_BULLET, CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_COLOR_BLACK,
				1000);
			break;
		}

		// �A���e�̒e�̐�
		m_nContinueCnt++;
	}

	// �w�肳�ꂽ�e���o���甭�˂��Ȃ�����
	if (m_nContinueCnt >= nBulletNum)
	{
		m_fBulletFlame = BULLET_INTERVAL + (float)(rand() % BULLET_RANDOM_INTERVAL);
	}
}

//====================================================================
// �g��
//====================================================================
void CEnemy::ScaleUp(void)
{
	if (m_fScale <= 1.0f)
	{
		// �k���ʂ����Z
		m_fScale += m_fScaleNum;

		// �T�C�Y�̕ύX
		D3DXVECTOR3 size = D3DXVECTOR3(m_Size.x * m_fScale, m_Size.y * m_fScale, 0.0f);

		// Scene2D�ɃT�C�Y��n��
		SetSize2D(size);
	}
	else
	{
		m_fScale = 1.0f;
		m_bRotationScale = true;
	}
}

//=============================================================================
// ��������o��
//=============================================================================
void CEnemy::Appearance(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_����ݒ�
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �J���[�̌��Z
	m_nSubNumber -= m_nSubNum;

	// �J���[�ύX�̍ő�l
	if (m_nSubNumber <= 0)
	{
		// ����
		m_nSubNumber = 0;

		m_bFlashFlag = true;
	}

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nSubNumber);	// ���㒸�_�̐F	�����x255
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nSubNumber);	// �E�㒸�_�̐F	�����x255
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nSubNumber);	// �������_�̐F	�����x255
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nSubNumber);	// �E�����_�̐F	�����x255

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//=============================================================================
// �����蔻��
//=============================================================================
bool CEnemy::Collision(void)
{
	// �v���C���[�̏����󂯎��
	CPlayer *pPlayer = CGame::GetPlayer();

	// ���W���󂯎��
	D3DXVECTOR3 Target = pPlayer->GetPosition();

	if (Target.x - DECISION_PLAYER_SIZE_X / 2 < m_Pos.x + m_Size.x / 2 &&
		Target.x + DECISION_PLAYER_SIZE_X / 2 > m_Pos.x - m_Size.x / 2 &&
		Target.y - DECISION_PLAYER_SIZE_Y / 2 < m_Pos.y + m_Size.y / 2 &&
		Target.y + DECISION_PLAYER_SIZE_Y / 2 > m_Pos.y - m_Size.y / 2)
	{
		// �����蔻�菈��
			if (m_Etype != ENEMY_TYPE_ROTATION)
			{
				// �v���C���[�Ƀ_���[�W��^����
				pPlayer->HitDamage(10);
			}
			else
			{
				if (m_bRotationScale == true)
				{
					// �v���C���[�Ƀ_���[�W��^����
					pPlayer->HitDamage(10);
				}
			}

			return true;
	}

	return false;
}

//=============================================================================
// �����̏�����
//=============================================================================
void CEnemy::TransparentInit(void)
{
	if (m_Etype == ENEMY_TYPE_FOLLOW)
	{
		LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

		// ���_����ݒ�
		VERTEX_2D *pVtx;

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);	// �������_�̐F	�����x255
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);	// �E�����_�̐F	�����x255

		// ���_�o�b�t�@���A�����b�N����
		pVtxBuff->Unlock();

	}
}

//=============================================================================
// �^�������ȓG�̏�����
//=============================================================================
void CEnemy::InitThrough(D3DXVECTOR3 pos)
{
	if (pos.x <= SCREEN_WIDTH / 2)
	{
		m_bTwo_Sides = true;
	}
}

//=============================================================================
//  �T�C�Y���
//=============================================================================
D3DXVECTOR3 CEnemy::GetSize(void)
{
	return m_Size;
}