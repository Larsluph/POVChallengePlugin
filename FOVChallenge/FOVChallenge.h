#pragma once

#define null_check(var) if (var.IsNull()) return;
#define null_check_ptr(var) if (var == nullptr) return;
#define null_check_assign(var, expr) \
	auto (var) = (expr); \
	if (var.IsNull()) {cvarManager->log(#var " IsNull");return;}

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"

constexpr auto plugin_version = "1.0";

class FOVChallenge: public BakkesMod::Plugin::BakkesModPlugin
{
	std::shared_ptr<bool> enabled;
	std::shared_ptr<int> step;

	int prevScore = 0;
	bool isGameStarted = false;
	bool isGameEnded = false;

	ProfileCameraSettings temp_cam = { 0 };

	//Boilerplate
	virtual void onLoad();
	virtual void onUnload();

	// GameHooks
	void OnCountdown(std::string);
	void OnGameDestroyed(std::string);
	void OnBallcamToggled(std::string);

	// Utils
	void logCamera();
	void logCamera(ProfileCameraSettings);
	void setFOV(float, bool);
};
