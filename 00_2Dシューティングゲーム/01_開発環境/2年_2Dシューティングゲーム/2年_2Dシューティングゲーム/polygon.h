#ifndef _POLYGON_H_
#define _POLYGON_H_
//=====================================================
//
// �|���S���N���X�w�b�_�[ [polygon.h]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "main.h"
#include "manager.h"
#include "scene.h"

//=====================================================
// �O���錾
//=====================================================
class CScene;

//=====================================================
// �N���X�w�b�_�[
//=====================================================
class CPolygon : public CScene
{
public:
	//=============================================================================
	// �\���̒�`
	//=============================================================================
	typedef struct
	{
		D3DXVECTOR3 pos;	// ���_���W
		float rhw;			// ���W
		D3DCOLOR col;		// ���_�J���[
		D3DXVECTOR2 tex;	// �e�N�X�`�����W
	}VERTEX_2D;

	CPolygon();										// �R���X�g���N�^
	virtual ~CPolygon();							// �f�X�g���N�^

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);			// ����������
	virtual void Uninit(void);													// �I������
	virtual void Update(void);													// �X�V����
	virtual void Draw(void);													// �`�揈��

	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);		// �|���S������

	void SetPos(D3DXVECTOR3 pos);												// ���W�ݒ�
	void SetColor(D3DXCOLOR color);												// �F�̐ݒ�
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void);									// �o�b�t�@���

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�̃|�C���^
	D3DXVECTOR3 m_size;						// �|���S���̃T�C�Y
	D3DXVECTOR3 m_pos;						// ���C�t�̈ʒu
	TYPE m_type;							// �^�C�v
};

#endif