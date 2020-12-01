//=============================================================================
//
// �|���S���̐ݒ� [scene2d.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene.h"
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"
#include "player.h"
#include "bg.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SCALE_UP_NUM		(0.05f)				// �g��̒l
#define SCALE_DOWN_NUM		(0.03f)				// �k���̉��Z��
#define TRANS_PARENCY_DOWN	(30)				// �����x���Z

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene2D::CScene2D()
{
	m_pTexture = NULL;							// �e�N�X�`���̃|�C���^
	m_pVtxBuff = NULL;							// ���_�o�b�t�@�̃|�C���^
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �|���S���̃T�C�Y
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �|���S���̍��W
	m_nCountAnim = 0;							// �A�j���[�V�����̃J�E���^�[
	m_nCountAnimPattern = 0;					// �A�j���[�V�����p�^�[���̃J�E���^
	m_nCounterAnim = 0;							// �A�j���[�V�����̑���
	m_nPatternAnim = 0;							// �A�j���[�V�����̐�
	m_nSpeedTexture = 0;						// �e�N�X�`���̈ړ����x
	m_fDivisionCounter = 0.0f;					// �X�N���[���̃J�E���^�[
	m_fDivisionBaseNum = 0.0f;					// �X�N���[���̈ړ���
	m_fScaleUp = 0.0f;							// �g��̒l
	m_fScaleDown = 1.0f;						// �k���̒l
	m_nEffectCntFlame = 0;
	m_nTransParencyNum = 255;
	m_nLoop = 1;								// ���[�v���邩
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �����o�ϐ��ɒl�ݒ�
	m_pos = pos;
	m_size = size;
	SetType(type);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,													// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,														// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,													// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pVtxBuff,														// ���_�o�b�t�@�ւ̃|�C���^
		NULL)))																// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);

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
void CScene2D::Uninit(void)
{
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �V�[�������[�X
	CScene::Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene2D::Update(void)
{
	// �A�j���[�V�����̐ݒ肪���ꂽ�Ƃ�
	if (m_nPatternAnim != 0)
	{
		// �A�j���[�V�������X�V����
		UpdateAnimation();
	}
	else if (m_nSpeedTexture != 0)
	{
		// �A�j���[�V�������X�V����
		UpdateScroll();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene2D::Draw(void)
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
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
		0,
		NUM_POLYGON);				// �v���~�e�B�u�̐�
}

//=============================================================================
// �ʒu���X�V����֐�
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �T�C�Y�̐ݒ�
//=============================================================================
void CScene2D::SetSize2D(D3DXVECTOR3 size)
{
	m_size = size;

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �ʒu��Ԃ��֐�
//=============================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
// �e�N�X�`���ݒ�֐�
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
// ���������̒l���
//=============================================================================
void CScene2D::SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_pos = pos;		// �|���S���̃T�C�Y
	m_size = size;		// �|���S���̍��W
}

//=============================================================================
// ���W���
//=============================================================================
void CScene2D::SetP(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================
// �A�j���[�V�������擾
//=============================================
void CScene2D::InitAnimation(int nCounterAnim, int nPatternAnim, int nLoop)
{
	m_nCounterAnim = nCounterAnim;
	m_nPatternAnim = nPatternAnim;
	m_nLoop = nLoop;

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W���X�V
	pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================
// �A�j���[�V�����X�V�֐�
//=============================================
void CScene2D::UpdateAnimation(void)
{
	// �����̃A�j���[�V�����J�E���g��i�߂āA�p�^�[����؂�ւ���
	m_nCountAnim++;
	// ���_���(�e�N�X�`�����W)�̍X�V
	if (m_nCountAnim >= m_nCounterAnim)	// �����̑���
	{
		// �A�j���[�V�����̃J�E���g��0�ɂ���
		m_nCountAnim = 0;

		// �A�j���[�V�����̃p�^�[�����J�E���g������
		m_nCountAnimPattern++;
	}

	// �A�j���[�V�������I�������
	if (m_nCountAnimPattern >= m_nPatternAnim)
	{
		// ���l��߂��Ă���
		m_nCountAnimPattern = 0;

		if (m_nLoop == 0)
		{
			// �I������
			Uninit();
		}
	}
	else
	{
		// ���_����ݒ�
		VERTEX_2D *pVtx;

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`�����W���X�V
		pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 1.0f);

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//=============================================
// �e�N�X�`���̃X�N���[�������擾
//=============================================
void CScene2D::InitScroll(int nSpeed, float fDivision)
{
	m_nSpeedTexture = nSpeed;
	m_fDivisionBaseNum = fDivision;
}

//=============================================================================
// �|���S���g��
//=============================================================================
bool CScene2D::ScaleUp(D3DXVECTOR3 pos)
{
	m_pos = pos;

	// ���_����ݒ�
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2 * m_fScaleUp), m_pos.y - (m_size.y / 2 * m_fScaleUp), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2 * m_fScaleUp), m_pos.y - (m_size.y / 2 * m_fScaleUp), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2 * m_fScaleUp), m_pos.y + (m_size.y / 2 * m_fScaleUp), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2 * m_fScaleUp), m_pos.y + (m_size.y / 2 * m_fScaleUp), 0.0f);

	if (m_fScaleUp <= 1.0f)
	{
		// �g��
		m_fScaleUp += SCALE_UP_NUM;
	}
	else
	{	// �g�債�I�������
	//	m_bScaleUp = true;

		return true;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	return false;
}

//=============================================================================
// �|���S���k��
//=============================================================================
bool CScene2D::ScaleDown(D3DXVECTOR3 pos, int nLife)
{
	m_nEffectCntFlame++;
	m_pos = pos;

	// ���_����ݒ�
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2 * m_fScaleDown), m_pos.y - (m_size.y / 2 * m_fScaleDown), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2 * m_fScaleDown), m_pos.y - (m_size.y / 2 * m_fScaleDown), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2 * m_fScaleDown), m_pos.y + (m_size.y / 2 * m_fScaleDown), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2 * m_fScaleDown), m_pos.y + (m_size.y / 2 * m_fScaleDown), 0.0f);

	if (m_nEffectCntFlame <= nLife)
	{
		m_fScaleDown -= SCALE_DOWN_NUM;
	}
	else
	{	// �g�債�I�������
		//	m_bScaleUp = true;
		return true;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	return false;
}

