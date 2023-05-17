#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "PlayerBullet.h"

class Player {
public:
	///< summary>
	/// 初期化
	///</summary>
	///<param name="model">モデル</param>
	///<param name="textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model, uint32_t textureHandle);
	///< summary>
	/// 更新
	///</summary>
	void Update();

	void Rotate();
	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();
	///< summary>
	/// 描画
	///</summary>
	void Draw(ViewProjection viewProjection);
	
private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//キーボード入力
	Input* input_ = nullptr;
	//弾
	PlayerBullet* bullet_ = nullptr;
};
