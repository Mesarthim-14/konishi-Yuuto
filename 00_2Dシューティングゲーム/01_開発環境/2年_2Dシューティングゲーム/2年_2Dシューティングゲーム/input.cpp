//=====================================================
//
// 3D�Q�[�� �L�[���͏��� [input.cpp]
// Author:�����D�l
//
//=====================================================

//=====================================================
// �C���N���[�h�t�@�C��
//=====================================================
#include "input.h"

//=====================================================
// static����������
//=====================================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//=====================================================
// �R���X�g���N�^
//=====================================================
CInput::CInput()
{
	m_pDevice = NULL;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CInput::~CInput()
{

}

//=====================================================
// �����������i���z�֐��j
//=====================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		// DirectInput�I�u�W�F�N�g�̍쐬
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
		// ���̓f�o�C�X(�L�[�{�[�h)�̍쐬
		if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
		{
			return E_FAIL;
		}
		// �f�[�^�t�H�[�}�b�g��ݒ�
		if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
		{
			return E_FAIL;
		}
		// �������[�h��ݒ�(�t�H�A�O���E���h����r�����[�h)
		if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
		{
			return E_FAIL;
		}

		// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
		m_pDevice->Acquire();
	}
	return S_OK;
}

//=====================================================
// �I�������i���z�֐��j
//=====================================================
void CInput::Uninit(void)
{
	// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	if (m_pDevice != NULL)
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����J��(���͐���I��)
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	// DirectInput�I�u�W�F�N�g�̊J��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}