//=============================================================================
// �����x
//=============================================================================
bool CScene2D::TransParency(D3DXVECTOR3 pos, int nLife)
{
	m_nEffectCntFlame++;
	m_pos = pos;

	// ���_����ݒ�
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2 * m_fScaleDown), m_pos.y - (m_size.y / 2 * m_fScaleDown), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2 * m_fScaleDown), m_pos.y - (m_size.y / 2 * m_fScaleDown), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2 * m_fScaleDown), m_pos.y + (m_size.y / 2 * m_fScaleDown), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2 * m_fScaleDown), m_pos.y + (m_size.y / 2 * m_fScaleDown), 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(0, 100, 255, m_nTransParencyNum);	// ���㒸�_�̐F	�����x255
	pVtx[1].col = D3DCOLOR_RGBA(0, 100, 255, m_nTransParencyNum);	// �E�㒸�_�̐F	�����x255
	pVtx[2].col = D3DCOLOR_RGBA(0, 100, 255, m_nTransParencyNum);	// �������_�̐F	�����x255
	pVtx[3].col = D3DCOLOR_RGBA(0, 100, 255, m_nTransParencyNum);	// �E�����_�̐F	�����x255


	if (m_nEffectCntFlame <= nLife)
	{
		m_nTransParencyNum -= TRANS_PARENCY_DOWN;
	}
	else
	{	// �g�債�I�������
		return true;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	return false;
}

//=============================================
// �e�N�X�`���̃X�N���[�������X�V
//=============================================
void CScene2D::UpdateScroll(void)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// �J�E���^�[��i�߂�
	m_nCounterAnim++;
	// ���_���(�e�N�X�`�����W)�̍X�V
	if (m_nCounterAnim >= m_nSpeedTexture)		// �����̑���
	{
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`�����W���X�V
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - m_fDivisionCounter);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - m_fDivisionCounter);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f - m_fDivisionCounter);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f - m_fDivisionCounter);

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();

		// �A�j���[�V�����̃p�^�[�����J�E���g������
		m_fDivisionCounter += m_fDivisionBaseNum;
		m_nCounterAnim = 0;
	}
}

//=============================================================================
// �o�b�t�@���
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 CScene2D::GetVtxBuff(void)
{
	return m_pVtxBuff;
}

//=============================================================================
// �T�C�Y���
//=============================================================================
D3DXVECTOR3 CScene2D::GetSize2D(void)
{
	return m_size;
}
