//=============================================================================
//
// �e�̏��� [bullet.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "bullet.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "explosion.h"
#include "sound.h"
#include "enemy.h"
#include "effect.h"
#include "laser.h"
#include "boss.h"
#include "score.h"
#include "game.h"
#include "gage.h"
#include "spark.h"
#include "surroundings.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_BULLET_ANIME_SPEED	(2)				// �A�j���[�V�����̑��x
#define PLAYER_BULLET_ANIME_COUNTER	(4)				// �A�j���[�V�����̐�
#define CURRENT_BULLET_SPEED_X		(5.0f)			// �Ǐ]���̒e�̑��x
#define COUNTER_BULLET_SPEED_Y		(5.0f)			// �Ǐ]���̒e�̑��x
#define BULLET_SCORE_NUM			(10)			// �e���z�������Ƃ��̃X�R�A

#define FIRE_WARK_ANGLE				(20)			// �ԉΒe�̊p�x
#define FIRE_WARK_SPPED				(2)				// �ԉΒe�̑��x
#define FIRE_WARK_DISTANCE			(20)			// �ԉΒe�̔�������

#define BULLET_COLOR_MAX			(50)			// �ϐF�̍ő�l
#define BULLET_COLOR_MIN			(0)				// �ϐF�̍ŏ��l

//=============================================================================
// static����������
//=============================================================================
LPDIRECT3DTEXTURE9 CBullet::m_apTexture[MAX_BULLET_TEXTURE] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBullet::CBullet()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_type = BULLET_TYPE_NONE;
	m_Ctype = BULLET_COLOR_NONE;
	m_Bcategory = BULLET_CATEGORY_NONE;
	m_nSubColor = 0;
	m_nSubCol = 5;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
	TYPE type, BULLET_TYPE Btype, BULLET_COLOR Ctype,
	int nLife)
{
	// �C���X�^���X����
	CBullet *pBullet = new CBullet;

	// ����������
	pBullet->Init(pos, size, type);		// ���������
	pBullet->SetType(Btype, Ctype);		// �^�C�v�̐ݒ�

	// �o���b�g�̎��
	switch (Btype)
	{
		// �v���C���[�̎�
	case BULLET_TYPE_PLAYER:

		// �F�̎��
		switch (Ctype)
		{
		case BULLET_COLOR_WHITE:		// �����e

			// �e�N�X�`��
			pBullet->BindTexture(m_apTexture[0]);
			// �A�j���[�V����������
			pBullet->InitAnimation(PLAYER_BULLET_ANIME_SPEED, PLAYER_BULLET_ANIME_COUNTER, -1);
			break;

		case BULLET_COLOR_BLACK:		// �����e

			// �e�N�X�`��
			pBullet->BindTexture(m_apTexture[1]);
			// �A�j���[�V����������
			pBullet->InitAnimation(PLAYER_BULLET_ANIME_SPEED, PLAYER_BULLET_ANIME_COUNTER, -1);
			break;
		}

		break;

		// �G�̎�
	case BULLET_TYPE_ENEMY:

		// �F�̎��
		switch (Ctype)
		{
			// �����e
		case BULLET_COLOR_WHITE:
			// �e�N�X�`���̐ݒ�
			pBullet->BindTexture(m_apTexture[2]);
			break;

			// �����e
		case BULLET_COLOR_BLACK:
			// �e�N�X�`���̐ݒ�
			pBullet->BindTexture(m_apTexture[3]);
			break;
		}
	}
	// �e�̐ݒ�
	pBullet->SetBullet(move, nLife, size);

	return pBullet;
}

