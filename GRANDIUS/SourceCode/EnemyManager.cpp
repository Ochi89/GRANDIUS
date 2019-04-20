
//=============================================================================
//	@file	EnemyManager.cpp
//	@brief	�G�l�~�[�}�l�[�W���[
//	@autor	���m ���
//	@date	2018/11/16
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyManager.h"
#include "EnemyBase.h"
#include "BossManager.h"
#include "CurveEnemy.h"
#include "ReturnEnemy.h"
#include "FloatingEnemy.h"
#include "LineEnemy.h"
#include "TurningEnemy.h"
#include "UpDownEnemy.h"
#include "PlayerManager.h"
#include "ShotManager.h"
#include "ItemManager.h"
#include "Key.h"
#include "HitChecker.h"
#include "SoundEffect.h"
#include "Sound.h"
#include "Warning.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const float EnemyManager::MAX_EMERGNCE_INTERVAL_TIME = 100.0f;	//	�o���^�C�}�[�̍ő�Ԋu
const float	EnemyManager::MAX_WAIT_TIME = 20.0f;				//	�ҋ@���Ԃ̍ő�
const float	EnemyManager::PART_INTERAL = 250.0f;				//	�p�[�g�̊Ԋu
const float	EnemyManager::MIN_ALIVE_TIME = 80.0f;				//	�������Ԃ̍ŏ�
const float	EnemyManager::MEDIUM_BOSS_EMERGE_TIME = 1700.0f;	//	���{�X�̏o�����̎���
const float	EnemyManager::LAST_BOSS_EMERGE_TIME = 10500.0f;		//	�ŏI�{�X�̏o�����̎���
const float	EnemyManager::WARNING_SE_TIME = 10430.0f;			//	�x�����̎���
const float	EnemyManager::PRODUCTION_TIME = 5100.0f;			//	���o�̎���
const float	EnemyManager::MAX_FLAME = 14625.0f;					//	�t���[���̍ő�
const float	EnemyManager::RESET_FLAME = 10825.0f;				//	�t���[���̃��Z�b�g�l
const float EnemyManager::MAX_X_POS = 130.0f;					//	X���W�̍ő�
const float EnemyManager::MIN_X_POS = -130.0f;					//	X���W�̍ŏ�
const float EnemyManager::MAX_Y_POS = 120.0f;					//	Y���W�̍ő�
const float EnemyManager::MIN_Y_POS = 0.0f;						//	Y���W�̍ŏ�
const float	EnemyManager::SKIP = 1.0f;						//	�X�L�b�v

