#include "pch.h"
#include "FOVChallenge.h"

void FOVChallenge::logCamera() {
	null_check_assign(cam, gameWrapper->GetCamera());
	auto cam_settings = cam.GetCameraSettings();
	logCamera(cam_settings);
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
	null_check_assign(cam, gameWrapper->GetCamera());
	auto cam_settings = cam.GetCameraSettings();
	float new_fov;

	if (isDelta) {
		new_fov = cam_settings.FOV + fov;
		if (cam_settings.FOV == 110) {
			cvarManager->log("FOV already maximized. Keep it up!");
			return;
		}
		else if (cam_settings.FOV == 60) {
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
	
	cvarManager->log("Changed FOV: " + std::to_string(cam_settings.FOV) + " -> " + std::to_string(new_fov));
	gameWrapper->Toast("FOV Challenge Plugin", "FOV Changed to " + std::to_string(new_fov) + " (previously " + std::to_string(cam_settings.FOV) + ")");

	logCamera(cam_settings);
	cam_settings.FOV = new_fov;
	cam.SetCameraSettings(cam_settings);
	logCamera();
}
