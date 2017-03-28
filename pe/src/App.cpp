#include "pe/App.h"

#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/LuaScript/LuaScript.h>
#include <Urho3D/LuaScript/LuaFile.h>
#include <Urho3D/LuaScript/LuaScriptInstance.h>
#include <Urho3D/LuaScript/LuaFunction.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Resource/XMLFile.h>
#include <Urho3D/Resource/ResourceCache.h>

using namespace Urho3D;

// ----------------------------------------------------------------------------
App::App(Context* context) :
    Application(context)
{
}

// ----------------------------------------------------------------------------
void App::Setup()
{
    engineParameters_["WindowTitle"] = "Primal Equestria";
    engineParameters_["FullScreen"]  = false;
    engineParameters_["Headless"]    = false;
}

// ----------------------------------------------------------------------------
void App::Start()
{
    CreateScene();
    SetupViewports();

    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(App, HandleKeyDown));
}

// ----------------------------------------------------------------------------
void App::Stop()
{
}

// ----------------------------------------------------------------------------
void App::CreateScene()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    scene_ = SharedPtr<Scene>(new Scene(context_));
    XMLFile* sceneXML = cache->GetResource<XMLFile>("Scenes/TestScene.xml");
    scene_->LoadXML(sceneXML->GetRoot());

    // set up camera
    cameraNode_ = scene_->CreateChild("Camera");
    Camera* camera = cameraNode_->CreateComponent<Camera>();
    camera->SetFarClip(300.0f);
    cameraNode_->SetPosition(Vector3(0.0f, 5.0f, -20.0f));
}

// ----------------------------------------------------------------------------
void App::SetupViewports()
{
    Renderer* renderer = GetSubsystem<Renderer>();
    Camera* camera = cameraNode_->GetComponent<Camera>();
    Viewport* viewport = new Viewport(context_, scene_, camera);
    renderer->SetViewport(0, viewport);
}

// ----------------------------------------------------------------------------
void App::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    using namespace KeyDown;

    // Check for pressing ESC
    int key = eventData[P_KEY].GetInt();
    if(key == KEY_ESCAPE)
        engine_->Exit();
}

// ----------------------------------------------------------------------------
URHO3D_DEFINE_APPLICATION_MAIN(App)
