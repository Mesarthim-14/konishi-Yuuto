//=============================================================================
//
// �t���b�V������ [flash.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "flash.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "sound.h"
#include "game.h"
#include "laser.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FLASH_ANGLE		(360)			// �p�x
#define FLASH_SPPED		(1.5f)			// ���x
#define FLASH_DISTANCE	(14)			// ����

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CFlash::m_apTexture[MAX_FLASH_TEXTURE] = {};

//=============================================================================
// �C���X�^���X����
//=============================================================================
CFlash * CFlash::Create(D3DXVECTOR3 pos,
	D3DXVECTOR3 size, TYPE type, FLASH_COLOR Ctype, FLASH_TYPE Ftype, int nLife)
{
	// �C���X�^���X����
	CFlash *pFlash = new CFlash;

	if (pFlash != NULL)
	{
		// �����̐ݒ�
		int nDistance = rand() % FLASH_DISTANCE + rand() % FLASH_DISTANCE;

		// �����_���ŏo�������߂�
		D3DXVECTOR3 TargetPos = D3DXVECTOR3(pos.x + nDistance * cosf(D3DXToRadian(90 + (rand() % FLASH_ANGLE - rand() % FLASH_ANGLE))),
			pos.y - 20.0f - nDistance * sinf(D3DXToRadian(90 + (rand() % FLASH_ANGLE - rand() % FLASH_ANGLE))), 0.0f);


		// �ړ���
		D3DXVECTOR3 move = D3DXVECTOR3(cosf(D3DXToRadian(90 + (rand() % FLASH_ANGLE - rand() % FLASH_ANGLE))) * FLASH_SPPED,
			sinf(D3DXToRadian(90 + (rand() % FLASH_ANGLE - rand() % FLASH_ANGLE))) * -FLASH_SPPED, 0.0f);

		// ����������
		pFlash->Init(TargetPos, size, type);	// ���������
		pFlash->m_TargetOld = pos;				// �ŏ��̍��W
		pFlash->SetMove(move);					// �ړ���
		pFlash->SetFType(Ftype);				// ���
		pFlash->SetColor(Ctype);				// �F
		pFlash->InitColor();					// �F�̏�����
		pFlash->BindTexture(m_apTexture[0]);	// �e�N�X�`���ݒ�
		pFlash->m_nLife = nLife;				// ���C�t�ݒ�
	}

	return pFlash;
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CFlash::Load(void)
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
void CFlash::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_FLASH_TEXTURE; nCount++)
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
CFlash::CFlash()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_TargetOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Ctype = FLASH_COLOR_NONE;
	m_Ftype = FLASH_TYPE_NONE;
	m_pVtxBuff = NULL;
	m_nLife = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFlash::~CFlash()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CFlash::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CScene2D::Init(pos, size, type);
	m_Pos = pos;

	return S_OK;
}

