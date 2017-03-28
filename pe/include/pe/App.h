#include <Urho3D/Engine/Application.h>

namespace Urho3D {
    class Node;
    class Scene;
}

class UISpellCrafter;

class App : public Urho3D::Application
{
public:
    App(Urho3D::Context* context);
    virtual void Setup() override;
    virtual void Start() override;
    virtual void Stop() override;

private:

    void CreateScene();

    void HandleKeyDown(Urho3D::StringHash eventType, Urho3D::VariantMap& eventData);
    void SetupViewports();

    Urho3D::SharedPtr<Urho3D::Scene> scene_;
    Urho3D::SharedPtr<Urho3D::Node> cameraNode_;
};
