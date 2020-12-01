//=============================================================================
//
// �{���N���X [bomb.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "bomb.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "sound.h"

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CBomb::m_apTexture[MAX_BOMB_TEXTURE] = {};

//=============================================================================
// �C���X�^���X����
//=============================================================================
CBomb * CBomb::Create(D3DXVECTOR3 pos,
	D3DXVECTOR3 size, TYPE type, BOMB_TYPE Btype, BOMB_COLOR BColor,
	int nAngle, int nBaseAngle, int nDistance, int nLife)
{
	// �������m��
	CBomb *pBomb = new CBomb;

	if (pBomb != NULL)
	{
		// �{���̎��
		switch (Btype)
		{
		case BOMB_TYPE_SHOCK:
		{// �Ռ��h�̎�

			// �����̐ݒ�
			int nDis = rand() % nDistance + rand() % nDistance;

			// �����_���ŏo�������߂�
			D3DXVECTOR3 TargetPos = D3DXVECTOR3(pos.x + nDistance * cosf(D3DXToRadian(nAngle)),
				pos.y + nDistance * sinf(D3DXToRadian(nAngle)), 0.0f);

			// ����������
			pBomb->Init(TargetPos, size, type);

			// �Â����W�ݒ�
			pBomb->m_TargetOld = pos;

			D3DXVECTOR3 move = D3DXVECTOR3(cosf(D3DXToRadian(nAngle)) * BOMB_SPPED,
				sinf(D3DXToRadian(nAngle)) * +BOMB_SPPED, 0.0f);

			// �ړ���
			pBomb->m_move = move;

			// �J���[�̐ݒ�
			pBomb->m_BColor = BColor;

			// �J���[�̐ݒ�
			pBomb->InitColor();

			// �e�N�X�`���ݒ�
			pBomb->BindTexture(m_apTexture[0]);

			// ���C�t
			pBomb->m_nLife = nLife;
		}
			break;

		case BOMB_TYPE_SPARK:
		{// �Ή�

			// �����̐ݒ�
			int nDis = rand() % nDistance + rand() % nDistance;

			// �����_���ŏo�������߂�
			D3DXVECTOR3 TargetPos = D3DXVECTOR3(pos.x + nDis * cosf(D3DXToRadian((rand() % nAngle - rand() % nAngle))),
				pos.y - nDis * sinf(D3DXToRadian((rand() % nAngle - rand() % nAngle))), 0.0f);

			// ����������
			pBomb->Init(TargetPos, size, type);

			// �Â����W�ݒ�
			pBomb->m_TargetOld = pos;

			D3DXVECTOR3 move = D3DXVECTOR3(cosf(D3DXToRadian(nBaseAngle + (rand() % nAngle - rand() % nAngle))) * BOMB_SPPED,
				sinf(D3DXToRadian(nBaseAngle + (rand() % nAngle - rand() % nAngle))) * -BOMB_SPPED, 0.0f);

			// �ړ���
			pBomb->m_move = move;

			// �J���[������
			pBomb->InitColor();

			// �e�N�X�`���ݒ�
			pBomb->BindTexture(m_apTexture[0]);

			// ���C�t�̏���
			pBomb->m_nLife = nLife - rand() % 20;
		}

			break;
		}
	}
	return pBomb;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBomb::CBomb()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_TargetOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pVtxBuff = NULL;
	m_nLife = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBomb::~CBomb()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CScene2D::Init(pos, size, TYPE_EFFECT);
	m_Pos = pos;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBomb::Uninit(void)
{
	// 2D�|���S���I������
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBomb::Update(void)
{
	// ���C�t���Z
	m_nLife--;

	// 2D�|���S���X�V����
	CScene2D::Update();

	// �ړ��ʍX�V
	m_Pos += m_move;

	// ���W��n��
	SetPosition(m_Pos);

	// ���C�t��0�ɂȂ�����
	if (m_nLife <= 0)
	{
		// �I������
		Uninit();
		return;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBomb::Draw(void)
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

//=============================================================================
// �J���[�̐ݒ�
//=============================================================================
void CBomb::InitColor(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �{���̐F
	switch (m_BColor)
	{
	case BOMB_COLOR_WHITE:
		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(0, 100, 255, 255);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DCOLOR_RGBA(0, 100, 255, 255);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DCOLOR_RGBA(0, 100, 255, 255);	// �������_�̐F	�����x255
		pVtx[3].col = D3DCOLOR_RGBA(0, 100, 255, 255);	// �E�����_�̐F	�����x255
		break;
	case BOMB_COLOR_BLACK:
		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 100, 0, 255);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DCOLOR_RGBA(255, 100, 0, 255);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DCOLOR_RGBA(255, 100, 0, 255);	// �������_�̐F	�����x255
		pVtx[3].col = D3DCOLOR_RGBA(255, 100, 0, 255);	// �E�����_�̐F	�����x255
		break;
	default:
		break;
	}

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CBomb::Load(void)
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
void CBomb::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_BOMB_TEXTURE; nCount++)
	{
		// �e�N�X�`���̊J��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}