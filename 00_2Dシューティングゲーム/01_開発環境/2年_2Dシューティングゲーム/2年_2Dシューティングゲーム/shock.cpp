//=============================================================================
//
// �Ռ��N���X���� [shock.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "shock.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SCALE_UP_NUM	(0.08f)
#define SUB_ALPHA_NUM	(6)

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CShock::m_apTexture[MAX_SHOCK_TEXTURE] = {};

//=============================================================================
// �C���X�^���X����
//=============================================================================
CShock * CShock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type, COLOR_TYPE Ctype)
{
	// �C���X�^���X����
	CShock *pShock = new CShock;

	// ����������
	pShock->Init(pos, size, type);

	// �ړ��ʐݒ�
	pShock->SetShock(Ctype);

	switch (Ctype)
	{
	case COLOR_TYPE_WHITE:
		// �e�N�X�`��
		pShock->BindTexture(m_apTexture[0]);
		break;

	case COLOR_TYPE_BLACK:
		// �e�N�X�`��
		pShock->BindTexture(m_apTexture[1]);
		break;
	}
	return pShock;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CShock::CShock()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0);
	m_Ctype = COLOR_TYPE_NONE;
	m_fScaleNumber = 0.0f;
	m_fScaleNum = 0.0f;
	m_nSubAlpha = 0;
	m_nSubAlphaNum = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CShock::~CShock()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CShock::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CScene2D::Init(pos, size, type);

	m_Pos = pos;
	m_size = size;
	m_fScaleNum = SCALE_UP_NUM;
	m_nSubAlphaNum = SUB_ALPHA_NUM;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CShock::Uninit(void)
{
	// 2D�|���S���I������
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CShock::Update(void)
{
	// ���݂̈ʒu���擾
	m_Pos = GetPosition();

	// 2D�|���S���X�V����
	CScene2D::Update();

	// �X�P�[���A�b�v
	SizeUp();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CShock::Draw(void)
{
	// 2D�|���S���`�揈��
	CScene2D::Draw();
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
void CShock::SetShock(COLOR_TYPE Ctype)
{
	m_Ctype = Ctype;
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CShock::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/shock003.png",
		&m_apTexture[0]);

	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/shock002.png",
		&m_apTexture[1]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CShock::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_SHOCK_TEXTURE; nCount++)
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
// �X�P�[���A�b�v
//=============================================================================
void CShock::SizeUp(void)
{
	// �g��ʉ��Z
	m_fScaleNumber += m_fScaleNum;

	// �T�C�Y�̐ݒ�
	D3DXVECTOR3 size = D3DXVECTOR3(m_size.x * m_fScaleNumber, m_size.y * m_fScaleNumber, 0.0f);

	// �����ɂ��鏈��
	UpdateInvisible();

	if (m_fScaleNumber >= 2.0)
	{
		m_fScaleNumber = 2.0f;

		// �I������
		Uninit();
		return;
	}
	// �T�C�Y��n��
	SetSize2D(size);
}

//=============================================================================
// �����x���Z
//=============================================================================
void CShock::UpdateInvisible(void)
{
	// �����x�̈����l�����Z
	m_nSubAlpha += m_nSubAlphaNum;

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	// ���_����ݒ�
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nSubAlpha);	// ���㒸�_�̐F	�����x255
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nSubAlpha);	// �E�㒸�_�̐F	�����x255
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nSubAlpha);	// �������_�̐F	�����x255
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nSubAlpha);	// �E�����_�̐F	�����x255

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();

}