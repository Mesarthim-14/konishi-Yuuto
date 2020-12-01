//=====================================================
//
// �|���S���N���X [polygon.cpp]
// Author:�����D�l
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "polygon.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"

//=====================================================
// static����������
//=====================================================

//=====================================================
// �R���X�g���N�^
//=====================================================
CPolygon::CPolygon()
{
	m_pVtxBuff = NULL;	// ���_�o�b�t�@�̃|�C���^
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CPolygon::~CPolygon()
{
}

//=============================================================================
//�|���S���N���X�̃N���G�C�g����
//=============================================================================
CPolygon * CPolygon::Create( D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	//�|���S���N���X�̃|�C���^�ϐ�
	CPolygon *pPolygon = NULL;

	//�������̊m��
	pPolygon = new CPolygon;

	//���������m�ۂł��Ă�����
	if (pPolygon != NULL)
	{
		//�����������Ăяo��
		pPolygon->Init(pos, size, type);
	}
	else
	{
		return NULL;
	}
	return pPolygon;
}


//=====================================================
// ����������
//=====================================================
HRESULT CPolygon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	// �o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,				// (�Œ�)
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// (�Œ�)
		&m_pVtxBuff,					// �ϐ������ς��ƕύX���K�v
		NULL);

	//�����ʒu�̐ݒ�
	m_pos = pos;

	//�傫���̐ݒ�
	m_size = size;

	//�e�N�X�`���̐ݒ�
	//SetType(type);

	VERTEX_2D * pVtx;		// ���_���ւ̃|�C���^

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�( Z�̌`�ɔz�u����)  / �l�p�`�̒��_�̈ʒu
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);

	// rhw�̐ݒ�(�l��1.0�ŌŒ�)		/ ���܂�ς��邱�Ƃ͂Ȃ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CPolygon::Uninit(void)
{
	// ���_�o�b�t�@�̊J��
 	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �����[�X
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CPolygon::Update(void)
{

}

//=====================================================
// �`�揈��
//=====================================================
void CPolygon::Draw(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);


	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
		0,
		2);								// �v���~�e�B�u�̐�
}

//=====================================================
// �|�W�V�����̐ݒ�
//=====================================================
void CPolygon::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=====================================================
// �F�̐ݒ�
//=====================================================
void CPolygon::SetColor(D3DXCOLOR color)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�f�[�^�����b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�J���[�̐ݒ�
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

}

//=====================================================
// �o�b�t�@���
//=====================================================
LPDIRECT3DVERTEXBUFFER9 CPolygon::GetVtxBuff(void)
{
	return m_pVtxBuff;
}