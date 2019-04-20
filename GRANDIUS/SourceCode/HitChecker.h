
//=============================================================================
//	@file	HitChecker.h
//	@brief	�q�b�g�`�F�b�J�[
//	@autor	���m ���
//	@date	2018/12/13
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

//-----------------------------------------------------------------------------
//	@brief	�O���錾
//-----------------------------------------------------------------------------
class PlayerManager;
class EnemyManager;
class BossManager;
class ShotManager;
class StayShotManager;
class ItemManager;
class PlayerBase;
class EnemyBase;
class Shot;
class UILife;
class UIGauge;
class SoundEffect;

//-----------------------------------------------------------------------------
//	@brief	�q�b�g�`�F�b�J�[�N���X
//-----------------------------------------------------------------------------
class HitChecker final
{
public:

//==================== �񋓑� =====================//

	//	�����蔻��̎��
	enum HIT_CHECKER_KIND
	{
		CIRCLE,
		RECT,
	};

//===================== �֐� ======================//

	//	�v���C���[�ƃG�l�~�[�̓����蔻��
	static void PlayerToEnemy(PlayerManager& _playerManager, EnemyManager& _enemyManager, ItemManager& _itemManager);

	//	�v���C���[�ƒ��{�X�̓����蔻��
	static void PlayerToMediumBoss(PlayerManager& _playerManager, BossManager& _bossManager);

	//	�v���C���[�ƍŏI�{�X�̓����蔻��
	static void PlayerToLastBoss(PlayerManager& _playerManager, BossManager& _bossManager);


	//	�v���C���[�ƃG�l�~�[�̒e�̓����蔻��
	static void PlayerToEnemyShot(PlayerManager& _playerManager, ShotManager& _shotManager);


	//	�v���C���[�e�ƃG�l�~�[�̓����蔻��
	static void PlayerShotToEnemy(ShotManager& _shotManager, EnemyManager& _enemyManager, ItemManager& _itemManager, UIGauge& _gaugeUI);

	//	�v���C���[�e�ƒ��{�X�̓����蔻��
	static void PlayerShotToMediumBoss(ShotManager& _shotManager, BossManager& _bossManager, UIGauge& _gaugeUI);

	//	�v���C���[�e�ƍŏI�{�X�̓����蔻��
	static void PlayerShotToLastBoss(PlayerManager& _playerManager, ShotManager& _shotManager, BossManager& _bossManager, UIGauge& _gaugeUI);
	

	//	�v���C���[�؍ݒe�ƃG�l�~�[�̓����蔻��
	static void PlayerStayShotToEnemy(StayShotManager& _stayShotManager, EnemyManager& _enemyManager, ItemManager& _itemManager, UIGauge& _gaugeUI);

	//	�v���C���[�؍ݒe�ƒ��{�X�̓����蔻��
	static void PlayerStayShotToMediumBoss(StayShotManager& _stayShotManager, BossManager& _bossManager, UIGauge& _gaugeUI);

	//	�v���C���[�؍ݒe�ƍŏI�{�X�̓����蔻��
	static void PlayerStayShotToLastBoss(PlayerManager& _playerManager, StayShotManager& _stayShotManager, BossManager& _bossManager, UIGauge& _gaugeUI);


	//	�v���C���[�ƃA�C�e���̓����蔻��
	static void PlayerToItem(PlayerManager& _playerManager, ItemManager& _itemManager, SoundEffect& _soundEffect, UIGauge& _gaugeUI);


	//	�v���C���[�̕K�E�Z�Ƃ��ׂĂ̓����蔻��
	static void PlayerSpecialAttackToAllObject(PlayerManager& _playerManager, EnemyManager& _enemyManager, BossManager& _bossManager, ShotManager& _shotManager, ItemManager& _itemManager);


	//=============================================================================
	//	@brief	�ȉ��A�f�o�b�O�p�̓����蔻��̕`��֐�
	//=============================================================================


	//	�v���C���[�ƃG�l�~�[�̓����蔻��̕`��
	static void PlayerToEnemyOfDraw(PlayerManager& _playerManager, EnemyManager& _enemyManager);

	//	�v���C���[�ƒ��{�X�̓����蔻��̕`��
	static void PlayerToMediumBossOfDraw(PlayerManager& _playerManager, BossManager& _bossManager);

	//	�v���C���[�ƍŏI�{�X�̓����蔻��̕`��
	static void PlayerToLastBossOfDraw(PlayerManager& _playerManager, BossManager& _bossManager);


	//	�v���C���[�ƃG�l�~�[�̒e�̓����蔻��̕`��
	static void PlayerToEnemyShotOfDraw(PlayerManager& _playerManager, ShotManager& _shotManager);


	//	�v���C���[�̒e�ƃG�l�~�[�̓����蔻��̕`��
	static void PlayerShotToEnemyOfDraw(ShotManager& _shotManager, EnemyManager& _enemyManager);

	//	�v���C���[�̒e�ƒ��{�X�̓����蔻��̕`��
	static void PlayerShotToMediumBossOfDraw(ShotManager& _shotManager, BossManager& _bossManager);

	//	�v���C���[�e�ƍŏI�{�X�̓����蔻��̕`��
	static void PlayerShotToLastBossOfDraw(ShotManager& _shotManager, BossManager& _bossManager);


	//	�v���C���[�؍ݒe�ƃG�l�~�[�̓����蔻��̕`��
	static void PlayerStayShotToEnemyOfDraw(StayShotManager& _stayShotManager, EnemyManager& _enemyManager);

	//	�v���C���[�؍ݒe�ƒ��{�X�̓����蔻��̕`��
	static void PlayerStayShotToMediumBossOfDraw(StayShotManager& _stayShotManager, BossManager& _bossManager);

	//	�v���C���[�؍ݒe�ƍŏI�{�X�̓����蔻��̕`��
	static void PlayerStayShotToLastBossOfDraw(StayShotManager& _stayShotManager, BossManager& _bossManager);


	//	�v���C���[�ƃA�C�e���̓����蔻��̕`��
	static void PlayerToItemOfDraw(PlayerManager& _playerManager, ItemManager& _item);


	//	�v���C���[�̕K�E�Z�Ƃ��ׂĂ̓����蔻��̕`��
	static void PlayerSpecialAttackToAllObjectOfDraw(PlayerManager& _playerManager, EnemyManager& _enemyManager, BossManager& _bossManager);

private:

//================== ���������֐� ==================//

	//	�I�u�W�F�N�g�Ԃ̋����𑪂�
	static bool _AskObjectLenght(const VECTOR _pos1, const VECTOR _pos2);

	//	�~�`�̓����蔻��
	static bool _CircleHitCheck(Circle _target1, Circle _target2);

	//	��`�̓����蔻��
	static bool _BoxHitCheck(Rect _target1, Rect _target2);

	//	�~�`�̓����蔻��̕`��
	static void _CircleHitCheckOfDraw(Circle _target1, Circle _target2);

	//	��`�̓����蔻��̕`��
	static void _BoxHitCheckOfDraw(Rect _target1, Rect _target2);

//===================== �ÓI�萔 ===================//

	static const float ACTIVE_LENGHT;			//	�����蔻��̗L������

};
