//=====================================================
//
// �x��N���X [alert.cpp]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "alert.h"
#include "manager.h"
#include "renderer.h"
#include "warning.h"
#include "sound.h"

//=====================================================
// �}�N����`
//=====================================================
#define ALERT_END_FLAME			(300)			// �A���[�g�̏I���t���[��
#define ALERTLOGO_START_FLAME	(50)			// ���S���o���t���[��
#define SUB_COLOR_NUM			(15)			// �J���[�̑�����

//=====================================================
// �|���S������
//=====================================================
CAlert * CAlert::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// �������m��
	CAlert *pAlert = new CAlert;

	if (pAlert != NULL)
	{
		// ������
		pAlert->Init(pos, size, type);		// ����������
		pAlert->InitColor();				// �J���[�̐ݒ�
		pAlert->SetType(type);				// �^�C�v�̐ݒ�
	}

	// �T�E���h�ݒ�
	CSound *pSound = NULL;
	pSound = CManager::GetSound();
	pSound->Play(CSound::SOUND_LABEL_WARNING);

	return pAlert;
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CAlert::CAlert()
{
	m_nSubNumber = 255;
	m_nSubNum = SUB_COLOR_NUM;
	m_nAlertFlame = 0;
	m_bAlertFlag = false;
	m_pWarning = NULL;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CAlert::~CAlert()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CAlert::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type)
{
	// ����������
	CPolygon::Init(pos, move, type);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CAlert::Uninit(void)
{
	// �I������
	CPolygon::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CAlert::Update(void)
{
	// �X�V����
	CPolygon::Update();

	// ���̓_��
	FlashPolygon();
}

//=====================================================
// �`�揈��
//=====================================================
void CAlert::Draw(void)
{
	// �`�揈��
	CPolygon::Draw();
}

//=====================================================
// �J���[�̏�����
//=====================================================
void CAlert::InitColor(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);	// ���㒸�_�̐F	�����x255
	pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);	// �E�㒸�_�̐F	�����x255
	pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);	// �������_�̐F	�����x255
	pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);	// �E�����_�̐F	�����x255

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//=====================================================
// �|���S���̓_��
//=====================================================
void CAlert::FlashPolygon(void)
{
	// �t���[�������Z
	m_nAlertFlame++;

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �J���[�����Z
	m_nSubNumber -= m_nSubNum;

	if (m_nSubNumber <= 0)
	{
		// 0�ɂȂ�����؂�ւ�
		m_nSubNumber = 0;
		m_nSubNum *= -1;
	}
	else if (m_nSubNumber >= 255)
	{
		// 255�ɂȂ�����؂�ւ�
		m_nSubNumber = 255;
		m_nSubNum *= -1;
	}
	
	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255 - m_nSubNumber, 0, 0, 100);	// ���㒸�_�̐F	�����x255
	pVtx[1].col = D3DCOLOR_RGBA(255 - m_nSubNumber, 0, 0, 100);	// �E�㒸�_�̐F	�����x255
	pVtx[2].col = D3DCOLOR_RGBA(255 - m_nSubNumber, 0, 0, 100);	// �������_�̐F	�����x255
	pVtx[3].col = D3DCOLOR_RGBA(255 - m_nSubNumber, 0, 0, 100);	// �E�����_�̐F	�����x255

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();

	// �A���[�g���S�̐���
	CreateAlertLogo();

	// ���̃t���[���ŏI������
	if (m_nAlertFlame >= ALERT_END_FLAME)
	{
		m_bAlertFlag = true;

		// ���S�̏I��
		m_pWarning->Uninit();
	}
}

//=====================================================
// �A���[�g���S�̐���
//=====================================================
void CAlert::CreateAlertLogo(void)
{
	// �A���[�g���S�̏o��
	if (m_nAlertFlame >= ALERTLOGO_START_FLAME)
	{
		if (m_pWarning == NULL)
		{
			// �A���[�g���S����
			m_pWarning = CWarning::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
				D3DXVECTOR3(WARNING_SIZE_X, WARNING_SIZE_Y, 0.0f), TYPE_WARNING);
		}
	}
}

//=====================================================
// �A���[�g�̏��
//=====================================================
bool CAlert::GetAlertFlag(void)
{
	return m_bAlertFlag;
}