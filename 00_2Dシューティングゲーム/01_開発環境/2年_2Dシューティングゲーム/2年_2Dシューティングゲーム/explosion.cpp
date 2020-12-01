//=============================================================================
//
// �������� [explosion.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "explosion.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "sound.h"

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CExplosion::m_apTexture[MAX_EXPLOSION_TEXTURE] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CExplosion::CExplosion()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Ctype = COLOR_TYPE_NONE;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CExplosion::~CExplosion()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CScene2D::Init(pos, size, type);

	// ���W���
	m_Pos = pos;

	// �����̎��
	switch (m_Ctype)
	{
	case COLOR_TYPE_WHITE:
	case COLOR_TYPE_BLACK:
		// �A�j���[�V�����ݒ�
		InitAnimation(EXPLOSION_ANIM_SPEED, EXPLOSION_ANIM_PATTERN, 0);
		break;

	case COLOR_TYPE_BOSS:
		// �A�j���[�V�����ݒ�
		InitAnimation(BOSS_EXPLOSION_ANIM_SPEED, BOSS_EXPLOSION_ANIM_PATTERN, 0);
		break;
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CExplosion::Uninit(void)
{
	// 2D�|���S���I������
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CExplosion::Update(void)
{
	// ���݂̈ʒu���擾
	m_Pos = GetPosition();

	m_Pos += m_move;

	// ���W��n��
	SetPosition(m_Pos);

	// 2D�|���S���X�V����
	CScene2D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CExplosion::Draw(void)
{
	// 2D�|���S���`�揈��
	CScene2D::Draw();
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CExplosion * CExplosion::Create(D3DXVECTOR3 pos,  D3DXVECTOR3 move, D3DXVECTOR3 size, TYPE type, COLOR_TYPE Ctype)
{
	// �������m��
	CExplosion *pExplosion = new CExplosion;

	// ����������
	pExplosion->m_Ctype = Ctype;				// �^�C�v�ݒ�
	pExplosion->Init(pos, size, type);			// ����������
	pExplosion->SetExplosion(move, Ctype);		// �ړ��ʐݒ�

	// �F�̏���
	switch (Ctype)
	{
		// �����Ƃ�
	case COLOR_TYPE_WHITE:
		// �e�N�X�`���ݒ�
		pExplosion->BindTexture(m_apTexture[0]);
		break;

		// �����Ƃ�
	case COLOR_TYPE_BLACK:
		// �e�N�X�`���ݒ�
		pExplosion->BindTexture(m_apTexture[1]);
		break;

		// �{�X�̎�
	case COLOR_TYPE_BOSS:
		// �e�N�X�`���ݒ�
		pExplosion->BindTexture(m_apTexture[2]);
		break;
	}

	return pExplosion;
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
void CExplosion::SetExplosion(D3DXVECTOR3 move, COLOR_TYPE Ctype)
{
	m_move = move;
	m_Ctype = Ctype;
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CExplosion::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/Explosion002.png",
		&m_apTexture[0]);		

	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/Explosion001.png",
		&m_apTexture[1]);

	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/Explosion100.png",
		&m_apTexture[2]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CExplosion::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_EXPLOSION_TEXTURE; nCount++)
	{
		// �e�N�X�`���̊J��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}