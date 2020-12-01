//=============================================================================
//
// �|���S���̐ݒ� [scene.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene.h"
#include "renderer.h"
#include "scene2d.h"

//=============================================================================
// static������
//=============================================================================
CScene *CScene::m_apScene[MAX_OBJECT] = {};
int CScene::m_nNumAll = 0;
int CScene::m_nNumEnemy = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene()
{
	// �����o�ϐ�������
	m_nID = 0;
	m_type = TYPE_NONE;

	for (int nCntScene = 0; nCntScene < MAX_OBJECT; nCntScene++)
	{
		// ���ꂼ��NULL�̂Ƃ�
		if (m_apScene[nCntScene] == NULL)
		{
			// Scene2D�̏��
			m_apScene[nCntScene] = this;
			m_nID = nCntScene;
			// ��̉��Z
			m_nNumAll++;
			break;
		}
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCntScene = 0; nCntScene < MAX_OBJECT; nCntScene++)
	{
		// ���ꂼ��NULL�̂Ƃ�
		if (m_apScene[nCntScene] != NULL)
		{
			// �X�V����
			m_apScene[nCntScene]->Update();
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	TYPE type;

	// �D�揇�ʂ����TYPE����`��
	for (int nCntType = 0; nCntType < TYPE_MAX; nCntType++)
	{
		for (int nCntScene = 0; nCntScene < MAX_OBJECT; nCntScene++)
		{
			// �g���Ă�����
			if (m_apScene[nCntScene] != NULL)
			{
				// ���̔ԍ��̃^�C�v����
				type = m_apScene[nCntScene]->GetType();

				// �^�C�v����v������
				if (type == nCntType)
				{
					// �`�揈��
					m_apScene[nCntScene]->Draw();
				}
			}
		}
	}
}

//=============================================================================
// �S�Ẵ����[�X
//=============================================================================
void CScene::ReleaseAll(void)
{
		for (int nCntScene = 0; nCntScene < MAX_OBJECT; nCntScene++)
		{
			// ���ꂼ��NULL�̂Ƃ�
			if (m_apScene[nCntScene] != NULL)
			{
				TYPE type = m_apScene[nCntScene]->GetType();

				if (type != TYPE_FADE)
				{
					// �I������
					m_apScene[nCntScene]->Uninit();
				}
			}
		}

		for (int nCntScene = 0; nCntScene < MAX_OBJECT; nCntScene++)
		{
			// ���ꂼ��NULL�̂Ƃ�
			if (m_apScene[nCntScene] != NULL)
			{
				TYPE type = m_apScene[nCntScene]->GetType();

				if (type != TYPE_FADE)
				{
					// �������J��
		//			delete[] * m_apScene;
					m_apScene[nCntScene] = NULL;
				}
			}
		}

	// �G�l�~�[�̑��������Z�b�g
	m_nNumEnemy = 0;
}

//=============================================================================
// �V�[������Ԃ�
//=============================================================================
CScene * CScene::GetScene(int nCount)
{
	return m_apScene[nCount];
}

//=============================================================================
// �P�������[�X
//=============================================================================
void CScene::Release()
{
	if (m_apScene[m_nID] != NULL)
	{
		TYPE type;
		int nID = m_nID;

		// ���̔ԍ��̃^�C�v����
		type = m_apScene[m_nID]->GetType();

		// ���݂̔ԍ��̃��������J��
		delete m_apScene[nID];
		m_apScene[nID] = NULL;

		// ���������Z
		m_nNumAll--;

		// �G�l�~�[�������猸�Z
		if (type == TYPE_ENEMY)
		{
			m_nNumEnemy--;
		}
	}
}

//=============================================================================
// �G�l�~�[�̃J�E���g
//=============================================================================
void CScene::CountEnemy()
{
	m_nNumEnemy++;
}

//=============================================================================
// �^�C�v�ݒ�
//=============================================================================
void CScene::SetType(TYPE type)
{
	m_type = type;
}

//=============================================================================
// �^�C�v���
//=============================================================================
CScene::TYPE CScene::GetType(void)
{
	return m_type;
}

//=============================================================================
// �G�l�~�[���̏��
//=============================================================================
int CScene::GetEnemyNum(void)
{
	return m_nNumEnemy;
}