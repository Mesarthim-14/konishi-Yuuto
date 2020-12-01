//=============================================================================
//
// �}�Y���t���b�V������ [muzzle_flash.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "muzzle_flash.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "sound.h"
#include "game.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MUZZLE_FLASH_ANGLE		(30)	// �p�x
#define MUZZLE_FLASH_SPPED		(1)		// ���x
#define MUZZLE_FLASH_DISTANCE	(28)	// ��������

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CMuzzleFlash::m_apTexture[MAX_MUZZLE_FLASH_TEXTURE] = {};

//=============================================================================
// �C���X�^���X����
//=============================================================================
CMuzzleFlash * CMuzzleFlash::Create(D3DXVECTOR3 pos, 
	D3DXVECTOR3 size, TYPE type, EFFECT_COLOR Ctype, int nLife)
{
	// �C���X�^���X����
	CMuzzleFlash *pMuzzleFlash = new CMuzzleFlash;

	if (pMuzzleFlash != NULL)
	{
		// �����̐ݒ�
		int nDistance = rand() % MUZZLE_FLASH_DISTANCE + rand() % MUZZLE_FLASH_DISTANCE;

		// �����_���ŏo�������߂�
		D3DXVECTOR3 TargetPos = D3DXVECTOR3(pos.x + nDistance * cosf(D3DXToRadian(90 + (rand() % MUZZLE_FLASH_ANGLE - rand() % MUZZLE_FLASH_ANGLE)) ),
			pos.y - nDistance * sinf(D3DXToRadian(90 + (rand() % MUZZLE_FLASH_ANGLE - rand() % MUZZLE_FLASH_ANGLE))), 0.0f);

		// ����������
		pMuzzleFlash->Init(TargetPos, size, type);
		pMuzzleFlash->m_TargetOld = pos;

		// �ړ���
		D3DXVECTOR3 move = D3DXVECTOR3(cosf(D3DXToRadian(90 + (rand() % MUZZLE_FLASH_ANGLE - rand() % MUZZLE_FLASH_ANGLE))) * MUZZLE_FLASH_SPPED,
			sinf(D3DXToRadian(90 + (rand() % MUZZLE_FLASH_ANGLE - rand() % MUZZLE_FLASH_ANGLE))) * -MUZZLE_FLASH_SPPED, 0.0f);
		
		// �����̐ݒ�
		pMuzzleFlash->SetMove(move);

		// �J���[�̎�ސݒ�
		pMuzzleFlash->SetColor(Ctype);

		// �J���[������
		pMuzzleFlash->InitColor();

		// �e�N�X�`���ݒ�
		pMuzzleFlash->BindTexture(m_apTexture[0]);

		// �̗͂̐ݒ�
		pMuzzleFlash->m_nLife = nLife;
	}

	return pMuzzleFlash;
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CMuzzleFlash::Load(void)
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
void CMuzzleFlash::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_MUZZLE_FLASH_TEXTURE; nCount++)
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
CMuzzleFlash::CMuzzleFlash()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_TargetOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Ctype = MUZZLE_FLASH_COLOR_NONE;
	m_Etype = MUZZLE_FLASH_TYPE_NONE;
	m_pVtxBuff = NULL;
	m_nLife = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMuzzleFlash::~CMuzzleFlash()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMuzzleFlash::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CScene2D::Init(pos, size, type);
	m_Pos = pos;

	return S_OK;
}

//=============================================================================
// �J���[�̐ݒ�
//=============================================================================
void CMuzzleFlash::InitColor(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �F�̐ݒ�
	switch (m_Ctype)
	{
		// �����Ƃ�
	case MUZZLE_FLASH_COLOR_WHITE:

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(30, 30, 255, 255);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DCOLOR_RGBA(30, 30, 255, 255);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DCOLOR_RGBA(30, 30, 255, 255);	// �������_�̐F	�����x255
		pVtx[3].col = D3DCOLOR_RGBA(30, 30, 255, 255);	// �E�����_�̐F	�����x255
		break;

		// �����Ƃ�
	case MUZZLE_FLASH_COLOR_BLACK:
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
void CMuzzleFlash::Uninit(void)
{
	// 2D�|���S���I������
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMuzzleFlash::Update(void)
{
	// ���C�t���Z
	m_nLife--;

	// 2D�|���S���X�V����
	CScene2D::Update();

	// ���W�X�V
	GetPlayerPos();

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
void CMuzzleFlash::Draw(void)
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
void CMuzzleFlash::GetPlayerPos(void)
{
	// ���E�̍��W�X�V�p
	static int nNum = 0;

	// �v���C���[�̏��擾
	CPlayer *pPlayer = CGame::GetPlayer();

	if (nNum % 2 == 0)
	{
		// �^�[�Q�b�g�̏��m��
		D3DXVECTOR3 Target = D3DXVECTOR3(pPlayer->GetPosition().x - PLAYER_SHOT_POS_X, pPlayer->GetPosition().y - PLAYER_SHOT_POS_Y + 10, 0.0f);

		// �ʒu���X�V
		D3DXVECTOR3 TargetMove = D3DXVECTOR3(Target.x - m_TargetOld.x, Target.y - m_TargetOld.y, 0.0f);

		// �ړ��ʂ𑫂�
		m_Pos += TargetMove;

		nNum++;

		// �Â����W�X�V
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

		nNum++;

		// �Â����W�X�V
		m_TargetOld = Target;
	}
}


//=============================================================================
// �J���[�ݒ�
//=============================================================================
void CMuzzleFlash::SetColor(EFFECT_COLOR Ctype)
{
	m_Ctype = Ctype;
}

//=============================================
// �ړ��ʐݒ�
//=============================================
void CMuzzleFlash::SetMove(D3DXVECTOR3 move)
{
	// �ړ��ʂ�ݒ�
	m_move = move;
}