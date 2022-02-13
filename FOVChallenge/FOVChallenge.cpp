#include "pch.h"
#include "FOVChallenge.h"


BAKKESMOD_PLUGIN(FOVChallenge, "FOV Challenge Plugin", plugin_version, 0)


void FOVChallenge::onLoad()
{
	enabled = std::make_shared<bool>(true);
	cvarManager->registerCvar("FOV_enable", "1", "Enable FOV Challenge Plugin", true, true, 0, true, 1, true).bindTo(enabled);

	step = std::make_shared<int>(5);
	cvarManager->registerCvar("FOV_step", "5", "Step used to change FOV", true, true, -50, true, 50, true).bindTo(step);

	cvarManager->registerNotifier("log_cam", [&](std::vector<std::string> args) {
		logCamera();
		}, "Logs camera FOV to console", PERMISSION_ALL);

	gameWrapper->HookEvent("Function GameEvent_TA.Countdown.BeginState", bind(&FOVChallenge::OnCountdown, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function TAGame.GameEvent_Soccar_TA.EventMatchEnded", bind(&FOVChallenge::OnGameDestroyed, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function TAGame.GameEvent_TA.Destroyed", bind(&FOVChallenge::OnGameDestroyed, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function TAGame.CameraState_BallCam_TA.UpdateAirAndGroundCamera", bind(&FOVChallenge::OnBallcamToggled, this, std::placeholders::_1));
}

void FOVChallenge::onUnload()
{
}