//=============================================================================
// �G�̃J�E���^�[�e
//=============================================================================
CBullet * CBullet::CounterAttack(
	D3DXVECTOR3 pos, D3DXVECTOR3 size,
	TYPE type, BULLET_TYPE Btype, BULLET_COLOR Ctype, BULLET_CATEGORY Bcate,
	int nLife, int nBulletNum)
{
	for (int nCount = 0; nCount < nBulletNum; nCount++)
	{
		// �v���C���[�̏��
		CPlayer *pPlayer = CGame::GetPlayer();
		D3DXVECTOR3 Ppos = pPlayer->GetPosition();

		//���@���擾����
		float fPposx = Ppos.x, fPposy = Ppos.y;		// ���@�̍��W
		float fEposx = pos.x, fEposy = pos.y;		// �G�̍��W
		float fAngle;								// �p�x

		//�p�x�����߂�
		fAngle = atan2f((fEposx - fPposx), (fEposy - fPposy));

		// �C���X�^���X����
		CBullet *pBullet = new CBullet;

		// ����������
		pBullet->Init(pos, size, type);		// ���������
		pBullet->SetType(Btype, Ctype);		// �^�C�v���ݒ�
		pBullet->SetCategory(Bcate);		// �o���b�g�̎��

		// �F�̎��
		switch (Ctype)
		{
			// �����e
		case BULLET_COLOR_WHITE:

			// �e�N�X�`�����
			pBullet->BindTexture(m_apTexture[2]);
			break;

			// �����e
		case BULLET_COLOR_BLACK:

			// �e�N�X�`�����
			pBullet->BindTexture(m_apTexture[3]);
			break;
		}

		// �����_���e�̐ݒ�
		D3DXVECTOR3 EffectMove =
			D3DXVECTOR3((0.25f*(float)(rand() % 5 - rand() % 5 - rand() % 5)),
				COUNTER_BULLET_SPEED_Y + (0.3f*(float)(rand() % 5 + rand() % 5 + rand() % 5)),
				0.0f);

		// �e�̐ݒ�
		pBullet->SetBullet(EffectMove, nLife, size);
	}

	return S_OK;
}

//=============================================================================
// ���@�擾�e
//=============================================================================
CBullet * CBullet::CurrentAttack(D3DXVECTOR3 pos, D3DXVECTOR3 Ppos,
	D3DXVECTOR3 size, TYPE type,
	BULLET_TYPE Btype, BULLET_COLOR Ctype,
	int nLife)
{
	//���@���擾����
	float fPposx = Ppos.x, fPposy = Ppos.y;		// ���@�̍��W
	float fEposx = pos.x, fEposy = pos.y;		// �G�̍��W
	float fAngle;								// �p�x

	//�p�x�����߂�
	fAngle = atan2f((fEposx - fPposx), (fEposy - fPposy));

	// �C���X�^���X����
	CBullet *pBullet = new CBullet;

	// ����������
	pBullet->Init(pos, size, type);
	pBullet->SetType(Btype, Ctype);

	// �F�̎��
	switch (Ctype)
	{
	case BULLET_COLOR_WHITE:		// �����e

		// �e�N�X�`��
		pBullet->BindTexture(m_apTexture[2]);
		break;

		// �����e
	case BULLET_COLOR_BLACK:

		// �e�N�X�`��
		pBullet->BindTexture(m_apTexture[3]);
		break;
	}

	// �ړI�̍��W
	D3DXVECTOR3 Target = D3DXVECTOR3(
		(sinf(fAngle)*-CURRENT_BULLET_SPEED_X),
		cosf(fAngle)*-COUNTER_BULLET_SPEED_Y, 0.0f);

	// �e�̐ݒ�
	pBullet->SetBullet(Target, nLife, size);

	return pBullet;
}

