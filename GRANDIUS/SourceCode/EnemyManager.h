
//=============================================================================
//	@file	EnemyManager.h
//	@brief	�G�l�~�[�}�l�[�W���[
//	@autor	���m ���
//	@date	2018/11/16
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
class EnemyBase;
class BossManager;
class PlayerManager;
class ShotManager;
class ItemManager;
class EnemyCounter;
class SoundEffect;
class Sound;
class Warning;

//-----------------------------------------------------------------------------
//	@brief	�G�l�~�[�Ǘ��N���X
//-----------------------------------------------------------------------------
class EnemyManager final
{
public:

//==================== �񋓑� =====================//

	//	�G�l�~�[�̎��
	enum ENEMY_KIND
	{
		NONE = -1,			//	�Ȃ�
		ENEMY_LINE = 0,		//	����
		ENEMY_FLOATING,		//	���V
		ENEMY_CURVE,		//	�Ȑ�
		ENEMY_RETURN,		//	�A��
		ENEMY_TURNING,		//	����
		ENEMY_UP_DOWN,		//	�㉺
		ENEMY_NUM			//	�ԕ�
	};

	//	�G�̑���
	enum ENEMY_FORMATION_NUM
	{
		FORMATION_NONE,	//	����Ȃ�
		FORMATION_1,	//	����P
		FORMATION_2,	//	����Q
		FORMATION_3,	//	����R
		FORMATION_4,	//	����S
		FORMATION_5,	//	����T
		FORMATION_NUM,	//	����
	};

//===================== �֐� ======================//

	//	�R���X�g���N�^ / �f�X�g���N�^
	EnemyManager();
	~EnemyManager();

	//	�쐬����
	void Create();

	//	�������
	void Release();

	//	��������
	void Initialize();

	//	�X�V����
	void Update(PlayerManager& _playerManager, ShotManager& _shotManager, BossManager& _bossManager, ItemManager& _item, Sound& _sound, SoundEffect& _soundEffect, Warning& _warning);

	//	�`�揈��
	void Draw();

	//	���X�g������
	void RemoveFromList(const EnemyBase* _enemyPtr, ItemManager& _item);

	//	������G�l�~�[���̌��Z
	void SubEnemyCount(const ENEMY_FORMATION_NUM _formationNum) { m_enemyCounter[(int)_formationNum]--; };

	//	������G�l�~�[���̌��Z
	void SubEnemyCount(const int _formationNum) { m_enemyCounter[_formationNum]--; };

//==================== getter =====================//

	//	�g�p���X�g�̃T�C�Y�� getter
	const int GetListSize() const { return (int)m_useList.size(); }

	//	�G�l�~�[�ւ̃|�C���^�� getter
	EnemyBase* GetEnemyPtr(const int _num);

	//	������̃G�l�~�[���� getter
	const int GetEnemyInFormationNum(const ENEMY_FORMATION_NUM _formationNum) const { return m_enemyCounter[(int)_formationNum]; };

	//	������̃G�l�~�[���� getter
	const int GetEnemyInFormationNum(const int _formationNum) const { return m_enemyCounter[_formationNum]; };

	//	������ɃG�l�~�[�͑��݂��邩�� getter
	const bool GetIsEnemyExistence(const ENEMY_FORMATION_NUM _formationNum) const { return (m_enemyCounter[(int)_formationNum] > 0); };

	//	������ɃG�l�~�[�͑��݂��邩�� getter
	const bool GetIsEnemyExistence(const int _formationNum) const { return (m_enemyCounter[_formationNum] > 0); };

private:

//===================== �\���� =====================//

	struct EntryBuffer
	{
		EnemyBase*	m_pBuf[CommonConstant::MAX_ENEMY_ENTRY_NUM];			//	�o�b�t�@
		bool		m_isInUse[CommonConstant::MAX_ENEMY_ENTRY_NUM];			//	�������̎g�p��
	};

//================== ���������֐� ==================//

	//	�G�l�~�[�̓o�^
	void _EnemyEntry();

