#pragma once

#include <Urho3D/UI/UIElement.h>

class UISpellCrafter : public Urho3D::UIElement
{
    URHO3D_OBJECT(UISpellCrafter, UIElement)

public:
    UISpellCrafter(Urho3D::Context* context);
    virtual ~UISpellCrafter();

    void OpenCrafter();
    void CloseCrafter();
    void ToggleCrafter();

private:
    void HandleToggleSpellCrafter(Urho3D::StringHash eventType, Urho3D::VariantMap& data);
    bool isOpen_;
};
