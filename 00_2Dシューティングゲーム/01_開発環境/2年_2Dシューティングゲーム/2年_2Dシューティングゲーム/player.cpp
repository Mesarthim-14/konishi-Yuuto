//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "player.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "bullet.h"
#include "shield.h"
#include "ui.h"
#include "laser.h"
#include "fade.h"
#include "game.h"
#include "gage.h"
#include "remain.h"
#include "explosion.h"
#include "muzzle_flash.h"
#include "joypad.h"
#include "bomb.h"
#include "enemy.h"
#include "bullet.h"
#include "bomb_ui.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_LIFE				(1)			// �v���C���[�̗̑�
#define PLAYER_BULLET_SIZE_X	(30)		// �v���C���[�̒e�̃T�C�Y(��)
#define PLAYER_BULLET_SIZE_Y	(120)		// �v���C���[�̒e�̃T�C�Y(�c)
#define PLAYER_SPEED			(5.0f)	 	// �v���C���[�̑��x
#define BULLET_INTERVAL			(5)			// �e�̘A�ˊԊu
#define PLAYER_STOCK			(3)			// �v���C���[�̎c�@
#define PLAYER_ARMOR_COUNT		(240)		// ���G����
#define PLAYER_BOMB_NUM			(1)			// �{���̐�

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_BulletState = 0;
	m_nLife = 0;
	m_nStock = 0;
	m_nLaserFlame = 0;
	m_nLaserCounter = 0;
	m_bShildInfo = false;
	m_bShildScaleInfo = false;
	m_pShield = NULL;
	m_pGage = NULL;
	m_pLaser = NULL;
	m_pBombUi = NULL;
	m_nResurrectionCnt = 0;
	m_bPlayerDraw = false;
	m_bUseLaser = false;
	m_State = PLAYER_STATE_NONE;
	m_StateCount = 0;
	m_nBombFlame = 0;
	m_nBombNum = 0;
	m_nBombCount = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CPlayer::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/player001.png",
		&m_pTexture);		// �e�N�X�`���ւ̃|�C���^

	return S_OK;
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// �������m��
	CPlayer *pPlayer = new CPlayer;

	// ����������
	pPlayer->Init(pos, size, type);	

	// �Q�[�W�̘g����
	pPlayer->m_pGage = CGage::Create(D3DXVECTOR3(WALL_SIZE_X - 100.0f, SCREEN_HEIGHT - 202.5f, 0.0f), D3DXVECTOR3(GAGE_SIZE_X + 5.0f, GAGE_SIZE_Y + 5.0f, 0.0f),
		TYPE_SCORE, CGage::GAGE_TYPE_FLAME);

	// �Q�[�W����
	pPlayer->m_pGage = CGage::Create(D3DXVECTOR3(WALL_SIZE_X - 100.0f, SCREEN_HEIGHT - 200.0f, 0.0f), D3DXVECTOR3(GAGE_SIZE_X, GAGE_SIZE_Y, 0.0f),
		TYPE_SCORE, CGage::GAGE_TYPE_BLUE);

	return pPlayer;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// �l�̑��
	m_BulletState = BULLET_INTERVAL;	// �e�̊Ԋu������
	m_nLife = PLAYER_LIFE;				// �̗�
	m_nLaserFlame = LASER_FLAME;		// ���[�U�[�̃t���[��

	// �����󂯓n��
	CScene2D::SetPolygon(pos, size);

	// �e�N�X�`���󂯓n��
	BindTexture(m_pTexture);

	// �|���S��������
	CScene2D::Init(pos, size, type);

	// �����V�[���h�̐���
	m_pShield = CShield::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(SHIELD_SIZE_X, SHIELD_SIZE_Y, 0.0f), 
		TYPE_SHIELD, CShield::SHIELD_TYPE_WHITE);

	if (m_pBombUi == NULL)
	{
		m_pBombUi = CBombUi::Create(
			D3DXVECTOR3(195.0f, 630.0f, 0.0f), D3DXVECTOR3(BOMB_UI_SIZE_X, BOMB_UI_SIZE_Y, 0.0f), TYPE_SCORE);
	}

	// �V�[���h�𔒂�
	m_bShildInfo = true;

	// �{���̏�����
	m_nBombCount = PLAYER_BOMB_NUM;

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CPlayer::UnLoad(void)
{
	// �e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	// �I������
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	m_Pos = GetPosition();

	// �X�V����
	CScene2D::Update();

	// �v���C���[�̏��
	UpdateState();

	if (m_bPlayerDraw == false)
	{
		// �v���C���[����֐�
		PlayerControl();

		m_Pos += m_Move;

		if (m_pShield != NULL)
		{
			// �V�[���h�ɍ��W��n��
			m_bShildScaleInfo = m_pShield->ScaleUp(m_Pos);
		}
	}

	 // �{���̓����蔻��
	if (m_bBombUse == true)
	{
		// �{���̓����蔻��
		if (BombCollision() == true)
		{
			CScene *pScene = NULL;
			if (pScene == NULL)
			{
				// �V�[�����擾
				pScene = CScene::GetScene(m_nBombNum);

				// �������̃L���X�g
				CScene2D *pScene2D = (CScene2D*)pScene;

				if (pScene2D != NULL)
				{
					switch (m_BombType)
					{
					case TYPE_ENEMY:
					{
						// �G�̃T�C�Y�擾
						CEnemy *pEnemy = (CEnemy*)pScene2D;

						// ���C�t���ւ炷
						pEnemy->HitDamage(30);

					}
					break;

					case TYPE_BULLET:
					{
						// �G�̃T�C�Y�擾
						CBullet *pBullet = (CBullet*)pScene2D;

						// ���C�t���ւ炷
						pBullet->DecreaseLife(10000);
					}
					break;

					}

				}
			}
		}
	}

	// ���W��n��
	SetPosition(m_Pos);

	// �̗͂������Ȃ�����
	if (m_nLife <= 0)
	{
		if (m_pShield != NULL)
		{
			// �V�[���h����
			m_pShield->Uninit();
			m_pShield = NULL;
		}
	}

	// ��������
	if (m_bPlayerDraw == true)
	{
		Resurrection();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	if (m_bPlayerDraw == false)
	{
		// �`�揈��
		CScene2D::Draw();
	}
}

//=============================================================================
// �v���C���[����֐�
//=============================================================================
void CPlayer::PlayerControl(void)
{
	// �W���C�p�b�h�̎擾
	DIJOYSTATE js = CInputJoypad::GetStick(0);

	if (js.lX != 0.0f || js.lY != 0)
	{
		float fAngle = atan2f((float)js.lX, (float)js.lY);

		// �W���C�p�b�h����
		m_Pos.x += sinf(fAngle)* PLAYER_SPEED;
		m_Pos.y += cosf(fAngle)* PLAYER_SPEED;
	}

	// �L�[�{�[�h�X�V
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	// W�L�[���������Ƃ�
	if (pKeyboard->GetPress(DIK_W))
	{
		m_Pos.y += cosf(D3DX_PI)*PLAYER_SPEED;
	}
	// S�L�[���������Ƃ�
	if (pKeyboard->GetPress(DIK_S))
	{
		m_Pos.y += cosf(0)*PLAYER_SPEED;
	}
	// A�L�[���������Ƃ�
	if (pKeyboard->GetPress(DIK_A))
	{
		m_Pos.x -= sinf(D3DX_PI / 2)*PLAYER_SPEED;
	}
	// D�L�[���������Ƃ�
	if (pKeyboard->GetPress(DIK_D))
	{
		m_Pos.x += sinf(D3DX_PI / 2)*PLAYER_SPEED;
	}

	// �V�[���h�����̏���
	if (pKeyboard->GetTrigger(DIK_RSHIFT) || CManager::GetJoypad()->GetJoystickTrigger(2, 0))
	{
		if (m_bUseLaser == true)
		{
			m_bUseLaser = false;
		}

		if (m_bShildScaleInfo == true)
		{
			// �V�[���h����
			if (m_bShildInfo == true)
			{	
				//�����Ƃ�
				if (m_pShield != NULL)
				{
					// �V�[���h����
					m_pShield->Uninit();
					m_pShield = NULL;
				}
				m_bShildInfo = false;
				// �����Ƃ�
				m_pShield = CShield::Create(m_Pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXVECTOR3(SHIELD_SIZE_X, SHIELD_SIZE_Y, 0.0f),
					TYPE_SHIELD, CShield::SHIELD_TYPE_BLACK);
			}
			else
			{
				// �����Ƃ�
				if (m_pShield != NULL)
				{
					// �V�[���h����
					m_pShield->Uninit();
					m_pShield = NULL;
				}
				m_bShildInfo = true;
				// �����Ƃ�
				m_pShield = CShield::Create(m_Pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXVECTOR3(SHIELD_SIZE_X, SHIELD_SIZE_Y, 0.0f),
					TYPE_SHIELD, CShield::SHIELD_TYPE_WHITE);
			}
		}
	}

	// SPACE�L�[�������ꂽ��
	if (pKeyboard->GetPress(DIK_SPACE) && m_bUseLaser == false || CManager::GetJoypad()->GetJoystickPress(0, 0))
	{
		// �v���C���[�̐F
		if (m_bShildScaleInfo == true)
		{
			// �o���b�g�̊Ԋu
			if (m_BulletState == BULLET_INTERVAL)
			{
				CSound *pSound = NULL;
				pSound = CManager::GetSound();
				pSound->Play(CSound::SOUND_LABEL_SHOT);

				if (m_bShildInfo == true)
				{
					// �e�̐���
					CBullet::Create(D3DXVECTOR3(m_Pos.x + PLAYER_SHOT_POS_X, m_Pos.y - PLAYER_SHOT_POS_Y, 0.0f),
						D3DXVECTOR3(0.0f, -15.0f, 0.0f),
						D3DXVECTOR3(PLAYER_BULLET_SIZE_X, PLAYER_BULLET_SIZE_Y, 0.0f),
						TYPE_BULLET, CBullet::BULLET_TYPE_PLAYER, CBullet::BULLET_COLOR_WHITE,
						100);

					// �e�̐���
					CBullet::Create(D3DXVECTOR3(m_Pos.x - PLAYER_SHOT_POS_X, m_Pos.y - PLAYER_SHOT_POS_Y, 0.0f),
						D3DXVECTOR3(0.0f, -15.0f, 0.0f),
						D3DXVECTOR3(PLAYER_BULLET_SIZE_X, PLAYER_BULLET_SIZE_Y, 0.0f),
						TYPE_BULLET, CBullet::BULLET_TYPE_PLAYER, CBullet::BULLET_COLOR_WHITE,
						100);

					// �}�Y���t���b�V���̐���
					for (int nCount = 0; nCount < MUZZLE_FLASH_NUM; nCount++)
					{
						CMuzzleFlash::Create(D3DXVECTOR3(m_Pos.x + PLAYER_SHOT_POS_X, m_Pos.y - PLAYER_SHOT_POS_Y + 10, 0.0f),
							D3DXVECTOR3(MUZZLE_FLASH_SIZE_X, MUZZLE_FLASH_SIZE_Y, 0.0f),
							TYPE_EFFECT, CMuzzleFlash::MUZZLE_FLASH_COLOR_WHITE, MUZZLE_FLASH_LIFE);

						CMuzzleFlash::Create(D3DXVECTOR3(m_Pos.x - PLAYER_SHOT_POS_X, m_Pos.y - PLAYER_SHOT_POS_Y + 10, 0.0f),
							D3DXVECTOR3(MUZZLE_FLASH_SIZE_X, MUZZLE_FLASH_SIZE_Y, 0.0f),
							TYPE_EFFECT, CMuzzleFlash::MUZZLE_FLASH_COLOR_WHITE, MUZZLE_FLASH_LIFE);
					}
				}
				else
				{
					// �e�̐���
					CBullet::Create(D3DXVECTOR3(m_Pos.x + PLAYER_SHOT_POS_X, m_Pos.y - PLAYER_SHOT_POS_Y , 0.0f),
						D3DXVECTOR3(0.0f, -15.0f, 0.0f),
						D3DXVECTOR3(PLAYER_BULLET_SIZE_X, PLAYER_BULLET_SIZE_Y, 0.0f),
						TYPE_BULLET, CBullet::BULLET_TYPE_PLAYER, CBullet::BULLET_COLOR_BLACK,
						100);
					// �e�̐���
					CBullet::Create(D3DXVECTOR3(m_Pos.x - PLAYER_SHOT_POS_X, m_Pos.y - PLAYER_SHOT_POS_Y, 0.0f),
						D3DXVECTOR3(0.0f, -15.0f, 0.0f),
						D3DXVECTOR3(PLAYER_BULLET_SIZE_X, PLAYER_BULLET_SIZE_Y, 0.0f),
						TYPE_BULLET, CBullet::BULLET_TYPE_PLAYER, CBullet::BULLET_COLOR_BLACK,
						100);

					// �}�Y���t���b�V���̐���
					for (int nCount = 0; nCount < MUZZLE_FLASH_NUM; nCount++)
					{
						CMuzzleFlash::Create(D3DXVECTOR3(m_Pos.x + PLAYER_SHOT_POS_X, m_Pos.y - PLAYER_SHOT_POS_Y + 10, 0.0f),
							D3DXVECTOR3(MUZZLE_FLASH_SIZE_X, MUZZLE_FLASH_SIZE_Y, 0.0f),
							TYPE_EFFECT, CMuzzleFlash::MUZZLE_FLASH_COLOR_BLACK, MUZZLE_FLASH_LIFE);

						CMuzzleFlash::Create(D3DXVECTOR3(m_Pos.x - PLAYER_SHOT_POS_X, m_Pos.y - PLAYER_SHOT_POS_Y + 10, 0.0f),
							D3DXVECTOR3(MUZZLE_FLASH_SIZE_X, MUZZLE_FLASH_SIZE_Y, 0.0f),
							TYPE_EFFECT, CMuzzleFlash::MUZZLE_FLASH_COLOR_BLACK, MUZZLE_FLASH_LIFE);
					}
				}
			}
		}
		// �J�E���^�[�����Z
		m_BulletState--;

		// 0�ɂȂ����猳�̒l�ɖ߂�
		if (m_BulletState <= 0)
		{
			m_BulletState = BULLET_INTERVAL;
		}
	}

	// L�L�[�������ꂽ��
	if (pKeyboard->GetTrigger(DIK_L) && m_pGage->GetLaserNum() >= 10 || CManager::GetJoypad()->GetJoystickTrigger(7, 0))
	{
			if (m_bShildScaleInfo == true)
			{
				if (m_bShildInfo == true)
				{
					// �g���K�[
					if (m_bUseLaser == true)
					{
						if (m_nLaserCounter >= 100)
						{
							m_bUseLaser = false;
							m_nLaserCounter = 0;
						}
					}
					else
					{
						if (m_nLaserCounter >= 100)
						{
							if (m_pLaser == NULL)
							{
								// �e�̐���
								m_pLaser = CLaser::Create(D3DXVECTOR3(m_Pos.x + 0.0f, m_Pos.y + 5.0f, 0.0f),
									D3DXVECTOR3(0.0f, -15.0f, 0.0f),
									D3DXVECTOR3(LASER_SIZE_X, LASER_SIZE_Y, 0.0f),
									TYPE_LASER, CLaser::LASER_COLOR_WHITE);
							}

							// �T�E���h�̏���
							CSound *pSound = NULL;
							pSound = CManager::GetSound();
							pSound->Play(CSound::SOUND_LABEL_LASER);

							m_bUseLaser = true;
							m_nLaserCounter = 0;
						}
					}
				}
				else if (m_bShildInfo == false)
				{
					// �{�^���������ꂽ
					// �g���K�[
					if (m_bUseLaser == true)
					{
						if (m_nLaserCounter >= 100)
						{
							m_bUseLaser = false;
							m_nLaserCounter = 0;
						}
					}
					else
					{
						if (m_nLaserCounter >= 100)
						{
							if (m_pLaser == NULL)
							{	
								// ���[�U�[�̐���
								m_pLaser = CLaser::Create(D3DXVECTOR3(m_Pos.x + 0.0f, m_Pos.y + 15.0f, 0.0f),
									D3DXVECTOR3(0.0f, -15.0f, 0.0f),
									D3DXVECTOR3(LASER_SIZE_X, LASER_SIZE_Y, 0.0f),
									TYPE_LASER, CLaser::LASER_COLOR_BLACK);
							}

							// ���̏���
							CSound *pSound = NULL;
							pSound = CManager::GetSound();
							pSound->Play(CSound::SOUND_LABEL_LASER);

							m_bUseLaser = true;
							m_nLaserCounter = 0;
						}
					}
				}
			}
	}

	// �{���̏���
	if (m_nBombCount > 0 &&pKeyboard->GetTrigger(DIK_B) && m_bUseLaser == false || 
		m_nBombCount > 0 &&CManager::GetJoypad()->GetJoystickTrigger(5, 0))
	{
		m_nBombCount--;

		CSound *pSound = NULL;
		pSound = CManager::GetSound();
		pSound->Play(CSound::SOUND_LABEL_BOMB);

		if (m_pBombUi != NULL)
		{
			// �{����UI������
			m_pBombUi->Uninit();
			m_pBombUi = NULL;
		}
		if (m_bShildInfo == true)
		{
			// �{���̏Ռ��g����
			for (int nCount = 0; nCount < BOMB_NUM; nCount++)
			{
				CBomb::Create(m_Pos,
					D3DXVECTOR3(BOMB_SIZE_X, BOMB_SIZE_Y, 0.0f),
					TYPE_EFFECT, CBomb::BOMB_TYPE_SHOCK, CBomb::BOMB_COLOR_WHITE,
					nCount* (BOMB_ANGLE / BOMB_NUM), 180, BOMB_DISTANCE, BOMB_LIFE);

				CBomb::Create(m_Pos,
					D3DXVECTOR3(BOMB_SIZE_X, BOMB_SIZE_Y, 0.0f),
					TYPE_EFFECT, CBomb::BOMB_TYPE_SHOCK, CBomb::BOMB_COLOR_WHITE,
					nCount* (BOMB_ANGLE / BOMB_NUM), 180, BOMB_DISTANCE, BOMB_LIFE);
			}

			// �{���̉ΉԐ���
			for (int nCount = 1; nCount < BOMB_SPARK_NUM + 1; nCount++)
			{
				CBomb::Create(m_Pos,
					D3DXVECTOR3(BOMB_SPARK_SIZE_X, BOMB_SPARK_SIZE_Y, 0.0f),
					TYPE_EFFECT, CBomb::BOMB_TYPE_SPARK, CBomb::BOMB_COLOR_WHITE,
					nCount * (BOMB_SPARK_ANGLE / BOMB_SPARK_NUM), 90, BOMB_SPARK_DISTANCE, BOMB_SPARK_LIFE);

				CBomb::Create(m_Pos,
					D3DXVECTOR3(BOMB_SPARK_SIZE_X, BOMB_SPARK_SIZE_Y, 0.0f),
					TYPE_EFFECT, CBomb::BOMB_TYPE_SPARK, CBomb::BOMB_COLOR_WHITE,
					nCount * (BOMB_SPARK_ANGLE / BOMB_SPARK_NUM), 90, BOMB_SPARK_DISTANCE, BOMB_SPARK_LIFE);
			}
		}
		else
		{
			// �{���̏Ռ��g����
			for (int nCount = 0; nCount < BOMB_NUM; nCount++)
			{
				CBomb::Create(m_Pos,
					D3DXVECTOR3(BOMB_SIZE_X, BOMB_SIZE_Y, 0.0f),
					TYPE_EFFECT, CBomb::BOMB_TYPE_SHOCK, CBomb::BOMB_COLOR_BLACK,
					nCount* (BOMB_ANGLE / BOMB_NUM), 180, BOMB_DISTANCE, BOMB_LIFE);

				CBomb::Create(m_Pos,
					D3DXVECTOR3(BOMB_SIZE_X, BOMB_SIZE_Y, 0.0f),
					TYPE_EFFECT, CBomb::BOMB_TYPE_SHOCK, CBomb::BOMB_COLOR_BLACK,
					nCount* (BOMB_ANGLE / BOMB_NUM), 180, BOMB_DISTANCE, BOMB_LIFE);
			}

			// �{���̉ΉԐ���
			for (int nCount = 1; nCount < BOMB_SPARK_NUM + 1; nCount++)
			{
				CBomb::Create(m_Pos,
					D3DXVECTOR3(BOMB_SPARK_SIZE_X, BOMB_SPARK_SIZE_Y, 0.0f),
					TYPE_EFFECT, CBomb::BOMB_TYPE_SPARK, CBomb::BOMB_COLOR_BLACK,
					nCount * (BOMB_SPARK_ANGLE / BOMB_SPARK_NUM), 90, BOMB_SPARK_DISTANCE, BOMB_SPARK_LIFE);

				CBomb::Create(m_Pos,
					D3DXVECTOR3(BOMB_SPARK_SIZE_X, BOMB_SPARK_SIZE_Y, 0.0f),
					TYPE_EFFECT, CBomb::BOMB_TYPE_SPARK, CBomb::BOMB_COLOR_BLACK,
					nCount * (BOMB_SPARK_ANGLE / BOMB_SPARK_NUM), 90, BOMB_SPARK_DISTANCE, BOMB_SPARK_LIFE);

			}

		}
		m_bBombUse = true;
	}
	if (m_bUseLaser == true)
	{
		m_nLaserFlame++;

		if (m_nLaserFlame >= LASER_FLAME)
		{
			// �Q�[�W�̌��Z
			m_pGage->SubtractGame(10);
			m_nLaserFlame = 0;
		}

		// �Q�[�W�����ʈȉ���������
		if (m_pGage->GetLaserNum() <= 10)
		{
			m_bUseLaser = false;
		}
		m_nLaserCounter++;
	}
	else
	{
		m_nLaserCounter++;
	}

	// ���[�U�[���g���Ă�����
	if (m_pLaser != NULL)
	{

		if (m_pLaser->GetSize().x <= 0.0f)
		{
			// ���[�U�[�̏I������
			m_pLaser->Uninit();
			m_pLaser = NULL;

			m_bUseLaser = false;

			// ���̏���
			CSound *pSound = NULL;
			pSound = CManager::GetSound();
			pSound->Stop(CSound::SOUND_LABEL_LASER);

		}
	}

	// ������
	if (m_Pos.x - PLAYER_SIZE_X / 2 < WALL_SIZE_X)
	{
		m_Pos.x = WALL_SIZE_X + PLAYER_SIZE_X / 2;
	}
	// �E����
	if (m_Pos.x + PLAYER_SIZE_X / 2 > SCREEN_WIDTH - WALL_SIZE_X)
	{
		m_Pos.x =  SCREEN_WIDTH - WALL_SIZE_X - PLAYER_SIZE_X / 2;
	}
	// �㔻��
	if (m_Pos.y - PLAYER_SIZE_Y / 2 < 0.0f)
	{
		m_Pos.y = PLAYER_SIZE_Y / 2;
	}
	// ������
	if (m_Pos.y + PLAYER_SIZE_Y / 2 > SCREEN_HEIGHT)
	{
		m_Pos.y = SCREEN_HEIGHT - PLAYER_SIZE_Y / 2;
	}
}

//=============================================================================
// ����
//=============================================================================
void CPlayer::Resurrection(void)
{
	// �����̃J�E���g
	m_nResurrectionCnt++;

	if (m_bPlayerDraw == false)
	{
		// �������܂���
		m_bPlayerDraw = true;
		m_State = PLAYER_STATE_REVIVE;
		m_nBombCount = PLAYER_BOMB_NUM;

		if (m_pBombUi == NULL)
		{
			m_pBombUi = CBombUi::Create(
				D3DXVECTOR3(195.0f, 630.0f, 0.0f), D3DXVECTOR3(BOMB_UI_SIZE_X, BOMB_UI_SIZE_Y, 0.0f), TYPE_SCORE);
		}

		// �X�R�A�����Z
		CRemain *pRemain = CGame::GetRemain();
		if (pRemain != NULL)
		{
			// �c�@�����炷
			pRemain->SetRemain(1);
		}
	}

	if (m_nResurrectionCnt >= 50)
	{
		// �c�@�̃J�E���g���グ��
		m_nStock++;

		// �c�@�����������烊�U���g
		if (m_nStock >= PLAYER_STOCK&& CManager::GetFade()->Get() == CFade::FADE_NONE)
		{
			// �I������
			Uninit();

			// �t�F�[�h����
			CManager::GetFade()->SetFade(CManager::MODE_RESULT);
			return;
		}

		// ���[�U�[���g���Ă�����
		if (m_pLaser != NULL)
		{
			// ���[�U�[�̏I������
			m_pLaser->Uninit();
			m_pLaser = NULL;

			m_bUseLaser = false;
		}

		// ���C�t�ƍ��W��߂�
		m_nLife = PLAYER_LIFE;
		m_Pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 700.0f, 0.0f);

		// Scene2D��pos��n��
		SetPosition(m_Pos);

		// �V�[���h����
		m_pShield = CShield::Create(m_Pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(SHIELD_SIZE_X, SHIELD_SIZE_Y, 0.0f),
			TYPE_SHIELD, CShield::SHIELD_TYPE_WHITE);

		// ������
		m_nResurrectionCnt = 0;
		m_bPlayerDraw = false;
		m_bShildInfo = true;

		// ���[�U�[�̒l�����炷
		int nGame = m_pGage->GetLaserNum();
		m_pGage->SubtractGame(nGame);
	}
}

