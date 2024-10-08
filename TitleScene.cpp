#include "TitleScene.h"
#include "Input.h"
#include <numbers>

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {
	delete modelFont_;
	delete modelPlayer_;
	delete modelPush_;
}

void TitleScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();



// ビュープロジェクション
	viewProjection_.Initialize();

	modelFont_ = Model::CreateFromOBJ("titleFont");
	modelPlayer_ = Model::CreateFromOBJ("player");
	modelPush_ = Model::CreateFromOBJ("push_Space");

	worldTransformFont_.Initialize();
	worldTransformPlayer_.Initialize();
	worldTransformPush_.Initialize();

	worldTransformFont_.translation_.y = 10;
	worldTransformPlayer_.translation_.y = -8;
	worldTransformPush_.translation_.y = 5;
	worldTransformFont_.scale_ = {2, 2, 2};
	worldTransformPlayer_.scale_ = {8, 8, 8};
	worldTransformPush_.scale_ = {2, 2, 2};
	worldTransformPlayer_.rotation_.y = std::numbers::pi_v<float>;

}

void TitleScene::Update() {
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		finished_ = true;
	}
	// タイマーを加算
	timer_ += 1.0f / 60.0f;

	worldTransformPlayer_.rotation_.y =
		std::numbers::pi_v<float> + std::sin(std::numbers::pi_v<float> * 2.0f * timer_ / kMotionTime);

	// 行列を更新
	worldTransformFont_.UpdateMatrix();
	worldTransformPlayer_.UpdateMatrix();
	worldTransformPush_.UpdateMatrix();
}

void TitleScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	// ここに3Dオブジェクトの描画処理を追加できる
	modelFont_->Draw(worldTransformFont_, viewProjection_);
	modelPlayer_->Draw(worldTransformPlayer_, viewProjection_);
	modelPush_->Draw(worldTransformPush_, viewProjection_);

	// 3Dオブジェクト描画処理後
	Model::PostDraw();
}
