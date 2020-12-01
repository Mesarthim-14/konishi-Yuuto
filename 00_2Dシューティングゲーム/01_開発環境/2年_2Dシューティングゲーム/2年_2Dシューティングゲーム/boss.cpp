//=============================================================================
//
// �{�X�N���X	[boss.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "boss.h"
#include "renderer.h"
#include "manager.h"
#include "bullet.h"
#include "ui.h"
#include "fade.h"
#include "hpbar.h"
#include "fire.h"
#include "spark.h"
#include "surroundings.h"
#include "time.h"
#include "explosion.h"
#include "score.h"
#include "game.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define BOSS_LIFE				(500)					// �{�X�̗̑�
#define BOSS_SECOND_LIFE		(600)					// ���t�F�C�Y�̗̑�
#define THIRD_BOSS_LIFE			(800)					// ��O�t�F�[�Y�̗̑�

#define APPEARANCE_MOVE_Y		(15.0f)					// �o�ꎞ�̃X�s�[�h
#define BOSS_MOVE_X				(0.02f)					// �{�X�̉��ړ�
#define BULLET_SHOT_FLAME		(200)					// �e���˂̃t���[��
#define BULLET_SWITCH_CNT		(10)					// �F�̕ς��J�E���g
#define BOSS_COLOR_NUM			(10)					// �F�̕ω�
#define BOSS_COLOR_MAX			(150)					// �J���[�ύX�̍ő�
#define BOSS_COLOR_MIN			(0)						// �J���[�ύX�̍ŏ�
#define BOSS_ARMOR_TIME			(5)						// ���G�̎���
#define BOSS_CHANGE_COLOR		(35)					// �J���[��ς���t���[��
#define BOSS_CHANGE_PHASES		(350)					// �t�F�[�Y��ς��鎞��
#define BOSS_END_FLAME			(100)					// �{�X�����񂾂Ƃ��̏����鎞��

#define FIRST_BULLET_NUM		(32)					// �ŏ��̒e�̐�
#define FIRST_BULLET_INTERVAL	(20)					// �e��łԊu
#define FIRST_CHANGE_ANGLE		(15)					// �p�x�̕ύX
#define FIRST_SPARK_INTERVAL	(50)					// �{�X�̉ΉԂ��o��t���[��
#define FIRST_SPARK_NUM			(80)					// �ΉԂ̐�

#define SECOND_BULLET_FLAME		(30)					// ���t�F�C�Y
#define SECOND_BOSS_MOVE		(1.0f)					// ���t�F�[�Y�ړ���
#define SECOND_SPARK_INTERVAL	(30)					// �{�X�̉ΉԂ��o��t���[��
#define SECOND_SPARK_NUM		(80)					// �ΉԂ̐�

#define THIRD_BOSS_MOVE			(1.5f)					// ��O�t�F�[�Y�̈ړ���
#define THIRD_SHOT_FLAME		(20)					// �e���˂̃t���[��
#define THIRD_SWITCH_CNT		(400)					// �F�̕ς��J�E���g
#define THIRD_BULLET_NUM		(6)						// ��O�t�F�[�Y�̒e�̗�
#define THIRD_BULLET_SPPED		(5)						// ��O�t�F�[�Y�̒e�̑��x
#define THIRD_CHANGE_ANGLE		(15)					// �p�x�̕ύX

#define RETIRE_MOVE_Y			(-5.0f)					// �P�ނ̎��̈ړ���
#define RETIRE_TIME				(300)					// �P�ގ��̃t���[��

#define BOSS_EXPLOSION_FLAME	(10)					// �{�X�̔����t���[��
#define BOSS_EXPLOSION_COUNT	(10)					// �����̉�

#define BOSS_SCORE				(50000)					// �{�X�̃X�R�A

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CBoss::m_apTexture[MAX_BOSS_TEXTURE] = {};