//=============================================================================
// �v���C���[��ԍX�V
//=============================================================================
void CPlayer::UpdateState(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	// ���_����ݒ�
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	switch (m_State)
	{
		// �ʏ���
	case PLAYER_STATE_NORMAL:
		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �������_�̐F	�����x255
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�����_�̐F	�����x255
		break;

		// �h����
	case PLAYER_STATE_REVIVE:
		// ����
		m_StateCount++;

		if (m_StateCount % 2 == 0)
		{
			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 50);	// ���㒸�_�̐F	�����x255
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 50);	// �E�㒸�_�̐F	�����x255
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 50);	// �������_�̐F	�����x255
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 50);	// �E�����_�̐F	�����x255
		}
		else
		{
			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// ���㒸�_�̐F	�����x255
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�㒸�_�̐F	�����x255
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �������_�̐F	�����x255
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�����_�̐F	�����x255
		}

		if (m_StateCount >= PLAYER_ARMOR_COUNT)
		{
			// �ʏ��Ԃɖ߂�
			m_State = PLAYER_STATE_NORMAL;
			m_StateCount = 0;
		}
		break;
	case PLAYER_STATE_LASER:
		break;
	}

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//=============================================================================
// �_���[�W���󂯂��Ƃ�
//=============================================================================
void CPlayer::HitDamage(int nCount)
{
	if (m_State != PLAYER_STATE_REVIVE)
	{
		// ���C�t���Z
		m_nLife -= nCount;

		if (m_nLife <= 0)
		{
			CSound *pSound = NULL;
			pSound = CManager::GetSound();
			pSound->Play(CSound::SOUND_LABEL_BOMB);

			if (m_bShildInfo == true)
			{
				// ��������
				CExplosion::Create(
					m_Pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, 0.0f),
					TYPE_EXPLOSION, CExplosion::COLOR_TYPE_WHITE);
			}
			else
			{
				// ��������
				CExplosion::Create(
					m_Pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, 0.0f),
					TYPE_EXPLOSION, CExplosion::COLOR_TYPE_BLACK);
			}

			// �����̏���
			Resurrection();
		}
	}
}

