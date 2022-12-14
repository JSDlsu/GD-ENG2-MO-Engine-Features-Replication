#include "BNS_CameraHandler.h"

#include "BNS_Camera.h"

BNS_CameraHandler* BNS_CameraHandler::sharedInstance = nullptr;

BNS_CameraHandler::BNS_CameraHandler()
{
    BNS_Camera* cameraPtr(new BNS_Camera("BNS_Camera", BNS_ObjectTypes::CAMERA, 0));
    BNS_Camera* cameraPtr1(new BNS_Camera("BNS_Camera", BNS_ObjectTypes::CAMERA, 1));
    BNS_Camera* cameraPtr2(new BNS_Camera("BNS_Camera", BNS_ObjectTypes::CAMERA, 2));
    BNS_Camera* cameraPtr3(new BNS_Camera("BNS_Camera", BNS_ObjectTypes::CAMERA, 3));

    sceneCameras.emplace_back(cameraPtr);
    sceneCameras.emplace_back(cameraPtr1);
    sceneCameras.emplace_back(cameraPtr2);
    sceneCameras.emplace_back(cameraPtr3);
}

BNS_CameraHandler::~BNS_CameraHandler()
{
    std::vector<BNS_Camera*>::iterator i;
    for (i = sceneCameras.begin(); i != sceneCameras.end(); i++)
    {
        delete (*i);
    }
    sceneCameras.empty();
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
     return dynamic_cast<BNS_Camera*>(&*sceneCameras[currentCamIndex])->GetCamViewMatrix();
}
Matrix4x4 BNS_CameraHandler::GetSceneCameraProjMatrix()
{
    return dynamic_cast<BNS_Camera*>(&*sceneCameras[currentCamIndex])->GetCurrentProjMatrix();
}
Matrix4x4 BNS_CameraHandler::GetSceneCameraOrthoMatrix()
{
    return dynamic_cast<BNS_Camera*>(&*sceneCameras[currentCamIndex])->GetCameraOrthoMatrix();
}
Matrix4x4 BNS_CameraHandler::GetSceneCameraPerspecMatrix()
{
    return dynamic_cast<BNS_Camera*>(&*sceneCameras[currentCamIndex])->GetCamPerspectiveMatrix();
}

Matrix4x4 BNS_CameraHandler::GetSceneCameraMatrix()
{
    return dynamic_cast<BNS_Camera*>(&*sceneCameras[currentCamIndex])->GetMatrix();
}

Vector3D BNS_CameraHandler::GetSceneCameraPos()
{
    return dynamic_cast<BNS_Camera*>(&*sceneCameras[currentCamIndex])->GetLocalPosition();
}

BNS_Camera* BNS_CameraHandler::GetSceneCamera()
{
    return sceneCameras[currentCamIndex];
}
