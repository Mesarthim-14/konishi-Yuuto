//=============================================================================
//
// �Q�[�����[�h�̏��� [game.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "game.h"
#include "renderer.h"
#include "input.h"
#include "keyboard.h"
#include "sound.h"
#include "light.h"
#include "laser.h"
#include "score.h"
#include "ui.h"
#include "bg.h"
#include "player.h"
#include "boss.h"
#include "manager.h"
#include "fade.h"
#include "remain.h"
#include "alert.h"
#include "icon.h"
#include "message.h"
#include "ranking.h"
#include "time.h"
#include "tutorial.h"

//=============================================================================
// static������
//=============================================================================
CScore *CGame::m_pScore = NULL;
int CGame::m_nCntEnemy = 0;
CBoss *CGame::m_pBoss = NULL;
CRemain *CGame::m_pRemain = NULL;
CAlert *CGame::m_pAlert = NULL;
CPlayer *CGame::m_pPlayer = NULL;
CIcon *CGame::m_pIcon = NULL;
CMessage *CGame::m_pMessage = NULL;
CTime *CGame::m_pTime = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	m_bCurrentFlag = false;
	m_nCntFlame = 0;
	m_nCntThroughFrame = 0;
	m_nCntThroughEnemy = 0;
	m_bThroughFlag = false;
	m_bThroughSwitch = false;
	m_gameState = GAMESTATE_NONE;
	m_Phase = GAME_PHASE_NONE;
	m_nCounterGameState = 0;
	m_nCntEnemyPop = 0;
	m_bBossFlag = false;
	m_nGameCounter = 0;
	m_bFirstPhaseEnd = false;
	m_bSecondPhaseEnd = false;
	m_bThirdPhaseEnd = false;
	m_nCntFollow = 0;
	m_nIconSoundFlame = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGame::Init(void)
{
	// �X�R�A����������
	m_pScore = new CScore;
	if (m_pScore != NULL)
	{
		m_pScore->Init(D3DXVECTOR3(WALL_SIZE_X * 0.75f, 50.0f, 0.0f),
			D3DXVECTOR3(NUMBER_SIZE_X, NUMBER_SIZE_Y, 0.0f),
			CScene::TYPE_SCORE);
	}

	if (m_pRemain == NULL)
	{
		// �c�@�̏�����
		m_pRemain = new CRemain;
		if (m_pRemain != NULL)
		{
			m_pRemain->Init(D3DXVECTOR3(WALL_SIZE_X * 0.73f, 690.0f, 0.0f),
				D3DXVECTOR3(REMAIN_SIZE_X, REMAIN_SIZE_Y, 0.0f),
				CScene::TYPE_SCORE);
		}
	}

	// �w�i�𐶐�
	CBackground::Create(
		D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 
		D3DXVECTOR3(BG_SIZE_X, WALL_SIZE_Y, 0.0f), CScene::TYPE_BG);

	// �v���C���[�̐���
	if (m_pPlayer == NULL)
	{
		m_pPlayer = CPlayer::Create(
			D3DXVECTOR3(600.0f, 600.0f, 0.0f), D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, 0.0f), CScene::TYPE_PLAYER);
	}

	// �ǂ̐���
	CUi::Create(
		D3DXVECTOR3(WALL_SIZE_X / 2, WALL_SIZE_Y / 2, 0.0f), 
		D3DXVECTOR3(WALL_SIZE_X, WALL_SIZE_Y, 0.0f),
		CScene::TYPE_UI, CUi::UI_TYPE_WALL);

	// �ǂ̐���
	CUi::Create(
		D3DXVECTOR3(SCREEN_WIDTH - WALL_SIZE_X / 2, WALL_SIZE_Y / 2, 0.0f), 
		D3DXVECTOR3(WALL_SIZE_X, WALL_SIZE_Y, 0.0f),
		CScene::TYPE_UI, CUi::UI_TYPE_WALL);

	// �g�̐���
	CUi::Create(
		D3DXVECTOR3(WALL_SIZE_X - 14.0f, WALL_SIZE_Y / 2, 0.0f),
		D3DXVECTOR3(WAKU_SIZE_X , WAKU_SIZE_Y, 0.0f),
		CScene::TYPE_UI, CUi::UI_TYPE_WAKU);

	// �g�̐���
	CUi::Create(
		D3DXVECTOR3(SCREEN_WIDTH - WALL_SIZE_X + 14.0f, WALL_SIZE_Y / 2, 0.0f),
		D3DXVECTOR3(WAKU_SIZE_X, WAKU_SIZE_Y, 0.0f),
		CScene::TYPE_UI, CUi::UI_TYPE_WAKU);

	// �c�@�̕\��
	CUi::Create(
		D3DXVECTOR3(WALL_SIZE_X * 0.58f, 685.0f, 0.0f),
		D3DXVECTOR3(SHIP_SIZE_X, SHIP_SIZE_Y, 0.0f),
		CScene::TYPE_UI, CUi::UI_TYPE_REMAIN);

	CTutorial::Create(
		D3DXVECTOR3(SCREEN_WIDTH - WALL_SIZE_X / 2 + 10.0f, WALL_SIZE_Y / 2, 0.0f), 
		D3DXVECTOR3(TUTORIAL_SIZE_X, TUTORIAL_SIZE_Y, 0.0f), CScene::TYPE_UI);

	//// �T�E���h�ݒ�
	CSound *pSound = NULL;
	pSound = CManager::GetSound();
	pSound->Play(CSound::SOUND_LABEL_GAME);

	m_gameState = GAMESTATE_NORMAL;		// �ʏ��Ԃɐݒ�
	m_Phase = GAME_PHASE_FIRST;
	m_nCounterGameState = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
	if (m_pScore != NULL)
	{
		CRanking::SetRanking(m_pScore->GetScore());
		// �X�R�A�I������
		m_pScore = NULL;
	}

	// �^�C��
	if (m_pTime != NULL)
	{
		m_pTime = NULL;
	}

	if (m_pPlayer != NULL)
	{
		// �v���C���[�I������
		m_pPlayer = NULL;
	}

	if (m_pBoss != NULL)
	{
		// �{�X�I������
		m_pBoss = NULL;
	}

	if (m_pRemain != NULL)
	{
		m_pRemain = NULL;
	}

	// �T�E���h�ݒ�
	CSound *pSound = NULL;
	pSound = CManager::GetSound();
	pSound->Stop(CSound::SOUND_LABEL_BOSS);

