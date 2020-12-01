//=============================================================================
//
// �^�C�g���̏��� [title.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//==================================================================
// �C���N���[�h
//==================================================================
#include "title.h"
#include "titlebg.h"
#include "renderer.h"
#include "keyboard.h"
#include "manager.h"
#include "fade.h"
#include "start_logo.h"
#include "crow.h"
#include "manager.h"
#include "joypad.h"
#include "sound.h"

//==================================================================
// static����������
//==================================================================
CTitleBg *CTitle::m_pTitleBg = NULL;

//==================================================================
// �R���X�g���N�^
//==================================================================
CTitle::CTitle()
{
	m_nCrowCreateFlame = 499;
}

//==================================================================
// �f�X�g���N�^
//==================================================================
CTitle::~CTitle()
{

}

//==================================================================
// ����������
//==================================================================
HRESULT CTitle::Init()
{
	// �^�C�g��
	m_pTitleBg = CTitleBg::Create(
		D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 
		D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CScene::TYPE_BG );

	// �^�C�g�����S
	CStartLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, START_LOGO_POS_Y, 0.0f),
		D3DXVECTOR3(START_LOGO_SIZE_X, START_LOGO_SIZE_Y, 0.0f), CScene::TYPE_UI);

	// �T�E���h�ݒ�
	CSound *pSound = NULL;
	pSound = CManager::GetSound();
	pSound->Play(CSound::SOUND_LABEL_TITLE);

	return S_OK;
}

//==================================================================
// �I������
//==================================================================
void CTitle::Uninit(void)
{
	if (m_pTitleBg != NULL)
	{
		m_pTitleBg->Uninit();
	}
}

//==================================================================
// �X�V����
//==================================================================
void CTitle::Update(void)
{
	m_nCrowCreateFlame++;

	// ���Ԋu��
	if (m_nCrowCreateFlame % 500 == 0)
	{
		for (int nCount = 0; nCount < 3; nCount++)
		{
			// �J���X����
			CCrow::Create(D3DXVECTOR3(CROW_POS_X -nCount*90.0f, CROW_POS_Y, 0.0f), D3DXVECTOR3(CROW_MOVE_X, CROW_MOVE_Y, 0.0f),
				D3DXVECTOR3(CROW_SIZE_X, CROW_SIZE_Y, 0.0f), CScene::TYPE_ENEMY);
		}
	}

	// �L�[�{�[�h�X�V
	CKeyboard *pKeyboard = CManager::GetKeyboard();
	
	// �t�F�[�h���
	CFade::FADE fade = CManager::GetFade()->Get();

	// W�L�[���������Ƃ�
	if (pKeyboard->GetTrigger(DIK_RETURN) && 
		fade == CFade::FADE_NONE ||
		CManager::GetJoypad()->GetJoystickTrigger(11, 0) && 
		fade == CFade::FADE_NONE)
	{

		CSound *pSound = NULL;
		pSound = CManager::GetSound();
		pSound->Stop(CSound::SOUND_LABEL_TITLE);

		CManager::GetFade()->SetFade(CManager::MODE_GAME);
	}
}

//==================================================================
// �`�揈��
//==================================================================
void CTitle::Draw(void)
{

}

//==================================================================
// �^�C�g���w�i�̏��
//==================================================================
CTitleBg * CTitle::GetTitleBg(void)
{
	return m_pTitleBg;
}