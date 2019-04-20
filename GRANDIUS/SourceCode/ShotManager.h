
//=============================================================================
//	@file	ShotManager.h
//	@brief	�V���b�g�}�l�[�W���[
//	@autor	���m ���
//	@date	2018/12/12
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�v���v���Z�b�T
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "Common.h"
#include <list>

//-----------------------------------------------------------------------------
//	@brief	�O���錾
//-----------------------------------------------------------------------------
class Shot;
class SoundEffect;

//-----------------------------------------------------------------------------
//	@brief	�V���b�g�}�l�[�W���[
//-----------------------------------------------------------------------------
class ShotManager final
{
public:

//==================== �񋓑� =====================//

	//	�V���b�g�̎��
	enum SHOT_KIND
	{
		PLAYER_SHOT,
		ENEMY_SHOT,
	};

//===================== �֐� ======================//

	//	�R���X�g���N�^ / �f�X�g���N�^
	ShotManager();
	~ShotManager();

	//	�쐬����
	void Create();

	//	�������
	void Release();

	//	�X�V����
	void Update();

	//	�`�揈��
	void Draw();

	//	���X�g�ɓo�^
	void RegisterOnList(const SHOT_KIND _shotKind, const VECTOR _startPos, const VECTOR _startDir, const float _speed, SoundEffect& _soundEffect);

	//	���X�g�ɓo�^
	void RegisterOnList(const SHOT_KIND _shotKind, const VECTOR _startPos, const VECTOR _startDir, const float _speed);

	//	���X�g����폜
	void RemoveFromList(const SHOT_KIND _shotKind, const Shot* _shotPtr);

//==================== getter =====================//

	//	�g�p���X�g�̃T�C�Y�� getter
	const int GetListSize(const SHOT_KIND _shotKind) const;

	//	�V���b�g�ւ̃|�C���^�� getter
	Shot* GetShotPtr(const SHOT_KIND _shotKind, const int _num);

private:

//================== ���������֐� ==================//

	//	�|�C���^�̎擾
	Shot* _GetShotPtr(std::list<Shot*>& _useList, const int _num);
	
	//	���X�g�̓o�^
	void _RegisterOnList(std::list<Shot*>& _useList, std::list<Shot*>& _unusedList, const VECTOR _startPos, const VECTOR _startDir, const float _speed, SoundEffect& _soundEffect);

	//	���X�g�̓o�^
	void _RegisterOnList(std::list<Shot*>& _useList, std::list<Shot*>& _unusedList, const VECTOR _startPos, const VECTOR _startDir, const float _speed);

	//	���X�g�̍X�V
	void _UpdateList(const SHOT_KIND _shotKind);
	void _UpdateList(std::list<Shot*>& _useList);

	//	���X�g�̕`��
	void _DrawList(const SHOT_KIND _shotKind);
	void _DrawList(std::list<Shot*>& _useList);

	//	���X�g����폜
	void _RemoveFromList(const SHOT_KIND _shotKind);
	void _RemoveFromList(std::list<Shot*>& _useList, std::list<Shot*>& _unusedList);
	void _RemoveFromList(std::list<Shot*>& _useList, std::list<Shot*>& _unusedList, const Shot* _shotPtr);

	//	�ŏI�I�ȉ������
	void _FinalRelease();

//=================== �����o�ϐ� ===================//

	Shot*						m_pPlayerShot[CommonConstant::MAX_SHOT_NUM];	//	�V���b�g
	Shot*						m_pEnemyShot[CommonConstant::MAX_SHOT_NUM];		//	�V���b�g
	std::list<Shot*>			m_usePlayerShotList;							//	�v���C���[�p�̎g�p�V���b�g���X�g
	std::list<Shot*>			m_useEnemyShotList;								//	�G�l�~�[�p�̎g�p�V���b�g���X�g
	std::list<Shot*>			m_unusedPlayerShotList;							//	���g�p�V���b�g���X�g
	std::list<Shot*>			m_unusedEnemyShotList;							//	���g�p�V���b�g���X�g
	int							m_sourceEnemyShotModelHandle;					//	��{�̃G�l�~�[�e�̃��f���n���h��
	int							m_sourcePlayerShotModelHandle;					//	��{�̃v���C���[�e�̃��f���n���h��

//===================== �ÓI�萔 ===================//

	static const float MAX_X_POS;		//	X���W�̍ő�
	static const float MIN_X_POS;		//	X���W�̍ŏ�
	static const float MAX_Y_POS;		//	Y���W�̍ő�
	static const float MIN_Y_POS;		//	Y���W�̍ŏ�

};