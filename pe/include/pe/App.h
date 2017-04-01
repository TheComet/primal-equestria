#include <Urho3D/Engine/Application.h>

namespace Urho3D {
    class DebugHud;
    class Node;
    class Scene;
    class XMLFile;
}

class SpellCrafter;

class App : public Urho3D::Application
{
public:
    App(Urho3D::Context* context);
    virtual void Setup() override;
    virtual void Start() override;
    virtual void Stop() override;

private:
    void RegisterObjectFactories();
    void RegisterSubsystems();
    void CreateUI();
    void CreateDebugHud();
    void CreateScene();
    void SetupViewports();

    void HandleButtonToggleSpellCrafter(Urho3D::StringHash eventType, Urho3D::VariantMap& data);
    void HandleButtonExit(Urho3D::StringHash eventType, Urho3D::VariantMap& data);
    void HandleFileChanged(Urho3D::StringHash eventType, Urho3D::VariantMap& eventData);

    Urho3D::SharedPtr<Urho3D::XMLFile> sceneXML_;
    Urho3D::SharedPtr<Urho3D::Scene> scene_;
    Urho3D::SharedPtr<Urho3D::Node> cameraNode_;

#ifdef DEBUG
    void HandlePostRenderUpdate(Urho3D::StringHash eventType, Urho3D::VariantMap& eventData);
    void HandleKeyDown(Urho3D::StringHash eventType, Urho3D::VariantMap& eventData);

    Urho3D::SharedPtr<Urho3D::DebugHud> debugHud_;
    bool drawDebug_;
#endif
};
