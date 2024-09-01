#include "ClearSceen.h"

ClearSceen::ClearSceen() {}

ClearSceen::~ClearSceen() {
	delete modelFont_;
	delete modelPlayer_;
	delete modelFontNumber_;
}

void ClearSceen::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ビュープロジェクション
	viewProjection_.Initialize();

	modelFont_ = Model::CreateFromOBJ("clearFont");
	modelPlayer_ = Model::CreateFromOBJ("player");
	modelFontNumber_ = Model::CreateFromOBJ("push_0");

	worldTransformFont_.Initialize();
	worldTransformPlayer_.Initialize();
	worldTransformFontNumber_.Initialize();

	worldTransformFont_.translation_.y = 10;
	worldTransformFontNumber_.translation_.y = 5;
	worldTransformPlayer_.translation_.y = -8;
	worldTransformFont_.scale_ = {2, 2, 2};
	worldTransformFontNumber_.scale_ = {8, 8, 8};
	worldTransformPlayer_.scale_ = {8, 8, 8};
	worldTransformPlayer_.rotation_.y = std::numbers::pi_v<float>;
}

void ClearSceen::Update() {

	if (Input::GetInstance()->PushKey(DIK_0)) {
		finished_ = true;
	}
	// タイマーを加算
	timer_ += 1.0f / 60.0f;

	worldTransformPlayer_.rotation_.y = std::numbers::pi_v<float> + std::sin(std::numbers::pi_v<float> * 2.0f * timer_ / kMotionTime);

	// 行列を更新
	worldTransformFont_.UpdateMatrix();
	worldTransformPlayer_.UpdateMatrix();
}

void ClearSceen::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	// ここに3Dオブジェクトの描画処理を追加できる
	modelFont_->Draw(worldTransformFont_, viewProjection_);
	modelPlayer_->Draw(worldTransformPlayer_, viewProjection_);
	modelFontNumber_->Draw(worldTransformFontNumber_, viewProjection_);

	// 3Dオブジェクト描画処理後
	Model::PostDraw();
}
