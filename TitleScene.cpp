#include "TitleScene.h"
#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>
#include<iostream>
#include<fstream>
#include<string>

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {
	delete model_;
	delete player_;
	delete debugCamera_;

	for (Enemy* enemy : enemys_) {
		delete enemy;
	}

	for (EnemyBullet* bullet : enemyBullets_) {
		delete bullet;
	}

	delete skydome_;
	delete skydomeModel_;
	delete railCamera_;
}

void TitleScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandle_ = TextureManager::Load("diamond.png");
	TextureManager::Load("reticle.png");
	model_ = Model::Create();

	worldTransform_.Initialize();
	viewProjection_.Initialize();

	// �f�o�b�O�J�����̐���
	debugCamera_ = new DebugCamera(1280, 720);

	input_ = Input::GetInstance();

	// �������\���̕\����L����
	AxisIndicator::GetInstance()->SetVisible(true);
	// �Q�Ƃ���r���[�v���W�F�N�V�������w��
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	// ���L�����̐���
	player_ = new Player();
	Vector3 playerPosition(0, 0, 30);
	player_->Initialize(model_, textureHandle_, playerPosition);

	// �V��
	skydomeModel_ = Model::CreateFromOBJ("skydome", true);
	skydome_ = new Skydome();
	skydome_->Initialize(skydomeModel_);

	// ���[���J����
	railCamera_ = new RailCamera();
	railCamera_->Initialize({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f});
	player_->Setparent(&railCamera_->GetWorldTransform());
}

void TitleScene::Update() {

	player_->Update(viewProjection_);

	skydome_->Update();

	debugCamera_->Update();

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_RETURN)) {
		if (isDebugCameraActive_ == false) {
			isDebugCameraActive_ = true;
		} else {
			isDebugCameraActive_ = false;
		}
	}
#endif
	// �J�����̏���
	if (isDebugCameraActive_) {
		// �f�o�b�O�J�����̍X�V
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// �r���[�v���W�F�N�V�����s��̓]��
		viewProjection_.TransferMatrix();
	} else {
		railCamera_->Update();
		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
		// �r���[�v���W�F�N�V�����s��̍X�V�Ɠ]��
		viewProjection_.TransferMatrix();
	}
	if (input_->TriggerKey(DIK_SPACE)) {
	
	}
}

void TitleScene::Draw() {

	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(commandList);

	/// <summary>
	/// �����ɔw�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
	// �[�x�o�b�t�@�N���A
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3D�I�u�W�F�N�g�`��
	// 3D�I�u�W�F�N�g�`��O����
	Model::PreDraw(commandList);

	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// </summary>

	for (Enemy* enemy : enemys_) {
		enemy->Draw(viewProjection_);
	}

	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Draw(viewProjection_);
	}

	player_->Draw(viewProjection_);
	skydome_->Draw(viewProjection_);

	// 3D�I�u�W�F�N�g�`��㏈��
	Model::PostDraw();
#pragma endregion

#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(commandList);

	/// <summary>
	/// �����ɑO�i�X�v���C�g�̕`�揈����ǉ��ł���
	player_->DrawUI();

	/// </summary>

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();

#pragma endregion
}
