#pragma once

#include <Urho3D/Core/Object.h>

namespace Urho3D {
    class Window;
}

class SpellCrafter : public Urho3D::Object
{
    URHO3D_OBJECT(SpellCrafter, Object)

public:
    SpellCrafter(Urho3D::Context* context);
    virtual ~SpellCrafter();
    static void RegisterObject(Urho3D::Context* context);

    void OpenCrafter();
    void CloseCrafter();
    bool IsOpen();

private:

    Urho3D::SharedPtr<Urho3D::Window> window_;
};
