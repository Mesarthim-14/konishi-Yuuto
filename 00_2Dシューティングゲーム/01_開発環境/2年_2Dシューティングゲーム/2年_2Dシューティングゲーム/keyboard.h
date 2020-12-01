//=====================================================
//
// �L�[�{�[�h [keyboard.h]
// Author : Konishi Yuuto
//
//=====================================================
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

//=====================================================
// �C���N���[�h�t�@�C��
//=====================================================
#include "main.h"
#include "input.h"

//=====================================================
// �}�N����`
//=====================================================
#define NUM_KEY_MAX (256)			// �L�[�ő吔

//=====================================================
// �O���錾
//=====================================================
class CInput;

//=====================================================
// �C���v�b�g�N���X
//=====================================================
class CKeyboard : public CInput
{
public:
	CKeyboard();		// �R���X�g���N�^
	~CKeyboard();		// �f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	bool GetPress(int nKey);					// �������̏���
	bool GetTrigger(int nKey);				// �����ꂽ����
	bool GetRelease(int nKey);

private:
	 BYTE m_aState[NUM_KEY_MAX];			// �L�[�{�[�h�̓��͏�񃏁[�N
	 BYTE m_aStateTrigger[NUM_KEY_MAX];		// �L�[�{�[�h�̃g���K�[���
	 BYTE m_aKeyStateRelease[NUM_KEY_MAX];	//�L�[�{�[�h�̃����[�X���

};

#endif