//#define TEST_ENEMY_ENTRY 0

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
EnemyManager::EnemyManager()
{
	m_entryTime = 0.0f;

	//	�������̊m�ۂ�����ƁA�g�p�t���O�̏�����
	for (int i = 0; i < ENEMY_KIND::ENEMY_NUM; i++)
	{
		for (int j = 0; j < CommonConstant::MAX_ENEMY_ENTRY_NUM; j++)
		{
			m_entryBuffer[i].m_pBuf[j] = NULL;
			m_entryBuffer[i].m_isInUse[j] = false;
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
EnemyManager::~EnemyManager()
{
	//	�ŏI�I�ȉ������
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬����
//-----------------------------------------------------------------------------
void EnemyManager::Create()
{
	//	��{�̃��f���n���h���̓ǂݍ���
	m_sourceModelHandle[ENEMY_KIND::ENEMY_LINE] = MV1LoadModel("Data/Model/Enemy/LineEnemy.mqo");
	m_sourceModelHandle[ENEMY_KIND::ENEMY_FLOATING] = MV1LoadModel("Data/Model/Enemy/FloatingEnemy.mqo");
	m_sourceModelHandle[ENEMY_KIND::ENEMY_CURVE] = MV1LoadModel("Data/Model/Enemy/CurveEnemy.mqo");
	m_sourceModelHandle[ENEMY_KIND::ENEMY_RETURN] = MV1LoadModel("Data/Model/Enemy/ReturnEnemy.mqo");
	m_sourceModelHandle[ENEMY_KIND::ENEMY_TURNING] = MV1LoadModel("Data/Model/Enemy/TurningEnemy.mqo");
	m_sourceModelHandle[ENEMY_KIND::ENEMY_UP_DOWN] = MV1LoadModel("Data/Model/Enemy/UpDownEnemy.mqo");

	CommonDebug::Assert((m_sourceModelHandle[ENEMY_KIND::ENEMY_LINE] <= -1), " [ EnemyManager.cpp ] : error : model loading failed.");
	CommonDebug::Assert((m_sourceModelHandle[ENEMY_KIND::ENEMY_FLOATING] <= -1), " [ EnemyManager.cpp ] : error : model loading failed.");
	CommonDebug::Assert((m_sourceModelHandle[ENEMY_KIND::ENEMY_CURVE] <= -1), " [ EnemyManager.cpp ] : error : model loading failed.");
	CommonDebug::Assert((m_sourceModelHandle[ENEMY_KIND::ENEMY_RETURN] <= -1), " [ EnemyManager.cpp ] : error : model loading failed.");
	CommonDebug::Assert((m_sourceModelHandle[ENEMY_KIND::ENEMY_TURNING] <= -1), " [ EnemyManager.cpp ] : error : model loading failed.");
	CommonDebug::Assert((m_sourceModelHandle[ENEMY_KIND::ENEMY_UP_DOWN] <= -1), " [ EnemyManager.cpp ] : error : model loading failed.");

	//	�������̊m�ۂ�����
	for (int i = 0; i < CommonConstant::MAX_ENEMY_ENTRY_NUM; i++)
	{
		m_entryBuffer[ENEMY_KIND::ENEMY_LINE].m_pBuf[i] = new LineEnemy(m_sourceModelHandle[ENEMY_KIND::ENEMY_LINE]);
		m_entryBuffer[ENEMY_KIND::ENEMY_FLOATING].m_pBuf[i] = new FloatingEnemy(m_sourceModelHandle[ENEMY_KIND::ENEMY_FLOATING]);
		m_entryBuffer[ENEMY_KIND::ENEMY_CURVE].m_pBuf[i] = new CurveEnemy(m_sourceModelHandle[ENEMY_KIND::ENEMY_CURVE]);
		m_entryBuffer[ENEMY_KIND::ENEMY_RETURN].m_pBuf[i] = new ReturnEnemy(m_sourceModelHandle[ENEMY_KIND::ENEMY_RETURN]);
		m_entryBuffer[ENEMY_KIND::ENEMY_TURNING].m_pBuf[i] = new TurningEnemy(m_sourceModelHandle[ENEMY_KIND::ENEMY_TURNING]);
		m_entryBuffer[ENEMY_KIND::ENEMY_UP_DOWN].m_pBuf[i] = new UpDownEnemy(m_sourceModelHandle[ENEMY_KIND::ENEMY_UP_DOWN]);
	}

	//	���������A�G�l�~�[�X�̔\�͂̍쐬
	for (int i = 0; i < ENEMY_KIND::ENEMY_NUM; i++)
	{
		for (int j = 0; j < CommonConstant::MAX_ENEMY_ENTRY_NUM; j++)
		{
			m_entryBuffer[i].m_pBuf[j]->Initialize();
			m_entryBuffer[i].m_pBuf[j]->Create();
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�������
//-----------------------------------------------------------------------------
void EnemyManager::Release()
{
	//	���X�g���ɓo�^����Ă���Ƃ��A�N���A����
	if (!m_useList.empty()) { m_useList.clear(); }

	for (int i = 0; i < ENEMY_KIND::ENEMY_NUM; i++)
	{
		//	���f���̃A�����[�h
		MV1DeleteModel(m_sourceModelHandle[i]);

		for (int j = 0; j < CommonConstant::MAX_ENEMY_ENTRY_NUM; j++)
		{
			//	�������̉��
			CommonSafe::Delete(m_entryBuffer[i].m_pBuf[j]);
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	��������
//-----------------------------------------------------------------------------
void EnemyManager::Initialize()
{
#ifdef TEST_ENEMY_ENTRY
	//	�G�l�~�[�o���^�C���̏�����
	m_entryTime = 0.0f;
#else
	//	�G�l�~�[�o���^�C���̏�����
	m_entryTime = 0.0f;
#endif

	//	�G�l�~�[�̌v���J�E���g�̏�����
	for (int i = 0; i < ENEMY_FORMATION_NUM::FORMATION_NUM; i++)
	{
		m_enemyCounter[i] = 0;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void EnemyManager::Update(PlayerManager& _playerManager, ShotManager& _shotManager, BossManager& _bossManager, ItemManager& _item, Sound& _sound, SoundEffect& _soundEffect, Warning& _warning)
{
	//	���{�X�̓o�^
	const bool isEntryMediumBoss = m_entryTime == MEDIUM_BOSS_EMERGE_TIME;
	if (isEntryMediumBoss) { _bossManager.SetIsMediumBossEmerge(true); }

	//	SE
	const bool isWarningSE = m_entryTime == WARNING_SE_TIME;
	if (isWarningSE) { _soundEffect.OnPlaySound(_soundEffect.ONE_SE_KIND::ONE_SE_WARNING); _sound.SetIsChageSound(true); _warning.SetIsWarningStart(true); }

	//	�ŏI�{�X�̓o�^
	const bool isEntryLastBoss = m_entryTime == LAST_BOSS_EMERGE_TIME;
	if (isEntryLastBoss) { _bossManager.SetIsLastBossEmerge(true); }

	///		�Q�[�����Ԓ����̂��߁A�폜
	////	���o�J�n
	//const bool isProduction = m_entryTime == PRODUCTION_TIME;
	//if (isProduction) { PRODUCTION->SetIsSceneProduction(true); }

	//	�K�E�Z�ȊO�̂Ƃ���
	//	�N���A���Ă��Ȃ��Ƃ��̂�
	//	�X�V����
	const bool isNotClearProduction = !PRODUCTION->GetIsClearProduction();
	const bool isNotSpecialProduction = !PRODUCTION->GetIsSpecialProduction();
	const bool isNotClear = !_playerManager.GetIsClear();
	const bool isActive = isNotSpecialProduction && isNotClearProduction && isNotClear;
	if (isActive)
	{
		//	���X�g�ɓo�^
		_EnemyEntry();
	}

	//	���X�g�̍X�V
	_ListUpdate(_playerManager, _shotManager, _soundEffect);

	//	���X�g����폜
	_RemoveFromList(_item);
}

//-----------------------------------------------------------------------------
//	@brief	�`�揈��
//-----------------------------------------------------------------------------
void EnemyManager::Draw()
{
	//	�g�p���X�g�ɓo�^����Ă���Ƃ�
	const bool isAlreadyEntry = !m_useList.empty();
	if (isAlreadyEntry)
	{
		//	���X�g�̉񐔕���
		std::list<EnemyBase*>::iterator ite;
		for (ite = m_useList.begin(); ite != m_useList.end(); ite++)
		{
			//	�`��
			(*ite)->Draw();
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	���X�g����폜
//-----------------------------------------------------------------------------
void EnemyManager::RemoveFromList(const EnemyBase* _enemyPtr, ItemManager& _item)
{
	//	�g�p���X�g�ɓo�^����Ă���Ƃ�
	const bool isAlreadyEntry = !m_useList.empty();
	if (isAlreadyEntry)
	{
		//	���X�g�̉񐔕���
		std::list<EnemyBase*>::iterator ite;
		for (ite = m_useList.begin(); ite != m_useList.end(); ite++)
		{
			//	_enemyPtr �ƈ�v�����A
			//	�G�l�~�[�����X�g����폜����
			const bool isSame = _enemyPtr == (*ite);
			if (isSame)
			{
				//	�G�l�~�[�̎��S���ɃA�C�e���������Ă���Ȃ�A
				//	�A�C�e�����X�g�ɒǉ�����
				const bool isHavingItems = (*ite)->GetIsHavingItems();
				if (isHavingItems) { _item.RegisterOnList((*ite)->GetPos()); }

				//	�G�l�~�[���g�p�\�ɂ���
				int enemyID = (*ite)->GetEntryID();
				int enemyKind = (*ite)->GetEntryKind();
				m_entryBuffer[enemyKind].m_isInUse[enemyID] = false;

				//	����������͏����Ȃ��̂�
				//	������������
				(*ite)->Initialize();

				//	�g�p���X�g����폜
				m_useList.remove(*ite);

				break;
			}
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�G�l�~�[�ւ̃|�C���^�� getter
//-----------------------------------------------------------------------------
EnemyBase* EnemyManager::GetEnemyPtr(const int _num)
{
	int counter = 0;

	//	�g�p���X�g�ɓo�^����Ă���Ƃ�
	const bool isAlreadyEntry = !m_useList.empty();
	if (isAlreadyEntry)
	{
		//	���X�g�̉񐔕���
		std::list<EnemyBase*>::iterator ite;
		for (ite = m_useList.begin(); ite != m_useList.end(); ite++)
		{
			//	_num �ƈ�v�����|�C���^��Ԃ�
			const bool isSame = counter == _num;
			if (isSame) { return (*ite); }
			counter++;
		}
	}

	return NULL;
}

//-----------------------------------------------------------------------------
//	@brief	�G�l�~�[�̓o�^
//-----------------------------------------------------------------------------
void EnemyManager::_EnemyEntry()
{
#ifdef TEST_ENEMY_ENTRY

#else

	//	�G�l�~�[�p�[�g�P
	_EnemyParts1();

	//	�G�l�~�[�p�[�g�Q
	_EnemyParts2();

	//	�G�l�~�[�p�[�g�R
	_EnemyParts3();

	//	�G�l�~�[�p�[�g�S
	_EnemyParts4();

	//	�G�l�~�[�p�[�g�T
	_EnemyParts5();

#endif // TEST_ENEMY_ENTRY

	m_entryTime++;

	//	�G�l�~�[�o�����Ԃ̍ő�Ȃ̂ŁA
	//	�{�X���̃U�R�p�[�g�̌J��Ԃ�
	const bool isMaxTime = m_entryTime >= MAX_FLAME;
	if (isMaxTime) { m_entryTime = RESET_FLAME; }
}

//-----------------------------------------------------------------------------
//	@brief	���X�g�̍X�V
//-----------------------------------------------------------------------------
void EnemyManager::_ListUpdate(PlayerManager& _playerManager, ShotManager& _shot, SoundEffect& _soundEffect)
{
	//	�g�p���X�g�ɓo�^����Ă���Ƃ�
	const bool isAlreadyEntry = !m_useList.empty();
	if (isAlreadyEntry)
	{
		//	���X�g�̉񐔕���
		std::list<EnemyBase*>::iterator ite;
		for (ite = m_useList.begin(); ite != m_useList.end(); ite++)
		{
			//	�������Ԃ̉��Z
			(*ite)->AddAliveTime();

			//	�X�V
			(*ite)->Update(_playerManager, _shot, _soundEffect);
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	���X�g����폜
//-----------------------------------------------------------------------------
void EnemyManager::_RemoveFromList(ItemManager& _item)
{
	//	�g�p���X�g�ɓo�^����Ă���Ƃ�
	const bool isAlreadyEntry = !m_useList.empty();
	if (isAlreadyEntry)
	{
		//	���X�g�̉񐔕���
		std::list<EnemyBase*>::iterator ite;
		for (ite = m_useList.begin(); ite != m_useList.end(); ite++)
		{
			//	�������Ă����ɏ��ł��Ȃ��悤�ɁA
			//	�ŏ��̐������Ԃ𒴂�����A�폜����
			const bool isActiveMinAlive = (*ite)->GetAliveTime() >= MIN_ALIVE_TIME;
			if (isActiveMinAlive)
			{
				//	��ʊO�̂Ƃ��A�폜
				const bool isOverTop = (*ite)->GetPos().y >= MAX_Y_POS;
				const bool isOverButtom = (*ite)->GetPos().y <= MIN_Y_POS;
				const bool isOverRight = (*ite)->GetPos().x >= MAX_X_POS;
				const bool isOverLeft = (*ite)->GetPos().x <= MIN_X_POS;
				const bool isOverPos = isOverTop || isOverButtom || isOverRight || isOverLeft;
				if (isOverPos)
				{
					//	�G�l�~�[���g�p�\�ɂ���
					const int enemyID = (*ite)->GetEntryID();
					const int enemyKind = (*ite)->GetEntryKind();
					m_entryBuffer[enemyKind].m_isInUse[enemyID] = false;

					//	���񂩂�폜
					const int formationID = (*ite)->GetFormationID();
					SubEnemyCount(formationID);

					//	����������͏����Ȃ��̂�
					//	������������
					(*ite)->Initialize();

					//	�g�p���X�g����폜
					m_useList.remove(*ite);

					break;
				}

				//	���炩�Ƀq�b�g�����̂ŁA�폜
				const bool isDeleateActive = (*ite)->GetIsDeleate();
				if (isDeleateActive)
				{
					//	�G�l�~�[���g�p�\�ɂ���
					int enemyID = (*ite)->GetEntryID();
					int enemyKind = (*ite)->GetEntryKind();
					m_entryBuffer[enemyKind].m_isInUse[enemyID] = false;

					//	����������͏����Ȃ��̂�
					//	������������
					(*ite)->Initialize();

					//	�g�p���X�g����폜
					m_useList.remove(*ite);

					break;
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�G�l�~�[�p�[�g�P
//-----------------------------------------------------------------------------
void EnemyManager::_EnemyParts1()
{
	//	�O���U�R�p�[�g�P
	_FormationEntry(ENEMY_KIND::ENEMY_CURVE, 50.0f, 10.0f, VGet(120.0f, 90.0f, 0.0f), 10, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_1);
	_FormationEntry(ENEMY_KIND::ENEMY_CURVE, 200.0f, 10.0f, VGet(120.0f, 20.0f, 0.0f), 10, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_2);
	_FormationEntry(ENEMY_KIND::ENEMY_CURVE, 350.0f, 10.0f, VGet(120.0f, 90.0f, 0.0f), 10, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_3);
	_FormationEntry(ENEMY_KIND::ENEMY_CURVE, 500.0f, 10.0f, VGet(120.0f, 20.0f, 0.0f), 10, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_4);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_RETURN, 700.0f, 20.0f, 25.0f, VGet(-150.0f, 85.0f, 50.0f), 4, false, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	_FormationEntry(ENEMY_KIND::ENEMY_CURVE, 850.0f, 10.0f, VGet(120.0f, 90.0f, 0.0f), 10, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_5);
	_FormationEntry(ENEMY_KIND::ENEMY_CURVE, 850.0f, 10.0f, VGet(120.0f, 20.0f, 0.0f), 10, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_1);
	_FormationEntry(ENEMY_KIND::ENEMY_CURVE, 1050.0f, 10.0f, VGet(120.0f, 60.0f, 0.0f), 10, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_2);
	_FormationEntry(ENEMY_KIND::ENEMY_CURVE, 1050.0f, 10.0f, VGet(120.0f, 40.0f, 0.0f), 10, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_3);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_RETURN, 1300.0f, 0.0f, 15.0f, VGet(-150.0f, 85.0f, 50.0f), 3, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_RETURN, 1300.0f, 0.0f, 15.0f, VGet(-150.0f, 35.0f, 50.0f), 2, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_RETURN, 1400.0f, 0.0f, 15.0f, VGet(-150.0f, 85.0f, 50.0f), 2, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_RETURN, 1400.0f, 0.0f, 15.0f, VGet(-150.0f, 45.0f, 50.0f), 3, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_RETURN, 1450.0f, 0.0f, 15.0f, VGet(120.0f, 85.0f, 50.0f), 2, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_RETURN, 1450.0f, 0.0f, 15.0f, VGet(120.0f, 35.0f, 50.0f), 2, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_RETURN, 1500.0f, 0.0f, 15.0f, VGet(120.0f, 70.0f, 50.0f), 3, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_RETURN, 1600.0f, 0.0f, 15.0f, VGet(-150.0f, 85.0f, 50.0f), 5, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);

}

//-----------------------------------------------------------------------------
//	@brief	�G�l�~�[�p�[�g�Q
//-----------------------------------------------------------------------------
void EnemyManager::_EnemyParts2()
{
	//	���{�X�p�[�g
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_FLOATING, 1850.0f, 0.0f, 10.0f, VGet(120.0f, 85.0f, 0.0f), 3, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_FLOATING, 1850.0f, 0.0f, 10.0f, VGet(120.0f, 30.0f, 0.0f), 3, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_FLOATING, 1950.0f, 0.0f, 10.0f, VGet(120.0f, 85.0f, 0.0f), 5, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_FLOATING, 2050.0f, 0.0f, 10.0f, VGet(120.0f, 85.0f, 0.0f), 3, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_FLOATING, 2050.0f, 0.0f, 10.0f, VGet(120.0f, 30.0f, 0.0f), 3, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_FLOATING, 2150.0f, 0.0f, 10.0f, VGet(120.0f, 85.0f, 0.0f), 3, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_FLOATING, 2150.0f, 0.0f, 10.0f, VGet(120.0f, 30.0f, 0.0f), 3, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_FLOATING, 2250.0f, 0.0f, 10.0f, VGet(120.0f, 85.0f, 0.0f), 3, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_FLOATING, 2250.0f, 0.0f, 10.0f, VGet(120.0f, 30.0f, 0.0f), 3, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_FLOATING, 2350.0f, 0.0f, 10.0f, VGet(120.0f, 85.0f, 0.0f), 5, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_FLOATING, 2450.0f, 0.0f, 10.0f, VGet(120.0f, 85.0f, 0.0f), 3, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_FLOATING, 2450.0f, 0.0f, 10.0f, VGet(120.0f, 30.0f, 0.0f), 3, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_FLOATING, 2550.0f, 0.0f, 10.0f, VGet(120.0f, 85.0f, 0.0f), 5, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_FLOATING, 2650.0f, 0.0f, 10.0f, VGet(120.0f, 85.0f, 0.0f), 5, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_FLOATING, 2750.0f, 0.0f, 10.0f, VGet(120.0f, 85.0f, 0.0f), 5, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_FLOATING, 2850.0f, 0.0f, 10.0f, VGet(120.0f, 85.0f, 0.0f), 3, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_FLOATING, 2850.0f, 0.0f, 10.0f, VGet(120.0f, 30.0f, 0.0f), 3, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
}

//-----------------------------------------------------------------------------
//	@brief	�G�l�~�[�p�[�g�R
//-----------------------------------------------------------------------------
void EnemyManager::_EnemyParts3()
{
	///		�Q�[�����Ԓ����̂��߁A�폜�����������X�L�b�v
	const bool isSkip = m_entryTime == 3000.0f;
	if (isSkip) { m_entryTime = 5500.0f - SKIP; }

	///		�Q�[�����Ԓ����̂��߁A�폜
	////	�O���U�R�p�[�g�Q
	//_FormationEntry(ENEMY_KIND::ENEMY_LINE, 3000.0f, 10.0f, VGet(120.0f, 90.0f, 0.0f), 15, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_1);
	//_FormationEntry(ENEMY_KIND::ENEMY_LINE, 3000.0f, 10.0f, VGet(120.0f, 30.0f, 0.0f), 15, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_2);
	//_FormationEntry(ENEMY_KIND::ENEMY_LINE, 3100.0f, 10.0f, VGet(120.0f, 60.0f, 0.0f), 15, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_3);
	//_VerticalFormationEntry(ENEMY_KIND::ENEMY_RETURN, 3200.0f, 0.0f, 10.0f, VGet(-150.0f, 85.0f, 50.0f), 3, false, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	//_VerticalFormationEntry(ENEMY_KIND::ENEMY_RETURN, 3200.0f, 0.0f, 10.0f, VGet(-150.0f, 35.0f, 50.0f), 3, false, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	//_VerticalFormationEntry(ENEMY_KIND::ENEMY_RETURN, 3300.0f, 0.0f, 10.0f, VGet(-150.0f, 60.0f, 50.0f), 3, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	//_VerticalFormationEntry(ENEMY_KIND::ENEMY_RETURN, 3400.0f, 0.0f, 15.0f, VGet(-150.0f, 85.0f, 50.0f), 5, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	//_VerticalFormationEntry(ENEMY_KIND::ENEMY_RETURN, 3450.0f, 0.0f, 15.0f, VGet(-150.0f, 85.0f, 50.0f), 5, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	//_VerticalFormationEntry(ENEMY_KIND::ENEMY_RETURN, 3500.0f, 0.0f, 15.0f, VGet(-150.0f, 85.0f, 50.0f), 5, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_NONE);
	//_FormationEntry(ENEMY_KIND::ENEMY_CURVE, 3600.0f, 10.0f, VGet(120.0f, 90.0f, 0.0f), 10, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_1);
	//_FormationEntry(ENEMY_KIND::ENEMY_CURVE, 3650.0f, 10.0f, VGet(160.0f, 70.0f, 0.0f), 10, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_2);
	//_FormationEntry(ENEMY_KIND::ENEMY_CURVE, 3700.0f, 10.0f, VGet(200.0f, 51.0f, 0.0f), 10, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_3);
	//_FormationEntry(ENEMY_KIND::ENEMY_CURVE, 4000.0f, 10.0f, VGet(120.0f, 20.0f, 0.0f), 10, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_4);
	//_FormationEntry(ENEMY_KIND::ENEMY_CURVE, 4050.0f, 10.0f, VGet(160.0f, 40.0f, 0.0f), 10, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_5);
	//_FormationEntry(ENEMY_KIND::ENEMY_RETURN, 4300.0f, 10.0f, VGet(-150.0f, 20.0f, 50.0f), 10, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_1);
	//_FormationEntry(ENEMY_KIND::ENEMY_RETURN, 4450.0f, 10.0f, VGet(-150.0f, 40.0f, 50.0f), 10, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_2);
	//_FormationEntry(ENEMY_KIND::ENEMY_RETURN, 4600.0f, 10.0f, VGet(-150.0f, 60.0f, 50.0f), 10, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_3);
	//_FormationEntry(ENEMY_KIND::ENEMY_RETURN, 4750.0f, 10.0f, VGet(-150.0f, 80.0f, 50.0f), 10, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_4);
}

//-----------------------------------------------------------------------------
//	@brief	�G�l�~�[�p�[�g�S
//-----------------------------------------------------------------------------
void EnemyManager::_EnemyParts4()
{
	//	�㔼�U�R�p�[�g
	_FormationEntry(ENEMY_KIND::ENEMY_TURNING, 5500.0f, 20.0f, VGet(120.0f, 90.0f, 0.0f), 5, true, false, (int)ENEMY_FORMATION_NUM::FORMATION_1);
	_FormationEntry(ENEMY_KIND::ENEMY_TURNING, 5500.0f, 20.0f, VGet(120.0f, 30.0f, 0.0f), 5, true, false, (int)ENEMY_FORMATION_NUM::FORMATION_2);
	_FormationEntry(ENEMY_KIND::ENEMY_TURNING, 5900.0f, 20.0f, VGet(200.0f, 70.0f, 0.0f), 5, true, false, (int)ENEMY_FORMATION_NUM::FORMATION_3);
	_FormationEntry(ENEMY_KIND::ENEMY_TURNING, 5900.0f, 20.0f, VGet(200.0f, 50.0f, 0.0f), 5, true, false, (int)ENEMY_FORMATION_NUM::FORMATION_4);
	_FormationEntry(ENEMY_KIND::ENEMY_TURNING, 6200.0f, 20.0f, VGet(150.0f, 70.0f, 0.0f), 5, true, false, (int)ENEMY_FORMATION_NUM::FORMATION_5);
	_FormationEntry(ENEMY_KIND::ENEMY_TURNING, 6200.0f, 20.0f, VGet(150.0f, 50.0f, 0.0f), 5, true, false, (int)ENEMY_FORMATION_NUM::FORMATION_1);
	_FormationEntry(ENEMY_KIND::ENEMY_TURNING, 6600.0f, 20.0f, VGet(120.0f, 90.0f, 0.0f), 5, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_2);
	_FormationEntry(ENEMY_KIND::ENEMY_TURNING, 6600.0f, 20.0f, VGet(120.0f, 30.0f, 0.0f), 5, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_3);
	_FormationEntry(ENEMY_KIND::ENEMY_TURNING, 6600.0f, 20.0f, VGet(200.0f, 70.0f, 0.0f), 5, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_4);
	_FormationEntry(ENEMY_KIND::ENEMY_TURNING, 6600.0f, 20.0f, VGet(200.0f, 50.0f, 0.0f), 5, true, true, (int)ENEMY_FORMATION_NUM::FORMATION_5);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_UP_DOWN, 7000.0f, 10.0f, 40.0f, VGet(70.0f, -50.0f, 50.0f), 4, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_1);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_UP_DOWN, 7000.0f, 10.0f, 40.0f, VGet(90.0f, 170.0f, 50.0f), 5, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_2);
	_FormationEntry(ENEMY_KIND::ENEMY_FLOATING, 7300.0f, 10.0f, VGet(120.0f, 85.0f, 0.0f), 10, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_3);
	_FormationEntry(ENEMY_KIND::ENEMY_FLOATING, 7300.0f, 10.0f, VGet(120.0f, 20.0f, 0.0f), 10, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_4);
	_FormationEntry(ENEMY_KIND::ENEMY_LINE, 7400.0f, 10.0f, VGet(120.0f, 60.0f, 0.0f), 10, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_5);

	///		�Q�[�����Ԓ����̂��߁A�폜�����������X�L�b�v
	const bool isSkip1 = m_entryTime == 7600.0f;
	if (isSkip1) { m_entryTime = 8800.0f - SKIP; }

	///		�Q�[�����Ԓ����̂��߁A�폜
	//_FormationEntry(ENEMY_KIND::ENEMY_TURNING, 7700.0f, 20.0f, VGet(120.0f, 90.0f, 0.0f), 5, true, false, (int)ENEMY_FORMATION_NUM::FORMATION_5);
	//_FormationEntry(ENEMY_KIND::ENEMY_TURNING, 7900.0f, 20.0f, VGet(140.0f, 70.0f, 0.0f), 5, true, false, (int)ENEMY_FORMATION_NUM::FORMATION_1);
	//_FormationEntry(ENEMY_KIND::ENEMY_TURNING, 8100.0f, 20.0f, VGet(160.0f, 50.1f, 0.0f), 5, true, false, (int)ENEMY_FORMATION_NUM::FORMATION_2);
	//_FormationEntry(ENEMY_KIND::ENEMY_TURNING, 8300.0f, 20.0f, VGet(120.0f, 20.0f, 0.0f), 5, true, false, (int)ENEMY_FORMATION_NUM::FORMATION_3);
	//_FormationEntry(ENEMY_KIND::ENEMY_TURNING, 8500.0f, 20.0f, VGet(150.0f, 50.0f, 0.0f), 5, true, false, (int)ENEMY_FORMATION_NUM::FORMATION_4);

	_VerticalFormationEntry(ENEMY_KIND::ENEMY_UP_DOWN, 8800.0f, 10.0f, 40.0f, VGet(70.0f, 1750.0f, 50.0f), 4, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_5);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_UP_DOWN, 9000.0f, 10.0f, 40.0f, VGet(90.0f, -50.0f, 50.0f), 5, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_1);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_UP_DOWN, 9200.0f, 10.0f, 40.0f, VGet(70.0f, 170.0f, 50.0f), 4, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_2);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_UP_DOWN, 9400.0f, 10.0f, 40.0f, VGet(90.0f, -50.0f, 50.0f), 5, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_3);
	_VerticalFormationEntry(ENEMY_KIND::ENEMY_UP_DOWN, 9600.0f, 10.0f, 40.0f, VGet(70.0f, 170.0f, 50.0f), 4, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_4);
	
	///		�Q�[�����Ԓ����̂��߁A�폜�����������X�L�b�v
	const bool isSkip2 = m_entryTime == 9800.0f;
	if (isSkip2) { m_entryTime = 10300.0f; }

	///		�Q�[�����Ԓ����̂��߁A�폜
	//_VerticalFormationEntry(ENEMY_KIND::ENEMY_UP_DOWN, 9800.0f, 10.0f, 40.0f, VGet(70.0f, -50.0f, 50.0f), 4, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_5);
	//_VerticalFormationEntry(ENEMY_KIND::ENEMY_UP_DOWN, 9800.0f, 10.0f, 40.0f, VGet(90.0f, 170.0f, 50.0f), 5, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_1);
	//_VerticalFormationEntry(ENEMY_KIND::ENEMY_UP_DOWN, 10000.0f, 10.0f, 40.0f, VGet(70.0f, -50.0f, 50.0f), 4, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_2);
	//_VerticalFormationEntry(ENEMY_KIND::ENEMY_UP_DOWN, 10000.0f, 10.0f, 40.0f, VGet(90.0f, 170.0f, 50.0f), 5, false, false, (int)ENEMY_FORMATION_NUM::FORMATION_3);
}

//-----------------------------------------------------------------------------
//	@brief	�G�l�~�[�p�[�g�T
//-----------------------------------------------------------------------------
void EnemyManager::_EnemyParts5()
{
	//	�{�X���̃U�R�p�[�g
	_FormationEntry(ENEMY_KIND::ENEMY_LINE, 10825.0f, 10.0f, VGet(120.0f, 80.0f, 0.0f), 8, true, false, (int)ENEMY_FORMATION_NUM::FORMATION_4);
	_FormationEntry(ENEMY_KIND::ENEMY_LINE, 11225.0f, 10.0f, VGet(120.0f, 30.0f, 0.0f), 8, true, false, (int)ENEMY_FORMATION_NUM::FORMATION_5);
	_FormationEntry(ENEMY_KIND::ENEMY_LINE, 11625.0f, 10.0f, VGet(120.0f, 30.0f, 0.0f), 8, true, false, (int)ENEMY_FORMATION_NUM::FORMATION_1);
	_FormationEntry(ENEMY_KIND::ENEMY_LINE, 12225.0f, 10.0f, VGet(120.0f, 80.0f, 0.0f), 8, true, false, (int)ENEMY_FORMATION_NUM::FORMATION_2);
	_FormationEntry(ENEMY_KIND::ENEMY_LINE, 12870.0f, 10.0f, VGet(120.0f, 80.0f, 0.0f), 8, true, false, (int)ENEMY_FORMATION_NUM::FORMATION_3);
	_FormationEntry(ENEMY_KIND::ENEMY_LINE, 13400.0f, 10.0f, VGet(120.0f, 30.0f, 0.0f), 8, true, false, (int)ENEMY_FORMATION_NUM::FORMATION_4);
	_FormationEntry(ENEMY_KIND::ENEMY_LINE, 14050.0f, 10.0f, VGet(120.0f, 30.0f, 0.0f), 8, true, false, (int)ENEMY_FORMATION_NUM::FORMATION_5);
}

//-----------------------------------------------------------------------------
//	@brief	�����g�܂��ēo�^
//-----------------------------------------------------------------------------
void EnemyManager::_FormationEntry(const ENEMY_KIND _enemyKind, const float _startTime, const float _intervalTime, const VECTOR _startPos, const int _formationNum, 
									const bool _isUseShot, const bool _isRestriction, const int _formation)
{
	//	�푰�͈͊O����
	const bool isKindSizeOver = _enemyKind < ENEMY_KIND::NONE || _enemyKind > ENEMY_KIND::ENEMY_NUM;
	CommonDebug::Assert(isKindSizeOver, " [ EnemyManager.cpp ] : error : enemy kind over.");
	if (isKindSizeOver) { return; }

	//	�܂��J�n���ԂłȂ����͖�������
	if (m_entryTime < _startTime) { return; }

	//	������G�l�~�[���̉��Z
	if (m_entryTime == _startTime) { m_enemyCounter[_formation] = _formationNum; }

	for (int num = 0; num < _formationNum; num++)
	{
		//	�܂��J�n���ԂłȂ����͖�������
		float entryTime = (_startTime + (_intervalTime * num));
		if (m_entryTime != entryTime) { continue; }

		//	�o�^����
		_Registration(_enemyKind, _startPos, entryTime, _isUseShot, _isRestriction, _formation);
	}
}

//-----------------------------------------------------------------------------
//	@brief	�o�^����
//-----------------------------------------------------------------------------
void EnemyManager::_Registration(const ENEMY_KIND _enemyKind, const VECTOR _startPos, const float _entryTime, const bool _isUseShot, const bool _isRestriction, const int _formation)
{
	//	�g�p���X�g�o�^����
	const bool isListEntry = m_entryTime == _entryTime;
	if (isListEntry)
	{
		VECTOR tmpPos = CommonConstant::ORIGIN;

		//	�󂢂Ă���o�b�t�@��T���A
		//	�G�l�~�[��ǉ�
		switch (_enemyKind)
		{
			//	�����G�l�~�[��ǉ�
		case ENEMY_KIND::ENEMY_LINE:
			tmpPos = VGet(_startPos.x, _startPos.y, _startPos.z);
			if (_OneEnemyRegistrationToShotProbaility((int)ENEMY_KIND::ENEMY_LINE, tmpPos, _isUseShot, _isRestriction, _formation)) { return; }
			break;

			//	���V�G�l�~�[��ǉ�
		case ENEMY_KIND::ENEMY_FLOATING:
			tmpPos = VGet(_startPos.x, _startPos.y, _startPos.z);
			if (_OneEnemyRegistrationToShotProbaility((int)ENEMY_KIND::ENEMY_FLOATING, tmpPos, _isUseShot, _isRestriction, _formation)) { return; }
			break;

			//	�Ȑ��G�l�~�[��ǉ�
		case ENEMY_KIND::ENEMY_CURVE:
			tmpPos = VGet(_startPos.x, _startPos.y, _startPos.z);
			if (_OneEnemyRegistrationToShotProbaility((int)ENEMY_KIND::ENEMY_CURVE, tmpPos, _isUseShot, _isRestriction, _formation)) { return; }
			break;

			//	�A�҃G�l�~�[��ǉ�
		case ENEMY_KIND::ENEMY_RETURN:

			//	�A�҃G�l�~�[�� X���W �̓}�C�i�X�̕������炵���A
			//	�����Ȃ��̂ŁA�v���X�������Ă���A�}�C�i�X�ɕϊ�����
			if (_startPos.x >= 0) { tmpPos = VGet(-_startPos.x, _startPos.y, _startPos.z); }
			else { tmpPos = VGet(_startPos.x, _startPos.y, _startPos.z); }
			if (_OneEnemyRegistrationToShotProbaility((int)ENEMY_KIND::ENEMY_RETURN, tmpPos, _isUseShot, _isRestriction, _formation)) { return; }
			break;

		case ENEMY_TURNING:
			tmpPos = VGet(_startPos.x, _startPos.y, _startPos.z);
			if (_OneEnemyRegistrationToShotProbaility((int)ENEMY_KIND::ENEMY_TURNING, tmpPos, _isUseShot, _isRestriction, _formation)) { return; }
			break;

		case ENEMY_UP_DOWN:
			tmpPos = VGet(_startPos.x, _startPos.y, _startPos.z);
			if (_OneEnemyRegistrationToShotProbaility((int)ENEMY_KIND::ENEMY_TURNING, tmpPos, _isUseShot, _isRestriction, _formation)) { return; }
			break;
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�����g�܂��ċA�҃G�l�~�[�̓o�^
//-----------------------------------------------------------------------------
void EnemyManager::_VerticalFormationEntry(const ENEMY_KIND _enemyKind, const float _startTime, const float _intervalTime, const float _shiftInterval, const VECTOR _startPos, 
										   const int _formationNum, const bool _isUseShot, const bool _isHavingItem, const int _formation)
{
	//	�܂��J�n���ԂłȂ����͖�������
	if (m_entryTime < _startTime) { return; }

	if(m_entryTime == _startTime) { m_enemyCounter[_formation] = _formationNum; }
	
	for (int num = 0; num < _formationNum; num++)
	{
		//	�܂��J�n���ԂłȂ����͖�������
		float entryTime = (_startTime + (_intervalTime * num));
		if (m_entryTime != entryTime) { continue; }

		//	�G�l�~�[��ǉ�
		_VerticalRegistration(_enemyKind, _startPos, entryTime, _shiftInterval, num, _isUseShot, _isHavingItem, _formation);
	}
}

//-----------------------------------------------------------------------------
//	@brief	�A�҃G�l�~�[�̓o�^
//-----------------------------------------------------------------------------
void EnemyManager::_VerticalRegistration(const ENEMY_KIND _enemyKind, const VECTOR _startPos, const float _entryTime, const float _shiftInterval,
										 const int _num, const bool _isUseShot, const bool _isHavingItem, const int _formation)
{
	VECTOR tmpPos = CommonConstant::ORIGIN;

	//	�g�p���X�g�o�^����
	const bool isListEntry = m_entryTime == _entryTime;
	if (isListEntry)
	{
		//	�G�l�~�[��ǉ�
		switch (_enemyKind)
		{
			//	���V�G�l�~�[��ǉ�
		case ENEMY_KIND::ENEMY_FLOATING:
			//	�G�l�~�[��̕��̓o�^
			tmpPos = VGet(_startPos.x, _startPos.y - (_shiftInterval * _num), _startPos.z);
			if (_OneEnemyRegistration((int)ENEMY_KIND::ENEMY_FLOATING, tmpPos, _isUseShot, _isHavingItem, _formation)) { return; }
			break;

			//	�A�҃G�l�~�[��ǉ�
		case ENEMY_KIND::ENEMY_RETURN:

			//	�A�҃G�l�~�[�� X���W �̓}�C�i�X�̕������炵���A
			//	�����Ȃ��̂ŁA�v���X�������Ă���A�}�C�i�X�ɕϊ�����
			if (_startPos.x >= 0) { tmpPos = VGet(-_startPos.x, _startPos.y - (_shiftInterval * _num), _startPos.z); }
			else { tmpPos = VGet(_startPos.x, _startPos.y - (_shiftInterval * _num), _startPos.z); }
			if (_OneEnemyRegistration((int)ENEMY_KIND::ENEMY_RETURN, tmpPos, _isUseShot, _isHavingItem, _formation)) { return; }
			break;

		case ENEMY_UP_DOWN:
			tmpPos = VGet(_startPos.x - (_shiftInterval * _num), _startPos.y, _startPos.z);
			if (_OneEnemyRegistration((int)ENEMY_KIND::ENEMY_UP_DOWN, tmpPos, _isUseShot, _isHavingItem, _formation)) { return; }
			break;
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	��̕��̃G�l�~�[�̓o�^
//-----------------------------------------------------------------------------
bool EnemyManager::_OneEnemyRegistration(const int _enemyKind, const VECTOR _startPos, const bool _isUseShot, const bool _isHavingItem, const int _formation)
{
	for (int i = 0; i < CommonConstant::MAX_ENEMY_ENTRY_NUM; i++)
	{
		//	�g�p���Ă��Ȃ��G�l�~�[��T��
		if (!m_entryBuffer[_enemyKind].m_isInUse[i])
		{
			//	������Ԃ̐ݒ�
			m_entryBuffer[_enemyKind].m_pBuf[i]->SetPos(_startPos);
			m_entryBuffer[_enemyKind].m_pBuf[i]->SetEntryID(i);
			m_entryBuffer[_enemyKind].m_pBuf[i]->SetEntryKind(_enemyKind);
			m_entryBuffer[_enemyKind].m_pBuf[i]->SetFormationID((int)_formation);

			//	�G�l�~�[���g�p��Ԃɂ���
			m_entryBuffer[_enemyKind].m_isInUse[i] = true;

			//	�V���b�g���g�����ǂ����ƁA
			//	�A�C�e���������Ă��邩
			if (_isUseShot)
			{
				//	�V���b�g���g��
				m_entryBuffer[_enemyKind].m_pBuf[i]->SetIsUseShot(true);
			}
			else
			{
				//	�V���b�g���g��Ȃ�
				m_entryBuffer[_enemyKind].m_pBuf[i]->SetIsUseShot(false);
			}

			if (_isHavingItem)
			{
				//	�A�C�e����5����1�Ŏ���
				bool isActive = CommonFunction::GetRand(0, 5) == 0;
				if (isActive) { m_entryBuffer[_enemyKind].m_pBuf[i]->SetIsHavingItems(true); }
				else { m_entryBuffer[_enemyKind].m_pBuf[i]->SetIsHavingItems(false); }
			}
			else
			{
				m_entryBuffer[_enemyKind].m_pBuf[i]->SetIsHavingItems(false);
			}

			//	�g�p���X�g�ɓo�^
			m_useList.push_back(m_entryBuffer[_enemyKind].m_pBuf[i]);
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
//	@brief	��̕��̓o�^���A�V���b�g�͓񕪂̈�̊m���Ŏg�p����
//-----------------------------------------------------------------------------
bool EnemyManager::_OneEnemyRegistrationToShotProbaility(const int _enemyKind, const VECTOR _startPos, const bool _isUseShot, const bool _isRestriction, const int _formation)
{
	for (int i = 0; i < CommonConstant::MAX_ENEMY_ENTRY_NUM; i++)
	{
		//	�g�p���Ă��Ȃ��G�l�~�[��T��
		if (!m_entryBuffer[_enemyKind].m_isInUse[i])
		{
			//	������Ԃ̐ݒ�
			m_entryBuffer[_enemyKind].m_pBuf[i]->SetPos(_startPos);
			m_entryBuffer[_enemyKind].m_pBuf[i]->SetEntryID(i);
			m_entryBuffer[_enemyKind].m_pBuf[i]->SetEntryKind(_enemyKind);
			m_entryBuffer[_enemyKind].m_pBuf[i]->SetFormationID((int)_formation);

			//	�G�l�~�[���g�p��Ԃɂ���
			m_entryBuffer[_enemyKind].m_isInUse[i] = true;

			//	�V���b�g���g����
			if (_isUseShot)
			{
				//	��������
				if (_isRestriction)
				{
					//	�Y�����������̂Ƃ���
					//	�V���b�g�͎g��
					bool isActive = i % 2 == 0;
					if (isActive) { m_entryBuffer[_enemyKind].m_pBuf[i]->SetIsUseShot(true); }
					else { m_entryBuffer[_enemyKind].m_pBuf[i]->SetIsUseShot(false); }
				}
				else
				{
					m_entryBuffer[_enemyKind].m_pBuf[i]->SetIsUseShot(true);
				}
			}
			else
			{
				//	�V���b�g�͎g��Ȃ�
				m_entryBuffer[_enemyKind].m_pBuf[i]->SetIsUseShot(false);
			}

			//	�A�C�e���͎����Ȃ�
			m_entryBuffer[_enemyKind].m_pBuf[i]->SetIsHavingItems(false);

			//	�g�p���X�g�ɓo�^
			m_useList.push_back(m_entryBuffer[_enemyKind].m_pBuf[i]);
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ������
//-----------------------------------------------------------------------------
void EnemyManager::_FinalRelease()
{
	//	���X�g���ɓo�^����Ă���Ƃ��A�N���A����
	if (!m_useList.empty()) { m_useList.clear(); }

	for (int i = 0; i < ENEMY_KIND::ENEMY_NUM; i++)
	{
		//	���f���̃A�����[�h
		MV1DeleteModel(m_sourceModelHandle[i]);

		for (int j = 0; j < CommonConstant::MAX_ENEMY_ENTRY_NUM; j++)
		{
			//	�������̉��
			CommonSafe::Delete(m_entryBuffer[i].m_pBuf[j]);
		}
	}
}
