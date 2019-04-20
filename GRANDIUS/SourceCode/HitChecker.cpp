
//=============================================================================
//	@file	HitChecker.cpp
//	@brief	�q�b�g�`�F�b�J�[
//	@autor	���m ���
//	@date	2018/12/13
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "HitChecker.h"
#include "Common.h"
#include "PlayerManager.h"
#include "EnemyManager.h"
#include "BossManager.h"
#include "ShotManager.h"
#include "StayShotManager.h"
#include "ItemManager.h"
#include "PlayerBase.h"
#include "EnemyBase.h"
#include "MediumBoss.h"
#include "LastBoss.h"
#include "Shot.h"
#include "StayShot.h"
#include "Item.h"
#include "UILife.h"
#include "UIGauge.h"
#include "UIScore.h"
#include "SoundEffect.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const float HitChecker::ACTIVE_LENGHT = 15.0f;			//	�����蔻��L������

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�ƃG�l�~�[�̓����蔻��
//-----------------------------------------------------------------------------
void HitChecker::PlayerToEnemy(PlayerManager& _playerManager, EnemyManager& _enemyManager, ItemManager& _itemManager)
{
	//	�v���C���[�̃|�C���^�̎擾
	PlayerBase* player = _playerManager.GetPlayerPtr();

	for (int i = 0; i < _enemyManager.GetListSize(); i++)
	{
		//	�G�l�~�[�̃|�C���^�̎擾
		EnemyBase* enemy = _enemyManager.GetEnemyPtr(i);

		//	�|�C���^�����݂���Ȃ�
		if (player && enemy)
		{
			//	�I�u�W�F�N�g�Ԃ̋����𑪂�
			//	true �̂Ƃ��̂݁A�����蔻��̌v�Z���s��
			const bool isActive = _AskObjectLenght(player->GetPos(), enemy->GetPos());
			if (isActive)
			{
				//	�܂��_���[�W���󂯂Ă��Ȃ��Ƃ��A
				//	�����蔻����󂯎��
				const bool isNotInvincible = !player->GetIsInvincible() && !player->GetIsInvincibleAfterLaser();
				const bool isNotDamage = isNotInvincible && !player->GetIsDamage() && !enemy->GetIsHIt();
				if (isNotDamage)
				{
					//	�����蔻��
					const bool isHit = _CircleHitCheck(player->GetCircle(), enemy->GetCircle());
					if (isHit)
					{
						//	�q�b�g�����̂ŁA
						//	�v���C���[�̎c�@�����炷

						//	�v���C���[�̎c�@�����炷
						player->OnHitDamage();
						player->SetIsDamage(true);

						//	���񂩂�폜
						const int formationID = enemy->GetFormationID();
						_enemyManager.SubEnemyCount(formationID);

						//	�A�C�e���������Ă���Ƃ����A
						//	��������ׂē|������A
						//	�A�C�e���𐶐�
						const bool isHavingItems = enemy->GetIsHavingItems();
						const bool isEnemyExistence = _enemyManager.GetIsEnemyExistence(formationID);
						const bool isSetItem = ((formationID != 0) && !isEnemyExistence) || isHavingItems;
						if (isSetItem) { _itemManager.RegisterOnList(enemy->GetPos()); }

						//	�G�l�~�[�ɂ��q�b�g����
						enemy->SetIsHit(true);

						//	�X�R�A�̉��Z
						SCORE->AddScore(SCORE->ADD_SCORE::ADD_SCORE_ENEMY);
					}
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�ƒ��{�X�̓����蔻��
//-----------------------------------------------------------------------------
void HitChecker::PlayerToMediumBoss(PlayerManager& _playerManager, BossManager& _bossManager)
{
	//	�v���C���[�̃|�C���^�̎擾
	PlayerBase* player = _playerManager.GetPlayerPtr();

	//	���{�X�̃|�C���^�̎擾
	MediumBoss* mediumBoss = _bossManager.GetMediumBoss();

	//	�|�C���^�����݂���Ȃ�
	if (player && mediumBoss)
	{
		//	�I�u�W�F�N�g�Ԃ̋����𑪂�
		//	true �̂Ƃ��̂݁A�����蔻��̌v�Z���s��
		const bool isActive = _AskObjectLenght(player->GetPos(), mediumBoss->GetPos());
		if (isActive)
		{
			//	�܂��_���[�W���󂯂Ă��Ȃ��Ƃ��A
			//	�����蔻����󂯎��
			const bool isNotInvincible = !player->GetIsInvincible() && !player->GetIsInvincibleAfterLaser();
			const bool isNotDamage = isNotInvincible && !player->GetIsDamage();
			if (isNotDamage)
			{
				//	�����蔻��
				const bool isHit = _CircleHitCheck(player->GetCircle(), mediumBoss->GetCircle());
				if (isHit)
				{
					//	�q�b�g�����̂ŁA
					//	�v���C���[�̎c�@�����炷

					//	�v���C���[�̎c�@�����炷
					player->OnHitDamage();
					player->SetIsDamage(true);
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�ƍŏI�{�X�̓����蔻��
//-----------------------------------------------------------------------------
void HitChecker::PlayerToLastBoss(PlayerManager& _playerManager, BossManager& _bossManager)
{
	static const int right = 0;
	static const int left = 1;

	//	�v���C���[�̃|�C���^�̎擾
	PlayerBase* player = _playerManager.GetPlayerPtr();

	//	���{�X�̃|�C���^�̎擾
	LastBoss* lastBoss = _bossManager.GetLastBossPtr();

	//	�|�C���^�����݂���Ȃ�
	if (player && lastBoss)
	{
		//	�܂��_���[�W���󂯂Ă��Ȃ��Ƃ��A
		//	�����蔻����󂯎��
		const bool isNotInvincible = !player->GetIsInvincible() && !player->GetIsInvincibleAfterLaser();
		const bool isNotDamage = isNotInvincible && !player->GetIsDamage();
		if (isNotDamage)
		{
			//	�����蔻��
			const bool isCoreActive = lastBoss->GetIsRightCoreAlive() || lastBoss->GetIsRightCoreAlive();
			const bool isHitBody = _CircleHitCheck(player->GetCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_BODY)) && isCoreActive;
			const bool isHitArmRight = _CircleHitCheck(player->GetCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_ARM, right)) && lastBoss->GetIsRightCoreAlive();
			const bool isHitArmLeft = _CircleHitCheck(player->GetCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_ARM, left)) && lastBoss->GetIsLeftCoreAlive();
			const bool isHitArmBodyRight = _BoxHitCheck(player->GetRect(), lastBoss->GetArmRect(right)) && lastBoss->GetIsRightCoreAlive();
			const bool isHitArmBodyLeft = _BoxHitCheck(player->GetRect(), lastBoss->GetArmRect(left)) && lastBoss->GetIsLeftCoreAlive();
			const bool isHitLaserRight = _BoxHitCheck(player->GetRect(), lastBoss->GetLaserRect(right)) && lastBoss->GetIsRightCoreAlive();
			const bool isHitLaserLeft = _BoxHitCheck(player->GetRect(), lastBoss->GetLaserRect(left)) && lastBoss->GetIsLeftCoreAlive();
			const bool isHitCenterBarrel = _BoxHitCheck(player->GetRect(), lastBoss->GetCenterBarrelRect()) && isCoreActive;
			const bool isHitOnly = isHitBody || isHitArmRight || isHitArmLeft || isHitArmBodyRight || isHitArmBodyLeft || isHitLaserRight || isHitLaserLeft || isHitCenterBarrel;
			if (isHitOnly)
			{
				//	�v���C���[�̎c�@�����炷
				player->OnHitDamage();
				player->SetIsDamage(true);
			}

			const bool isHitCoreRight = _CircleHitCheck(player->GetCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_CORE, right)) && lastBoss->GetIsRightCoreAlive();
			if (isHitCoreRight)
			{
				//	�{�X�̃p�[�c�Ƀ_���[�W��^����
				lastBoss->OnHitCoreDamage(right);

				//	�v���C���[�̎c�@�����炷
				player->OnHitDamage();
				player->SetIsDamage(true);
			}

			const bool isHitCoreLeft = _CircleHitCheck(player->GetCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_CORE, left)) && lastBoss->GetIsLeftCoreAlive();
			if (isHitCoreLeft)
			{
				//	�{�X�̃p�[�c�Ƀ_���[�W��^����
				lastBoss->OnHitCoreDamage(left);

				//	�v���C���[�̎c�@�����炷
				player->OnHitDamage();
				player->SetIsDamage(true);
			}

			const bool isHitSideBarrelRight = _CircleHitCheck(player->GetCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_SIDE_BARREL, right)) && lastBoss->GetIsRightSideBarrelAlive();
			if (isHitSideBarrelRight)
			{
				//	�{�X�̃p�[�c�Ƀ_���[�W��^����
				lastBoss->OnHitSideBarrelDamage(right);

				//	�v���C���[�̎c�@�����炷
				player->OnHitDamage();
				player->SetIsDamage(true);
			}

			const bool isHitSideBarrelLeft = _CircleHitCheck(player->GetCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_SIDE_BARREL, left)) && lastBoss->GetIsLeftSideBarrelAlive();
			if (isHitSideBarrelLeft)
			{
				//	�{�X�̃p�[�c�Ƀ_���[�W��^����
				lastBoss->OnHitSideBarrelDamage(left);

				//	�v���C���[�̎c�@�����炷
				player->OnHitDamage();
				player->SetIsDamage(true);
			}

			//	�{�X�̔j���
			lastBoss->DestructionSituation();

			//	���ׂĔj��
			const bool isAllDestruction = lastBoss->GetIsAllDestruction();
			if (isAllDestruction) { _playerManager.SetIsClear(true); }
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�ƃG�l�~�[�̒e�̓����蔻��
//-----------------------------------------------------------------------------
void HitChecker::PlayerToEnemyShot(PlayerManager& _playerManager, ShotManager& _shotManager)
{
	//	�v���C���[�̃|�C���^�̎擾
	PlayerBase* player = _playerManager.GetPlayerPtr();

	for (int i = 0; i < _shotManager.GetListSize(ShotManager::SHOT_KIND::ENEMY_SHOT); i++)
	{
		//	�V���b�g�̃|�C���^�̎擾
		Shot* shot = _shotManager.GetShotPtr(ShotManager::SHOT_KIND::ENEMY_SHOT, i);

		//	�|�C���^�����݂���Ȃ�
		if (player && shot)
		{
			//	�I�u�W�F�N�g�Ԃ̋����𑪂�
			//	true �̂Ƃ��̂݁A�����蔻��̌v�Z���s��
			const bool isActive = _AskObjectLenght(player->GetPos(), shot->GetPos());
			if (isActive)
			{
				//	�܂��_���[�W���󂯂Ă��Ȃ��Ƃ��A
				//	�����蔻����󂯎��
				const bool isNotInvincible = !player->GetIsInvincible() && !player->GetIsInvincibleAfterLaser();
				const bool isNotDamage = isNotInvincible && !player->GetIsDamage();
				if (isNotDamage)
				{
					//	�����蔻��
					const bool isHit = _CircleHitCheck(player->GetCircle(), shot->GetCircle());
					if (isHit)
					{
						//	�q�b�g�����̂ŁA
						//	�v���C���[�̎c�@�����炷

						//	�v���C���[�̎c�@�����炷
						player->OnHitDamage();
						player->SetIsDamage(true);

						//	�G�l�~�[�̒e�����X�g����폜����
						_shotManager.RemoveFromList(ShotManager::SHOT_KIND::ENEMY_SHOT, shot);
					}
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�̒e�ƃG�l�~�[�̓����蔻��
//-----------------------------------------------------------------------------
void HitChecker::PlayerShotToEnemy(ShotManager& _shotManager, EnemyManager& _enemyManager, ItemManager& _itemManager, UIGauge& _gaugeUI)
{
	for (int i = 0; i < _shotManager.GetListSize(ShotManager::SHOT_KIND::PLAYER_SHOT); i++)
	{
		//	�V���b�g�̃|�C���^�̎擾
		Shot* shot = _shotManager.GetShotPtr(ShotManager::SHOT_KIND::PLAYER_SHOT, i);

		for (int j = 0; j < _enemyManager.GetListSize(); j++)
		{
			//	�G�l�~�[�̃|�C���^�̎擾
			EnemyBase* enemy = _enemyManager.GetEnemyPtr(j);

			//	�|�C���^�����݂���Ȃ�
			if (shot && enemy)
			{
				//	�I�u�W�F�N�g�Ԃ̋����𑪂�
				//	true �̂Ƃ��̂݁A�����蔻��̌v�Z���s��
				const bool isActive = _AskObjectLenght(shot->GetPos(), enemy->GetPos());
				if (isActive)
				{
					//	�G�l�~�[���q�b�g���Ă��Ȃ��Ƃ�
					const bool isNotDamage = !enemy->GetIsHIt();
					if (isNotDamage)
					{

						//	�����蔻��
						const bool isHit = _CircleHitCheck(shot->GetCircle(), enemy->GetCircle());
						if (isHit)
						{
							//	�q�b�g�����̂ŁA
							//	�G�l�~�[�ƃv���C���[�̒e���A
							//	���X�g����폜����

							//	�G�l�~�[�����X�g����폜����
							//	���񂩂�폜
							const int formationID = enemy->GetFormationID();
							_enemyManager.SubEnemyCount(formationID);

							//	�A�C�e���������Ă���Ƃ����A
							//	��������ׂē|������A
							//	�A�C�e���𐶐�
							const bool isHavingItems = enemy->GetIsHavingItems();
							const bool isEnemyExistence = _enemyManager.GetIsEnemyExistence(formationID);
							const bool isSetItem = ((formationID != 0) && !isEnemyExistence) || isHavingItems;
							if (isSetItem) { _itemManager.RegisterOnList(enemy->GetPos()); }

							//	�G�l�~�[�ɂ��q�b�g����
							enemy->SetIsHit(true);

							//	�v���C���[�̒e�����X�g����폜����
							_shotManager.RemoveFromList(ShotManager::SHOT_KIND::PLAYER_SHOT, shot);

							//	�Q�[�W�̉��Z
							_gaugeUI.AddGauge(_gaugeUI.ADD_GAUGE_KIND::ENEMY);

							//	�X�R�A�̉��Z
							SCORE->AddScore(SCORE->ADD_SCORE::ADD_SCORE_ENEMY);
						}
					}
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�̒e�ƃ{�X�̓����蔻��
//-----------------------------------------------------------------------------
void HitChecker::PlayerShotToMediumBoss(ShotManager& _shotManager, BossManager& _bossManager, UIGauge& _gaugeUI)
{
	for (int i = 0; i < _shotManager.GetListSize(ShotManager::SHOT_KIND::PLAYER_SHOT); i++)
	{
		//	�V���b�g�̃|�C���^�̎擾
		Shot* shot = _shotManager.GetShotPtr(ShotManager::SHOT_KIND::PLAYER_SHOT, i);

		//	���{�X�̃|�C���^�̎擾
		MediumBoss* mediumBoss = _bossManager.GetMediumBoss();

		//	�|�C���^�����݂���Ȃ�
		if (shot && mediumBoss)
		{
			//	�I�u�W�F�N�g�Ԃ̋����𑪂�
			//	true �̂Ƃ��̂݁A�����蔻��̌v�Z���s��
			const bool isActive = _AskObjectLenght(shot->GetPos(), mediumBoss->GetPos());
			if (isActive)
			{
				//	�����蔻��
				const bool isHit = _CircleHitCheck(shot->GetCircle(), mediumBoss->GetCircle());
				if (isHit)
				{
					//	�q�b�g�����̂ŁA
					//	�v���C���[�̒e�����X�g����폜���A
					//	�{�X�Ƀ_���[�W��^����

					//	�{�X���_���[�W���󂯂��ꍇ�A
					//	�A�����ē���Ȃ��悤�ɐ���
					if (!mediumBoss->GetIsDamage())
					{
						//	�{�X�Ƀ_���[�W��^���A
						//	�{�X��_�ł�����
						mediumBoss->OnHitDamage();
					}

					//	�v���C���[�̒e�����X�g����폜����
					_shotManager.RemoveFromList(ShotManager::SHOT_KIND::PLAYER_SHOT, shot);

					//	�Q�[�W�̉��Z
					const bool isDamageMoment = !mediumBoss->GetIsDamage();
					if (isDamageMoment) { _gaugeUI.AddGauge(_gaugeUI.ADD_GAUGE_KIND::BOSS); }
				}

			}
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�e�ƍŏI�{�X�̓����蔻��
//-----------------------------------------------------------------------------
void HitChecker::PlayerShotToLastBoss(PlayerManager& _playerManager, ShotManager& _shotManager, BossManager& _bossManager, UIGauge& _gaugeUI)
{
	static const int right = 0;
	static const int left = 1;

	for (int i = 0; i < _shotManager.GetListSize(ShotManager::SHOT_KIND::PLAYER_SHOT); i++)
	{
		//	�V���b�g�̃|�C���^�̎擾
		Shot* shot = _shotManager.GetShotPtr(ShotManager::SHOT_KIND::PLAYER_SHOT, i);

		//	���{�X�̃|�C���^�̎擾
		LastBoss* lastBoss = _bossManager.GetLastBossPtr();

		//	�|�C���^�����݂���Ȃ�
		if (shot && lastBoss)
		{
			//	�����蔻��
			const bool isCoreActive = lastBoss->GetIsRightCoreAlive() || lastBoss->GetIsRightCoreAlive();
			const bool isHitBody = _CircleHitCheck(shot->GetCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_BODY)) && isCoreActive;
			const bool isHitArmRight = _CircleHitCheck(shot->GetCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_ARM, right)) && lastBoss->GetIsRightCoreAlive();
			const bool isHitArmLeft = _CircleHitCheck(shot->GetCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_ARM, left)) && lastBoss->GetIsLeftCoreAlive();
			const bool isHitCenterBarrel = _BoxHitCheck(shot->GetRect(), lastBoss->GetCenterBarrelRect()) && isCoreActive;
			const bool isHitOnly = isHitBody || isHitArmRight || isHitArmLeft || isHitCenterBarrel;
			if (isHitOnly)
			{
				//	�v���C���[�̒e�����X�g����폜����
				_shotManager.RemoveFromList(ShotManager::SHOT_KIND::PLAYER_SHOT, shot);
			}

			const bool isHitCoreRight = _CircleHitCheck(shot->GetCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_CORE, right)) && lastBoss->GetIsRightCoreAlive();
			if (isHitCoreRight)
			{
				//	�Q�[�W�̉��Z
				const bool isDamageMoment = !lastBoss->GetIsCoreDamage(right);
				if (isDamageMoment) { _gaugeUI.AddGauge(_gaugeUI.ADD_GAUGE_KIND::BOSS); }

				//	�{�X�̃p�[�c�Ƀ_���[�W��^����
				lastBoss->OnHitCoreDamage(right);

				//	�v���C���[�̒e�����X�g����폜����
				_shotManager.RemoveFromList(ShotManager::SHOT_KIND::PLAYER_SHOT, shot);
			}

			const bool isHitCoreLeft = _CircleHitCheck(shot->GetCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_CORE, left)) && lastBoss->GetIsLeftCoreAlive();
			if (isHitCoreLeft)
			{
				//	�Q�[�W�̉��Z
				const bool isDamageMoment = !lastBoss->GetIsCoreDamage(left);
				if (isDamageMoment) { _gaugeUI.AddGauge(_gaugeUI.ADD_GAUGE_KIND::BOSS); }

				//	�{�X�̃p�[�c�Ƀ_���[�W��^����
				lastBoss->OnHitCoreDamage(left);

				//	�v���C���[�̒e�����X�g����폜����
				_shotManager.RemoveFromList(ShotManager::SHOT_KIND::PLAYER_SHOT, shot);
			}

			const bool isHitSideBarrelRight = _CircleHitCheck(shot->GetCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_SIDE_BARREL, right)) && lastBoss->GetIsRightSideBarrelAlive();
			if (isHitSideBarrelRight)
			{
				//	�Q�[�W�̉��Z
				const bool isDamageMoment = !lastBoss->GetIsSideBarrelDamage(right);
				if (isDamageMoment) { _gaugeUI.AddGauge(_gaugeUI.ADD_GAUGE_KIND::BOSS); }

				//	�{�X�̃p�[�c�Ƀ_���[�W��^����
				lastBoss->OnHitSideBarrelDamage(right);

				//	�v���C���[�̒e�����X�g����폜����
				_shotManager.RemoveFromList(ShotManager::SHOT_KIND::PLAYER_SHOT, shot);
			}

			const bool isHitSideBarrelLeft = _CircleHitCheck(shot->GetCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_SIDE_BARREL, left)) && lastBoss->GetIsLeftSideBarrelAlive();
			if (isHitSideBarrelLeft)
			{
				//	�Q�[�W�̉��Z
				const bool isDamageMoment = !lastBoss->GetIsSideBarrelDamage(left);
				if (isDamageMoment) { _gaugeUI.AddGauge(_gaugeUI.ADD_GAUGE_KIND::BOSS); }

				//	�{�X�̃p�[�c�Ƀ_���[�W��^����
				lastBoss->OnHitSideBarrelDamage(left);

				//	�v���C���[�̒e�����X�g����폜����
				_shotManager.RemoveFromList(ShotManager::SHOT_KIND::PLAYER_SHOT, shot);
			}

			//	�{�X�̔j���
			lastBoss->DestructionSituation();

			//	���ׂĔj��
			const bool isAllDestruction = lastBoss->GetIsAllDestruction();
			if (isAllDestruction) { _playerManager.SetIsClear(true); }
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�؍ݒe�ƃG�l�~�[�̓����蔻��
//-----------------------------------------------------------------------------
void HitChecker::PlayerStayShotToEnemy(StayShotManager& _stayShotManager, EnemyManager& _enemyManager, ItemManager& _itemManager, UIGauge& _gaugeUI)
{
	for (int i = 0; i < _stayShotManager.GetListSize(); i++)
	{
		//	�V���b�g�̃|�C���^�̎擾
		StayShot* stayShot = _stayShotManager.GetStayShotPtr(i);

		for (int j = 0; j < _enemyManager.GetListSize(); j++)
		{
			//	�G�l�~�[�̃|�C���^�̎擾
			EnemyBase* enemy = _enemyManager.GetEnemyPtr(j);

			//	�|�C���^�����݂���Ȃ�
			if (stayShot && enemy)
			{
				//	�I�u�W�F�N�g�Ԃ̋����𑪂�
				//	true �̂Ƃ��̂݁A�����蔻��̌v�Z���s��
				const bool isActive = _AskObjectLenght(stayShot->GetPos(), enemy->GetPos());
				if (isActive)
				{
					//	�G�l�~�[���q�b�g���Ă��Ȃ��Ƃ�
					const bool isNotDamage = !enemy->GetIsHIt();
					if (isNotDamage)
					{
						//	�����蔻��
						const bool isHit = _CircleHitCheck(stayShot->GetCircle(), enemy->GetCircle());
						if (isHit)
						{
							//	�q�b�g�����̂ŁA
							//	�G�l�~�[�ƃv���C���[�̒e���A
							//	���X�g����폜����

							//	�G�l�~�[�����X�g����폜����
							//	���񂩂�폜
							const int formationID = enemy->GetFormationID();
							_enemyManager.SubEnemyCount(formationID);

							//	�A�C�e���������Ă���Ƃ����A
							//	��������ׂē|������A
							//	�A�C�e���𐶐�
							const bool isHavingItems = enemy->GetIsHavingItems();
							const bool isEnemyExistence = _enemyManager.GetIsEnemyExistence(formationID);
							const bool isSetItem = ((formationID != 0) && !isEnemyExistence) || isHavingItems;
							if (isSetItem) { _itemManager.RegisterOnList(enemy->GetPos()); }

							//	�G�l�~�[�ɂ��q�b�g����
							enemy->SetIsHit(true);

							//	�q�b�g�����̂ŁA
							//	�V���b�g�̃��[�h��ύX
							stayShot->SetIsChangeStay(true);

							//	�Q�[�W�̉��Z
							_gaugeUI.AddGauge(_gaugeUI.ADD_GAUGE_KIND::ENEMY);

							//	�X�R�A�̉��Z
							SCORE->AddScore(SCORE->ADD_SCORE::ADD_SCORE_ENEMY);
						}
					}
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�؍ݒe�ƒ��{�X�̓����蔻��
//-----------------------------------------------------------------------------
void HitChecker::PlayerStayShotToMediumBoss(StayShotManager& _stayShotManager, BossManager& _bossManager, UIGauge& _gaugeUI)
{
	for (int i = 0; i < _stayShotManager.GetListSize(); i++)
	{
		//	�V���b�g�̃|�C���^�̎擾
		StayShot* stayShot = _stayShotManager.GetStayShotPtr(i);

		//	���{�X�̃|�C���^�̎擾
		MediumBoss* mediumBoss = _bossManager.GetMediumBoss();

		//	�|�C���^�����݂���Ȃ�
		if (stayShot && mediumBoss)
		{
			//	�I�u�W�F�N�g�Ԃ̋����𑪂�
			//	true �̂Ƃ��̂݁A�����蔻��̌v�Z���s��
			const bool isActive = _AskObjectLenght(stayShot->GetPos(), mediumBoss->GetPos());
			if (isActive)
			{
				//	�����蔻��
				const bool isHit = _CircleHitCheck(stayShot->GetCircle(), mediumBoss->GetCircle());
				if (isHit)
				{
					//	�q�b�g�����̂ŁA
					//	�v���C���[�̒e�����X�g����폜���A
					//	�{�X�Ƀ_���[�W��^����

					//	�{�X���_���[�W���󂯂��ꍇ�A
					//	�A�����ē���Ȃ��悤�ɐ���
					if (!mediumBoss->GetIsDamage())
					{
						//	�{�X�Ƀ_���[�W��^���A
						//	�{�X��_�ł�����
						mediumBoss->OnHitDamage();
					}

					//	�q�b�g�����̂ŁA
					//	�V���b�g�̃��[�h��ύX
					stayShot->SetIsChangeStay(true);

					//	�Q�[�W�̉��Z
					const bool isDamageMoment = !mediumBoss->GetIsDamage();
					if (isDamageMoment) { _gaugeUI.AddGauge(_gaugeUI.ADD_GAUGE_KIND::BOSS); }
				}

			}
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�؍ݒe�ƍŏI�{�X�̓����蔻��
//-----------------------------------------------------------------------------
void HitChecker::PlayerStayShotToLastBoss(PlayerManager& _playerManager, StayShotManager& _stayShotManager, BossManager& _bossManager, UIGauge& _gaugeUI)
{
	static const int right = 0;
	static const int left = 1;

	for (int i = 0; i < _stayShotManager.GetListSize(); i++)
	{
		//	�V���b�g�̃|�C���^�̎擾
		StayShot* stayShot = _stayShotManager.GetStayShotPtr(i);

		//	�ŏI�{�X�̃|�C���^�̎擾
		LastBoss* lastBoss = _bossManager.GetLastBossPtr();

		//	�|�C���^�����݂���Ȃ�
		if (stayShot && lastBoss)
		{
			//	�����蔻��
			const bool isCoreActive = lastBoss->GetIsRightCoreAlive() || lastBoss->GetIsRightCoreAlive();
			const bool isHitBody = _CircleHitCheck(stayShot->GetCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_BODY)) && isCoreActive;
			const bool isHitArmRight = _CircleHitCheck(stayShot->GetCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_ARM, right)) && lastBoss->GetIsRightCoreAlive();
			const bool isHitArmLeft = _CircleHitCheck(stayShot->GetCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_ARM, left)) && lastBoss->GetIsLeftCoreAlive();
			const bool isHitCenterBarrel = _BoxHitCheck(stayShot->GetRect(), lastBoss->GetCenterBarrelRect()) && isCoreActive;
			const bool isHitOnly = isHitBody || isHitArmRight || isHitArmLeft || isHitCenterBarrel;
			if (isHitOnly)
			{
				//	�q�b�g�����̂ŁA
				//	�V���b�g�̃��[�h��ύX
				stayShot->SetIsChangeStay(true);
			}

			const bool isHitCoreRight = _CircleHitCheck(stayShot->GetCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_CORE, right)) && lastBoss->GetIsRightCoreAlive();
			if (isHitCoreRight)
			{
				//	�Q�[�W�̉��Z
				const bool isDamageMoment = !lastBoss->GetIsCoreDamage(right);
				if (isDamageMoment) { _gaugeUI.AddGauge(_gaugeUI.ADD_GAUGE_KIND::BOSS); }

				//	�{�X�̃p�[�c�Ƀ_���[�W��^����
				lastBoss->OnHitCoreDamage(right);

				//	�q�b�g�����̂ŁA
				//	�V���b�g�̃��[�h��ύX
				stayShot->SetIsChangeStay(true);
			}

			const bool isHitCoreLeft = _CircleHitCheck(stayShot->GetCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_CORE, left)) && lastBoss->GetIsLeftCoreAlive();
			if (isHitCoreLeft)
			{
				//	�Q�[�W�̉��Z
				const bool isDamageMoment = !lastBoss->GetIsCoreDamage(left);
				if (isDamageMoment) { _gaugeUI.AddGauge(_gaugeUI.ADD_GAUGE_KIND::BOSS); }

				//	�{�X�̃p�[�c�Ƀ_���[�W��^����
				lastBoss->OnHitCoreDamage(left);

				//	�q�b�g�����̂ŁA
				//	�V���b�g�̃��[�h��ύX
				stayShot->SetIsChangeStay(true);
			}

			const bool isHitSideBarrelRight = _CircleHitCheck(stayShot->GetCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_SIDE_BARREL, right)) && lastBoss->GetIsRightSideBarrelAlive();
			if (isHitSideBarrelRight)
			{
				//	�Q�[�W�̉��Z
				const bool isDamageMoment = !lastBoss->GetIsSideBarrelDamage(right);
				if (isDamageMoment) { _gaugeUI.AddGauge(_gaugeUI.ADD_GAUGE_KIND::BOSS); }

				//	�{�X�̃p�[�c�Ƀ_���[�W��^����
				lastBoss->OnHitSideBarrelDamage(right);

				//	�q�b�g�����̂ŁA
				//	�V���b�g�̃��[�h��ύX
				stayShot->SetIsChangeStay(true);

			}

			const bool isHitSideBarrelLeft = _CircleHitCheck(stayShot->GetCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_SIDE_BARREL, left)) && lastBoss->GetIsLeftSideBarrelAlive();
			if (isHitSideBarrelLeft)
			{
				//	�Q�[�W�̉��Z
				const bool isDamageMoment = !lastBoss->GetIsSideBarrelDamage(left);
				if (isDamageMoment) { _gaugeUI.AddGauge(_gaugeUI.ADD_GAUGE_KIND::BOSS); }

				//	�{�X�̃p�[�c�Ƀ_���[�W��^����
				lastBoss->OnHitSideBarrelDamage(left);

				//	�q�b�g�����̂ŁA
				//	�V���b�g�̃��[�h��ύX
				stayShot->SetIsChangeStay(true);
			}

			//	�{�X�̔j���
			lastBoss->DestructionSituation();

			//	���ׂĔj��
			const bool isAllDestruction = lastBoss->GetIsAllDestruction();
			if (isAllDestruction) { _playerManager.SetIsClear(true); }
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�ƃA�C�e���̓����蔻��
//-----------------------------------------------------------------------------
void HitChecker::PlayerToItem(PlayerManager& _playerManager, ItemManager& _itemManager, SoundEffect& _soundEffect, UIGauge& _gaugeUI)
{
	//	�v���C���[�̃|�C���^�̎擾
	PlayerBase* player = _playerManager.GetPlayerPtr();

	for (int i = 0; i < _itemManager.GetListSize(); i++)
	{
		//	�A�C�e���̃|�C���^�̎擾
		Item* item = _itemManager.GetItemPtr(i);

		//	�|�C���^�����݂���Ȃ�
		if (player && item)
		{
			//	�I�u�W�F�N�g�Ԃ̋����𑪂�
			//	true �̂Ƃ��̂݁A�����蔻��̌v�Z���s��
			const bool isActive = _AskObjectLenght(player->GetPos(), item->GetPos());
			if (isActive)
			{
				//	�����蔻��
				const bool isHit = _BoxHitCheck(player->GetItemHitRect(), item->GetRect());
				if (isHit)
				{
					//	�q�b�g�����̂ŁA
					//	�A�C�e���J�E���^�𑝂₵�A
					//	�A�C�e���̓��X�g����폜����

					//	�A�C�e���擾�G�t�F�N�g���J�n���Ă��Ȃ��Ƃ���
					//	�G�t�F�N�g���Đ�����
					const bool isNotStartEffect = !player->GetIsStartEffectGetItem();
					if(isNotStartEffect) { player->SetIsStartEffectGetItem(true); }

					//	�A�C�e�������X�g����폜����
					_itemManager.RemoveFromList(item);

					//	SE
					_soundEffect.OnPlaySound(_soundEffect.SE_KIND::SE_ITEM);

					//	�Q�[�W�̉��Z
					_gaugeUI.AddGauge(_gaugeUI.ADD_GAUGE_KIND::ITEM);

					//	�X�R�A�̉��Z
					SCORE->AddScore(SCORE->ADD_SCORE::ADD_SCORE_ITEM);
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�̕K�E�Z�Ƃ��ׂĂ̓����蔻��
//-----------------------------------------------------------------------------
void HitChecker::PlayerSpecialAttackToAllObject(PlayerManager& _playerManager, EnemyManager& _enemyManager, BossManager& _bossManager, ShotManager& _shotManager, ItemManager& _itemManager)
{
	//	�K�E�Z�̂Ƃ�
	const bool isSpecialProductionHitActive = PRODUCTION->GetIsSpecialProduction();
	if (isSpecialProductionHitActive)
	{
		//	�v���C���[�̎擾
		PlayerBase* player = _playerManager.GetPlayerPtr();

		const int size = _enemyManager.GetListSize();
		for (int i = 0; i < size; i++)
		{
			//	�G�l�~�[�̃|�C���^�̎擾
			EnemyBase* enemy = _enemyManager.GetEnemyPtr(i);
			if (player && enemy)
			{
				//	�G�l�~�[���q�b�g���Ă��Ȃ��Ƃ�
				const bool isNotDamage = !enemy->GetIsHIt();
				if (isNotDamage)
				{
					//	�����蔻��
					const bool isHit = _BoxHitCheck(player->GetLaserHitRect(), enemy->GetRect());
					if (isHit)
					{
						//	���񂩂�폜
						const int formationID = enemy->GetFormationID();
						_enemyManager.SubEnemyCount(formationID);

						//	�A�C�e���������Ă���Ƃ����A
						//	��������ׂē|������A
						//	�A�C�e���𐶐�
						const bool isHavingItems = enemy->GetIsHavingItems();
						const bool isEnemyExistence = _enemyManager.GetIsEnemyExistence(formationID);
						const bool isSetItem = ((formationID != 0) && !isEnemyExistence) || isHavingItems;
						if (isSetItem) { _itemManager.RegisterOnList(enemy->GetPos()); }

						//	�G�l�~�[�ɂ��q�b�g����
						enemy->SetIsHit(true);

						//	�X�R�A�̉��Z
						SCORE->AddScore(SCORE->ADD_SCORE::ADD_SCORE_ENEMY);
					}
				}
			}
		}

		//	���{�X�̃|�C���^�̎擾
		MediumBoss* mediumBoss = _bossManager.GetMediumBoss();
		if (player && mediumBoss)
		{
			//	�{�X���o�����Ă���Ȃ�
			const bool isMediumBossEmerge = mediumBoss->GetIsEmerge() || mediumBoss->GetIsStarted();
			if (isMediumBossEmerge)
			{
				//	�����蔻��
				const bool isHit = _BoxHitCheck(player->GetLaserHitRect(), mediumBoss->GetRect());
				if (isHit)
				{
					//	�_���[�W��^����
					mediumBoss->OnHitDamage();
				}
			}
		}

		//	�ŏI�{�X�̃|�C���^�̎擾
		LastBoss* lastBoss = _bossManager.GetLastBossPtr();
		if (player && lastBoss)
		{
			const int right = 0;
			const int left = 1;

			const bool isHitCoreRight = _BoxHitCheck(player->GetLaserHitRect(), lastBoss->GetCoreRect(right)) && lastBoss->GetIsRightCoreAlive();
			if (isHitCoreRight)
			{
				//	�{�X�̃p�[�c�Ƀ_���[�W��^����
				lastBoss->OnHitCoreDamage(right);
			}

			const bool isHitCoreLeft = _BoxHitCheck(player->GetLaserHitRect(), lastBoss->GetCoreRect(left)) && lastBoss->GetIsLeftCoreAlive();
			if (isHitCoreLeft)
			{
				//	�{�X�̃p�[�c�Ƀ_���[�W��^����
				lastBoss->OnHitCoreDamage(left);
			}

			const bool isHitSideBarrelRight = _BoxHitCheck(player->GetLaserHitRect(), lastBoss->GetSideBarrelRect(right)) && lastBoss->GetIsRightSideBarrelAlive();
			if (isHitSideBarrelRight)
			{
				//	�{�X�̃p�[�c�Ƀ_���[�W��^����
				lastBoss->OnHitSideBarrelDamage(right);
			}

			const bool isHitSideBarrelLeft = _BoxHitCheck(player->GetLaserHitRect(), lastBoss->GetSideBarrelRect(left)) && lastBoss->GetIsLeftSideBarrelAlive();
			if (isHitSideBarrelLeft)
			{
				//	�{�X�̃p�[�c�Ƀ_���[�W��^����
				lastBoss->OnHitSideBarrelDamage(left);
			}
		}

		//	�G�̒e�����ׂď���
		for (int i = 0; i < _shotManager.GetListSize(ShotManager::SHOT_KIND::ENEMY_SHOT); i++)
		{
			//	�V���b�g�̃|�C���^�̎擾
			Shot* shot = _shotManager.GetShotPtr(ShotManager::SHOT_KIND::ENEMY_SHOT, i);

			//	�|�C���^�����݂���Ȃ�
			if (shot)
			{
				//	�G�l�~�[�̒e�����X�g����폜����
				_shotManager.RemoveFromList(ShotManager::SHOT_KIND::ENEMY_SHOT, shot);
			}
		}
	}

	//	�ŏI�{�X�̃|�C���^�̎擾
	LastBoss* lastBoss = _bossManager.GetLastBossPtr();
	if (lastBoss)
	{
		//	�{�X�̔j���
		lastBoss->DestructionSituation();

		//	���ׂĔj��
		const bool isAllDestruction = lastBoss->GetIsAllDestruction();
		if (isAllDestruction) { _playerManager.SetIsClear(true); }
	}
}


//=============================================================================
//	@brief	�ȉ��A�f�o�b�O�p�̓����蔻��̕`��֐�
//=============================================================================


//-----------------------------------------------------------------------------
//	@brief	�v���C���[�ƃG�l�~�[�̓����蔻��̕`��
//-----------------------------------------------------------------------------
void HitChecker::PlayerToEnemyOfDraw(PlayerManager& _playerManager, EnemyManager& _enemyManager)
{
	//	�v���C���[�̃|�C���^�̎擾
	PlayerBase* player = _playerManager.GetPlayerPtr();

	for (int i = 0; i < _enemyManager.GetListSize(); i++)
	{
		//	�G�l�~�[�̃|�C���^�̎擾
		EnemyBase* enemy = _enemyManager.GetEnemyPtr(i);

		//	�|�C���^�����݂���Ȃ�
		if (player && enemy)
		{
			//	�����蔻��̕`��
			_CircleHitCheckOfDraw(player->GetCircle(), enemy->GetCircle());
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�ƒ��{�X�̓����蔻��̕`��
//-----------------------------------------------------------------------------
void HitChecker::PlayerToMediumBossOfDraw(PlayerManager& _playerManager, BossManager& _bossManager)
{
	//	�v���C���[�̃|�C���^�̎擾
	PlayerBase* player = _playerManager.GetPlayerPtr();

	//	���{�X�̃|�C���^�̎擾
	MediumBoss* mediumBoss = _bossManager.GetMediumBoss();

	//	�|�C���^�����݂���Ȃ�
	if (player && mediumBoss)
	{
		//	�����蔻��̕`��
		_CircleHitCheckOfDraw(player->GetCircle(), mediumBoss->GetCircle());
	}
}

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�ƍŏI�{�X�̓����蔻��̕`��
//-----------------------------------------------------------------------------
void HitChecker::PlayerToLastBossOfDraw(PlayerManager& _playerManager, BossManager& _bossManager)
{
	//	�v���C���[�̃|�C���^�̎擾
	PlayerBase* player = _playerManager.GetPlayerPtr();

	//	�ŏI�{�X�̃|�C���^�̎擾
	LastBoss* lastBoss = _bossManager.GetLastBossPtr();

	//	�|�C���^�����݂���Ȃ�
	if (player && lastBoss)
	{
		if (lastBoss->GetIsAppearance())
		{
			//	�����蔻��̕`��
			_BoxHitCheckOfDraw(player->GetRect(), lastBoss->GetCenterBarrelRect());
			_CircleHitCheckOfDraw(player->GetCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_BODY));

			if (lastBoss->GetIsLeftCoreAlive())
			{
				DrawSphere3D(lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_CORE, 1).m_centerPoint, lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_CORE, 1).m_radius, 5, 0x00ffff, 0x00ffff, false);
				DrawSphere3D(lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_ARM, 1).m_centerPoint, lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_ARM, 1).m_radius, 5, 0x00ffff, 0x00ffff, false);
				_BoxHitCheckOfDraw(lastBoss->GetLaserRect(1), lastBoss->GetArmRect(1));
			}

			if (lastBoss->GetIsRightCoreAlive())
			{
				DrawSphere3D(lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_CORE, 0).m_centerPoint, lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_CORE, 0).m_radius, 5, 0x00ffff, 0x00ffff, false);
				DrawSphere3D(lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_ARM, 0).m_centerPoint, lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_ARM, 0).m_radius, 5, 0x00ffff, 0x00ffff, false);
				_BoxHitCheckOfDraw(lastBoss->GetLaserRect(0), lastBoss->GetArmRect(0));
			}

			if (lastBoss->GetIsRightSideBarrelAlive())
			{
				DrawSphere3D(lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_SIDE_BARREL, 0).m_centerPoint, lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_SIDE_BARREL, 0).m_radius, 5, 0x00ffff, 0x00ffff, false);
			}

			if (lastBoss->GetIsLeftSideBarrelAlive())
			{
				DrawSphere3D(lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_SIDE_BARREL, 1).m_centerPoint, lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_SIDE_BARREL, 1).m_radius, 5, 0x00ffff, 0x00ffff, false);
			}
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�ƃG�l�~�[�̒e�̓����蔻��̕`��
//-----------------------------------------------------------------------------
void HitChecker::PlayerToEnemyShotOfDraw(PlayerManager& _playerManager, ShotManager& _shotManager)
{
	//	�v���C���[�̃|�C���^�̎擾
	PlayerBase* player = _playerManager.GetPlayerPtr();

	for (int i = 0; i < _shotManager.GetListSize(ShotManager::SHOT_KIND::ENEMY_SHOT); i++)
	{
		//	�V���b�g�̃|�C���^�̎擾
		Shot* shot = _shotManager.GetShotPtr(ShotManager::SHOT_KIND::ENEMY_SHOT, i);

		//	�|�C���^�����݂���Ȃ�
		if (player && shot)
		{
			//	�����蔻��̕`��
			_CircleHitCheckOfDraw(player->GetCircle(), shot->GetCircle());
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�̒e�ƃG�l�~�[�̓����蔻��̕`��
//-----------------------------------------------------------------------------
void HitChecker::PlayerShotToEnemyOfDraw(ShotManager& _shotManager, EnemyManager& _enemyManager)
{
	for (int i = 0; i < _shotManager.GetListSize(ShotManager::SHOT_KIND::PLAYER_SHOT); i++)
	{
		//	�V���b�g�̃|�C���^�̎擾
		Shot* shot = _shotManager.GetShotPtr(ShotManager::SHOT_KIND::PLAYER_SHOT, i);

		for (int j = 0; j < _enemyManager.GetListSize(); j++)
		{
			//	�G�l�~�[�̃|�C���^�̎擾
			EnemyBase* enemy = _enemyManager.GetEnemyPtr(j);

			//	�|�C���^�����݂���Ȃ�
			if (shot && enemy)
			{
				//	�����蔻��̕`��
				_CircleHitCheckOfDraw(shot->GetCircle(), enemy->GetCircle());
			}
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�̒e�ƒ��{�X�̓����蔻��̕`��
//-----------------------------------------------------------------------------
void HitChecker::PlayerShotToMediumBossOfDraw(ShotManager& _shotManager, BossManager& _bossManager)
{
	for (int i = 0; i < _shotManager.GetListSize(ShotManager::SHOT_KIND::PLAYER_SHOT); i++)
	{
		//	�V���b�g�̃|�C���^�̎擾
		Shot* shot = _shotManager.GetShotPtr(ShotManager::SHOT_KIND::PLAYER_SHOT, i);

		//	���{�X�̃|�C���^�̎擾
		MediumBoss* mediumBoss = _bossManager.GetMediumBoss();

		//	�|�C���^�����݂���Ȃ�
		if (shot && mediumBoss)
		{
			//	�����蔻��̕`��
			_CircleHitCheckOfDraw(shot->GetCircle(), mediumBoss->GetCircle());
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�̒e�ƍŏI�{�X�̓����蔻��̕`��
//-----------------------------------------------------------------------------
void HitChecker::PlayerShotToLastBossOfDraw(ShotManager& _shotManager, BossManager& _bossManager)
{
	for (int i = 0; i < _shotManager.GetListSize(ShotManager::SHOT_KIND::PLAYER_SHOT); i++)
	{
		//	�V���b�g�̃|�C���^�̎擾
		Shot* shot = _shotManager.GetShotPtr(ShotManager::SHOT_KIND::PLAYER_SHOT, i);

		//	�ŏI�{�X�̃|�C���^�̎擾
		LastBoss* lastBoss = _bossManager.GetLastBossPtr();

		//	�|�C���^�����݂���Ȃ�
		if (shot && lastBoss)
		{
			if (lastBoss->GetIsAppearance())
			{
				//	�����蔻��̕`��
				DrawCube3D(shot->GetRect().m_vertexTop, shot->GetRect().m_vertexUnder, 5, GetColor(255, 255, 255), false);
				_CircleHitCheckOfDraw(shot->GetCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_BODY));

				if (lastBoss->GetIsLeftCoreAlive())
				{
					DrawSphere3D(lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_CORE, 1).m_centerPoint, lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_CORE, 1).m_radius, 5, 0x00ffff, 0x00ffff, false);
					DrawSphere3D(lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_ARM, 1).m_centerPoint, lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_ARM, 1).m_radius, 5, 0x00ffff, 0x00ffff, false);
					_BoxHitCheckOfDraw(lastBoss->GetLaserRect(1), lastBoss->GetArmRect(1));
				}

				if (lastBoss->GetIsRightCoreAlive())
				{
					DrawSphere3D(lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_CORE, 0).m_centerPoint, lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_CORE, 0).m_radius, 5, 0x00ffff, 0x00ffff, false);
					DrawSphere3D(lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_ARM, 0).m_centerPoint, lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_ARM, 0).m_radius, 5, 0x00ffff, 0x00ffff, false);
					_BoxHitCheckOfDraw(lastBoss->GetLaserRect(0), lastBoss->GetArmRect(0));
				}

				if (lastBoss->GetIsRightSideBarrelAlive())
				{
					DrawSphere3D(lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_SIDE_BARREL, 0).m_centerPoint, lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_SIDE_BARREL, 0).m_radius, 5, 0x00ffff, 0x00ffff, false);
				}

				if (lastBoss->GetIsLeftSideBarrelAlive())
				{
					DrawSphere3D(lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_SIDE_BARREL, 1).m_centerPoint, lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_SIDE_BARREL, 1).m_radius, 5, 0x00ffff, 0x00ffff, false);
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�؍ݒe�ƃG�l�~�[�̓����蔻��
//-----------------------------------------------------------------------------
void HitChecker::PlayerStayShotToEnemyOfDraw(StayShotManager& _stayShotManager, EnemyManager& _enemyManager)
{
	for (int i = 0; i < _stayShotManager.GetListSize(); i++)
	{
		//	�V���b�g�̃|�C���^�̎擾
		StayShot* stayShot = _stayShotManager.GetStayShotPtr(i);

		for (int j = 0; j < _enemyManager.GetListSize(); j++)
		{
			//	�G�l�~�[�̃|�C���^�̎擾
			EnemyBase* enemy = _enemyManager.GetEnemyPtr(j);

			//	�|�C���^�����݂���Ȃ�
			if (stayShot && enemy)
			{
				//	�����蔻��̕`��
				_CircleHitCheckOfDraw(stayShot->GetCircle(), enemy->GetCircle());
			}
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�؍ݒe�ƒ��{�X�̓����蔻��
//-----------------------------------------------------------------------------
void HitChecker::PlayerStayShotToMediumBossOfDraw(StayShotManager& _stayShotManager, BossManager& _bossManager)
{
	for (int i = 0; i < _stayShotManager.GetListSize(); i++)
	{
		//	�V���b�g�̃|�C���^�̎擾
		StayShot* stayShot = _stayShotManager.GetStayShotPtr(i);

		//	���{�X�̃|�C���^�̎擾
		MediumBoss* mediumBoss = _bossManager.GetMediumBoss();

		//	�|�C���^�����݂���Ȃ�
		if (stayShot && mediumBoss)
		{
			//	�����蔻��̕`��
			_CircleHitCheckOfDraw(stayShot->GetCircle(), mediumBoss->GetCircle());
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�؍ݒe�ƍŏI�{�X�̓����蔻��̕`��
//-----------------------------------------------------------------------------
void HitChecker::PlayerStayShotToLastBossOfDraw(StayShotManager& _stayShotManager, BossManager& _bossManager)
{
	for (int i = 0; i < _stayShotManager.GetListSize(); i++)
	{
		//	�V���b�g�̃|�C���^�̎擾
		StayShot* stayShot = _stayShotManager.GetStayShotPtr(i);

		//	�ŏI�{�X�̃|�C���^�̎擾
		LastBoss* lastBoss = _bossManager.GetLastBossPtr();

		//	�|�C���^�����݂���Ȃ�
		if (stayShot && lastBoss)
		{
			if (lastBoss->GetIsAppearance())
			{
				//	�����蔻��̕`��
				DrawCube3D(stayShot->GetRect().m_vertexTop, stayShot->GetRect().m_vertexUnder, 5, GetColor(255, 255, 255), false);
				_CircleHitCheckOfDraw(stayShot->GetCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_BODY));

				if (lastBoss->GetIsLeftCoreAlive())
				{
					DrawSphere3D(lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_CORE, 1).m_centerPoint, lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_CORE, 1).m_radius, 5, 0x00ffff, 0x00ffff, false);
					DrawSphere3D(lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_ARM, 1).m_centerPoint, lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_ARM, 1).m_radius, 5, 0x00ffff, 0x00ffff, false);
					_BoxHitCheckOfDraw(lastBoss->GetLaserRect(1), lastBoss->GetArmRect(1));
				}

				if (lastBoss->GetIsRightCoreAlive())
				{
					DrawSphere3D(lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_CORE, 0).m_centerPoint, lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_CORE, 0).m_radius, 5, 0x00ffff, 0x00ffff, false);
					DrawSphere3D(lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_ARM, 0).m_centerPoint, lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_ARM, 0).m_radius, 5, 0x00ffff, 0x00ffff, false);
					_BoxHitCheckOfDraw(lastBoss->GetLaserRect(0), lastBoss->GetArmRect(0));
				}

				if (lastBoss->GetIsRightSideBarrelAlive())
				{
					DrawSphere3D(lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_SIDE_BARREL, 0).m_centerPoint, lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_SIDE_BARREL, 0).m_radius, 5, 0x00ffff, 0x00ffff, false);
				}

				if (lastBoss->GetIsLeftSideBarrelAlive())
				{
					DrawSphere3D(lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_SIDE_BARREL, 1).m_centerPoint, lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_SIDE_BARREL, 1).m_radius, 5, 0x00ffff, 0x00ffff, false);
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�ƃA�C�e���̓����蔻��̕`��
//-----------------------------------------------------------------------------
void HitChecker::PlayerToItemOfDraw(PlayerManager& _playerManager, ItemManager& _item)
{
	//	�v���C���[�̃|�C���^�̎擾
	PlayerBase* player = _playerManager.GetPlayerPtr();

	for (int i = 0; i < _item.GetListSize(); i++)
	{
		//	�A�C�e���̃|�C���^�̎擾
		Item* item = _item.GetItemPtr(i);

		//	�|�C���^�����݂���Ȃ�
		if (player && item)
		{
			//	�����蔻��̕`��
			_BoxHitCheckOfDraw(player->GetItemHitRect(), item->GetRect());
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�̕K�E�Z�Ƃ��ׂĂ̓����蔻��̕`��
//-----------------------------------------------------------------------------
void HitChecker::PlayerSpecialAttackToAllObjectOfDraw(PlayerManager& _playerManager, EnemyManager& _enemyManager, BossManager& _bossManager)
{
	//	�v���C���[�̃|�C���^�̎擾
	PlayerBase* player = _playerManager.GetPlayerPtr();

	const int size = _enemyManager.GetListSize();
	for (int i = 0; i < size; i++)
	{
		//	�G�l�~�[�̃|�C���^�̎擾
		EnemyBase* enemy = _enemyManager.GetEnemyPtr(i);

		//	�|�C���^�����݂���Ȃ�
		if (player && enemy)
		{
			//	�����蔻��̕`��
			_BoxHitCheckOfDraw(player->GetLaserHitRect(), enemy->GetRect());
		}
	}

	//	���{�X�̃|�C���^�̎擾
	MediumBoss* mediumBoss = _bossManager.GetMediumBoss();

	//	�|�C���^�����݂���Ȃ�
	if (player && mediumBoss)
	{
		//	�����蔻��̕`��
		_BoxHitCheckOfDraw(player->GetLaserHitRect(), mediumBoss->GetRect());
	}

	LastBoss* lastBoss = _bossManager.GetLastBossPtr();
	if (player && lastBoss)
	{
		if (lastBoss->GetIsAppearance())
		{
			//	�����蔻��̕`��
			//_CircleHitCheckOfDraw(player->GetLaserCircle(), lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_BODY));

			if (lastBoss->GetIsLeftCoreAlive())
			{
				DrawSphere3D(lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_CORE, 1).m_centerPoint, lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_CORE, 1).m_radius, 5, 0x00ffff, 0x00ffff, false);
				DrawSphere3D(lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_ARM, 1).m_centerPoint, lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_ARM, 1).m_radius, 5, 0x00ffff, 0x00ffff, false);
				_BoxHitCheckOfDraw(lastBoss->GetLaserRect(1), lastBoss->GetArmRect(1));
			}

			if (lastBoss->GetIsRightCoreAlive())
			{
				DrawSphere3D(lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_CORE, 0).m_centerPoint, lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_CORE, 0).m_radius, 5, 0x00ffff, 0x00ffff, false);
				DrawSphere3D(lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_ARM, 0).m_centerPoint, lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_ARM, 0).m_radius, 5, 0x00ffff, 0x00ffff, false);
				_BoxHitCheckOfDraw(lastBoss->GetLaserRect(0), lastBoss->GetArmRect(0));
			}

			if (lastBoss->GetIsRightSideBarrelAlive())
			{
				DrawSphere3D(lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_SIDE_BARREL, 0).m_centerPoint, lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_SIDE_BARREL, 0).m_radius, 5, 0x00ffff, 0x00ffff, false);
			}

			if (lastBoss->GetIsLeftSideBarrelAlive())
			{
				DrawSphere3D(lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_SIDE_BARREL, 1).m_centerPoint, lastBoss->GetCircle(lastBoss->BOSS_PARTS_KIND::BOSS_PARTS_KIND_SIDE_BARREL, 1).m_radius, 5, 0x00ffff, 0x00ffff, false);
			}
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�I�u�W�F�N�g�Ԃ̋����𑪂�
//-----------------------------------------------------------------------------
bool HitChecker::_AskObjectLenght(const VECTOR _pos1, const VECTOR _pos2)
{
	//	�^�[�Q�b�g�܂ł̃x�N�g�������߂�
	VECTOR targetVec = VSub(_pos1, _pos2);
	float targetLen = VSize(targetVec);

	//	�^�[�Q�b�g�Ԃ̋���������菬�����Ȃ�����A
	//	�����蔻����s��
	return (targetLen <= ACTIVE_LENGHT);
}

//-----------------------------------------------------------------------------
//	@brief	�~�`���m�̓����蔻��
//-----------------------------------------------------------------------------
bool HitChecker::_CircleHitCheck(Circle _target1, Circle _target2)
{
	//	�����̌v�Z
	VECTOR distance = VSub(_target1.m_centerPoint, _target2.m_centerPoint);

	//	���������a��菬�����Ƃ��͓�����
	if (VSize(distance) < (_target1.m_radius + _target2.m_radius)) { return true; }
	return false;
}

//-----------------------------------------------------------------------------
//	@brief	��`���m�̓����蔻��
//-----------------------------------------------------------------------------
bool HitChecker::_BoxHitCheck(Rect _target1, Rect _target2)
{
	//	XY���œ����蔻��
	const bool isHitAxisXY = ((_target1.m_vertexTop.x <= _target2.m_vertexUnder.x) &&
		(_target1.m_vertexTop.y <= _target2.m_vertexUnder.y) &&
		(_target1.m_vertexUnder.x >= _target2.m_vertexTop.x) &&
		(_target1.m_vertexUnder.y >= _target2.m_vertexTop.y));

	//	XZ���œ����蔻��
	const bool isHitAxisXZ = ((_target1.m_vertexTop.x <= _target2.m_vertexUnder.x) &&
		(_target1.m_vertexTop.z <= _target2.m_vertexUnder.z) &&
		(_target1.m_vertexUnder.x >= _target2.m_vertexTop.x) &&
		(_target1.m_vertexUnder.z >= _target2.m_vertexTop.z));

	//	�n�ʂƂ̐ڐG����
	return  isHitAxisXY && isHitAxisXZ;
}

//-----------------------------------------------------------------------------
//	@brief	�~�`���m�̓����蔻��̕`��
//-----------------------------------------------------------------------------
void HitChecker::_CircleHitCheckOfDraw(Circle _target1, Circle _target2)
{
	//	�^�[�Q�b�g�P�̕`��
	DrawSphere3D(_target1.m_centerPoint, _target1.m_radius, 5, 0x00ffff, 0x00ffff, false);

	//	�^�[�Q�b�g�Q�̕`��
	DrawSphere3D(_target2.m_centerPoint, _target2.m_radius, 5, 0x00ffff, 0x00ffff, false);
}

//-----------------------------------------------------------------------------
//	@brief	��`���m�̓����蔻��̕`��
//-----------------------------------------------------------------------------
void HitChecker::_BoxHitCheckOfDraw(Rect _target1, Rect _target2)
{
	//	�^�[�Q�b�g�P�̕`��
	DrawCube3D(_target1.m_vertexTop, _target1.m_vertexUnder, 5, GetColor(255, 255, 255), false);

	//	�^�[�Q�b�g�Q�̕`��
	DrawCube3D(_target2.m_vertexTop, _target2.m_vertexUnder, 5, GetColor(255, 255, 255), false);
}
