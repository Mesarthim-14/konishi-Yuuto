#ifndef _RENDERER_H_
#define _RENDERER_H_
//=============================================================================
//
// �����_�����O�w�b�_�[ [renderer.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SCREEN_WIDTH (1280)		// �E�C���h�E�̕�	1280
#define SCREEN_HEIGHT (720)		// �E�C���h�E�̍���	720

// ���_�t�H�[�}�b�g(���_���W[2D]/���_�J���[/�e�N�X�`�����W)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//=============================================================================
// �����_���[�N���X
//=============================================================================
class CRenderer
{
public:
	CRenderer();		// �R���X�g���N�^
	~CRenderer();		// �f�X�g���N�^

	HRESULT Init(HWND hWnd, bool bWindow);	// ����������
	void Uninit(void);						// �I������
	void Update(void);						// �X�V����
	void Draw(void);						// �`�揈��

	void SetFPS(int nCountFPS);				// FPS�̐ݒ�
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	// �f�o�C�X�̏��󂯎��
private:
	// �����o�ϐ�
	void DrawFPS(void);					// �f�o�b�O�\��
	LPDIRECT3D9 m_pD3D;					// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice;		// Device�I�u�W�F�N�g(�`��ɕK�v)
	LPD3DXFONT m_pFont;					// �t�H���g�ւ̃|�C���^
	int m_nCountFPS;					// FPS�̃|�C���^
};
#endif