#include "HUD.h"
#include "Texture.h"
#include "Shader.h"
#include "Game.h"
#include "Renderer.h"
#include "Font.h"
#include <sstream>
#include <iomanip>

HUD::HUD(Game* game)
	:mGame(game)
	,mFont(nullptr)
	,mCoinCount(0)
	,mCheckpointTimer(-1)
{
	// Load font
	mFont = new Font();
	mFont->Load("Assets/Inconsolata-Regular.ttf");
	mTimerText = mFont->RenderText("00:00.00");
	mCoinCounter = mFont->RenderText("0/55");
}

HUD::~HUD()
{
	// Get rid of font
	if (mFont)
	{
		mFont->Unload();
		delete mFont;
	}
}

void HUD::Update(float deltaTime)
{
	// TODO
	mCheckpointTimer += deltaTime;
	mTime += deltaTime;
	mTimerText->Unload();
	delete mTimerText;

	int fraction = (int)(mTime*100)%100;
	int sec = ((int)mTime)%60; 
	int min = ((int)mTime) / 60;

	std::string newText = "";
	if (min < 10) newText += "0";
	newText += std::to_string(min) + ":";
	if (sec < 10) newText += "0";
	newText += std::to_string(sec) + ".";
	if (fraction < 10) newText += "0";
	newText += std::to_string(fraction);

	mTimerText = mFont->RenderText(newText);

}

void HUD::Draw(Shader* shader)
{
	// TODO
	DrawTexture(shader, mTimerText, Vector2(-420.0f, -325.0f));
	DrawTexture(shader, mCoinCounter, Vector2(-420.0f, -300.0f));
	if (mCheckpointTimer < 5.0f && mCheckpointText >= 0) {
		DrawTexture(shader, mCheckpointText, Vector2::Zero);
	}
}

void HUD::DrawTexture(class Shader* shader, class Texture* texture,
				 const Vector2& offset, float scale)
{
	// Scale the quad by the width/height of texture
	Matrix4 scaleMat = Matrix4::CreateScale(
		static_cast<float>(texture->GetWidth()) * scale,
		static_cast<float>(texture->GetHeight()) * scale,
		1.0f);
	// Translate to position on screen
	Matrix4 transMat = Matrix4::CreateTranslation(
		Vector3(offset.x, offset.y, 0.0f));	
	// Set world transform
	Matrix4 world = scaleMat * transMat;
	shader->SetMatrixUniform("uWorldTransform", world);
	// Set current texture
	texture->SetActive();
	// Draw quad
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void HUD::IncrementCoinCointer() {
	mCoinCounter->Unload();
	delete mCoinCounter;
	mCoinCount++;
	mCoinCounter = mFont->RenderText(std::to_string(mCoinCount)+"/55");
}

void HUD::DisplayCheckpointText(std::string c) {
	if (mCheckpointText != nullptr) {
		mCheckpointText->Unload();
		delete mCheckpointText;
	}
	mCheckpointTimer = 0;
	mCheckpointText = mFont->RenderText(c);
}