//=====================================================
//
// �t�F�[�h�N���X [fade.cpp]
// Author:�����D�l
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "fade.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include "scene.h"

//=====================================================
// static����������
//=====================================================

//=====================================================
// �R���X�g���N�^
//=====================================================
CFade::CFade()
{
	m_ColorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_fade = FADE_NONE;
	m_modeNext = CManager::MODE_TITLE;
	m_pPolygon = NULL;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CFade::~CFade()
{

}

//=====================================================
// create
//=====================================================
CFade * CFade::Create(void)
{
	// ����������
	CFade *pFade = new CFade;

	//���������m�ۂł��Ă�����
	if (pFade != NULL)
	{
		//�����������Ăяo��
		pFade->Init();
	}

	return pFade;
}

//=====================================================
// ����������
//=====================================================
HRESULT CFade::Init(void)
{
	m_fade = FADE_OUT;

	if (m_pPolygon == NULL)
	{
		//�|���S���N���X�𐶐�
		m_pPolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
			D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CScene::TYPE_FADE);
		m_pPolygon->SetType(CScene::TYPE_FADE);
	}

	//�F��ݒ�
	m_pPolygon->SetColor(m_ColorFade);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CFade::Uninit(void)
{
	if (m_pPolygon != NULL)
	{
		//�|���S���N���X�̏I�������Ăяo��
		m_pPolygon->Uninit();

		//�������̃N���A
		m_pPolygon = NULL;
	}
}

//=====================================================
// �X�V����
//=====================================================
void CFade::Update(void)
{
	if (m_pPolygon != NULL)
	{
		if (m_fade != FADE_NONE)
		{
			// �t�F�[�h������
			if (m_fade == FADE_IN)
			{
				// �t�F�[�h�C������
				m_ColorFade.a -= FADE_RATE;		// a�l�����Z���Č��̉�ʂ𕂂��オ�点��
				if (m_ColorFade.a <= 0.0f)
				{
					// �t�F�[�h�����I��
					m_ColorFade.a = 0.0f;
					m_fade = FADE_NONE;
				}
			}
			else if (m_fade == FADE_OUT)
			{
				// �t�F�[�h�A�E�g����
				m_ColorFade.a += FADE_RATE;		// a�l�����Z���Č��̉�ʂ������Ă���
				if (m_ColorFade.a >= 1.0f)
				{
					// �t�F�[�h�C�������ɐ؂�ւ�
					m_ColorFade.a = 1.0f;
					m_fade = FADE_IN;

					// ���[�h��ݒ�
					CManager::SetMode(m_modeNext);
				}
			}
			//�����x�̐ݒ�
			m_pPolygon->SetColor(m_ColorFade);
		}
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CFade::Draw(void)
{
	if (m_pPolygon != NULL)
	{
		//�|���S���N���X�̕`�揈���Ăяo��
		m_pPolygon->Draw();
	}
}

//=====================================================
// �t�F�[�h�̏�Ԑݒ菈��
//=====================================================
void CFade::SetFade(CManager::MODE modeNext)
{
	m_fade = FADE_OUT;
	m_modeNext = modeNext;
	m_ColorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//=====================================================
// �t�F�[�h��Ԃ̏��
//=====================================================
CFade::FADE CFade::Get(void)
{
	return m_fade;
}
