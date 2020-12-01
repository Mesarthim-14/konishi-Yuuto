//=============================================================================
//
// ���U���g�̏��� [result.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//==================================================================
// �C���N���[�h
//==================================================================
#include "result.h"
#include "resultbg.h"
#include "renderer.h"
#include "keyboard.h"
#include "manager.h"
#include "fade.h"
#include "ranking.h"
#include "joypad.h"
#include "sound.h"

//==================================================================
// static����������
//==================================================================
CResultBg *CResult::m_pResultBg = NULL;

//==================================================================
// �R���X�g���N�^
//==================================================================
CResult::CResult()
{

}

//==================================================================
// �f�X�g���N�^
//==================================================================
CResult::~CResult()
{

}

//==================================================================
// ����������
//==================================================================
HRESULT CResult::Init()
{
	// ���U���g����
	m_pResultBg = CResultBg::Create(
		D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CScene::TYPE_BG);

	// �����L���O����
	CRanking::Create();

	// �T�E���h�ݒ�
	CSound *pSound = NULL;
	pSound = CManager::GetSound();
	pSound->Play(CSound::SOUND_LABEL_RESULT);

	return S_OK;
}

//==================================================================
// �I������
//==================================================================
void CResult::Uninit(void)
{
	// �I������
	m_pResultBg->Uninit();
}

//==================================================================
// �X�V����
//==================================================================
void CResult::Update(void)
{
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
		// �T�E���h�ݒ�
		CSound *pSound = NULL;
		pSound = CManager::GetSound();
		pSound->Stop(CSound::SOUND_LABEL_RESULT);

		// �t�F�[�h�ڍs
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TITLE);

		return;
	}
}

//==================================================================
// �`�揈��
//==================================================================
void CResult::Draw(void)
{

}

//==================================================================
// �^�C�g���w�i�̏��
//==================================================================
CResultBg * CResult::GetResultBg(void)
{
	return m_pResultBg;
}