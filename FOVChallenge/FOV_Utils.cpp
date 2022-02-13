#include "pch.h"
#include "FOVChallenge.h"

void FOVChallenge::logCamera() {
	logCamera(temp_cam);
}

void FOVChallenge::logCamera(ProfileCameraSettings cam) {
	cvarManager->log("Distance: " + std::to_string(cam.Distance));
	cvarManager->log("FOV: " + std::to_string(cam.FOV));
	cvarManager->log("Height: " + std::to_string(cam.Height));
	cvarManager->log("Pitch: " + std::to_string(cam.Pitch));
	cvarManager->log("Stiffness: " + std::to_string(cam.Stiffness));
	cvarManager->log("SwivelSpeed: " + std::to_string(cam.SwivelSpeed));
	cvarManager->log("TransistionSpeed: " + std::to_string(cam.TransitionSpeed));
}

void FOVChallenge::setFOV(float fov, bool isDelta) {
	float new_fov;

	if (isDelta) {
		new_fov = temp_cam.FOV + fov;
		if (temp_cam.FOV == 110 && fov > 0) {
			cvarManager->log("FOV already maximized. Keep it up!");
			return;
		}
		else if (temp_cam.FOV == 60 && fov < 0) {
			cvarManager->log("FOV already minimized. u bad :)");
			return;
		}
	}
	else {
		if (fov > 110 || fov < 60) {
			cvarManager->log("invalid range. FOV should be between 60 and 110");
			return;
		}
		new_fov = fov;
	}

	new_fov = fminf(110.F, fmaxf(60.F, new_fov));
	
	cvarManager->log("Changed FOV: " + std::to_string(temp_cam.FOV) + " -> " + std::to_string(new_fov));
	gameWrapper->Toast("FOV Challenge Plugin", "FOV Changed to " + std::to_string(new_fov) + " (previously " + std::to_string(temp_cam.FOV) + ")");

	logCamera(temp_cam);
	temp_cam.FOV = new_fov;
	null_check_assign(cam, gameWrapper->GetCamera());
	cam.SetCameraSettings(temp_cam);
	logCamera();
}
