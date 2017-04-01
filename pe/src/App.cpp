#include "pe/App.h"
#include "pe/DebugTextScroll.h"
#include "pe/InputMapper.h"
#include "pe/InputMapperEvents.h"
#include "pe/SpellCrafter.h"

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/DebugHud.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/IO/IOEvents.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/XMLFile.h>
#include <Urho3D/Resource/ResourceEvents.h>
#include <Urho3D/UI/UI.h>

using namespace Urho3D;

// ----------------------------------------------------------------------------
URHO3D_DEFINE_APPLICATION_MAIN(App)

// ----------------------------------------------------------------------------
App::App(Context* context) :
    Application(context),
#ifdef DEBUG
    drawDebug_(false)
#endif
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
    UI* ui = GetSubsystem<UI>();
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    cache->SetAutoReloadResources(true);
    ui->GetRoot()->SetDefaultStyle(cache->GetResource<XMLFile>("UI/DefaultStyle.xml"));

    RegisterObjectFactories();
    RegisterSubsystems();
    CreateUI();
    CreateDebugHud();
    CreateScene();
    SetupViewports();

    SubscribeToEvent(E_BUTTONTOGGLESPELLCRAFTER, URHO3D_HANDLER(App, HandleButtonToggleSpellCrafter));
    SubscribeToEvent(E_BUTTONEXIT, URHO3D_HANDLER(App, HandleButtonExit));
    SubscribeToEvent(E_FILECHANGED, URHO3D_HANDLER(App, HandleFileChanged));

#ifdef DEBUG
    SubscribeToEvent(E_POSTRENDERUPDATE, URHO3D_HANDLER(App, HandlePostRenderUpdate));
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(App, HandleKeyDown));
#endif
}

// ----------------------------------------------------------------------------
void App::Stop()
{
}

// ----------------------------------------------------------------------------
void App::RegisterObjectFactories()
{
    SpellCrafter::RegisterObject(context_);
}

// ----------------------------------------------------------------------------
void App::RegisterSubsystems()
{
    context_->RegisterSubsystem(new InputMapper(context_));
    context_->RegisterSubsystem(new SpellCrafter(context_));
    context_->RegisterSubsystem(new DebugTextScroll(context_));

    GetSubsystem<DebugTextScroll>()->SetTextCount(20);
}

// ----------------------------------------------------------------------------
void App::CreateUI()
{
}

// ----------------------------------------------------------------------------
void App::CreateDebugHud()
{
#ifdef DEBUG
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    XMLFile* style = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");
    debugHud_ = engine_->CreateDebugHud();
    if(debugHud_)
        debugHud_->SetDefaultStyle(style);
#endif
}

// ----------------------------------------------------------------------------
void App::CreateScene()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    scene_ = SharedPtr<Scene>(new Scene(context_));
    sceneXML_ = cache->GetResource<XMLFile>("Scenes/TestScene.xml");
    scene_->LoadXML(sceneXML_->GetRoot());

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
void App::HandleButtonToggleSpellCrafter(StringHash eventType, VariantMap& eventData)
{
    SpellCrafter* crafter = GetSubsystem<SpellCrafter>();
    if (crafter->IsOpen())
    {
        crafter->CloseCrafter();
        scene_->SetTimeScale(1.0);
    }
    else
    {
        crafter->OpenCrafter();
        scene_->SetTimeScale(0.1);
    }
}

// ----------------------------------------------------------------------------
void App::HandleButtonExit(StringHash eventType, VariantMap& data)
{
    engine_->Exit();
}

// ----------------------------------------------------------------------------
void App::HandleFileChanged(StringHash eventType, VariantMap& eventData)
{
    using namespace FileChanged;

    if(sceneXML_ && sceneXML_->GetName() == eventData[P_RESOURCENAME].GetString())
    {
        URHO3D_LOGINFO("[App] Reloading scene");
        if(scene_)
        {
            float timeScale = scene_->GetTimeScale();
            scene_->LoadXML(sceneXML_->GetRoot());
            scene_->SetTimeScale(timeScale);
        }
    }
}

// ----------------------------------------------------------------------------
#ifdef DEBUG
void App::HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    if(scene_ == NULL || drawDebug_ == false)
        return;

    DebugRenderer* debugRenderer = scene_->GetComponent<DebugRenderer>();
    if(!debugRenderer)
        return;
    bool depthTest = true;

    PhysicsWorld* phy = scene_->GetComponent<PhysicsWorld>();
    phy->DrawDebugGeometry(depthTest);
}

// ----------------------------------------------------------------------------
void App::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    using namespace KeyDown;
    int key = eventData[P_KEY].GetInt();

    // Toggle debug geometry
    if (key == KEY_F1)
        drawDebug_ = !drawDebug_;

    // Toggle debug HUD
    if(key == KEY_F2)
    {
        if(debugHud_->GetMode() == DEBUGHUD_SHOW_NONE)
            debugHud_->SetMode(DEBUGHUD_SHOW_ALL);
        else if(debugHud_->GetMode() == DEBUGHUD_SHOW_ALL)
            debugHud_->SetMode(DEBUGHUD_SHOW_MEMORY);
        else
            debugHud_->SetMode(DEBUGHUD_SHOW_NONE);
    }

    // Toggle mouse visibility (for debugging)
    if(key == KEY_F9)
        GetSubsystem<Input>()->SetMouseVisible(!GetSubsystem<Input>()->IsMouseVisible());
}
#endif
