#include "pch.h"
#include "FOVChallenge.h"

void FOVChallenge::OnCountdown(std::string eventName) {
	if (!enabled || !gameWrapper->IsInGame()) return;

	gameWrapper->SetTimeout([&](GameWrapper* gw) {
		null_check_assign(localCar, gw->GetLocalCar());
		null_check_assign(localPRI, localCar.GetPRI());
		null_check_assign(localTeam, localPRI.GetTeam());

		if (!isGameStarted) {
			// On game start
			cvarManager->log("game started");
			prevScore = localTeam.GetScore();

			null_check_assign(cam, gw->GetCamera());
			temp_cam = cam.GetCameraSettings();
			logCamera();
			
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
				setFOV((float)*step, true);
#endif
			}
			else {
				// took a goal
				cvarManager->log("You've taken a goal! Losing FOV...");
#ifdef NDEBUG
				setFOV(-(float)(*step), true);
#endif
			}
			prevScore = newScore;
		}
	}, .1F);
}

void FOVChallenge::OnGameDestroyed(std::string eventName) {
	if (!enabled || isGameEnded) return;

	isGameStarted = false;
	isGameEnded = true;
}

void FOVChallenge::OnBallcamToggled(std::string eventName) {
	if (!enabled || !gameWrapper->IsInGame() || !isGameStarted) return;

#ifdef NDEBUG
	null_check_assign(cam, gameWrapper->GetCamera());
	cam.SetCameraSettings(temp_cam);
#endif
}