//=============================================================================
// �|���S������
//=============================================================================
CBoss * CBoss::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// �������m��
	CBoss *pBoss = new CBoss;

	if (pBoss != NULL)
	{
		// ����������
		pBoss->Init(pos, size, type);

		// �e�N�X�`���ݒ�
		pBoss->BindTexture(m_apTexture[0]);

		// �����ړ���
		pBoss->AppearanceMove();

		// �{�X�X�e�[�^�X�ݒ�
		pBoss->SetPos(pos);
		pBoss->SetSize(size);

		// HP�o�[
		pBoss->pHpbar = CHpbar::Create(
			D3DXVECTOR3(SCREEN_WIDTH / 2, 25.0f, 0.0f),
			D3DXVECTOR3(BAR_SIZE_X, BAR_SIZE_Y, 0.0f), TYPE_UI, BOSS_LIFE);
	}

	return pBoss;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBoss::CBoss()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_nBulletFlame = 0;
	m_nBulletCnt = 0;
	m_nBossPhases = 0;
	m_bColorFlag = true;
	m_State = ENEMY_STATE_NORMAL;
	m_nStateCnt = 0;
	pHpbar = NULL;
	m_nFlashFlame = 0;
	m_nSubNumber = 0;
	m_nSubNum = BOSS_COLOR_NUM;
	m_nPhaseFlame = 0;
	m_bExplosion = false;
	m_nExplosionCount = 0;
	m_bBossEnd = false;
	m_nEndCount = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBoss::~CBoss()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBoss::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CScene2D::Init(pos, size, type);

	// �l�̏�����
	m_Pos = pos;					// �����̍��W
	m_nLife = BOSS_LIFE;			// �{�X�̗̑�
	m_Fhase = BOSS_PHASE_FIRST;		// �{�X�̃t�F�[�Y

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBoss::Uninit(void)
{
	// �I������
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBoss::Update(void)
{
	// �X�V����
	CScene2D::Update();

	// ���W�X�V
	m_Pos = GetPosition();

	// �ړ��̍X�V
	m_Pos += m_Move;

	// �{�X�̏��
	switch (m_State)
	{
		// �ʏ펞
	case ENEMY_STATE_NORMAL:
		break;

	// �_���[�W���󂯂��Ƃ�
	case ENEMY_STATE_DAMAGE:

		// �t���[���J�E���g
		m_nStateCnt++;

		LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

		// ���_����ݒ�
		VERTEX_2D *pVtx;

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(120, 120, 120, 255);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DCOLOR_RGBA(120, 120, 120, 255);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DCOLOR_RGBA(120, 120, 120, 255);	// �������_�̐F	�����x255
		pVtx[3].col = D3DCOLOR_RGBA(120, 120, 120, 255);	// �E�����_�̐F	�����x255

		// ���_�o�b�t�@���A�����b�N����
		pVtxBuff->Unlock();

		// �J�E���g�����ɂȂ�����
		if (m_nStateCnt >= BOSS_ARMOR_TIME)
		{
			// ��Ԃ�߂�
			m_State = ENEMY_STATE_NORMAL;

			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// ���㒸�_�̐F	�����x255
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�㒸�_�̐F	�����x255
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �������_�̐F	�����x255
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�����_�̐F	�����x255

			// �J�E���^�[��߂�
			m_nStateCnt = 0;
		}
		break;
	}

	// �t�F�[�Y�̍X�V
	FhaseUpdate();

	// ���W��n��
	SetPosition(m_Pos);
	SetPos(m_Pos);

	// �P�ނ̎��Ԃ��߂�����
	if (CTime::GetRetire() == true)
	{
		// �P�ނ̏���
		Retire();
	}

	// �����蔻��
	Collision();

	// �{�X�����񂾂�
	if (m_bBossEnd == true)
	{
		// �t���[���J�E���g
		m_nEndCount++;

		// ��莞�ԂɂȂ�����
		if (m_nEndCount >= BOSS_END_FLAME)
		{
			// �I������
			Uninit();

			// ���U���g��ʂ�
			CManager::GetFade()->SetFade(CManager::MODE_RESULT);

			return;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBoss::Draw(void)
{
	// �{�X������ł��Ȃ��Ƃ�
	if (m_bBossEnd == false)
	{
		// �`�揈��
		CScene2D::Draw();
	}
}

//=============================================================================
// �o�ꎞ�̈ړ�
//=============================================================================
void CBoss::AppearanceMove(void)
{
	m_Move = D3DXVECTOR3(0.0f, APPEARANCE_MOVE_Y, 0.0f);
}

//=============================================================================
// �{�X�̃_���[�W����
//=============================================================================
void CBoss::HitBossDamage(int nNumber)
{
	// �P�ގ�����Ȃ��Ƃ�
	if (CTime::GetRetire() == false)
	{
		// �{�X�̃`�F���W�t���[������Ȃ��Ƃ�
		if (m_Fhase != BOSS_PHASE_CHANGE_01 && m_Fhase != BOSS_PHASE_CHANGE_02 && m_Fhase != BOSS_PHASE_EXPLOSION)
		{
			// �T�E���h����
			CSound *pSound = NULL;
			pSound = CManager::GetSound();
			pSound->Play(CSound::SOUND_LABEL_HIT);

			// �̗͂̌��Z
			m_nLife -= nNumber;

			// �̗̓o�[�̌��Z
			pHpbar->AddDamage(nNumber);
		}

		// �̗͂�0�ɂȂ�����
		if (m_nLife <= 0)
		{
			// �t�F�[�Y�̎��
			switch (m_Fhase)
			{
			// ���t�F�C�Y�̎�
			case BOSS_PHASE_FIRST:
			{
				m_nPhaseFlame = 0;

				// ����1�Ɉڍs
				m_Fhase = BOSS_PHASE_CHANGE_01;

				// �T�E���h����
				CSound *pSound = NULL;
				pSound = CManager::GetSound();
				pSound->Play(CSound::SOUND_LABEL_CHANGE);
			}
				break;

			// ���t�F�C�Y�̎�
			case BOSS_PHASE_SECOND:
			{
				m_nPhaseFlame = 0;

				// ����2�Ɉڍs
				m_Fhase = BOSS_PHASE_CHANGE_02;

				// �T�E���h����
				CSound *pSound = NULL;
				pSound = CManager::GetSound();
				pSound->Play(CSound::SOUND_LABEL_CHANGE);
			}
			break;

			// ��O�t�F�[�Y
			case BOSS_PHASE_THIRD:
			{
				//�@�t�F�[�Y�̃J�E���g��0�ɂ���
					m_nPhaseFlame = 0;

					// �X�R�A�����Z
					CScore *pScore = CGame::GetScore();
					pScore->SetScore(BOSS_SCORE);

					// ����2�Ɉڍs
					m_Fhase = BOSS_PHASE_EXPLOSION;
					m_bExplosion = true;
			}
			break;

			default:
				break;

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
// �t�F�C�Y�̍X�V
//=============================================================================
void CBoss::FhaseUpdate(void)
{
	// �t�F�[�Y�̎��
	switch (m_Fhase)
	{
		// ���t�F�C�Y
	case BOSS_PHASE_FIRST:
		FirstPhases();
		break;

		// �`�F���W�t�F�[�Y
	case BOSS_PHASE_CHANGE_01:

		// �t���[����i�߂�
		m_nPhaseFlame++;

		// �ΉԂ��o��Ԋu
		if (m_nPhaseFlame % FIRST_SPARK_INTERVAL == 0)
		{
			// �ΉԂ��o����� 
			int nBaseAngle = 0 - rand() % 180 - rand() % 180;

			for (int nCount = 0; nCount < FIRST_SPARK_NUM; nCount++)
			{
				// �ΉԂ̐���
				CSpark::Create(D3DXVECTOR3(m_Pos.x, m_Pos.y , 0.0f),
					D3DXVECTOR3(SPARK_SIZE_X, SPARK_SIZE_Y, 0.0f),
					TYPE_EXPLOSION, SPARK_BOSS_ANGLE, nBaseAngle, SPARK_CHANGE_DISTANCE, SPARK_CHANGE_LIFE);
			}
		}

		// �t�F�[�Y�ڍs
		ChangePhases();

		// �Q�[�W�̕\��
		pHpbar->SetHp(BOSS_SECOND_LIFE);

		if (m_nPhaseFlame >= BOSS_CHANGE_PHASES)
		{
			// ���t�F�[�Y�ȍ~
			m_Fhase = BOSS_PHASE_SECOND;

			// ���t�F�[�Y�̏�����
			InitSecondPhase();

			// �T�E���h����
			CSound *pSound = NULL;
			pSound = CManager::GetSound();
			pSound->Stop(CSound::SOUND_LABEL_CHANGE);
		}
		break;

		// ���t�F�C�Y
	case BOSS_PHASE_SECOND:

		// ���t�F�[�Y�̏���
		SecondPhases();
		break;

		// �`�F���W�t�F�[�Y2
	case BOSS_PHASE_CHANGE_02:

		// �t���[�����J�E���g
		m_nPhaseFlame++;

		// �ΉԂ��o��Ԋu
		if (m_nPhaseFlame % SECOND_SPARK_INTERVAL == 0)
		{
			// �ΉԂ��o����� 
			int nBaseAngle = 0 - rand() % 180 - rand() % 180;

			for (int nCount = 0; nCount < SECOND_SPARK_NUM; nCount++)
			{
				// �ΉԂ��o������
				CSpark::Create(D3DXVECTOR3(m_Pos.x, m_Pos.y, 0.0f),
					D3DXVECTOR3(SPARK_SIZE_X, SPARK_SIZE_Y, 0.0f),
					TYPE_EXPLOSION, SPARK_BOSS_ANGLE, nBaseAngle, SPARK_CHANGE_DISTANCE, SPARK_CHANGE_LIFE);
			}
		}

		// �t�F�[�Y�ڍs
		ChangePhases();

		// �Q�[�W�̕\��
		pHpbar->SetHp(THIRD_BOSS_LIFE);

		// �t�F�[�Y��ς��鏈��
		if (m_nPhaseFlame >= BOSS_CHANGE_PHASES)
		{
			// ��O�t�F�[�Y�ڍs
			m_Fhase = BOSS_PHASE_THIRD;

			// ��O�t�F�[�Y�̏�����
			InitThirdPhase();

			// ���̏���
			CSound *pSound = NULL;
			pSound = CManager::GetSound();
			pSound->Stop(CSound::SOUND_LABEL_CHANGE);

		}
		break;

		// ��O�t�F�[�Y
	case BOSS_PHASE_THIRD:

		// ��O�t�F�[�Y�̏���
		ThirdPhase();
		break;

		// �����t�F�[�Y
	case BOSS_PHASE_EXPLOSION:

		// �����t�F�[�Y�̏���
		ExplosionPhase();
		break;

	default:
		break;
	}
}

//=============================================================================
// �P�ނ̏���
//=============================================================================
void CBoss::Retire(void)
{
	// �P�ރt���[���J�E���g
	m_nRetireCount++;

	// �ړ��ʐݒ�
	m_Move = D3DXVECTOR3(0.0f, RETIRE_MOVE_Y, 0.0f);

	// �J�E���g�������z������{�X�̏I��
	if (m_nRetireCount >= RETIRE_TIME)
	{
		m_bBossEnd = true;
	}

}

//=============================================================================
// ���t�F�C�Y
//=============================================================================
void CBoss::FirstPhases(void)
{
	// �ړ��X�V����
	FirstUpdateMove();

	// �e���ˏ���
	FirstBulletShot();
}

//=============================================================================
// �{�X�̈ړ�����
//=============================================================================
void CBoss::FirstUpdateMove(void)
{
	// �{�X�̎~�܂�ꏊ
	if (m_Move.y > 0.0f)
	{
		m_Move.y -= 0.2f;
	}
	else
	{
		m_Move.y = 0.0f;

		// �����̈ړ��̐���
		if (m_Pos.x >= SCREEN_WIDTH - WALL_SIZE_X - 100.0f)
		{
			m_Move.x = -1.0f;
		}
		if (m_Pos.x <= WALL_SIZE_X + 100.0f)
		{
			m_Move.x = 1.0f;
		}
	}
}

//=============================================================================
// �e�̔��ˏ���
//=============================================================================
void CBoss::FirstBulletShot(void)
{
	// �o���b�g�̃J�E���g
	m_nBulletFlame++;

	// �e��łԊu
	if (m_nBulletFlame >= BULLET_SHOT_FLAME)
	{
		for (int nCount = 0; nCount < FIRST_BULLET_NUM; nCount++)
		{
			// �F�̏��
			if (m_bColorFlag == false)
			{
				// �e�̐���
				CBullet::Create(D3DXVECTOR3(
					m_Pos.x + 100.0f*cosf(D3DXToRadian((nCount * 360 / FIRST_BULLET_NUM) + m_nBulletCnt * FIRST_CHANGE_ANGLE)),
					m_Pos.y + 100.0f*sinf(D3DXToRadian((nCount * 360 / FIRST_BULLET_NUM) + m_nBulletCnt * FIRST_CHANGE_ANGLE)),
					0.0f),
					D3DXVECTOR3(cosf(D3DXToRadian((nCount * 360 / FIRST_BULLET_NUM) + m_nBulletCnt * FIRST_CHANGE_ANGLE)) * 2,
					sinf(D3DXToRadian((nCount * 360 / FIRST_BULLET_NUM) + m_nBulletCnt * FIRST_CHANGE_ANGLE)) * 2, 0.0f),
					D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), TYPE_BULLET,
					CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_COLOR_WHITE,
					1000);
			}
			else
			{
				// �e�̐���
				CBullet::Create(D3DXVECTOR3(
					m_Pos.x + 100.0f*cosf(D3DXToRadian((nCount * 360 / FIRST_BULLET_NUM)+ m_nBulletCnt * FIRST_CHANGE_ANGLE)) ,
					m_Pos.y + 100.0f*sinf(D3DXToRadian((nCount * 360 / FIRST_BULLET_NUM)+ m_nBulletCnt * FIRST_CHANGE_ANGLE)),
					0.0f),
					D3DXVECTOR3(cosf(D3DXToRadian((nCount * 360 / FIRST_BULLET_NUM) + m_nBulletCnt * FIRST_CHANGE_ANGLE)) * 2,
						sinf(D3DXToRadian((nCount * 360 / FIRST_BULLET_NUM) + m_nBulletCnt * FIRST_CHANGE_ANGLE)) * 2, 0.0f),
					D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), TYPE_BULLET,
					CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_COLOR_BLACK,
					1000);
			}
		}

		// ���̃t���[���̃J�E���g
		m_nBulletFlame = BULLET_SHOT_FLAME - FIRST_BULLET_INTERVAL;

		// �o���b�g�񐔃J�E���g
		m_nBulletCnt++;

		// �񐔂ŐF��ς���
		if (m_nBulletCnt % BULLET_SWITCH_CNT == 0)
		{
			// �F��ς��鏈��
			if (!m_bColorFlag)
			{
				m_bColorFlag = true;
			}
			else
			{
				m_bColorFlag = false;
			}
		}
	}
}

//=============================================================================
// �`�F���W�̃t�F�[�Y
//=============================================================================
void CBoss::ChangePhases(void)
{
	// �X�V����
	ChangeUpdateMove();

	// �_��
	ChangeFlash();
}

//=============================================================================
// �`�F���W�t�F�[�Y�̍X�V
//=============================================================================
void CBoss::ChangeUpdateMove(void)
{
	// �ړ���
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//====================================================================
// �|���S���̓_��
//====================================================================
void CBoss::ChangeFlash(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �J���[�̌��Z
	m_nSubNumber += m_nSubNum;

	// �J���[�ύX�̍ő�l
	if (m_nSubNumber >= BOSS_COLOR_MAX)
	{
		// ����
		m_nSubNumber = BOSS_COLOR_MAX;

		// �l�𔽓]
		m_nSubNum *= -1;
	}
	else if (m_nSubNumber <= BOSS_COLOR_MIN)
	{
		// �J���[�̍ŏ��l�̐���
		m_nSubNumber = BOSS_COLOR_MIN;

		// �t���[���J�E���g
		m_nFlashFlame++;

		// ���̃t���[���ȏ�ɂȂ�����
		if (m_nFlashFlame >= BOSS_CHANGE_COLOR)
		{
			m_nFlashFlame = 0;

			// �l�𔽓]
			m_nSubNum *= -1;
		}
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
// ���t�F�C�Y
//=============================================================================
void CBoss::SecondPhases(void)
{
	// �ړ��̍X�V����
	SecondUpdateMove();

	// �e��ł���
	SecondBulletShot();
}

//=============================================================================
// ���t�F�C�Y�̏�����
//=============================================================================
void CBoss::InitSecondPhase(void)
{
	// ���C�t�𑝂₷
	m_nLife = BOSS_SECOND_LIFE;

	// �ړ��ʐݒ�
	m_Move = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// ���㒸�_�̐F	�����x255
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�㒸�_�̐F	�����x255
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �������_�̐F	�����x255
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�����_�̐F	�����x255

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//=============================================================================
// ���t�F�C�Y�̍X�V
//=============================================================================
void CBoss::SecondUpdateMove(void)
{
	// �����̈ړ��𐧌�
	if (m_Pos.x >= SCREEN_WIDTH - WALL_SIZE_X - 100.0f)
	{
		m_Move.x = -SECOND_BOSS_MOVE;
	}
	if (m_Pos.x <= WALL_SIZE_X + 100.0f)
	{
		m_Move.x = SECOND_BOSS_MOVE;
	}
}

//=============================================================================
// ���t�F�C�Y�̍X�V
//=============================================================================
void CBoss::SecondBulletShot(void)
{
	// �o���b�g�̃t���[�����Z
	m_nBulletFlame++;

	// �e��ł���
	if (m_nBulletFlame >= SECOND_BULLET_FLAME)
	{
		// �����_���ŐF�����߂�
		if (rand() % 2 == 0)			// ��
		{
			// �ԉΔ���
			CFire::Create(m_Pos , D3DXVECTOR3(FIRE_SIZE_X, FIRE_SIZE_Y, 0.0f),
				CFire::TYPE_BULLET, CFire::FIRE_COLOR_WHITE, 50);
		}
		else							// ��
		{
			// �ԉΔ���
			CFire::Create(m_Pos, D3DXVECTOR3(FIRE_SIZE_X, FIRE_SIZE_Y, 0.0f),
				CFire::TYPE_BULLET, CFire::FIRE_COLOR_BLACK, 50);
		}

		// ���̃o���b�g�Ԋu
		m_nBulletFlame = 0;
	}
}

//=============================================================================
// ��O�t�F�[�Y
//=============================================================================
void CBoss::ThirdPhase(void)
{
	// �ړ��̍X�V����
	ThirdUpdateMove();

	// �e��ł���
	ThirdBulletShot();
}

//=============================================================================
// ��O�t�F�[�Y������
//=============================================================================
void CBoss::InitThirdPhase(void)
{
	// ��芪���̐���
	CSurroundings::Create(D3DXVECTOR3(WALL_SIZE_X + 50.0f, 50.0f, 0.0f),
		D3DXVECTOR3(SURROUNDINGS_SIZE_X, SURROUNDINGS_SIZE_Y, 0.0f), TYPE_SURROUNDINGS);

	// ��芪���̐���
	CSurroundings::Create(D3DXVECTOR3(SCREEN_WIDTH - WALL_SIZE_X - 50.0f, 50.0f, 0.0f),
		D3DXVECTOR3(SURROUNDINGS_SIZE_X, SURROUNDINGS_SIZE_Y, 0.0f), TYPE_SURROUNDINGS);

	// �l�̑��
	m_nLife = THIRD_BOSS_LIFE;								// ���C�t�𑝂₷
	m_Move = D3DXVECTOR3(-THIRD_BOSS_MOVE, 0.0f, 0.0f);		// �ړ��ʐݒ�
	m_nBulletFlame = 0;										// �e�̃t���[���J�E���g
	m_nBulletCnt = 0;										// �o���b�g�̐F�J�E���g

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	// ���_����ݒ�
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// ���㒸�_�̐F	�����x255
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�㒸�_�̐F	�����x255
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �������_�̐F	�����x255
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�����_�̐F	�����x255

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//=============================================================================
// ��O�t�F�[�Y�ړ��X�V
//=============================================================================
void CBoss::ThirdUpdateMove(void)
{
	// �ړ��̐���
	if (m_Pos.x >= SCREEN_WIDTH - WALL_SIZE_X - 100.0f)
	{
		m_Move.x = -THIRD_BOSS_MOVE;
	}

	if (m_Pos.x <= WALL_SIZE_X + 100.0f)
	{
		m_Move.x = THIRD_BOSS_MOVE;
	}
}

//=============================================================================
// ��O�t�F�[�Y�̒e�ł�
//=============================================================================
void CBoss::ThirdBulletShot(void)
{
	// �o���b�g�̃J�E���g
	m_nBulletFlame++;

	// �p�x�ύX�p�ϐ�
	static int nNum = 0;

	// �e��łԊu
	if (m_nBulletFlame >= THIRD_SHOT_FLAME)
	{
		nNum++;

		for (int nCount = 0; nCount < THIRD_BULLET_NUM; nCount++)
		{
			// �F�̏��
			if (m_bColorFlag == true)
			{
				// �p�x�����炷
				if (nNum % 2 == 0)
				{
					CBullet::Create(D3DXVECTOR3(m_Pos.x + 100.0f*cosf(D3DXToRadian(45 + (nCount * 90 / THIRD_BULLET_NUM) + THIRD_CHANGE_ANGLE)),
						m_Pos.y + 70.0f*sinf(D3DXToRadian(45 + (nCount * 90 / THIRD_BULLET_NUM) + THIRD_CHANGE_ANGLE)), 0.0f),
						D3DXVECTOR3(cosf(D3DXToRadian(45 + (nCount * 90 / THIRD_BULLET_NUM) + THIRD_CHANGE_ANGLE)) * THIRD_BULLET_SPPED,
							sinf(D3DXToRadian(45 + (nCount * 90 / THIRD_BULLET_NUM) + THIRD_CHANGE_ANGLE)) * THIRD_BULLET_SPPED, 0.0f),
						D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), TYPE_BULLET,
						CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_COLOR_WHITE,
						1000);
				}
				else
				{
					CBullet::Create(D3DXVECTOR3(m_Pos.x + 100.0f*cosf(D3DXToRadian(45 + (nCount * 90 / THIRD_BULLET_NUM) + THIRD_CHANGE_ANGLE)),
						m_Pos.y + 70.0f*sinf(D3DXToRadian(45 + (nCount * 90 / THIRD_BULLET_NUM) + THIRD_CHANGE_ANGLE)), 0.0f),
						D3DXVECTOR3(cosf(D3DXToRadian(45+(nCount * 120 / THIRD_BULLET_NUM - THIRD_CHANGE_ANGLE) )) * THIRD_BULLET_SPPED,
							sinf(D3DXToRadian(45 + (nCount * 120 / THIRD_BULLET_NUM- THIRD_CHANGE_ANGLE) )) * THIRD_BULLET_SPPED, 0.0f),
						D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), TYPE_BULLET,
						CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_COLOR_WHITE,
						1000);
				}
			}
			else
			{
				// �p�x�����炷
				if (nNum % 2 == 0)
				{
					CBullet::Create(D3DXVECTOR3(m_Pos.x + 100.0f*cosf(D3DXToRadian(45 + (nCount * 90 / THIRD_BULLET_NUM) + THIRD_CHANGE_ANGLE)),
						m_Pos.y + 70.0f*sinf(D3DXToRadian(45 + (nCount * 90 / THIRD_BULLET_NUM) + THIRD_CHANGE_ANGLE)), 0.0f),
						D3DXVECTOR3(cosf(D3DXToRadian(45 + (nCount * 90 / THIRD_BULLET_NUM) + THIRD_CHANGE_ANGLE)) * THIRD_BULLET_SPPED,
							sinf(D3DXToRadian(45 + (nCount * 90 / THIRD_BULLET_NUM) + THIRD_CHANGE_ANGLE)) * THIRD_BULLET_SPPED, 0.0f),
						D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), TYPE_BULLET,
						CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_COLOR_BLACK,
						1000);
				}
				else
				{
					CBullet::Create(D3DXVECTOR3(m_Pos.x + 100.0f*cosf(D3DXToRadian(45 + (nCount * 90 / THIRD_BULLET_NUM) + THIRD_CHANGE_ANGLE)),
						m_Pos.y + 70.0f*sinf(D3DXToRadian(45 + (nCount * 90 / THIRD_BULLET_NUM) + THIRD_CHANGE_ANGLE)), 0.0f),
						D3DXVECTOR3(cosf(D3DXToRadian(45 + (nCount * 120 / THIRD_BULLET_NUM - THIRD_CHANGE_ANGLE))) * THIRD_BULLET_SPPED,
							sinf(D3DXToRadian(45 + (nCount * 120 / THIRD_BULLET_NUM - THIRD_CHANGE_ANGLE))) * THIRD_BULLET_SPPED, 0.0f),
						D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), TYPE_BULLET,
						CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_COLOR_BLACK,
						1000);
				}
			}
		}

		// �t���[��������
		m_nBulletFlame = 0;

	}
	// �o���b�g�񐔃J�E���g
	m_nBulletCnt++;

	// �񐔂ŐF��ς���
	if (m_nBulletCnt >= THIRD_SWITCH_CNT)
	{
		if (m_bColorFlag == false)
		{
			m_bColorFlag = true;
		}
		else
		{
			m_bColorFlag = false;
		}

		m_nBulletCnt = 0;
	}
}

//=============================================================================
// �����t�F�[�Y
//=============================================================================
void CBoss::ExplosionPhase(void)
{
	// �ړ��ʐݒ�
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �t���[���J�E���g
	m_nExplosionFlame++;

	// �������ł�Ԋu
	if (m_nExplosionFlame % BOSS_EXPLOSION_FLAME == 0)
	{
		// ����ݒ�
		int nDis = rand() % 70 + rand() % 70- rand() % 70- rand() % 70;					// �����̐ݒ�
		int nAnlfe = rand() % 90 - rand() % 90 + rand() % 90 - rand() % 90;				// �p�x�̐ݒ�

		// �����_���ŏo�������߂�
		D3DXVECTOR3 TargetPos = D3DXVECTOR3(m_Pos.x + nDis * cosf(D3DXToRadian(nAnlfe)),
			m_Pos.y + nDis * sinf(D3DXToRadian(nAnlfe)), 0.0f);

		// �����̐ݒ�
		CExplosion::Create(D3DXVECTOR3(TargetPos.x, TargetPos.y, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOSS_EXPLOSION_SIZE_X, BOSS_EXPLOSION_SIZE_Y, 0.0f),
			TYPE_EXPLOSION, CExplosion::COLOR_TYPE_BOSS);

		// ���̐ݒ�
		CSound *pSound = NULL;
		pSound = CManager::GetSound();
		pSound->Play(CSound::SOUND_LABEL_BOSS_EXPLOSION);

		// ���������J�E���g
		m_nExplosionCount++;
	}

	// ��萔����������
	if (m_nExplosionCount >= BOSS_EXPLOSION_COUNT)
	{
		m_bBossEnd = true;
	}
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CBoss::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/enemy_boss.png",
		&m_apTexture[0]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CBoss::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_BOSS_TEXTURE; nCount++)
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
// ���C�t�̏��
//=============================================================================
int CBoss::GetLife(void)
{
	return m_nLife;
}

//=============================================================================
// �{�X�̃J���[���
//=============================================================================
bool CBoss::GetColor(void)
{
	return m_bColorFlag;
}

//=============================================================================
// �{�X�̔������
//=============================================================================
bool CBoss::GetExplosion(void)
{
	return m_bExplosion;
}