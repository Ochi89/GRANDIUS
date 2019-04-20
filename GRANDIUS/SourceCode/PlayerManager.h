
//=============================================================================
//	@file	PlayerManager.cpp
//	@brief	�v���C���[�}�l�[�W���[
//	@autor	���m ���
//	@date	2018/11/14
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�v���v���Z�b�T
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "PlayerBase.h"

//-----------------------------------------------------------------------------
//	@brief	�O���錾
//-----------------------------------------------------------------------------
class Pad;
class PlayerBase;
class ShotManager;
class StayShotManager;
class UIGauge;
class SoundEffect;
class EnemyManager;

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�Ǘ��N���X
//-----------------------------------------------------------------------------
class PlayerManager final
{
public:

//==================== �񋓑� =====================//

    //	�V�[���̎��
    enum PLAYER_INFO
    {
        PLAYER_TITLE,		//	�^�C�g��
        PLAYER_GAME,		//	�Q�[��
        PLAYER_RESULT,		//	���U���g
        PLAYER_DEMO,		//	�f��
    };

//===================== �֐� ======================//

	//	�R���X�g���N�^ / �f�X�g���N�^
	PlayerManager();
	~PlayerManager();

	//	�쐬����
	void Create(PLAYER_INFO _playerInfo);

	//	�������
	void Release();	

	//	�X�V����
    void Update();
    void Update(Pad& _pad, ShotManager& _shot, StayShotManager& _stayShot, SoundEffect& _soundEffect, UIGauge& _gauge);
    void Update(ShotManager& _shot, StayShotManager& _stayShot, SoundEffect& _soundEffect, UIGauge& _gauge, EnemyManager& _enemyManager);

	//	�`�揈��
	void Draw();

//==================== getter =====================//

	//	�v���C���[�ւ̃|�C���^�� getter
	PlayerBase* GetPlayerPtr() { return m_pPlayer; }

	//	�N���A�������� getter
	const bool GetIsClear() const { return m_isClear; }

//==================== setter =====================//

	//	�N���A�������� setter
	void SetIsClear(const bool _set) { m_isClear = _set; }

	//	���o���t���O�� setter
	void SetIsProduction(const bool _set) { m_isProduction = _set; }

private:

//================== ���������֐� ==================//

	//	�ŏI�I�ȉ������
	void _FinalRelease();

//=================== �����o�ϐ� ===================//

	int				m_sourceModelHandle;	//	��{�n���h��
	PlayerBase*		m_pPlayer;				//	�v���C���[
	bool			m_isClear;				//	�N���A�t���O
	bool			m_isProduction;			//	���o���t���O
};