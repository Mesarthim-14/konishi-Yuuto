#ifndef _NUMBER_H_
#define _NUMBER_H_
//=============================================================================
//
// �i���o�[�w�b�_�[ [number.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_NUMBER_TEXTURE (2)		// �e�N�X�`���̍ő吔

//=============================================================================
// �����_���[�N���X
//=============================================================================
class CNumber : public CScene
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

	typedef enum
	{
		NUMBER_TYPE_NONE = 0,	// �����l
		NUMBER_TYPE_SCORE,		// �X�R�A
		NUMBER_TYPE_RANKING,	// �����L���O
		NUMBER_TYPE_TIME,		// �^�C��
		NUMBER_TYPE_MAX
	}NUMBER_TYPE;

	CNumber();				// �R���X�g���N�^
	~CNumber();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);					// ����������
	void Uninit(void);															// �I������
	void Update(void);															// �X�V����
	void Draw(void);															// �`�揈��
	static HRESULT Load(void);													// �e�N�X�`�����[�h
	static void UnLoad(void);													// �e�N�X�`���A�����[�h
	static CNumber * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, 
		TYPE type, NUMBER_TYPE Ntype);											// �N���G�C�g
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);								// �e�N�X�`���̐ݒ�
	void SetNumber(int nScore);													// �i���o�[�̐ݒ�
	void NumberInit(D3DXVECTOR3 pos, D3DXVECTOR3 size);							// �i���o�[�������ݒ�
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void);									// �o�b�t�@���
	void SetNType(NUMBER_TYPE Ntype);											// �i���o�[�̃^�C�v�ݒ�

private:
	D3DXVECTOR3 m_Pos;											// ���W
	D3DXVECTOR3 m_Size;											// �T�C�Y
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							// �o�b�t�@
	D3DXVECTOR3 m_Move;											// �ړ�
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_NUMBER_TEXTURE];	// �e�N�X�`���̃|�C���^
	static LPDIRECT3DDEVICE9 m_pDevice;							// �f�o�C�X�̃|�C���^
	NUMBER_TYPE m_Ntype;										// �i���o�[�̃^�C�v
};

#endif