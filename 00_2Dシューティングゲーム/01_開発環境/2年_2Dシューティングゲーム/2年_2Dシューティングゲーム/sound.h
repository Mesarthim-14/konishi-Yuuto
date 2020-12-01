//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �����D�l
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "xaudio2.h"		// �T�E���h�����ŕK�v

//=============================================================================
// �T�E���h�N���X
//=============================================================================
class CSound
{
public:
	//=============================================================================
	// �T�E���h�t�@�C��
	//=============================================================================
	typedef enum
	{
		SOUND_LABEL_TITLE = 0,			// �^�C�g��
		SOUND_LABEL_GAME,				// �Q�[��
		SOUND_LABEL_RESULT,				// ���U���g
		SOUND_LABEL_BUTTON,				// �{�^��
		SOUND_LABEL_SHOT,				// �{�^��
		SOUND_LABEL_EXPLOSION,			// ����
		SOUND_LABEL_BOSS_EXPLOSION,		// �{�X�̔���
		SOUND_LABEL_LASER,				// ���[�U�[
		SOUND_LABEL_BOMB,				// �{��
		SOUND_LABEL_ICON,				// �A�C�R��
		SOUND_LABEL_MESSAGE,			// ���b�Z�[�W
		SOUND_LABEL_ARERT,				// �A���[�g
		SOUND_LABEL_WARNING,			// WARNING
		SOUND_LABEL_BOSS,				// �{�X
		SOUND_LABEL_HIT,				// �{�X
		SOUND_LABEL_CHANGE,				// �{�X�̉ΉԂ̉�
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//=============================================================================
	// �p�����[�^�\���̒�`
	//=============================================================================
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDPARAM;

	CSound();		// �R���X�g���N�^
	~CSound();		// �f�X�g���N�^

	HRESULT Init(HWND hWnd);			// ����������
	void Uninit(void);					// �I������
	HRESULT Play(SOUND_LABEL label);	// �T�E���h�Đ�
	void Stop(SOUND_LABEL label);		// �T�E���h�I��
	void Stop(void);
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:
	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

	// �e���f�ނ̃p�����[�^
	SOUNDPARAM m_aParam[SOUND_LABEL_MAX] =
	{
		{ "date/SOUND/title.wav", -1 },				// �^�C�g��
		{ "date/SOUND/game.wav", -1 },				// �Q�[��
		{ "date/SOUND/result.wav", -1 },			// ���U���g
		{ "date/SOUND/button000.wav", 0 },			// �{�^��
		{ "date/SOUND/shot.wav", 0 },				// �V���b�g
		{ "date/SOUND/explosion000.wav", 0 },		// ����
		{ "date/SOUND/BossExplosion.wav", 0 },		// �{�X�̔���
		{ "date/SOUND/laser000.wav", -1 },			// ���[�U�[
		{ "date/SOUND/bomb.wav", 0 },				// �{��
		{ "date/SOUND/icon.wav", 0 },				// �A�C�R��
		{ "date/SOUND/message.wav", 0 },			// ���b�Z�[�W
		{ "date/SOUND/alert.wav", -1 },				// �A���[�g
		{ "date/SOUND/warning.wav", 0 },			// WARNING
		{ "date/SOUND/boss.wav", 0 },				// �{�X
		{ "date/SOUND/Hit.wav", 0 },				// �{�X�̃q�b�g
		{ "date/SOUND/change.wav", -1 },			// �{�X�̃q�b�g
	};
};

#endif
