#ifndef _MANAGER_H_
#define _MANAGER_H_
//=============================================================================
//
// �}�l�[�W���[�����̃w�b�_�[ [manager.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
// �O���錾
//=============================================================================
class CTitle;
class CRenderer;
class CInput;
class CKeyboard;
class CSound;
class CGame;
class CResult;
class CFade;
class CInputJoypad;

//=============================================================================
// �}�l�[�W���[�N���X
//=============================================================================
class CManager
{
public:
	typedef enum
	{
		MODE_TITLE = 0,		// �^�C�g�����
		MODE_GAME,			// �Q�[�����
		MODE_RESULT,		// ���U���g���
		MODE_MAX			// �ő吔
	}MODE;

	CManager();		// �R���X�g���N�^
	~CManager();	// �f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);		// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

	void SetFPS(int nCountFPS);										// �f�o�b�O�\��
	static CRenderer *GetRenderer(void);							// �����_���[�̏��
	static CKeyboard *GetKeyboard(void);							// �L�[�{�[�h�̏��
	static CSound *GetSound(void);									// �T�E���h�̏��
	static CTitle *GetTitle(void);									// �^�C�g���̏��
	static CResult *GetResult(void);								// ���U���g�̏��
	static CFade *GetFade(void);									// �t�F�[�h���
	static CInputJoypad *GetJoypad(void);							// �W���C�p�b�h�̎擾����
	static void SetMode(MODE mode);									// ���[�h�̐ݒ�
	static MODE GetMode(void);										// ���[�h�̏��

private:
	static CRenderer *m_pRenderer;			// �����_���[�̃|�C���^
	static CInput *m_pInput;				// ���͏����̃|�C���^
	static CKeyboard *m_pKeyboard;			// �L�[�{�[�h�����̃|�C���^
	static CSound *m_pSound;				// �T�E���h�̃|�C���^
	static MODE m_Mode;						// ���[�h�̏��
	static CTitle *m_pTitle;				// �^�C�g���̃|�C���^
	static CGame *m_pGame;					// �Q�[���̃|�C���^
	static CResult *m_pResult;				// ���U���g��ʂ̃|�C���^
	static CFade *m_pFade;					// �t�F�[�h�̃|�C���^
	static CInputJoypad*m_pJoypad;			// �W���C�p�b�h�|�C���^

};

#endif