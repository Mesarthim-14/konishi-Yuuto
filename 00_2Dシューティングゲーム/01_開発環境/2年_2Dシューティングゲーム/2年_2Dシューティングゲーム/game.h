#ifndef _GAME_H_
#define _GAME_H_
//=============================================================================
//
// �^�C�g���Q�[���w�b�_�[ [title.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene.h"

//=============================================================================
// �O���錾
//=============================================================================
class CPlayer;
class CEnemy;
class CLight;
class CLaser;
class CScore;
class CBoss;
class CRemain;
class CAlert;
class CIcon;
class CMessage;
class CTime;

//=============================================================================
// �Q�[���N���X
//=============================================================================
class CGame
{
public:
	//=====================================================
	// �C���N���[�h
	//=====================================================
	typedef enum
	{
		GAMESTATE_NONE = 0,			// �������Ă��Ȃ����
		GAMESTATE_NORMAL,			// �ʏ���
		GAMESTATE_CLEAR,			// �N���A���
		GAMESTATE_END,				// �Q�[���I����ԁi��ʑJ�ڊJ�n�҂���ԁj
		GAMESTATE_MAX
	}GAMESTATE;

	typedef enum
	{
		GAME_PHASE_NONE = 0,		// �t�F�[�Y�̗�
		GAME_PHASE_FIRST,			// ���t�F�[�Y
		GAME_PHASE_MESSAGE,			// ���Ԃ̃��b�Z�[�W
		GAME_PHASE_SECOND,			// ���t�F�[�Y
		GAME_PHASE_THIRD,			// ��O�t�F�[�Y
		GAME_PHASE_FOUR,			// ��l�t�F�[�Y
		GAME_PHASE_BOSS,			// �{�X�t�F�[�Y
		GAME_PHASE_MAX
	}GAME_PHASE;

	CGame();		// �R���X�g���N�^
	~CGame();		// �f�X�g���N�^

	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetGame(void);

	static CScore *GetScore(void);			// �X�R�A�̏��
	static CBoss *GetBoss(void);			// �{�X�̏��
	static CRemain *GetRemain(void);		// �c�@�̏��
	static CPlayer *GetPlayer(void);		// �v���C���[�̏��
private:
	static CScore *m_pScore;				// �X�R�A�̃|�C���^
	static CBoss *m_pBoss;					// �{�X�̃|�C���^
	static CRemain *m_pRemain;				// �c�@�̃|�C���^
	static CAlert *m_pAlert;				// �x���A���[�g�̃|�C���^
	static CPlayer *m_pPlayer;				// �v���C���[�̃|�C���^
	static CIcon *m_pIcon;					// �v���C���[�̃A�C�R��
	static CMessage *m_pMessage;			// ���b�Z�[�W�̃|�C���^
	static CTime *m_pTime;					// �^�C���̃|�C���^
	static int m_nCntEnemy;					// �G�l�~�[�̐�
	bool m_bCurrentFlag;					// �J�E���g�̃t���O
	int m_nCntFlame;						// �t���[���̃J�E���g
	int m_nCntEnemyPop;						// �G�l�~�[�̏o���J�E���g
	int m_nCntThroughFrame;					// �G�l�~�[�̏o��J�E���g
	int m_nCntThroughEnemy;					// �G�l�~�[�̏o�����J�E���g
	int m_nCntFollow;						// �Ǐ]�̓G�̃J�E���g
	int m_nIconSoundFlame;					// �A�C�R�����̃t���[��
	bool m_bThroughFlag;					// �J�E���g�̃t���O
	bool m_bThroughSwitch;					// ����ւ��̃t���O
	GAMESTATE m_gameState;					// �Q�[���̏��
	GAME_PHASE m_Phase;						// �t�F�[�Y
	int m_nCounterGameState;				// �Q�[���̏�ԃJ�E���^�[
	int m_nGameCounter;						// �G�̏o���J�E���^�[
	bool m_bFirstPhaseEnd;					// ���t�F�[�Y�I��
	bool m_bSecondPhaseEnd;					// ���t�F�C�Y�I��
	bool m_bThirdPhaseEnd;					// ��O�t�F�[�Y�̏I��
	bool m_bBossFlag;						// �{�X�̃t���O
};
#endif