	//	���X�g�̍X�V
	void _ListUpdate(PlayerManager& _playerManager, ShotManager& _shot, SoundEffect& _soundEffect);

	//	���X�g������
	void _RemoveFromList(ItemManager& _item);

	//	�G�l�~�[�p�[�g�P
	void _EnemyParts1();

	//	�G�l�~�[�p�[�g�Q
	void _EnemyParts2();

	//	�G�l�~�[�p�[�g�R
	void _EnemyParts3();

	//	�G�l�~�[�p�[�g�S
	void _EnemyParts4();

	//	�G�l�~�[�p�[�g�T
	void _EnemyParts5();

	//	�����g��œo�^
	void _FormationEntry(const ENEMY_KIND _enemyKind, const float _startTime, const float _intervalTime, const VECTOR _startPos, const int _formationNum, 
						 const bool _isUseShot, const bool _isRestriction,  const int _formation);

	//	�o�^����
	void _Registration(const ENEMY_KIND _enemyKind, const VECTOR _startPos, const float _entryTime, const bool _isUseShot, const bool _isRestriction, const int _formation);

	//	�c�����g��œo�^
	void _VerticalFormationEntry(const ENEMY_KIND _enemyKind, const float _startTime, const float _intervalTime, const float _shiftInterval, const VECTOR _startPos, 
								 const int _formationNum, const bool _isUseShot, const bool _isHavingItem, const int _formation);

	//	�c�ɓo�^����
	void _VerticalRegistration(const ENEMY_KIND _enemyKind, const VECTOR _startPos, const float _entryTime, const float _shiftInterval, const int _num,
							   const bool _isUseShot, const bool _isHavingItem, const int _formation);

	//	��̕��̓o�^
	bool _OneEnemyRegistration(const int _enemyKind, const VECTOR _startPos, const bool _isUseShot, const bool _isHavingItem, const int _formation);

	//	��̕��̓o�^���A�V���b�g�͓񕪂̈�̊m���Ŏg�p����
	bool _OneEnemyRegistrationToShotProbaility(const int _enemyKind, const VECTOR _startPos, const bool _isUseShot, const bool _isRestriction, const int _formation);

	//	�ŏI�I�ȉ������
	void _FinalRelease();

//=================== �����o�ϐ� ===================//

	int						m_sourceModelHandle[ENEMY_KIND::ENEMY_NUM];				//	��{�n���h��
	EntryBuffer				m_entryBuffer[ENEMY_KIND::ENEMY_NUM];					//	�o�^�o�b�t�@
	std::list<EnemyBase*>	m_useList;												//	�g�p�G�l�~�[���X�g
	float					m_entryTime;											//	�o���^�C�}�[
	int						m_enemyCounter[ENEMY_FORMATION_NUM::FORMATION_NUM];		//	������̃G�l�~�[��

//===================== �ÓI�萔 ===================//

	static const float	MAX_EMERGNCE_INTERVAL_TIME;	//	�o���^�C�}�[�̍ő�Ԋu
	static const float	MAX_WAIT_TIME;				//	�ҋ@���Ԃ̍ő�
	static const float	PART_INTERAL;				//	�p�[�g�̊Ԋu
	static const float	MIN_ALIVE_TIME;				//	�������Ԃ̍ŏ�
	static const float	MEDIUM_BOSS_EMERGE_TIME;	//	���{�X�̏o�����̎���
	static const float	WARNING_SE_TIME;			//	�x�����̎���
	static const float	LAST_BOSS_EMERGE_TIME;		//	�ŏI�{�X�̏o�����̎���
	static const float	MAX_FLAME;					//	�t���[���̍ő�
	static const float	RESET_FLAME;				//	�t���[���̃��Z�b�g�l
 	static const float	PRODUCTION_TIME;			//	���o�̎���
	static const float	MAX_X_POS;					//	X���W�̍ő�
	static const float	MIN_X_POS;					//	X���W�̍ŏ�
	static const float	MAX_Y_POS;					//	Y���W�̍ő�
	static const float	MIN_Y_POS;					//	Y���W�̍ŏ�
	static const float	SKIP;						//	�X�L�b�v

};