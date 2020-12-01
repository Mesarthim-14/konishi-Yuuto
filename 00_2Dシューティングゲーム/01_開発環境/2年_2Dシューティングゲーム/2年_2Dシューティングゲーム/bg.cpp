//=============================================================================
//
// �o�b�O�O���E���h���� [bg.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "bg.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CBackground::m_apTexture[MAX_BG_TEXTURE] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBackground::CBackground()
{
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		m_apScene2D[nCount] = NULL;
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBackground::~CBackground()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CBackground * CBackground::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// �������m��
	CBackground *pBackground = new CBackground;

	// ����������
	pBackground->Init(pos, size, type);

	return pBackground;
}

//=============================================================================
// �e�N�X�`���̃��[�h
//=============================================================================
HRESULT CBackground::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/bg006.png",
		&m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/bg100.png",
		&m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/bg004.png",
		&m_apTexture[2]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̃A�����[�h
//=============================================================================
void CBackground::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		// �e�N�X�`���̊J��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBackground::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		// �g���Ă��Ȃ��Ƃ�
		if (m_apScene2D[nCount] == NULL)
		{
			// ����������
			m_apScene2D[nCount] = new CScene2D;									// �������m��
			m_apScene2D[nCount]->InitScroll(2, 0.008f + 0.004f*(float)nCount);	// �X�N���[�����
			m_apScene2D[nCount]->Init(pos, size, type);							// ���������
			m_apScene2D[nCount]->BindTexture(m_apTexture[nCount]);				// �e�N�X�`�����
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBackground::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		if (m_apScene2D[nCount] != NULL)
		{
			// �I������
			m_apScene2D[nCount]->Uninit();
			m_apScene2D[nCount] = NULL;
		}
	}

	// �����[�X
	Release();
}
 
//=============================================================================
// �X�V����
//=============================================================================
void CBackground::Update(void)
{
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		if (m_apScene2D[nCount] != NULL)
		{
			// �X�V����
			m_apScene2D[nCount]->Update();
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBackground::Draw(void)
{

}