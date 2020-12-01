//=============================================================================
//
// �G�̌����� [light.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "light.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "sound.h"

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CLight::m_apTexture[MAX_LIGHT_TEXTURE] = {};

//=============================================================================
// �C���X�^���X����
//=============================================================================
CLight * CLight::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,
	D3DXVECTOR3 size, TYPE type, LIGHT_TYPE Ltype)
{
	// �C���X�^���X����
	CLight *pLight = new CLight;

	if (pLight != NULL)
	{
		// ����������
		pLight->Init(pos, size, type);			// ���������
		pLight->SetMove(move);					// �ړ���
		pLight->BindTexture(m_apTexture[0]);	// �e�N�X�`���ݒ�
		pLight->SetColor(Ltype);				// �F�̐ݒ�
		pLight->InitColor();					// �F�̏�����
	}

	return pLight;
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CLight::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/effect000.jpg",
		&m_apTexture[0]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CLight::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_LIGHT_TEXTURE; nCount++)
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
// �J���[�̐ݒ�
//=============================================================================
void CLight::SetColor(LIGHT_TYPE Ctype)
{
	m_Ltype = Ctype;
}

//=============================================================================
// �J���[������
//=============================================================================
void CLight::InitColor(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �F�̐ݒ�
	switch (m_Ltype)
	{
		// ���̎�
	case LIGHT_TYPE_WHITE:
		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(0, 100, 255, 255);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DCOLOR_RGBA(0, 100, 255, 255);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DCOLOR_RGBA(0, 100, 255, 255);	// �������_�̐F	�����x255
		pVtx[3].col = D3DCOLOR_RGBA(0, 100, 255, 255);	// �E�����_�̐F	�����x255
		break;

		// ���̎�
	case LIGHT_TYPE_BLACK:
		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 40, 255);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 40, 255);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 40, 255);	// �������_�̐F	�����x255
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 40, 255);	// �E�����_�̐F	�����x255
		break;
	}
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLight::CLight()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bScaleUp = false;
	m_Ltype = LIGHT_TYPE_NONE;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLight::~CLight()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLight::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CScene2D::Init(pos, size, type);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLight::Uninit(void)
{
	// 2D�|���S���I������
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CLight::Update(void)
{
	// 2D�|���S���X�V����
	CScene2D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CLight::Draw(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���Z�������s��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// a�f�X�e�B�l�[�V�����J���[

	// 2D�|���S���`�揈��
	CScene2D::Draw();

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// a�f�X�e�B�l�[�V�����J���[
}

//=============================================
// �e�̐ݒ�
//=============================================
void CLight::SetMove(D3DXVECTOR3 move)
{
	// �ϐ��ɑ��
	m_move = move;
}