//	pSound->Stop(CSound::SOUND_LABEL_GAME);

	// �G�l�~�[�̑�����0�ɂ���
	m_nCntEnemy = 0;
}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	// �Q�[���̐ݒ�
	SetGame();

	switch (m_gameState)	// �Q�[�����
	{
	case GAMESTATE_NORMAL:	// �ʏ��Ԃ̎�
		break;
	case GAMESTATE_CLEAR:
		m_nCounterGameState++;	// �t���[�����𐔂���
		if (m_nCounterGameState >= 60)	// 1�b��(60�t���[��)
		{
			CManager::GetFade()->SetFade(CManager::MODE_RESULT);
		//	StopSound(SOUND_LABEL_BGM002);
			m_gameState = GAMESTATE_NONE;	// �������Ă��Ȃ���Ԃɂ���
			m_nCounterGameState = 0;		// ������������
		}
		break;

	case GAMESTATE_END:		// �Q�[���I����
		m_nCounterGameState++;	// �t���[�����𐔂���
		if (m_nCounterGameState >= 60)	// 1�b��(60�t���[��)
		{
			CManager::GetFade()->SetFade(CManager::MODE_RESULT);
			//	StopSound(SOUND_LABEL_BGM002);
			m_gameState = GAMESTATE_NONE;	// �������Ă��Ȃ���Ԃɂ���
			m_nCounterGameState = 0;		// ������������
		}
		break;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{

}


//=============================================================================
// �Q�[���̐ݒ�
//=============================================================================
void CGame::SetGame(void)
{
	m_nGameCounter++;
	int nChange = 0;

	switch (m_Phase)
	{
	// ���t�F�[�Y
	case GAME_PHASE_FIRST:

		switch (m_nGameCounter)
		{
		case 40:
			// �ŏ��̏o��
			for (int nCount = 0; nCount < 5; nCount++)
			{
				CEnemy::Create(
					D3DXVECTOR3(WALL_SIZE_X + 50.0f, 0.0f - (nCount * 60), 0.0f),
					D3DXVECTOR3(0.0f, 1.5f, 0.0f),
					D3DXVECTOR3(ENEMY_NORMAL_SIZE_X, ENEMY_NORMAL_SIZE_Y, 0.0f),
					CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_WHITE, CEnemy::ENEMY_TYPE_NORMAL);
				CScene::CountEnemy();
				m_nCntEnemy++;
			}
			break;

		case 140:

			// ���ڂ̏o��
			for (int nCount = 0; nCount < 5; nCount++)
			{
				CEnemy::Create(
					D3DXVECTOR3(SCREEN_WIDTH - WALL_SIZE_X - 50.0f, 0.0f - (nCount * 60), 0.0f),
					D3DXVECTOR3(0.0f, 1.5f, 0.0f),
					D3DXVECTOR3(ENEMY_NORMAL_SIZE_X, ENEMY_NORMAL_SIZE_Y, 0.0f),
					CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_BLACK, CEnemy::ENEMY_TYPE_NORMAL);
				CScene::CountEnemy();
				m_nCntEnemy++;
			}
			break;

		case 300:
			for (int nCount = 0; nCount < 5; nCount++)
			{
				CEnemy::Create(
					D3DXVECTOR3(WALL_SIZE_X + 50.0f, 0.0f - (nCount * 60), 0.0f),
					D3DXVECTOR3(0.0f, 1.5f, 0.0f),
					D3DXVECTOR3(ENEMY_NORMAL_SIZE_X, ENEMY_NORMAL_SIZE_Y, 0.0f),
					CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_WHITE, CEnemy::ENEMY_TYPE_NORMAL);
				CScene::CountEnemy();
				m_nCntEnemy++;

			}

			for (int nCount = 0; nCount < 5; nCount++)
			{
				CEnemy::Create(
					D3DXVECTOR3(SCREEN_WIDTH - WALL_SIZE_X - 50.0f, 0.0f - (nCount * 60), 0.0f),
					D3DXVECTOR3(0.0f, 1.5f, 0.0f),
					D3DXVECTOR3(ENEMY_NORMAL_SIZE_X, ENEMY_NORMAL_SIZE_Y, 0.0f),
					CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_BLACK, CEnemy::ENEMY_TYPE_NORMAL);
				CScene::CountEnemy();
				m_nCntEnemy++;

			}
			break;

		case 540:
			for (int nCntSnake = 0; nCntSnake < 7; nCntSnake++)
			{
				// �W�O�U�O�o��
				for (int nCount = 0; nCount < 3; nCount++)
				{
					CEnemy::Create(
						D3DXVECTOR3(WALL_SIZE_X + 75.0f + (nCount * 75), 0.0f - (nCntSnake * 40), 0.0f),
						D3DXVECTOR3(0.0f, 1.5f, 0.0f),
						D3DXVECTOR3(ENEMY_SNAKE_SIZE_X, ENEMY_SNAKE_SIZE_Y, 0.0f),
						CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_WHITE, CEnemy::ENEMY_TYPE_SNAKE);
					CScene::CountEnemy();
					m_nCntEnemy++;
				}
				for (int nCount = 0; nCount < 3; nCount++)
				{
					CEnemy::Create(
						D3DXVECTOR3(SCREEN_WIDTH - WALL_SIZE_X - 85.0f - (nCount * 75), 0.0f - (nCntSnake * 40), 0.0f),
						D3DXVECTOR3(0.0f, 1.5f, 0.0f),
						D3DXVECTOR3(ENEMY_SNAKE_SIZE_X, ENEMY_SNAKE_SIZE_Y, 0.0f),
						CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_BLACK, CEnemy::ENEMY_TYPE_SNAKE);
					CScene::CountEnemy();
					m_nCntEnemy++;
				}

			}
			// ���t�F�[�Y�I��
			m_bFirstPhaseEnd = true;
			break;

		default:
			break;
		}
		break;

		// �`���ԁ@���b�Z�[�W�`
	case GAME_PHASE_MESSAGE:
		switch (m_nGameCounter)
		{
		case 40:
			if (m_pIcon == NULL)
			{
				m_pIcon = CIcon::Create(
					D3DXVECTOR3(SCREEN_WIDTH - WALL_SIZE_X - 85.0f, 70.0f, 0.0f),
					D3DXVECTOR3(ICON_SIZE_X, ICON_SIZE_Y, 0.0f), CScene::TYPE_UI);

				// �T�E���h
				CSound *pSound = NULL;
				pSound = CManager::GetSound();
				pSound->Play(CSound::SOUND_LABEL_ICON);
			}
			break;

		}
		break;

		// ��O�t�F�[�Y
	case GAME_PHASE_SECOND:
		switch (m_nGameCounter)
		{
		case 40:
			for (int nCount = 0; nCount < CIRCLE_ENEMY_NUM; nCount++)
			{
				CEnemy::Circle(D3DXVECTOR3(
					WALL_SIZE_X + CIRCLE_DISTANCE*cosf(D3DXToRadian(CIRCLE_ANGLE + (nCount * CIRCLE_MAX_ANGLE / CIRCLE_ENEMY_NUM))),
					CIRCLE_INITIAL_Y + CIRCLE_DISTANCE*sinf(D3DXToRadian(CIRCLE_ANGLE + (nCount * CIRCLE_MAX_ANGLE / CIRCLE_ENEMY_NUM))), 0.0f),
					D3DXVECTOR3(ENEMY_NORMAL_SIZE_X, ENEMY_NORMAL_SIZE_Y, 0.0f),
					CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_WHITE, CEnemy::ENEMY_TYPE_CIRCLE,
					CIRCLE_DISTANCE, CIRCLE_ANGLE + (float)(nCount * CIRCLE_MAX_ANGLE / CIRCLE_ENEMY_NUM));
				CScene::CountEnemy();
				m_nCntEnemy++;
			}
			break;

		case 210:
			for (int nCount = 0; nCount < CIRCLE_ENEMY_NUM; nCount++)
			{
				CEnemy::Circle(D3DXVECTOR3(
					SCREEN_WIDTH - WALL_SIZE_X - CIRCLE_DISTANCE*cosf(D3DXToRadian(-CIRCLE_ANGLE + (nCount * CIRCLE_MAX_ANGLE / CIRCLE_ENEMY_NUM))),
					CIRCLE_INITIAL_Y + CIRCLE_DISTANCE*sinf(D3DXToRadian(-CIRCLE_ANGLE + (nCount * CIRCLE_MAX_ANGLE / CIRCLE_ENEMY_NUM))), 0.0f),
					D3DXVECTOR3(ENEMY_NORMAL_SIZE_X, ENEMY_NORMAL_SIZE_Y, 0.0f),
					CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_BLACK, CEnemy::ENEMY_TYPE_CIRCLE,
					-CIRCLE_DISTANCE, -(CIRCLE_ANGLE + (float)(nCount * CIRCLE_MAX_ANGLE / CIRCLE_ENEMY_NUM)));
				CScene::CountEnemy();
				m_nCntEnemy++;
			}
			break;

		case 390:		//260
			nChange = 0;
			for (int nCount = 0; nCount < 3; nCount++)
			{
				if (nChange % 2 == 0)
				{
					CEnemy::Create(
						D3DXVECTOR3(SCREEN_WIDTH - WALL_SIZE_X - 85.0f - ((float)nCount * 50.0f), 0.0f, 0.0f),
						D3DXVECTOR3(0.0f, 1.5f, 0.0f),
						D3DXVECTOR3(ENEMY_CURRENT_SIZE_X, ENEMY_CURRENT_SIZE_Y, 0.0f),
						CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_BLACK, CEnemy::ENEMY_TYPE_CURRENT);
					m_nCntEnemy++;
					CScene::CountEnemy();
					nChange++;
				}
				else
				{
					CEnemy::Create(
						D3DXVECTOR3(SCREEN_WIDTH - WALL_SIZE_X - 85.0f - ((float)nCount * 50.0f), 0.0f + (nCount * 60), 0.0f),
						D3DXVECTOR3(0.0f, 1.5f, 0.0f),
						D3DXVECTOR3(ENEMY_CURRENT_SIZE_X, ENEMY_CURRENT_SIZE_Y, 0.0f),
						CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_BLACK, CEnemy::ENEMY_TYPE_CURRENT);
					m_nCntEnemy++;
					CScene::CountEnemy();
					nChange++;
				}
			}
			break;
		case 470:
			nChange = 0;
			for (int nCount = 0; nCount < 3; nCount++)
			{
				if (nChange % 2 == 0)
				{
					CEnemy::Create(
						D3DXVECTOR3(WALL_SIZE_X + 175.0f - ((float)nCount * 50.0f), 0.0f, 0.0f),
						D3DXVECTOR3(0.0f, 1.5f, 0.0f),
						D3DXVECTOR3(ENEMY_CURRENT_SIZE_X, ENEMY_CURRENT_SIZE_Y, 0.0f),
						CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_WHITE, CEnemy::ENEMY_TYPE_CURRENT);
					m_nCntEnemy++;
					CScene::CountEnemy();
					nChange++;
				}
				else
				{
					CEnemy::Create(
						D3DXVECTOR3(WALL_SIZE_X + 175.0f - ((float)nCount * 50.0f), 0.0f + (nCount * 60), 0.0f),
						D3DXVECTOR3(0.0f, 1.5f, 0.0f),
						D3DXVECTOR3(ENEMY_CURRENT_SIZE_X, ENEMY_CURRENT_SIZE_Y, 0.0f),
						CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_WHITE, CEnemy::ENEMY_TYPE_CURRENT);
					m_nCntEnemy++;
					CScene::CountEnemy();
					nChange++;

				}
			}
			break;
		case 620:
			nChange = 0;
			for (int nCount = 0; nCount < 3; nCount++)
			{
				if (nChange % 2 == 0)
				{
					CEnemy::Create(
						D3DXVECTOR3(SCREEN_WIDTH - WALL_SIZE_X - 85.0f - ((float)nCount * 50.0f), 0.0f, 0.0f),
						D3DXVECTOR3(0.0f, 1.5f, 0.0f),
						D3DXVECTOR3(ENEMY_CURRENT_SIZE_X, ENEMY_CURRENT_SIZE_Y, 0.0f),
						CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_BLACK, CEnemy::ENEMY_TYPE_CURRENT);
					m_nCntEnemy++;
					CScene::CountEnemy();
					nChange++;
				}
				else
				{
					CEnemy::Create(
						D3DXVECTOR3(SCREEN_WIDTH - WALL_SIZE_X - 85.0f - ((float)nCount * 50.0f), 0.0f + (nCount * 60), 0.0f),
						D3DXVECTOR3(0.0f, 1.5f, 0.0f),
						D3DXVECTOR3(ENEMY_CURRENT_SIZE_X, ENEMY_CURRENT_SIZE_Y, 0.0f),
						CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_BLACK, CEnemy::ENEMY_TYPE_CURRENT);
					m_nCntEnemy++;
					CScene::CountEnemy();
					nChange++;
				}
			}
			break;

		case 700:
			nChange = 0;
			for (int nCount = 0; nCount < 3; nCount++)
			{
				if (nChange % 2 == 0)
				{
					CEnemy::Create(
						D3DXVECTOR3(WALL_SIZE_X + 175.0f - ((float)nCount * 50.0f), 0.0f, 0.0f),
						D3DXVECTOR3(0.0f, 1.5f, 0.0f),
						D3DXVECTOR3(ENEMY_CURRENT_SIZE_X, ENEMY_CURRENT_SIZE_Y, 0.0f),
						CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_WHITE, CEnemy::ENEMY_TYPE_CURRENT);
					m_nCntEnemy++;
					CScene::CountEnemy();
					nChange++;
				}
				else
				{
					CEnemy::Create(
						D3DXVECTOR3(WALL_SIZE_X + 175.0f - ((float)nCount * 50.0f), 0.0f + (nCount * 60), 0.0f),
						D3DXVECTOR3(0.0f, 1.5f, 0.0f),
						D3DXVECTOR3(ENEMY_CURRENT_SIZE_X, ENEMY_CURRENT_SIZE_Y, 0.0f),
						CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_WHITE, CEnemy::ENEMY_TYPE_CURRENT);
					m_nCntEnemy++;
					CScene::CountEnemy();
					nChange++;

				}
			}
			break;

		case 900:
			CEnemy::Create(
				D3DXVECTOR3(SCREEN_WIDTH - WALL_SIZE_X - 75.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 1.5f, 0.0f),
				D3DXVECTOR3(ENEMY_CURRENT_SIZE_X, ENEMY_CURRENT_SIZE_Y, 0.0f),
				CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_WHITE, CEnemy::ENEMY_TYPE_THROUGH);
			m_nCntEnemy++;
			CScene::CountEnemy();
			break;

		case 940:
			CEnemy::Create(
				D3DXVECTOR3(WALL_SIZE_X + 75.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 1.5f, 0.0f),
				D3DXVECTOR3(ENEMY_CURRENT_SIZE_X, ENEMY_CURRENT_SIZE_Y, 0.0f),
				CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_WHITE, CEnemy::ENEMY_TYPE_THROUGH);
			m_nCntEnemy++;
			CScene::CountEnemy();
			break;

		case 980:
			CEnemy::Create(
				D3DXVECTOR3(SCREEN_WIDTH - WALL_SIZE_X - 75.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 1.5f, 0.0f),
				D3DXVECTOR3(ENEMY_CURRENT_SIZE_X, ENEMY_CURRENT_SIZE_Y, 0.0f),
				CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_WHITE, CEnemy::ENEMY_TYPE_THROUGH);
			m_nCntEnemy++;
			CScene::CountEnemy();
			break;

		case 1020:
			CEnemy::Create(
				D3DXVECTOR3(WALL_SIZE_X + 75.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 1.5f, 0.0f),
				D3DXVECTOR3(ENEMY_CURRENT_SIZE_X, ENEMY_CURRENT_SIZE_Y, 0.0f),
				CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_WHITE, CEnemy::ENEMY_TYPE_THROUGH);
			m_nCntEnemy++;
			CScene::CountEnemy();
			break;

		case 1060:
			CEnemy::Create(
				D3DXVECTOR3(SCREEN_WIDTH - WALL_SIZE_X - 75.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 1.5f, 0.0f),
				D3DXVECTOR3(ENEMY_CURRENT_SIZE_X, ENEMY_CURRENT_SIZE_Y, 0.0f),
				CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_WHITE, CEnemy::ENEMY_TYPE_THROUGH);
			m_nCntEnemy++;
			CScene::CountEnemy();
			break;

		case 1100:
			CEnemy::Create(
				D3DXVECTOR3(WALL_SIZE_X + 75.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 1.5f, 0.0f),
				D3DXVECTOR3(ENEMY_CURRENT_SIZE_X, ENEMY_CURRENT_SIZE_Y, 0.0f),
				CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_BLACK, CEnemy::ENEMY_TYPE_THROUGH);
			m_nCntEnemy++;
			CScene::CountEnemy();
			break;

		case 1140:
			CEnemy::Create(
				D3DXVECTOR3(SCREEN_WIDTH - WALL_SIZE_X - 75.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 1.5f, 0.0f),
				D3DXVECTOR3(ENEMY_CURRENT_SIZE_X, ENEMY_CURRENT_SIZE_Y, 0.0f),
				CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_BLACK, CEnemy::ENEMY_TYPE_THROUGH);
			m_nCntEnemy++;
			CScene::CountEnemy();
			break;

		case 1180:
			CEnemy::Create(
				D3DXVECTOR3(WALL_SIZE_X + 75.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 1.5f, 0.0f),
				D3DXVECTOR3(ENEMY_CURRENT_SIZE_X, ENEMY_CURRENT_SIZE_Y, 0.0f),
				CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_BLACK, CEnemy::ENEMY_TYPE_THROUGH);
			m_nCntEnemy++;
			CScene::CountEnemy();
			break;

		case 1220:
			CEnemy::Create(
				D3DXVECTOR3(SCREEN_WIDTH - WALL_SIZE_X - 75.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 1.5f, 0.0f),
				D3DXVECTOR3(ENEMY_CURRENT_SIZE_X, ENEMY_CURRENT_SIZE_Y, 0.0f),
				CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_BLACK, CEnemy::ENEMY_TYPE_THROUGH);
			m_nCntEnemy++;
			CScene::CountEnemy();
			break;

		case 1260:
			CEnemy::Create(
				D3DXVECTOR3(WALL_SIZE_X + 75.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 1.5f, 0.0f),
				D3DXVECTOR3(ENEMY_CURRENT_SIZE_X, ENEMY_CURRENT_SIZE_Y, 0.0f),
				CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_BLACK, CEnemy::ENEMY_TYPE_THROUGH);
			m_nCntEnemy++;
			CScene::CountEnemy();
			break;

		case 1400:
			for (int nCount = 0; nCount < 10; nCount++)
			{
				CEnemy::Rotation(
					D3DXVECTOR3(600.0f, 500.0f, 0.0f),
					D3DXVECTOR3(0.0f, 1.5f, 0.0f),
					D3DXVECTOR3(ENEMY_NORMAL_SIZE_X, ENEMY_NORMAL_SIZE_Y, 0.0f),
					CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_WHITE, CEnemy::ENEMY_TYPE_ROTATION,
					INSIDE_ROTATION_RADIUS, 0.0f + ((float)nCount*(360.0f / 10.0f)));
				CScene::CountEnemy();
				m_nCntEnemy++;
			}
			for (int nCount = 0; nCount < 10; nCount++)
			{
				CEnemy::Rotation(
					D3DXVECTOR3(600.0f, 500.0f, 0.0f),
					D3DXVECTOR3(0.0f, 1.5f, 0.0f),
					D3DXVECTOR3(ENEMY_NORMAL_SIZE_X, ENEMY_NORMAL_SIZE_Y, 0.0f),
					CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_BLACK, CEnemy::ENEMY_TYPE_ROTATION,
					OUTSIDE_ROTATION_RADIUS, 0.0f + ((float)nCount*(360.0f / 10.0f)));
				CScene::CountEnemy();
				m_nCntEnemy++;
			}
			break;

		case 1800:
			for (int nCount = 0; nCount < 3; nCount++)
			{
				CEnemy::Direction(
					D3DXVECTOR3(WALL_SIZE_X + 75.0f, -10.0f - nCount*100.0f, 0.0f),
					D3DXVECTOR3(ENEMY_NORMAL_SIZE_X, ENEMY_NORMAL_SIZE_Y, 0.0f),
					CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_WHITE, CEnemy::ENEMY_TYPE_DIRECTION, 0);

				CScene::CountEnemy();
				m_nCntEnemy++;
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{
				CEnemy::Direction(
					D3DXVECTOR3(SCREEN_WIDTH - WALL_SIZE_X - 75.0f, -10.0f - nCount*100.0f, 0.0f),
					D3DXVECTOR3(ENEMY_NORMAL_SIZE_X, ENEMY_NORMAL_SIZE_Y, 0.0f),
					CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_WHITE, CEnemy::ENEMY_TYPE_DIRECTION, 1);

				CScene::CountEnemy();
				m_nCntEnemy++;
			}
			break;

		case 1900:
			for (int nCount = 0; nCount < 3; nCount++)
			{
				CEnemy::Direction(
					D3DXVECTOR3(WALL_SIZE_X + 75.0f, -10.0f - nCount*100.0f, 0.0f),
					D3DXVECTOR3(ENEMY_NORMAL_SIZE_X, ENEMY_NORMAL_SIZE_Y, 0.0f),
					CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_WHITE, CEnemy::ENEMY_TYPE_DIRECTION, 0);

				CScene::CountEnemy();
				m_nCntEnemy++;
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{
				CEnemy::Direction(
					D3DXVECTOR3(SCREEN_WIDTH - WALL_SIZE_X - 75.0f, -10.0f - nCount*100.0f, 0.0f),
					D3DXVECTOR3(ENEMY_NORMAL_SIZE_X, ENEMY_NORMAL_SIZE_Y, 0.0f),
					CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_WHITE, CEnemy::ENEMY_TYPE_DIRECTION, 1);

				CScene::CountEnemy();
				m_nCntEnemy++;
			}
			break;

		case 2000:

			m_bSecondPhaseEnd = true;

			for (int nCount = 0; nCount < 3; nCount++)
			{
				CEnemy::Direction(
					D3DXVECTOR3(WALL_SIZE_X + 75.0f, -10.0f - nCount*100.0f, 0.0f),
					D3DXVECTOR3(ENEMY_NORMAL_SIZE_X, ENEMY_NORMAL_SIZE_Y, 0.0f),
					CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_WHITE, CEnemy::ENEMY_TYPE_DIRECTION, 0);

				CScene::CountEnemy();
				m_nCntEnemy++;
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{
				CEnemy::Direction(
					D3DXVECTOR3(SCREEN_WIDTH - WALL_SIZE_X - 75.0f, -10.0f - nCount*100.0f, 0.0f),
					D3DXVECTOR3(ENEMY_NORMAL_SIZE_X, ENEMY_NORMAL_SIZE_Y, 0.0f),
					CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_WHITE, CEnemy::ENEMY_TYPE_DIRECTION, 1);

				CScene::CountEnemy();
				m_nCntEnemy++;
			}
			break;
		}
		break;

		case GAME_PHASE_THIRD:
			if (m_nGameCounter >= 40)
			{
				if (m_nGameCounter % 5 == 0 && m_nCntFollow <= 15)
				{
					m_bThirdPhaseEnd = true;
					int nDistance = 450 + (rand() % 300);

					CEnemy::Follow(
						D3DXVECTOR3(WALL_SIZE_X + nDistance *cosf(D3DXToRadian(0+((m_nCntFollow * 2) * (90 / 30)))),
						(SCREEN_HEIGHT - 100.0f) - nDistance *sinf(D3DXToRadian(0 + ((m_nCntFollow * 2) * (90 / 30)))),
						0.0f),
						D3DXVECTOR3(ENEMY_FOLLOW_SIZE_X, ENEMY_NORMAL_SIZE_Y, 0.0f),
						CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_WHITE, CEnemy::ENEMY_TYPE_FOLLOW);

					m_nCntFollow++;
					CScene::CountEnemy();
					m_nCntEnemy++;

				}
				else if (m_nGameCounter % 5 == 0 && m_nCntFollow > 15 && m_nCntFollow <= 60)
				{
					int nDistance = 450 + (rand() % 300);

					int nAngle = rand() % 90;

					CEnemy::Follow(
						D3DXVECTOR3(WALL_SIZE_X + nDistance *cosf(D3DXToRadian(nAngle)),
							(SCREEN_HEIGHT-100.0f) - nDistance *sinf(D3DXToRadian(nAngle)),
							0.0f),
						D3DXVECTOR3(ENEMY_FOLLOW_SIZE_X, ENEMY_NORMAL_SIZE_Y, 0.0f),
						CScene::TYPE_ENEMY, CEnemy::COLOR_TYPE_WHITE, CEnemy::ENEMY_TYPE_FOLLOW);

					m_nCntFollow++;
					CScene::CountEnemy();
					m_nCntEnemy++;

				}
			}

			break;

		case GAME_PHASE_FOUR:

			break;

	case GAME_PHASE_BOSS:
		if (m_bBossFlag == false)
		{

			if (m_pAlert == NULL)
			{
				m_pAlert = CAlert::Create(
					D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
					D3DXVECTOR3(580.0f, 300.0f, 0.0f),
					CScene::TYPE_WARNING);

				// �T�E���h�ݒ�
				CSound *pSound = NULL;
				pSound = CManager::GetSound();

				pSound->Stop(CSound::SOUND_LABEL_GAME);

				pSound->Play(CSound::SOUND_LABEL_ARERT);

			}
		}

		if (m_bBossFlag == false && m_pAlert != NULL)
		{
			bool bAlert = m_pAlert->GetAlertFlag();

			if (bAlert == true)
			{
				if (m_pBoss == NULL)
				{

					// �T�E���h�ݒ�
					CSound *pSound = NULL;
					pSound = CManager::GetSound();
					pSound->Play(CSound::SOUND_LABEL_BOSS);

					m_pBoss = CBoss::Create(D3DXVECTOR3(SCREEN_WIDTH - WALL_SIZE_X - 100.0f, -450.0f, 0.0f),
						D3DXVECTOR3(BOSS_SIZE_X, BOSS_SIZE_Y, 0.0f),
						CScene::TYPE_BOSS);

					CScene::CountEnemy();
					m_nCntEnemy++;
					m_bBossFlag = true;

					// �^�C��
					if (m_pTime == NULL)
					{
						m_pTime = new CTime;

						if (m_pTime != NULL)
						{
							m_pTime->Init(D3DXVECTOR3(SCREEN_WIDTH / 2 + 50.0f, 50.0f, 0.0f),
								D3DXVECTOR3(TIME_SIZE_X, TIME_SIZE_Y, 0.0f), CScene::TYPE_SCORE);
						}

					}

				}

				if (m_pAlert != NULL)
				{
					// �A���[�g�I������
					m_pAlert->Uninit();
					m_pAlert = NULL;

					// �T�E���h�ݒ�
					CSound *pSound = NULL;
					pSound = CManager::GetSound();
					pSound->Stop(CSound::SOUND_LABEL_ARERT);
				}
			}
		}
	}

	// ���t�F�[�Y�̏I��
	if (m_bFirstPhaseEnd == true)
	{
		int nNumEnemy = CScene::GetEnemyNum();

		if (nNumEnemy == 0)
		{
			m_Phase = GAME_PHASE_MESSAGE;
			m_bFirstPhaseEnd = false;
			m_nGameCounter = 0;
		}
	}

	// ���t�F�[�Y�̏I��
	if (m_bSecondPhaseEnd == true)
	{
		int nNumEnemy = CScene::GetEnemyNum();

		if (nNumEnemy == 0)
		{
			m_Phase = GAME_PHASE_THIRD;
			m_bSecondPhaseEnd = false;
			m_nGameCounter = 0;
		}
	}

	// ���t�F�[�Y�̏I��
	if (m_bThirdPhaseEnd == true)
	{
		int nNumEnemy = CScene::GetEnemyNum();

		if (nNumEnemy == 0)
		{
			m_Phase = GAME_PHASE_BOSS;
			m_bThirdPhaseEnd = false;
			m_nGameCounter = 0;
		}
	}


	// ����MESSAGE�A�C�R���̏I��
	if (m_pIcon != NULL)
	{
		m_nIconSoundFlame++;

		if (m_nIconSoundFlame % 80 == 0)
		{
			// �T�E���h
			CSound *pSound = NULL;
			pSound = CManager::GetSound();
			pSound->Play(CSound::SOUND_LABEL_ICON);
		}
		if (m_pIcon->GetEndIcon() == true)
		{
			m_pIcon->Uninit();
			m_pIcon = NULL;

			// ���b�Z�[�W�\��
			if (m_pMessage == NULL)
			{
				m_pMessage = CMessage::Create(
					D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
					D3DXVECTOR3(520.0f, 280.0f, 0.0f),
					CScene::TYPE_WARNING);

				// �T�E���h�X�g�b�v
				CSound *pSound = NULL;
				pSound = CManager::GetSound();
				pSound->Play(CSound::SOUND_LABEL_MESSAGE);
			}
			return;
		}
	}

	// ���ԃ��b�Z�[�W�I��
	if (m_pMessage != NULL)
	{
		if (m_pMessage->GetEndMessage() == true)
		{
			m_pMessage->Uninit();
			m_pMessage = NULL;

			// ���t�F�C�Y��
			m_Phase = GAME_PHASE_SECOND;
			m_nGameCounter = 0;
			return;
		}
	}

	int nCnt = m_nCntEnemy;			// 71
}

//=============================================================================
// �X�R�A����Ԃ�
//=============================================================================
CScore * CGame::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
// �{�X�̏���Ԃ�
//=============================================================================
CBoss * CGame::GetBoss(void)
{
	return m_pBoss;
}

//=============================================================================
// �c�@�̏��
//=============================================================================
CRemain * CGame::GetRemain(void)
{
	return m_pRemain;
}

//=============================================================================
// �v���C���[�̏��
//=============================================================================
CPlayer * CGame::GetPlayer(void)
{
	return m_pPlayer;
}