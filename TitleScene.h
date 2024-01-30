#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "RailCamera.h"
#include "SafeDelete.h"
#include "Skydome.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <sstream>

/// <summary>
/// �Q�[���V�[��
/// </summary>
class TitleScene {

public: // �����o�֐�
	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	TitleScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TitleScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private: // �����o�ϐ�
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	uint32_t textureHandle_ = 0;
	Model* model_ = nullptr;

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	// �v���C���[
	Player* player_ = nullptr;

	// �f�o�b�O�J�����L����
	bool isDebugCameraActive_ = false;

	// �f�o�b�O�J����
	DebugCamera* debugCamera_ = nullptr;

	// �G�֘A�̃��X�g
	std::list<Enemy*> enemys_;
	std::list<EnemyBullet*> enemyBullets_;

	// �V��
	Skydome* skydome_;
	Model* skydomeModel_ = nullptr;

	// ���[���J����
	RailCamera* railCamera_;
	bool isWaitTime_;
	int32_t waitTimer_;

	/// <summary>
	/// �Q�[���V�[���p
	/// </summary>
};
