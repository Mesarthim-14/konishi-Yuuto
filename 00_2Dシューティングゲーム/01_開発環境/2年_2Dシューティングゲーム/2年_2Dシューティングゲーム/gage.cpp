//=============================================================================
//
// �Q�[�W�N���X		[gage.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "gage.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "game.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_GAGE_NUM	(100)		// �Q�[�W�̍ő�l
#define FLASH_FLAME		(8)			// �_�ł̃t���[��

//=============================================================================
// static����������
//=============================================================================
LPDIRECT3DTEXTURE9 CGage::m_apTexture[MAX_GAGE_TEXTURE] = {};	// �e�N�X�`�����̃|�C���^

//=============================================================================
// �N���G�C�g
//=============================================================================
CGage * CGage::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type, GAGE_TYPE Gtype)
{
	// �������m��
	CGage *pGage = new CGage;

	// ����������
	pGage->Init(pos, size, type);			// ���������
	pGage->SetInfo(pos, size, Gtype);		// ���̐ݒ�
	pGage->m_nMaxLaserNum = MAX_GAGE_NUM;	// �ő��

	// �Q�[�W�̎��
	switch (Gtype)
	{
	case GAGE_TYPE_BLUE:
		// �o�[�̃��C��
		pGage->BindTexture(m_apTexture[0]);
		break;
	case GAGE_TYPE_FLAME:
		// �o�[�̘g
		pGage->BindTexture(m_apTexture[1]);
		break;
	}

	return pGage;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGage::CGage()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���W
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �T�C�Y
	m_Gtype = GAGE_TYPE_NONE;					// �Q�[�W�^�C�v
	m_nLaserNum = 0;							// ���[�U�[�̗�
	m_nMaxLaserNum = 0;							// ���[�U�[�̍ő��
	m_nFlashFlame = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGage::~CGage()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGage::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	CUi::Init(pos, size, type);

	// �{��
	if (m_Gtype == GAGE_TYPE_BLUE)
	{
		LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
		// ���_����ݒ�
		VERTEX_2D *pVtx;
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//HP���������ꍇ�A�摜�̉E������`�����߂�
		pVtx[0].pos = D3DXVECTOR3(m_Pos.x - GAGE_SIZE_X / 2, m_Pos.y - GAGE_SIZE_Y / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_Pos.x + GAGE_SIZE_X / 2, m_Pos.y - GAGE_SIZE_Y / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_Pos.x - GAGE_SIZE_X / 2, m_Pos.y + GAGE_SIZE_Y / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_Pos.x + GAGE_SIZE_X / 2, m_Pos.y + GAGE_SIZE_Y / 2, 0.0f);

		pVtx[0].col = D3DCOLOR_RGBA(50, 50, 255, 255);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DCOLOR_RGBA(50, 50, 255, 255);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DCOLOR_RGBA(50, 50, 255, 255);	// �������_�̐F	�����x255
		pVtx[3].col = D3DCOLOR_RGBA(50, 50, 255, 255);	// �E�����_�̐F	�����x255

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f - ((float)m_nLaserNum / (float)m_nMaxLaserNum));
		pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f - ((float)m_nLaserNum / (float)m_nMaxLaserNum));
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�o�b�t�@���A�����b�N����
		pVtxBuff->Unlock();
	}
	return E_NOTIMPL;
}