//=============================================================================
// �{���̓����蔻��
//=============================================================================
bool CPlayer::BombCollision(void)
{
	m_nBombFlame++;

	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		CScene *pScene = NULL;
		if (pScene == NULL)
		{
			// �V�[�����擾
			pScene = CScene::GetScene(nCount);

			// �������̃L���X�g
			CScene2D *pScene2D = (CScene2D*)pScene;

			if (pScene2D != NULL)
			{
				CScene::TYPE type = pScene->GetType();

				// �G�l�~�[�̎�
				if (type == TYPE_ENEMY)
				{
					// �^�[�Q�b�g�̏��m��
					D3DXVECTOR3 Target = pScene2D->GetPosition();

					// �G�̃T�C�Y�擾
					CEnemy *pEnemy = (CEnemy*)pScene2D;
					D3DXVECTOR3 size = pEnemy->GetSize();

					for (int nCntAngle = 0; nCntAngle < 360; nCntAngle++)
					{
						// �����Ƒ���̓����蔻��
						if (Target.x - size.x / 2 >= m_Pos.x + 350.0f * cosf(D3DXToRadian(nCntAngle)) &&
							Target.x + size.x / 2 <= m_Pos.x - 350.0f * cosf(D3DXToRadian(nCntAngle)) &&
							Target.y + size.y / 2 <= m_Pos.y - 350.0f * cosf(D3DXToRadian(nCntAngle)) &&
							Target.y - size.y / 2 >= m_Pos.y + 350.0f * cosf(D3DXToRadian(nCntAngle)))
						{
							m_BombType = type;

							// �G�l�~�[�̔ԍ��ۊ�
							m_nBombNum = nCount;
							return true;
						}
					}
				}
				else if(type == TYPE_BULLET)
				{
					// �^�[�Q�b�g�̏��m��
					D3DXVECTOR3 Target = pScene2D->GetPosition();

					// �G�̃T�C�Y�擾
					CBullet *pBullet = (CBullet*)pScene2D;
					D3DXVECTOR3 size = pBullet->GetSize();
					for (int nCntAngle = 0; nCntAngle < 360; nCntAngle++)
					{
						// �����Ƒ���̓����蔻��
						if (Target.x - size.x / 2 >= m_Pos.x + 350.0f * cosf(D3DXToRadian(nCntAngle)) &&
							Target.x + size.x / 2 <= m_Pos.x - 350.0f * cosf(D3DXToRadian(nCntAngle)) &&
							Target.y + size.y / 2 <= m_Pos.y - 350.0f * cosf(D3DXToRadian(nCntAngle)) &&
							Target.y - size.y / 2 >= m_Pos.y + 350.0f * cosf(D3DXToRadian(nCntAngle)))
						{

							pBullet->DecreaseLife(10000);
							m_BombType = type;

							// �G�l�~�[�̔ԍ��ۊ�
							m_nBombNum = nCount;
						}
					}
				}
			}
		}
	}

	if (m_nBombFlame >= 2)
	{
		m_bBombUse = false;
	}

	return false;
}

//=============================================================================
// �V�[���h��Ԃ�Ԃ�
//=============================================================================
bool CPlayer::GetShildInfo(void)
{
	return m_bShildInfo;
}

//=============================================================================
// ���[�U�[���g���Ă��邩
//=============================================================================
bool CPlayer::GetUseLaser(void)
{
	return m_bUseLaser;
}

//=============================================================================
// ���[�U�[�Q�[�W�̏��
//=============================================================================
CGage *CPlayer::GetGage(void)
{
	return m_pGage;
}

//=============================================================================
// ���[�U�[�̏��
//=============================================================================
CLaser * CPlayer::GetLaser(void)
{
	return m_pLaser;
}
