//=============================================================================
//
// �J���X�̃N���X [crow.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "crow.h"
#include "renderer.h"
#include "manager.h"
#include "alert.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CROW_FLAME			(1000)			// �J���X�̏o���t���[��
#define CROW_RANDOM_POS_Y	(30)			// �J���X�̍��W�����_���l

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CCrow::m_apTexture[MAX_CROW_TEXTURE] = {};

//=============================================================================
// �|���S������
//=============================================================================
CCrow * CCrow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, TYPE type)
{
	// �C���X�^���X����
	CCrow *pCrow = new CCrow;

	if (pCrow != NULL)
	{
		// �J���X�̍��W�ݒ�
		D3DXVECTOR3 RandomPos;
		RandomPos.y = pos.y - rand() % CROW_RANDOM_POS_Y - rand() % CROW_RANDOM_POS_Y - rand() % CROW_RANDOM_POS_Y;

		// ����������
		pCrow->Init(D3DXVECTOR3(pos.x, RandomPos.y, 0.0f), size, type);		// ���������
		pCrow->BindTexture(m_apTexture[0]);									// �e�N�X�`���̐ݒ�
		pCrow->m_move = move;												// �ړ��ʐݒ�
		pCrow->m_size = size;												// �T�C�Y����
		pCrow->InitAnimation(7, 6, -1);										// �A�j���[�V�������
	}

	return pCrow;
}

//====================================================================
// �R���X�g���N�^
//====================================================================
CCrow::CCrow()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounter = 0;
}

//====================================================================
// �f�X�g���N�^
//====================================================================
CCrow::~CCrow()
{

}

//====================================================================
// ����������
//====================================================================
HRESULT CCrow::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CScene2D::Init(pos, size, type);

	return S_OK;
}

//====================================================================
// �I������
//====================================================================
void CCrow::Uninit(void)
{
	// �I������
	CScene2D::Uninit();
}

//====================================================================
// �X�V����
//====================================================================
void CCrow::Update(void)
{
	// �X�V����
	CScene2D::Update();

	// ���W���󂯎��
	m_Pos = GetPosition();

	// �ړ��ʑ��
	m_Pos += m_move;

	// ���W��n��
	SetPosition(m_Pos);

	// ��ʊO�ɍs������
	if (0.0f > m_Pos.x && SCREEN_WIDTH < m_Pos.x&&
		0.0f > m_Pos.y && SCREEN_HEIGHT < m_Pos.y)
	{
		m_nCounter++;

		if (m_nCounter >= CROW_FLAME)
		{
			// �I������
			Uninit();
		}
	}
}

//====================================================================
// �`�揈��
//====================================================================
void CCrow::Draw(void)
{
	// �`�揈��
	CScene2D::Draw();
}

//====================================================================
// �e�N�X�`�����[�h
//====================================================================
HRESULT CCrow::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/crow.png",
		&m_apTexture[0]);

	return S_OK;
}

//====================================================================
// �e�N�X�`���A�����[�h
//====================================================================
void CCrow::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_CROW_TEXTURE; nCount++)
	{
		// �e�N�X�`���̊J��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}