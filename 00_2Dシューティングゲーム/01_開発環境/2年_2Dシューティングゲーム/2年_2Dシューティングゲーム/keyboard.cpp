//=====================================================
//
// 3D�Q�[�� �L�[���͏��� [keyboard.cpp]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// �C���N���[�h�t�@�C��
//=====================================================
#include "input.h"
#include "keyboard.h"

//=====================================================
// �R���X�g���N�^
//=====================================================
CKeyboard::CKeyboard()
{
	// �L�[���N���A
	memset(m_aState, 0, sizeof(m_aState));
	memset(m_aStateTrigger, 0, sizeof(m_aStateTrigger));
	memset(m_aKeyStateRelease, 0, sizeof(m_aKeyStateRelease));

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CKeyboard::~CKeyboard()
{

}

//=====================================================
// �L�[�{�[�h�̏�����
//=====================================================
HRESULT CKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	return S_OK;
}

//=====================================================
// �L�[�{�[�h�̏I������
//=====================================================
void CKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//=====================================================
// �L�[�{�[�h�̍X�V����
//=====================================================
void CKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];		// �L�[�{�[�h�̓��͏��

	int nCntKey;		// ���[�J���ϐ�

	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			// �g���K�[����
			m_aStateTrigger[nCntKey] = (m_aState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aState[nCntKey] ^ aKeyState[nCntKey])&~aKeyState[nCntKey];
			// �L�[�v���X����ۑ�
			m_aState[nCntKey] = aKeyState[nCntKey];
		}
	}

	// �L�[�{�[�h�̍X�V����
	else
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
		m_pDevice->Acquire();
	}
}

//=====================================================
// �L�[�{�[�h�̃v���X��Ԃ��擾
//=====================================================
bool CKeyboard::GetPress(int nKey)
{
	return (m_aState[nKey] & 0x80) ? true : false;
}
//=====================================================
// �L�[�{�[�h�̃g���K�[
//=====================================================
bool CKeyboard::GetTrigger(int nKey)
{
	return(m_aStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
//�L�[�{�[�h�̃����[�X���̎擾
//=============================================================================
bool CKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}