//=============================================================================
//
// �A���[�g���S�N���X [warning.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//====================================================================
// �C���N���[�h
//====================================================================
#include "warning.h"
#include "renderer.h"
#include "manager.h"
#include "alert.h"

//====================================================================
// �}�N����`
//====================================================================
#define SCALE_DOWN_NUM		(0.1f)		// �k���̒l
#define WARNING_COLOR_NUM	(5)			// �F�̕ω�
#define WARNING_COLOR_MAX	(150)		// �J���[�ύX�̍ő�
#define WARNING_COLOR_MIN	(0)			// �J���[�ύX�̍ŏ�
#define WARNING_CHANGE_TIME	(35)		// �J���[��ς���t���[��

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CWarning::m_apTexture[MAX_WARNING_TEXTURE] = {};

//====================================================================
// �|���S������
//====================================================================
CWarning * CWarning::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// �C���X�^���X����
	CWarning *pWarning = new CWarning;

	if (pWarning != NULL)
	{
		// ����������
		pWarning->Init(pos, size, type);

		// �e�N�X�`���̐ݒ�
		pWarning->BindTexture(m_apTexture[0]);

		// �T�C�Y����
		pWarning->m_size = size;
	}
	return pWarning;
}

//====================================================================
// �R���X�g���N�^
//====================================================================
CWarning::CWarning()
{
	m_fScale = 2.0f;
	m_fScaleNum = 0.0f;
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFlashFlame = 0;
	m_nSubNumber = 0;
	m_nSubNum = WARNING_COLOR_NUM;
}

//====================================================================
// �f�X�g���N�^
//====================================================================
CWarning::~CWarning()
{

}

//====================================================================
// ����������
//====================================================================
HRESULT CWarning::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CScene2D::Init(pos, size, type);

	// �k���ʂ�ݒ�
	m_fScaleNum = SCALE_DOWN_NUM;

	return S_OK;
}

//====================================================================
// �I������
//====================================================================
void CWarning::Uninit(void)
{
	// �I������
	CScene2D::Uninit();
}

//====================================================================
// �X�V����
//====================================================================
void CWarning::Update(void)
{
	// �X�V����
	CScene2D::Update();

	// �k��
	ScaleDown();

	// �_�ł�����
	FlashPolygon();
}

//====================================================================
// �`�揈��
//====================================================================
void CWarning::Draw(void)
{
	// �`�揈��
	CScene2D::Draw();
}

//====================================================================
// �e�N�X�`�����[�h
//====================================================================
HRESULT CWarning::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/WARNING.png",
		&m_apTexture[0]);

	return S_OK;
}

//====================================================================
// �e�N�X�`���A�����[�h
//====================================================================
void CWarning::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_WARNING_TEXTURE; nCount++)
	{
		// �e�N�X�`���̊J��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//====================================================================
// �k��
//====================================================================
void CWarning::ScaleDown(void)
{
	if (m_fScale >= 1.0f)
	{
		// �k���ʂ����Z
		m_fScale -= m_fScaleNum;

		// �T�C�Y�̐ݒ�
		D3DXVECTOR3 size = D3DXVECTOR3(m_size.x * m_fScale, m_size.y * m_fScale, 0.0f);
		SetSize2D(size);
	}
	else
	{
		m_fScale = 1.0f;
	}
}

//====================================================================
// �|���S���̓_��
//====================================================================
void CWarning::FlashPolygon(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_����ݒ�
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �J���[�̌��Z
	m_nSubNumber += m_nSubNum;

	// �J���[�ύX�̍ő�l
	if (m_nSubNumber >= WARNING_COLOR_MAX)
	{
		// ����
		m_nSubNumber = WARNING_COLOR_MAX;

		// �l�𔽓]
		m_nSubNum *= -1;
	}
	else if (m_nSubNumber <= WARNING_COLOR_MIN)
	{
		// �J���[�̍ŏ��l�̐���
		m_nSubNumber = WARNING_COLOR_MIN;

		// �t���[���J�E���g
		m_nFlashFlame++;

		// ���̃t���[���ȏ�ɂȂ�����
		if (m_nFlashFlame >= WARNING_CHANGE_TIME)
		{
			m_nFlashFlame = 0;

			// �l�𔽓]
			m_nSubNum *= -1;
		}
	}

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255 - m_nSubNumber, 255 - m_nSubNumber, 255);	// ���㒸�_�̐F	�����x255
	pVtx[1].col = D3DCOLOR_RGBA(255, 255 - m_nSubNumber, 255 - m_nSubNumber, 255);	// �E�㒸�_�̐F	�����x255
	pVtx[2].col = D3DCOLOR_RGBA(255, 255 - m_nSubNumber, 255 - m_nSubNumber, 255);	// �������_�̐F	�����x255
	pVtx[3].col = D3DCOLOR_RGBA(255, 255 - m_nSubNumber, 255 - m_nSubNumber, 255);	// �E�����_�̐F	�����x255

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}