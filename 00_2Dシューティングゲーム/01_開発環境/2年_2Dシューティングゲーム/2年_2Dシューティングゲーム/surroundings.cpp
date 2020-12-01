//=============================================================================
//
// ��芪���N���X	[surroundings.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "surroundings.h"
#include "renderer.h"
#include "manager.h"
#include "bullet.h"
#include "ui.h"
#include "fade.h"
#include "hpbar.h"
#include "fire.h"
#include "spark.h"
#include "game.h"
#include "boss.h"
#include "player.h"
#include "explosion.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SURROUNDINGS_LIFE				(500)		// ��芪���̗̑�
#define SURROUNDINGS_BULLET_INTERVAL	(30)		// �o���b�g�Ԋu

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CSurroundings::m_apTexture[MAX_SURROUNDINGS_TEXTURE] = {};

//=============================================================================
// �|���S������
//=============================================================================
CSurroundings * CSurroundings::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// �������m��
	CSurroundings *pSurroundings = new CSurroundings;

	if (pSurroundings != NULL)
	{
		// ����������
		pSurroundings->Init(pos, size, type);

		// �e�N�X�`���ݒ�
		pSurroundings->BindTexture(m_apTexture[0]);

		// �{�X�X�e�[�^�X�ݒ�
		pSurroundings->SetPos(pos);					// ���W
		pSurroundings->SetSize(size);				// �T�C�Y�ݒ�
		pSurroundings->m_nLife = SURROUNDINGS_LIFE;	// ���C�t�ݒ�
	}

	return pSurroundings;
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CSurroundings::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/enemy_q.png",
		&m_apTexture[0]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CSurroundings::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_SURROUNDINGS_TEXTURE; nCount++)
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
CSurroundings::CSurroundings()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_nBulletFlame = 0;
	m_nBulletCnt = 0;
	m_bColorFlag = true;
	m_State = ENEMY_STATE_NORMAL;
	m_nStateCnt = 0;
	m_nFlashFlame = 0;
	m_nSubNumber = 0;

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSurroundings::~CSurroundings()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSurroundings::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CScene2D::Init(pos, size, type);
	m_Pos = pos;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSurroundings::Uninit(void)
{
	// �I������
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CSurroundings::Update(void)
{
	// �X�V����
	CScene2D::Update();
	// ���W�X�V
	m_Pos = GetPosition();
	// �ړ��̍X�V
	m_Pos += m_Move;

	switch (m_State)
	{
	case ENEMY_STATE_NORMAL:
		break;
	case ENEMY_STATE_DAMAGE:
		m_nStateCnt++;
		LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
		// ���_����ݒ�
		VERTEX_2D *pVtx;
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(120, 120, 120, 255);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DCOLOR_RGBA(120, 120, 120, 255);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DCOLOR_RGBA(120, 120, 120, 255);	// �������_�̐F	�����x255
		pVtx[3].col = D3DCOLOR_RGBA(120, 120, 120, 255);	// �E�����_�̐F	�����x255

		// ���_�o�b�t�@���A�����b�N����
		pVtxBuff->Unlock();

		if (m_nStateCnt >= 5)
		{
			// ��Ԃ�߂�
			m_State = ENEMY_STATE_NORMAL;

			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// ���㒸�_�̐F	�����x255
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�㒸�_�̐F	�����x255
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �������_�̐F	�����x255
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�����_�̐F	�����x255

			// �J�E���^�[��߂�
			m_nStateCnt = 0;
		}
		break;
	}

	// ���W��n��
	SetPosition(m_Pos);
	SetPos(m_Pos);

	// �e��ł���
	BulletShot();

	// �����蔻��
	Collision();

	// �{�X�̏��擾
	CBoss *pBoss = CGame::GetBoss();
	
	if (pBoss->GetExplosion() == true)
	{
		m_nLife = 0;

		// ��������
		CExplosion::Create(D3DXVECTOR3(m_Pos.x, m_Pos.y, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
			D3DXVECTOR3(SURROUNDINGS_EXPLOSION_SIZE_X, SURROUNDINGS_EXPLOSION_SIZE_Y, 0.0f),
			TYPE_EXPLOSION, CExplosion::COLOR_TYPE_BOSS);
	}

	// �̗͂�0�ɂȂ�����
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
void CSurroundings::Draw(void)
{
	// �`�揈��
	CScene2D::Draw();
}

//=============================================================================
// �e��ł���
//=============================================================================
void CSurroundings::BulletShot(void)
{
	m_nBulletFlame++;

	if (m_nBulletFlame >= SURROUNDINGS_BULLET_INTERVAL)
	{
		// �{�X�̏��󂯎��
		CBoss *pBoss = CGame::GetBoss();
		bool bColor = pBoss->GetColor();

		// ���F��������
		if (bColor == true)
		{
			// �v���C���[�̏��擾
			CPlayer *pPlayer = CGame::GetPlayer();
			D3DXVECTOR3 Target = pPlayer->GetPosition();

			D3DXVECTOR3 RandomPos = D3DXVECTOR3(Target.x - rand() % 50 + rand() % 50 - rand() % 50 + rand() % 50, Target.y, 0.0f);

			// ���@�擾�e�𔭎�
			CBullet::CurrentAttack(D3DXVECTOR3(m_Pos.x, m_Pos.y, 0.0f),
				RandomPos, D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f),
				TYPE_BULLET, CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_COLOR_BLACK,
				1000);
		}
		else
		{
			// �v���C���[�̏��擾
			CPlayer *pPlayer = CGame::GetPlayer();
			D3DXVECTOR3 Target = pPlayer->GetPosition();

			D3DXVECTOR3 RandomPos = D3DXVECTOR3(Target.x - rand() % 50 + rand() % 50 - rand() % 50 + rand() % 50, Target.y, 0.0f);

			// ���@�擾�e�𔭎�
			CBullet::CurrentAttack(D3DXVECTOR3(m_Pos.x, m_Pos.y, 0.0f),
				RandomPos, D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f),
				TYPE_BULLET, CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_COLOR_WHITE,
				1000);
		}

		// �l������
		m_nBulletFlame = 0;
	}
}

//=============================================================================
// �_���[�W
//=============================================================================
void CSurroundings::HitSurroundings(int nNumber)
{
	m_nLife -= nNumber;
}

//=============================================================================
// ���C�t�̏��
//=============================================================================
int CSurroundings::GetLife(void)
{
	return m_nLife;
}
