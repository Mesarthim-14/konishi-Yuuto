//=========================================================
//
// �̗̓o�[�N���X�w�b�_�[	[hpber.cpp]
// Author : Konishi Yuuto
//
//=========================================================

//=========================================================
// �C���N���[�h
//=========================================================
#include "hpbar.h"
#include "manager.h"
#include "renderer.h"
#include "boss.h"
#include "game.h"

//=========================================================
// static������
//=========================================================
LPDIRECT3DTEXTURE9 CHpbar::m_apTexture[MAX_HPBAR_TEXTURE] = {};

//=========================================================
// �|���S������
//=========================================================
CHpbar * CHpbar::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type, int nLife)
{
	// �������m��
	CHpbar *pHpbar = new CHpbar;

	pHpbar->m_nMaxLife = nLife;				// �̗͂̐ݒ�
	pHpbar->m_nLife = nLife;				// ���C�t�̐ݒ�
	pHpbar->SetType(type);					// ��ނ̐ݒ�
	pHpbar->BindTexture(m_apTexture[0]);	// �e�N�X�`���̐ݒ�
	pHpbar->Init(pos, size, type);			// ������

	return pHpbar;
}

//=========================================================
// �R���X�g���N�^
//=========================================================
CHpbar::CHpbar()
{
	m_pVtxBuff = NULL;
	m_nLife = 0;
	m_nMaxLife = 0;
}

//=========================================================
// �f�X�g���N�^
//=========================================================
CHpbar::~CHpbar()
{
}

//=========================================================
// ����������
//=========================================================
HRESULT CHpbar::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX, 
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, 
		D3DPOOL_MANAGED, 
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	m_Pos = pos;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//���̏����͕ς��Ȃ�����

	//HP���������ꍇ�A�摜�̉E������`�����߂�
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x - BAR_SIZE_X / 2, m_Pos.y - BAR_SIZE_Y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Pos.x + BAR_SIZE_X / 2, m_Pos.y - BAR_SIZE_Y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x - BAR_SIZE_X / 2, m_Pos.y + BAR_SIZE_Y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Pos.x + BAR_SIZE_X / 2, m_Pos.y + BAR_SIZE_Y / 2, 0.0f);

	//rhw�̐ݒ�i�l��1.0�Őݒ肷��j
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[��ݒ�i0�`255�̒l�Őݒ肷��j
	pVtx[0].col = D3DCOLOR_RGBA(70, 185, 127, 255);
	pVtx[1].col = D3DCOLOR_RGBA(70, 185, 127, 255);
	pVtx[2].col = D3DCOLOR_RGBA(70, 185, 127, 255);
	pVtx[3].col = D3DCOLOR_RGBA(70, 185, 127, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(((float)m_nLife) * (1.0f / m_nMaxLife), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(((float)m_nLife) * (1.0f / m_nMaxLife), 1.0f);

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=========================================================
// �I������
//=========================================================
void CHpbar::Uninit(void)
{

}

//=========================================================
// �X�V����
//=========================================================
void CHpbar::Update(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//HP���������ꍇ�A�摜�̉E������`�����߂�

	pVtx[0].pos = D3DXVECTOR3(m_Pos.x - BAR_SIZE_X / 2, m_Pos.y - BAR_SIZE_Y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3((m_Pos.x - BAR_SIZE_X / 2) + (BAR_SIZE_X * (((float)m_nLife / m_nMaxLife))), m_Pos.y - BAR_SIZE_Y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x - BAR_SIZE_X / 2, m_Pos.y + BAR_SIZE_Y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3((m_Pos.x - BAR_SIZE_X / 2) + (BAR_SIZE_X  * (((float)m_nLife / m_nMaxLife))) , m_Pos.y + BAR_SIZE_Y / 2, 0.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(((float)m_nLife / m_nMaxLife), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(((float)m_nLife / m_nMaxLife), 1.0f);

	//HP�ɉ����ăJ���[��ς���i���^�����甼���܂ŗ΁j
	if (m_nLife <= m_nMaxLife&&m_nLife > m_nMaxLife / 2)
	{
		pVtx[0].col = D3DCOLOR_RGBA(70, 185, 127, 255);
		pVtx[1].col = D3DCOLOR_RGBA(70, 185, 127, 255);
		pVtx[2].col = D3DCOLOR_RGBA(70, 185, 127, 255);
		pVtx[3].col = D3DCOLOR_RGBA(70, 185, 127, 255);
	}

	//HP�ɉ����ăJ���[��ς���i��������4����1�܂ŉ��F�j
	if (m_nLife <= m_nMaxLife / 2 && m_nLife > m_nMaxLife / 4)
	{
		pVtx[0].col = D3DCOLOR_RGBA(254, 236, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(254, 236, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(254, 236, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(254, 236, 0, 255);
	}

	//HP�ɉ����ăJ���[��ς���i4����1����͐ԐF�j
	if (m_nLife <= m_nMaxLife / 4)
	{
		pVtx[0].col = D3DCOLOR_RGBA(254, 83, 12, 255);
		pVtx[1].col = D3DCOLOR_RGBA(254, 83, 12, 255);
		pVtx[2].col = D3DCOLOR_RGBA(254, 83, 12, 255);
		pVtx[3].col = D3DCOLOR_RGBA(254, 83, 12, 255);
	}

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=========================================================
// �`�揈��
//=========================================================
void CHpbar::Draw(void)
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
	pDevice->SetTexture(0, m_apTexture[0]);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
		0,
		NUM_POLYGON);				// �v���~�e�B�u�̐�}
}

//=========================================================
// �e�N�X�`�����[�h
//=========================================================
HRESULT CHpbar::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/3Dgame_HPbar001.png",
		&m_apTexture[0]);

	return S_OK;
}

//=========================================================
// �e�N�X�`���A�����[�h
//=========================================================
void CHpbar::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_HPBAR_TEXTURE; nCount++)
	{
		// �e�N�X�`���̊J��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=========================================================
// �_���[�W����
//=========================================================
void CHpbar::AddDamage(int nNumber)
{
	m_nLife -= nNumber;
}

//=========================================================
// ���C�t�̉�
//=========================================================
void CHpbar::SetHp(int nNumber)
{
	// ���C�t�����炵�Ă���
	m_nMaxLife = nNumber;

	// ���C�t�̉�
	if (m_nLife <= m_nMaxLife)
	{
		m_nLife += 3;
		if (m_nLife >= m_nMaxLife)
		{
			m_nLife = m_nMaxLife;
		}
	}
}