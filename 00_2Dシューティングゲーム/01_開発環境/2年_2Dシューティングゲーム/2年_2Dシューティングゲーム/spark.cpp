//=============================================================================
//
// �X�p�[�N�N���X [spark.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "spark.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CSpark::m_apTexture[MAX_SPARK_TEXTURE] = {};

//=============================================================================
// �C���X�^���X����
//=============================================================================
CSpark * CSpark::Create(D3DXVECTOR3 pos,
	D3DXVECTOR3 size, TYPE type, int nAngle, int nBaseAngle, int nDistance, int nLife)
{
	// �C���X�^���X����
	CSpark *pSpark = new CSpark;

	if (pSpark != NULL)
	{
		// �����̐ݒ�
		int nDis = rand() % nDistance + rand() % nDistance;

		// �����_���ŏo�������߂�
		D3DXVECTOR3 TargetPos = D3DXVECTOR3(pos.x + nDis * cosf(D3DXToRadian(nBaseAngle + (rand() % nAngle - rand() % nAngle))),
			pos.y - nDis * sinf(D3DXToRadian(nBaseAngle + (rand() % nAngle - rand() % nAngle))), 0.0f);

		// ����������
		pSpark->Init(TargetPos, size, type);
		pSpark->m_TargetOld = pos;

		// �ړ���
		D3DXVECTOR3 move = D3DXVECTOR3(cosf(D3DXToRadian(nBaseAngle + (rand() % nAngle - rand() % nAngle))) * SPARK_SPPED,
			sinf(D3DXToRadian(nBaseAngle + (rand() % nAngle - rand() % nAngle))) * -SPARK_SPPED, 0.0f);
		
		// �ړ���
		pSpark->SetMove(move);

		// �J���[������
		pSpark->InitColor();

		// �e�N�X�`���ݒ�
		pSpark->BindTexture(m_apTexture[0]);
		pSpark->m_nLife = nLife - rand() % 20;
	}
	return pSpark;
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CSpark::Load(void)
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
void CSpark::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_SPARK_TEXTURE; nCount++)
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
CSpark::CSpark()
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
CSpark::~CSpark()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSpark::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CScene2D::Init(pos, size, type);
	m_Pos = pos;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSpark::Uninit(void)
{
	// 2D�|���S���I������
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CSpark::Update(void)
{
	// ���C�t���Z
	m_nLife--;

	// 2D�|���S���X�V����
	CScene2D::Update();

	// �ړ��ʍX�V
	m_Pos += m_move;

	// ���W��n��
	SetPosition(m_Pos);

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
void CSpark::Draw(void)
{
	// �`�揈��
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���Z�������s��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);	// a�f�X�e�B�l�[�V�����J���[

	// 2D�|���S���`�揈��
	CScene2D::Draw();

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// a�f�X�e�B�l�[�V�����J���[
}

//=============================================================================
// �J���[�̐ݒ�
//=============================================================================
void CSpark::InitColor(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	// ���_����ݒ�
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 100, 0, 255);	// ���㒸�_�̐F	�����x255
	pVtx[1].col = D3DCOLOR_RGBA(255, 100, 0, 255);	// �E�㒸�_�̐F	�����x255
	pVtx[2].col = D3DCOLOR_RGBA(255, 100, 0, 255);	// �������_�̐F	�����x255
	pVtx[3].col = D3DCOLOR_RGBA(255, 100, 0, 255);	// �E�����_�̐F	�����x255

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//=============================================
// �ړ��ʐݒ�
//=============================================
void CSpark::SetMove(D3DXVECTOR3 move)
{
	// �ړ��ʂ�ݒ�
	m_move = move;
}