//=============================================================================
// �ԉΌ^�o���b�g
//=============================================================================
CBullet * CBullet::FireWorks(D3DXVECTOR3 pos, D3DXVECTOR3 size,
	TYPE type, BULLET_TYPE Btype, BULLET_COLOR Ctype, BULLET_CATEGORY Bcate, int nLife)
{
	// �C���X�^���X����
	CBullet *pBullet = new CBullet;

	// �����̐ݒ�
	int nDistance = rand() % FIRE_WARK_DISTANCE - rand() % FIRE_WARK_DISTANCE - rand() % FIRE_WARK_DISTANCE;
	int nSpeed = 5+ rand() % FIRE_WARK_SPPED + rand() % FIRE_WARK_SPPED;

	// �����_���ŏo�������߂�
	D3DXVECTOR3 TargetPos = D3DXVECTOR3(pos.x + nDistance * cosf(D3DXToRadian(90 + (rand() % FIRE_WARK_ANGLE - rand() % FIRE_WARK_ANGLE))),
		pos.y - nDistance * sinf(D3DXToRadian(90 + (rand() % FIRE_WARK_ANGLE - rand() % FIRE_WARK_ANGLE))), 0.0f);

	// �ړ��ʐݒ�
	D3DXVECTOR3 move = D3DXVECTOR3(cosf(D3DXToRadian(90 + (rand() % FIRE_WARK_ANGLE - rand() % FIRE_WARK_ANGLE))) * nSpeed,
		sinf(D3DXToRadian(90 + (rand() % FIRE_WARK_ANGLE - rand() % FIRE_WARK_ANGLE))) * nSpeed, 0.0f);

	// ����������
	pBullet->Init(TargetPos, size, type);

	switch (Ctype)
	{
		// �����e
	case BULLET_COLOR_WHITE:

		// �e�N�X�`���̐ݒ�
		pBullet->BindTexture(m_apTexture[2]);
		break;

		// �����e�̏���
	case BULLET_COLOR_BLACK:

		// �e�N�X�`���̐ݒ�
		pBullet->BindTexture(m_apTexture[3]);
		break;
	}

	// �^�C�v�̐ݒ�
	pBullet->SetType(Btype, Ctype);

	// �e�̎��
	pBullet->SetCategory(Bcate);

	// ���C�t�̐ݒ�
	int nRandomLife = nLife + (rand() % 40);

	// �e�̐ݒ�
	pBullet->SetBullet(move, nRandomLife, size);

	return pBullet;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CScene2D::Init(pos, size, type);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBullet::Uninit(void)
{
	// 2D�|���S���I������
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBullet::Update(void)
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

	// �ԉ΂̎�
	if (m_Bcategory == BULLET_CATEGORY_FIREWORKS)
	{
		// �ԉΒe�̍X�V
		FireWorksUpdate();
	}

	// ���C�t��0�ɂȂ�����
	if (m_nLife <= 0)
	{
		// �I������
		Uninit();
		return;
	}

	// ��ʊO����
	if (m_Pos.x  < 0.0f || m_Pos.x  > SCREEN_WIDTH ||
		m_Pos.y  < 0.0f || m_Pos.y  > SCREEN_HEIGHT)
	{
		// �̗͂�0�ɂ���
		m_nLife = 0;
	}

	for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
	{
		CScene *pScene = NULL;
		if (pScene == NULL)
		{
			// �V�[�����擾
			pScene = CScene::GetScene(nCount);

			// �������̃L���X�g
			CScene2D *pScene2D = (CScene2D*)pScene;

			if (pScene2D != NULL)
			{
				// ��ނ𔻕�
				CScene::TYPE type = pScene->GetType();

				// �G�l�~�[�̎�
				if (type == TYPE_ENEMY)
				{
					// �^�[�Q�b�g�̏��m��
					D3DXVECTOR3 Target = pScene2D->GetPosition();

					// �G�̃T�C�Y�擾
					CEnemy *pEnemy = (CEnemy*)pScene2D;
					D3DXVECTOR3 size = pEnemy->GetSize();

					// �G�l�~�[�̒e����Ȃ��Ƃ�
					if (m_type != BULLET_TYPE_ENEMY)
					{
						// �����蔻�菈��
						if (Collision(Target, size) == true)
						{
							// �o���b�g�̗̑͂�0
							m_nLife = 0;

							// �G�l�~�[�Ƀ_���[�W��^����
							pEnemy->HitDamage(1);
							break;
						}
					}
				}
				else if (type == TYPE_BOSS)
				{// �{�X�̎�

					// �^�[�Q�b�g�̏��m��
					D3DXVECTOR3 Target = pScene2D->GetPosition();

					// �G�̃T�C�Y�擾
					CBoss *pBoss = (CBoss*)pScene2D;
					D3DXVECTOR3 size = pBoss->GetSize();

					// �G�l�~�[�̒e����Ȃ��Ƃ�
					if (m_type != BULLET_TYPE_ENEMY)
					{
						// �����蔻�菈��
						if (Collision(Target, size) == true)
						{
							for (int nCount = 0; nCount < SPARK_BOSS_NUM; nCount++)
							{
								// �ΉԂ̐���
								CSpark::Create(D3DXVECTOR3(m_Pos.x, m_Pos.y - 30.0f, 0.0f) ,
									D3DXVECTOR3(SPARK_SIZE_X, SPARK_SIZE_Y, 0.0f),
									TYPE_EFFECT, SPARK_BOSS_ANGLE, SPARK_BASE_BOSS_ANGLE, SPARK_BOSS_DISTANCE, SPARK_LIFE);
							}

							// �̗͂�0��
							m_nLife = 0;

							// �{�X�Ƀ_���[�W��^����
							pBoss->HitBossDamage(2);
							break;
						}
					}
				}
				else if (type == TYPE_SURROUNDINGS)
				{// ��芪��

					// �^�[�Q�b�g�̏��m��
					D3DXVECTOR3 Target = pScene2D->GetPosition();

					// �G�̃T�C�Y�擾
					CSurroundings *pSurroundings = (CSurroundings*)pScene2D;
					D3DXVECTOR3 size = pSurroundings->GetSize();

					// �G�l�~�[�̒e����Ȃ��Ƃ�
					if (m_type != BULLET_TYPE_ENEMY)
					{
						// �����蔻�菈��
						if (Collision(Target, size) == true)
						{
							// �̗͂�0��
							m_nLife = 0;

							// ��芪���Ƀ_���[�W��^����
							pSurroundings->HitSurroundings(2);
							break;
						}
					}
				}

				// �v���C���[�̎�
				else if (type == TYPE_PLAYER)
				{
					// �^�[�Q�b�g�̏��m��
					D3DXVECTOR3 Target = pScene2D->GetPosition();

					// �����ȊO�̒e�̎�
					if (m_type != BULLET_TYPE_PLAYER)
					{
						// �����蔻�菈��
						if (Collision(Target, D3DXVECTOR3(DECISION_PLAYER_SIZE_X, DECISION_PLAYER_SIZE_Y, 0.0f)) == true)
						{
							// �o���b�g�̃��C�t��0�ɂ���
							m_nLife = 0;

							// �v���C���[�̏����󂯎��
							CPlayer *pPlayer = (CPlayer*)pScene2D;
							bool bPlayerInfo = pPlayer->GetShildInfo();

							// �v���C���[�̐F���
							if (bPlayerInfo == false)
							{
								// �Ⴄ�F��������
								if (m_Ctype == BULLET_COLOR_WHITE)
								{
									// �v���C���[�Ƀ_���[�W��^����
									pPlayer->HitDamage(1);
								}
								else
								{
									// �X�R�A�����Z
									CScore *pScore = CGame::GetScore();
									pScore->SetScore(BULLET_SCORE_NUM);

									// �Q�[�W�����܂�
									CGage *pGage = pPlayer->GetGage();
									pGage->AddGage(1);
								}
							}
							else
							{
								// �Ⴄ�F��������
								if (m_Ctype == BULLET_COLOR_BLACK)
								{
									// �v���C���[�Ƀ_���[�W��^����
									pPlayer->HitDamage(1);
								}
								else
								{
									// �X�R�A�����Z
									CScore *pScore = CGame::GetScore();
									pScore->SetScore(BULLET_SCORE_NUM);

									// �Q�[�W�ʂ𑝂₷
									CGage *pGage = pPlayer->GetGage();
									pGage->AddGage(1);
								}
							}
							break;
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	// 2D�|���S���`�揈��
	CScene2D::Draw();
}

//=============================================================================
// �ԉ΂̍X�V����
//=============================================================================
void CBullet::FireWorksUpdate(void)
{
	// �ԉ΂̏���
	ScaleDown(m_Pos, FIRE_WORKS_LIFE);
	m_move.y += 1.0f;
}

//====================================================================
// �|���S���̓_��
//====================================================================
void CBullet::FlashPolygon(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �J���[�̌��Z
	m_nSubColor += m_nSubCol;

	// �J���[�ύX�̍ő�l
	if (m_nSubColor >= BULLET_COLOR_MAX)
	{
		// ����
		m_nSubColor = BULLET_COLOR_MAX;

		// �l�𔽓]
		m_nSubCol *= -1;
	}
	else if (m_nSubColor <= BULLET_COLOR_MIN)
	{
		// �J���[�̍ŏ��l�̐���
		m_nSubColor = BULLET_COLOR_MIN;

		// �t���[���J�E���g
		m_nSubColor++;

		// �l�𔽓]
		m_nSubCol *= -1;
	}

	// �F�̎��
	switch (m_Ctype)
	{
		// �����Ƃ�
	case BULLET_COLOR_WHITE:

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255 - m_nSubColor, 255, 255 - m_nSubColor, 255);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DCOLOR_RGBA(255 - m_nSubColor, 255, 255 - m_nSubColor, 255);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DCOLOR_RGBA(255 - m_nSubColor, 255, 255 - m_nSubColor, 255);	// �������_�̐F	�����x255
		pVtx[3].col = D3DCOLOR_RGBA(255 - m_nSubColor, 255, 255 - m_nSubColor, 255);	// �E�����_�̐F	�����x255
		break;

		// �����Ƃ�
	case BULLET_COLOR_BLACK:

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255 - m_nSubColor, 255 - m_nSubColor, 255);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DCOLOR_RGBA(255, 255 - m_nSubColor, 255 - m_nSubColor, 255);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DCOLOR_RGBA(255, 255 - m_nSubColor, 255 - m_nSubColor, 255);	// �������_�̐F	�����x255
		pVtx[3].col = D3DCOLOR_RGBA(255, 255 - m_nSubColor, 255 - m_nSubColor, 255);	// �E�����_�̐F	�����x255
		break;

	}

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CBullet::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/bullet000.png",
		&m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/bullet001.png",
		&m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/bullet002.png",
		&m_apTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/�ԃo���A.png",
		&m_apTexture[3]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CBullet::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_BULLET_TEXTURE; nCount++)
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
// �����蔻��
//=============================================================================
bool CBullet::Collision(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	if (m_Bcategory = BULLET_CATEGORY_COUNTER)
	{
		// �v���C���[�̏��擾
		CPlayer *pPlayer = CGame::GetPlayer();
		bool bPlayerInfo = pPlayer->GetShildInfo();

		if (bPlayerInfo == true)
		{
			if (m_Ctype == BULLET_COLOR_WHITE)
			{
				size = D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, 0.0f);
			}
		}
		else
		{
			if (m_Ctype == BULLET_COLOR_BLACK)
			{
				size = D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, 0.0f);
			}
		}
	}
	if (m_type == BULLET_TYPE_PLAYER)
	{
		if (pos.x - size.x / 2 < m_Pos.x + m_Size.x / 5.0f &&
			pos.x + size.x / 2 > m_Pos.x - m_Size.x / 5.0f &&
			pos.y - size.y / 2 < m_Pos.y + m_Size.y / 5.0f - 20.0f &&
			pos.y + size.y / 2 > m_Pos.y - m_Size.y / 2.0f)
		{
			return true;
		}
	}
	else
	{
		if (pos.x - size.x / 2 < m_Pos.x + m_Size.x / 2 &&
			pos.x + size.x / 2 > m_Pos.x - m_Size.x / 2 &&
			pos.y - size.y / 2 < m_Pos.y + m_Size.y / 2 &&
			pos.y + size.y / 2 > m_Pos.y - m_Size.y / 2)
		{
			return true;
		}
	}
	return false;
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
void CBullet::SetBullet(D3DXVECTOR3 move, int nLife, D3DXVECTOR3 size)
{
	// �ϐ��ɑ��
	m_move = move;
	m_nLife = nLife;
	m_Size = size;
}

//=============================================================================
// �e�̎�ނ̐ݒ�
//=============================================================================
void CBullet::SetType(BULLET_TYPE type, BULLET_COLOR Ctype)
{
	m_type = type;
	m_Ctype = Ctype;
}

//=============================================================================
// �e�̎�ނ̐ݒ�
//=============================================================================
void CBullet::SetCategory(BULLET_CATEGORY Bcate)
{
	m_Bcategory = Bcate;
}

//=============================================================================
// ���C�t�����炷
//=============================================================================
void CBullet::DecreaseLife(int nNumber)
{
	m_nLife -= nNumber;
}

//=============================================================================
// �T�C�Y�̏��
//=============================================================================
D3DXVECTOR3 CBullet::GetSize(void)
{
	return m_Size;
}

//=============================================================================
// �F�̏��
//=============================================================================
CBullet::BULLET_COLOR CBullet::GetCtype(void)
{
	return m_Ctype;
}