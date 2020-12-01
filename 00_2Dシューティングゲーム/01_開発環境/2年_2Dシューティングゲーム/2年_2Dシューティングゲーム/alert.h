#ifndef _ALERT_H_
#define _ALERT_H_
//=====================================================
//
// �x��|���S���N���X�w�b�_�[ [alert.h]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "polygon.h"

//=====================================================
// �}�N����`
//=====================================================
#define ALERT_SIZE_X	(580.0f)		// �A���[�g�̃T�C�Y
#define ALERT_SIZE_Y	(300.0f)		// �A���[�g�̃T�C�Y

//=====================================================
// �O���錾
//=====================================================
class CScene;
class CWarning;

//=====================================================
// �N���X�w�b�_�[
//=====================================================
class CAlert : public CPolygon
{
public:
	CAlert();										// �R���X�g���N�^
	~CAlert();										// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type);					// ����������
	void Uninit(void);															// �I������
	void Update(void);															// �X�V����
	void Draw(void);															// �`�揈��

	static CAlert *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type);		// �|���S������

	void FlashPolygon(void);													// �|���S���̓_��
	void CreateAlertLogo(void);													// �A���[�g���S�̐���
	void InitColor(void);														// �F�̏�����
	bool GetAlertFlag(void);													// �A���[�g�̃t���O���

private:
	int m_nSubNumber;			// �J���[���Z
	int m_nSubNum;				// �J���[�̌��Z��
	int m_nAlertFlame;			// �_�ł̃t���[��
	bool m_bAlertFlag;			// �_�ŏI���̃t���O
	CWarning *m_pWarning;		// �A���[�g���S�̃|�C���^
};

#endif