//=============================================================================
//
// �i���o�[�w�b�_�[ [number.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "score.h"
#include "number.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SCORE_ANIM_PATTERN	(8)			// �A�j���[�V�����̃p�^�[��
#define NUMBER_NUM			(10)		// �i���o�[�̐�

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CNumber::m_apTexture[MAX_NUMBER_TEXTURE] = {};
LPDIRECT3DDEVICE9 CNumber::m_pDevice = NULL;

//=============================================================================
// �C���X�^���X����
//=============================================================================
CNumber * CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CScene::TYPE type, NUMBER_TYPE Ntype)
{
	// �C���X�^���X����
	CNumber *pNumber = new CNumber;

	if (pNumber != NULL)
	{
		// ����������
		pNumber->Init(pos, size, type);
		pNumber->NumberInit(pos, size);
		pNumber->SetNType(Ntype);
	}
	return pNumber;
}

//=============================================================================
// �e�N�X�`���̐ݒ�
//=============================================================================
void CNumber::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_apTexture[0] = pTexture;
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CNumber::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/number.png",
		&m_apTexture[0]);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/Number010.png",
		&m_apTexture[1]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CNumber::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER_TEXTURE; nCount++)
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
// �R���X�g���N�^
//=============================================================================
CNumber::CNumber()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pVtxBuff = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CNumber::~CNumber()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	m_pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@�̐���
	if (FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,														// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,															// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,														// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pVtxBuff,															// ���_�o�b�t�@�ւ̃|�C���^
		NULL)))																	// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	SetType(type);

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x / 2, pos.y - size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x / 2, pos.y - size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x / 2, pos.y + size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x / 2, pos.y + size.y / 2, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// ���㒸�_�̐F	�����x255
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�㒸�_�̐F	�����x255
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �������_�̐F	�����x255
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�����_�̐F	�����x255

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CNumber::Uninit(void)
{
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CNumber::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CNumber::Draw(void)
{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		m_pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		m_pDevice->SetFVF(FVF_VERTEX_2D);

		// �i���o�[�̎��
		switch (m_Ntype)
		{
			// �X�R�A
		case NUMBER_TYPE_SCORE:
			// �e�N�X�`���̐ݒ�
			m_pDevice->SetTexture(0, m_apTexture[0]);
			break;

			// �����L���O
		case NUMBER_TYPE_RANKING:
			// �e�N�X�`���̐ݒ�
			m_pDevice->SetTexture(0, m_apTexture[1]);
			break;

			// ���̑�
		default:
			// �e�N�X�`���̐ݒ�
			m_pDevice->SetTexture(0, m_apTexture[0]);
			break;
		}

		// �|���S���̕`��
		m_pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
			0,
			NUM_POLYGON);				// �v���~�e�B�u�̐�
}

//=============================================================================
// �i���o�[�̉��Z
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2((1.0f / NUMBER_NUM) * (float)nNumber, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((1.0f / NUMBER_NUM) * (float)nNumber + (1.0f / NUMBER_NUM), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((1.0f / NUMBER_NUM) * (float)nNumber, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((1.0f / NUMBER_NUM) * (float)nNumber + (1.0f / NUMBER_NUM), 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �i���o�[���̏�����
//=============================================================================
void CNumber::NumberInit(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_Pos = pos;
	m_Size = size;
}

//=============================================================================
// �i���o�[�̎�ޏ��
//=============================================================================
void CNumber::SetNType(NUMBER_TYPE Ntype)
{
	m_Ntype = Ntype;
}

//=============================================================================
// �o�b�t�@���
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 CNumber::GetVtxBuff(void)
{
	return m_pVtxBuff;
}