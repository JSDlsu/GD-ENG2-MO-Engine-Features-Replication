#include "BNS_CameraHandler.h"

#include "BNS_Camera.h"

BNS_CameraHandler* BNS_CameraHandler::sharedInstance = nullptr;

BNS_CameraHandler::BNS_CameraHandler()
{
    CameraPtr cameraPtr(new BNS_Camera("BNS_Camera", BNS_ObjectTypes::CAMERA));
    this->sceneCamera = cameraPtr;
}

BNS_CameraHandler::~BNS_CameraHandler()
{
    delete sharedInstance;
}

void BNS_CameraHandler::Initialize()
{
    sharedInstance = new BNS_CameraHandler();
}

BNS_CameraHandler* BNS_CameraHandler::GetInstance()
{
    return sharedInstance;
}

Matrix4x4 BNS_CameraHandler::GetSceneCameraViewMatrix()
{
    return dynamic_cast<BNS_Camera*>(&*sceneCamera)->GetCamViewMatrix();
}
Matrix4x4 BNS_CameraHandler::GetSceneCameraOrthoMatrix()
{
    return dynamic_cast<BNS_Camera*>(&*sceneCamera)->GetCameraOrthoMatrix();
}
Matrix4x4 BNS_CameraHandler::GetSceneCameraProjMatrix()
{
    return dynamic_cast<BNS_Camera*>(&*sceneCamera)->GetCamProjectionMatrix();
}

Matrix4x4 BNS_CameraHandler::GetSceneCameraMatrix()
{
    return dynamic_cast<BNS_Camera*>(&*sceneCamera)->GetMatrix();
}

Vector3D BNS_CameraHandler::GetSceneCameraPos()
{
    return dynamic_cast<BNS_Camera*>(&*sceneCamera)->GetLocalPosition();
}
