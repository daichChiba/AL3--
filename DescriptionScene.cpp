#include "DescriptionScene.h"

DescriptionScene::DescriptionScene() {}

DescriptionScene::~DescriptionScene() {
	delete modelFont_;
	delete modelFontNumber_;
}

void DescriptionScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ビュープロジェクション
	viewProjection_.Initialize();

	modelFont_ = Model::CreateFromOBJ("Description");
	modelFontNumber_ = Model::CreateFromOBJ("push_1");

	worldTransformFont_.Initialize();
	worldTransformFontNumber_.Initialize();

	worldTransformFont_.translation_.y = 10;
	worldTransformFont_.scale_ = {2, 2, 2};
	worldTransformFontNumber_.translation_.y = 5;
	worldTransformFontNumber_.scale_ = {8, 8, 8};
}

void DescriptionScene::Update() {
	if (Input::GetInstance()->PushKey(DIK_1)) {
		finished_ = true;
	}

	// 行列を更新
	worldTransformFont_.UpdateMatrix();
}

void DescriptionScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	// ここに3Dオブジェクトの描画処理を追加できる
	modelFont_->Draw(worldTransformFont_, viewProjection_);
	modelFontNumber_->Draw(worldTransformFontNumber_, viewProjection_);

	// 3Dオブジェクト描画処理後
	Model::PostDraw();
}