//=============================================================================
// �I������
//=============================================================================
void CGage::Uninit(void)
{
	CUi::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGage::Update(void)
{
	// �X�V����
	CUi::Update();

	// ���C���̃Q�[�W
	if (m_Gtype == GAGE_TYPE_BLUE)
	{
		// �����_���[�̏����󂯎��
		CRenderer *pRenderer = NULL;
		pRenderer = CManager::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

		LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

		//���_���ւ̃|�C���^
		VERTEX_2D *pVtx;

		//���_�o�b�t�@�����b�N
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].pos = D3DXVECTOR3(m_Pos.x - GAGE_SIZE_X / 2, (m_Pos.y + GAGE_SIZE_Y / 2) - (GAGE_SIZE_Y *(((float)m_nLaserNum / m_nMaxLaserNum))), 0.0f);
		pVtx[1].pos = D3DXVECTOR3((m_Pos.x + GAGE_SIZE_X / 2), (m_Pos.y + GAGE_SIZE_Y / 2) - (GAGE_SIZE_Y *(((float)m_nLaserNum / m_nMaxLaserNum))), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_Pos.x - GAGE_SIZE_X / 2, (m_Pos.y + GAGE_SIZE_Y / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3((m_Pos.x + GAGE_SIZE_X / 2), (m_Pos.y + GAGE_SIZE_Y / 2), 0.0f);

		// �J���[�̕ύX
		GetPlayerColor();

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f - ((float)m_nLaserNum / (float)m_nMaxLaserNum));
		pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f - ((float)m_nLaserNum / (float)m_nMaxLaserNum));
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�o�b�t�@���A�����b�N����
		pVtxBuff->Unlock();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGage::Draw(void)
{
	// �`�揈��
	CUi::Draw();
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CGage::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/GageBar222.png",
		&m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/Gagebar111.png",
		&m_apTexture[1]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CGage::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_GAGE_TEXTURE; nCount++)
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
// �Q�[�W�̃^�C�v��ݒ�
//=============================================================================
void CGage::SetInfo(D3DXVECTOR3 pos, D3DXVECTOR3 size, GAGE_TYPE Gtype)
{
	m_Pos = pos;
	m_Size = size;
	m_Gtype = Gtype;
}

//=============================================================================
// �Q�[�W�ʂ̉��Z
//=============================================================================
void CGage::AddGage(int nNumber)
{
	if (m_nLaserNum <= MAX_GAGE_NUM)
	{
		// ���[�U�[�̗ʉ��Z
		m_nLaserNum += nNumber;
	}
}

//=============================================================================
// �Q�[�W���Z
//=============================================================================
void CGage::SubtractGame(int nNumber)
{
	// �Q�[�W�����炷
	m_nLaserNum -= nNumber;

	if (m_nLaserNum <= 0)
	{
		m_nLaserNum = 0;
	}
}

//=============================================================================
// �Q�[�W�ʂ̉��Z
//=============================================================================
int CGage::GetLaserNum(void)
{
	return m_nLaserNum;
}

//=============================================================================
// �v���C���[�̐F���擾
//=============================================================================
void CGage::GetPlayerColor(void)
{
	m_nFlashFlame++;

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	CPlayer *pPlayer = CGame::GetPlayer();

	// �Q�[�W�̐F���
	if (pPlayer->GetShildInfo() == true)
	{
		// ���̃t���[���œ_��
		if (m_nFlashFlame % FLASH_FLAME == 0)
		{
			pVtx[0].col = D3DCOLOR_RGBA(150, 150, 255, 255);	// ���㒸�_�̐F	�����x255
			pVtx[1].col = D3DCOLOR_RGBA(150, 150, 255, 255);	// �E�㒸�_�̐F	�����x255
			pVtx[2].col = D3DCOLOR_RGBA(150, 150, 255, 255);	// �������_�̐F	�����x255
			pVtx[3].col = D3DCOLOR_RGBA(150, 150, 255, 255);	// �E�����_�̐F	�����x255
		}
		else
		{
			pVtx[0].col = D3DCOLOR_RGBA(50, 50, 255, 255);	// ���㒸�_�̐F	�����x255
			pVtx[1].col = D3DCOLOR_RGBA(50, 50, 255, 255);	// �E�㒸�_�̐F	�����x255
			pVtx[2].col = D3DCOLOR_RGBA(50, 50, 255, 255);	// �������_�̐F	�����x255
			pVtx[3].col = D3DCOLOR_RGBA(50, 50, 255, 255);	// �E�����_�̐F	�����x255
		}
	}
	else
	{
		// ���̃t���[���œ_��
		if (m_nFlashFlame % FLASH_FLAME == 0)
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 150, 150, 255);	// ���㒸�_�̐F	�����x255
			pVtx[1].col = D3DCOLOR_RGBA(255, 150, 150, 255);	// �E�㒸�_�̐F	�����x255
			pVtx[2].col = D3DCOLOR_RGBA(255, 150, 150, 255);	// �������_�̐F	�����x255
			pVtx[3].col = D3DCOLOR_RGBA(255, 150, 150, 255);	// �E�����_�̐F	�����x255
		}
		else
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 50, 50, 255);	// ���㒸�_�̐F	�����x255
			pVtx[1].col = D3DCOLOR_RGBA(255, 50, 50, 255);	// �E�㒸�_�̐F	�����x255
			pVtx[2].col = D3DCOLOR_RGBA(255, 50, 50, 255);	// �������_�̐F	�����x255
			pVtx[3].col = D3DCOLOR_RGBA(255, 50, 50, 255);	// �E�����_�̐F	�����x255
		}
	}
}