//=============================================================================
// �J���[�̐ݒ�
//=============================================================================
void CFlash::InitColor(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �F�̎��
	switch (m_Ctype)
	{
		// ���̎�
	case FLASH_COLOR_WHITE:

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(30, 30, 255, 255);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DCOLOR_RGBA(30, 30, 255, 255);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DCOLOR_RGBA(30, 30, 255, 255);	// �������_�̐F	�����x255
		pVtx[3].col = D3DCOLOR_RGBA(30, 30, 255, 255);	// �E�����_�̐F	�����x255
		break;

		// ���̎�
	case FLASH_COLOR_BLACK:
		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 40, 40, 255);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DCOLOR_RGBA(255, 40, 40, 255);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DCOLOR_RGBA(255, 40, 40, 255);	// �������_�̐F	�����x255
		pVtx[3].col = D3DCOLOR_RGBA(255, 40, 40, 255);	// �E�����_�̐F	�����x255
		break;
	}

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void CFlash::Uninit(void)
{
	// 2D�|���S���I������
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CFlash::Update(void)
{
	// ���C�t���Z
	m_nLife--;

	// 2D�|���S���X�V����
	CScene2D::Update();

	// �ʒu�̎��
	switch (m_Ftype)
	{
		// ��̎�
	case FLASH_TYPE_TOP:
		GetLaserTop();
		break;
		
		// ���̎�
	case FLASH_TYPE_SHOT:
		// ���W�X�V
		GetPlayerPos();
	}

	// �ړ��ʍX�V
	m_Pos += m_move;

	// ���W��n��
	SetPosition(m_Pos);

	// ���C�t��0�ɂȂ�����
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
void CFlash::Draw(void)
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
// �v���C���[�̈ʒu���擾
//=============================================================================
void CFlash::GetPlayerPos(void)
{
	// ��̍��W�����邽��
	static int nNum = 0;

	CPlayer *pPlayer = CGame::GetPlayer();

	if (nNum % 2 == 0)
	{
		// �^�[�Q�b�g�̏��m��
		D3DXVECTOR3 Target = D3DXVECTOR3(pPlayer->GetPosition().x - PLAYER_SHOT_POS_X, pPlayer->GetPosition().y - PLAYER_SHOT_POS_Y + 10, 0.0f);

		// �ʒu���X�V
		D3DXVECTOR3 TargetMove = D3DXVECTOR3(Target.x - m_TargetOld.x, Target.y - m_TargetOld.y, 0.0f);

		// �ړ��ʂ𑫂�
		m_Pos += TargetMove;

		// �J�E���g��i�߂�
		nNum++;

		// �Â����W���W���X�V
		m_TargetOld = Target;
	}
	else
	{
		// �^�[�Q�b�g�̏��m��
		D3DXVECTOR3 Target = D3DXVECTOR3(pPlayer->GetPosition().x + PLAYER_SHOT_POS_X, pPlayer->GetPosition().y - PLAYER_SHOT_POS_Y + 10, 0.0f);

		// �ʒu���X�V
		D3DXVECTOR3 TargetMove = D3DXVECTOR3(Target.x - m_TargetOld.x, Target.y - m_TargetOld.y, 0.0f);

		// �ړ��ʂ𑫂�
		m_Pos += TargetMove;

		// �J�E���g��i�߂�
		nNum++;

		// �Â����W���W���X�V
		m_TargetOld = Target;
	}
}

//=============================================================================
// �g�b�v�̏��
//=============================================================================
void CFlash::GetLaserTop(void)
{
	static int nNum = 0;

	CPlayer *pPlayer = CGame::GetPlayer();

	if (pPlayer->GetLaser() != NULL)
	{
		CLaser *pLaser = pPlayer->GetLaser();
		if (nNum % 2 == 0)
		{
			// �^�[�Q�b�g�̏��m��
			D3DXVECTOR3 Top = D3DXVECTOR3(pLaser->GetTop().x - PLAYER_SHOT_POS_X, pLaser->GetTop().y - PLAYER_SHOT_POS_Y, 0.0f);

			// �ʒu���X�V
			D3DXVECTOR3 TopMove = D3DXVECTOR3(Top.x - m_TargetOld.x, Top.y - m_TargetOld.y, 0.0f);

			// �ړ��ʂ𑫂�
			m_Pos += TopMove;

			// �J�E���g��i�߂�
			nNum++;

			// �Â����W���W���X�V
			m_TargetOld = Top;
		}
		else
		{
			// �^�[�Q�b�g�̏��m��
			D3DXVECTOR3 Target = D3DXVECTOR3(pLaser->GetTop().x + PLAYER_SHOT_POS_X, pLaser->GetTop().y - PLAYER_SHOT_POS_Y, 0.0f);

			// �ʒu���X�V
			D3DXVECTOR3 TargetMove = D3DXVECTOR3(Target.x - m_TargetOld.x, Target.y - m_TargetOld.y, 0.0f);

			// �ړ��ʂ𑫂�
			m_Pos += TargetMove;

			// �J�E���g��i�߂�
			nNum++;

			// �Â����W���W���X�V
			m_TargetOld = Target;
		}
	}
}

//=============================================================================
// �^�C�v�ݒ�
//=============================================================================
void CFlash::SetFType(FLASH_TYPE Ftype)
{
	m_Ftype = Ftype;
}

//=============================================================================
// �J���[�ݒ�
//=============================================================================
void CFlash::SetColor(FLASH_COLOR Ctype)
{
	m_Ctype = Ctype;
}

//=============================================
// �ړ��ʐݒ�
//=============================================
void CFlash::SetMove(D3DXVECTOR3 move)
{
	// �ړ��ʂ�ݒ�
	m_move = move;
}