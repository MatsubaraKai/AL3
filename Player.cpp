#include "Player.h"
#include "cassert"




void Player::Initialize(Model* model, uint32_t textureHandle) {
	//NULL�|�C���^�`�F�b�N
	assert(model);
	
	WorldTransform* worldTransform_ = nullptr;
}

void Player::Update() { 
	worldTransform_.TransferMatrix();


}

void Player::Draw(ViewProjection) { model_->Draw(worldTransform_, ViewProjection, textureHandle_); }

