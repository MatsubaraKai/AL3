#include "Player.h"
#include "Matrix.h"
#include "TextureManager.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include <cassert>



// 初期化
void Player::Initialize(Model* model, uint32_t textureHandle) {
	//NULLポインタチェック
	assert(model);
	

	model_= model;
	textureHandle_= textureHandle;

	worldTransform_.Initialize();

	input_ = Input::GetInstance();
}




void Player::Update() { 
	worldTransform_.TransferMatrix();
	//キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};
	//キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;
	//押した方向で移動ベクトルを変換(左右)
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	//押した方向で移動ベクトルを変更(上下)
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	}

	float moves[3] = {move.x + 1, move.y + 1, move.z + 1};

	ImGui::Begin("Player");
	ImGui::InputFloat3("InputFloat3", moves);
	ImGui::SliderFloat3("SliderFloat3", moves, 0.0f, 2.0f);
	ImGui::Text("DebugCamera SPACE\nRotate A D\nAttack W", 2050, 12, 31);
	ImGui::End();

	move.x = moves[0] - 1;
	move.y = moves[1] - 1;
	move.z = moves[2] - 1;



	Rotate();

	// 攻撃処理
	Attack();

	// 弾更新
	if (bullet_) {
		bullet_->Update();
	}


	// 移動制限
	const float kMoveLimitX = 33;
	const float kMoveLimitY = 17;

	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

}
void Player::Rotate() {
	// 回転速さ[ラジアン/frame]
	const float kRotSpeed = 0.02f;
	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y += kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	}
}
void Player::Attack() {
	if (input_->PushKey(DIK_W)) {
		// 弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_);

		// 弾を登録
		bullet_ = newBullet;
	}
}
void Player::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	// 弾描画
	if (bullet_) {
		bullet_->Draw(viewProjection);
	}
}



