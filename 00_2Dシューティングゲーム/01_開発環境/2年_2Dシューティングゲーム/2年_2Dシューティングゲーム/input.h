//=====================================================
//
// �C���v�b�g���� [input.h]
// Author:�����D�l
//
//=====================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//=====================================================
// �C���N���[�h�t�@�C��
//=====================================================
#include "main.h"
#define DIRECTINPUT_VERSION (0x0800)	// �x���Ώ��p("dinput.h"�̒��O�ɒ�`)
#include "dinput.h"

#pragma comment(lib, "dinput8.lib")

//=====================================================
// �}�N����`
//=====================================================
#define NUM_KEY_MAX (256)			// �L�[�ő吔

//=====================================================
// �C���v�b�g�N���X
//=====================================================
class CInput
{
public:
	CInput();					// �R���X�g���N�^
	virtual ~CInput() = 0;		// �f�X�g���N�^

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ����������
	virtual void Uninit(void);								// �I������
	virtual void Update(void) = 0;								// �X�V����

protected:
	static LPDIRECTINPUT8 m_pInput;				// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pDevice;				// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^

};

#endif
