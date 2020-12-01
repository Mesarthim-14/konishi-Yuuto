//=============================================================================
//
// �ԉ΍ŏ��̂�̏��� [fire.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "fire.h"
#include "renderer.h"
#include "manager.h"
#include "sound.h"
#include "bullet.h"
#include "time.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FIRE_MOVE_Y			(2.0f)			// �ړ���
#define FIRE_DISTANCE		(200)			// �������鋗��

//=============================================================================
// static����������
//=============================================================================
LPDIRECT3DTEXTURE9 CFire::m_apTexture[MAX_FIRE_TEXTURE] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFire::CFire()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_Ctype = FIRE_COLOR_NONE;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFire::~CFire()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CFire * CFire::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,
	TYPE type, FIRE_COLOR Ctype, int nLife)
{
	// �������m��
	CFire *pFire = new CFire;

	// ����������
	pFire->Init(D3DXVECTOR3(												// ����������
		pos.x - rand() % 120 + rand() % 120, pos.y, 0.0f), size, type);
	pFire->SetType(Ctype);													// ��ނ̐ݒ�
	pFire->SetFire(nLife, size);											// �e�̐ݒ�
	pFire->InitMove();														// �ړ��ʐݒ�
	pFire->m_nLife = nLife;													// �̗͂̑��
	pFire->BindTexture(m_apTexture[0]);										// �e�N�X�`���ݒ�

	return pFire;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CFire::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CScene2D::Init(pos, size, type);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CFire::Uninit(void)
{
	// 2D�|���S���I������
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CFire::Update(void)
{
	// 2D�|���S���X�V����
	CScene2D::Update();

	// ���݂̈ʒu���擾
	m_Pos = GetPosition();

	// �ړ��̍X�V
	m_Pos += m_move;

	// �򋗗��̃J�E���^�[���Z
	m_nLife--;

	// ���W��n��
	SetPosition(m_Pos);

	// ���C�t��0�ɂȂ�����
	if (m_nLife <= 0)
	{
		// �F�̎��
		switch (m_Ctype)
		{
			// �����Ƃ�
		case FIRE_COLOR_WHITE:
			for (int nCount = 0; nCount < FIRE_WORKS_NUM; nCount++)
			{
				// �ԉΒe���o��
				CBullet::FireWorks(m_Pos,
					D3DXVECTOR3(FIRE_WORKS_SIZE_X, FIRE_WORKS_SIZE_Y, 0.0f),
					TYPE_BULLET, CBullet::BULLET_TYPE_ENEMY,
					CBullet::BULLET_COLOR_WHITE, CBullet::BULLET_CATEGORY_FIREWORKS,
					FIRE_WORKS_LIFE);
			}
			break;

			// �����Ƃ�
		case FIRE_COLOR_BLACK:
			for (int nCount = 0; nCount < FIRE_WORKS_NUM; nCount++)
			{
				// �ԉΒe���o��
				CBullet::FireWorks(m_Pos,
					D3DXVECTOR3(FIRE_WORKS_SIZE_X, FIRE_WORKS_SIZE_Y, 0.0f),
					TYPE_BULLET, CBullet::BULLET_TYPE_ENEMY,
					CBullet::BULLET_COLOR_BLACK, CBullet::BULLET_CATEGORY_FIREWORKS,
					FIRE_WORKS_LIFE);
			}
			break;
		}

		// �I������
		Uninit();

		return;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CFire::Draw(void)
{
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
// �ړ��ʂ̐ݒ�
//=============================================================================
void CFire::InitMove(void)
{
	m_move = D3DXVECTOR3(0.0f, FIRE_MOVE_Y, 0.0f);
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
void CFire::SetFire(int nLife, D3DXVECTOR3 size)
{
	m_nLife = nLife;
	m_Size = size;
}

//=============================================================================
// �e�̎�ނ̐ݒ�
//=============================================================================
void CFire::SetType(FIRE_COLOR Ctype)
{
	m_Ctype = Ctype;
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CFire::Load(void)
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
void CFire::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_FIRE_TEXTURE; nCount++)
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
// �J���[�̏��
//=============================================================================
CFire::FIRE_COLOR CFire::GetCtype(void)
{
	return m_Ctype;
}