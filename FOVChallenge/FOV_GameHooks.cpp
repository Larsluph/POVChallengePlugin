#include "pch.h"
#include "FOVChallenge.h"

void FOVChallenge::OnCountdown(std::string eventName) {
	if (!enabled || !gameWrapper->IsInGame()) return;
	cvarManager->log("OnCountdown");

	gameWrapper->SetTimeout([&](GameWrapper* gw) {
		null_check_assign(cam, gw->GetCamera());
		base_cam = cam.GetCameraSettings();

		null_check_assign(localCar, gw->GetLocalCar());
		null_check_assign(localPRI, localCar.GetPRI());
		null_check_assign(localTeam, localPRI.GetTeam());

		if (!isGameStarted) {
			// On game start
			cvarManager->log("game started");
			prevScore = localTeam.GetScore();
			isGameStarted = true;
			isGameEnded = false;
		}
		else {
			// On goal
			int newScore = localTeam.GetScore();
			if (prevScore < newScore) {
				// scored
				cvarManager->log("You scored! Gaining FOV...");
#ifdef NDEBUG
				setFOV(5, true);
#endif
			}
			else {
				// took a goal
				cvarManager->log("You've taken a goal! Losing FOV...");
#ifdef NDEBUG
				setFOV(-5, true);
#endif
			}
			prevScore = newScore;
		}
	}, .1F);
}

void FOVChallenge::OnGameDestroyed(std::string eventName) {
	cvarManager->log("OnGameDestroyed");
	if (!enabled || isGameEnded) return;

	null_check_assign(cam, gameWrapper->GetCamera());
#ifdef NDEBUG
	cam.SetCameraSettings(base_cam);
#endif
	isGameStarted = false;
	isGameEnded = true;
}
