#pragma once

#include <Urho3D/Core/Object.h>

class InputMapper : public Urho3D::Object
{
    URHO3D_OBJECT(InputMapper, Object)

public:
    InputMapper(Urho3D::Context* context);

private:
    void HandleKeyUp(Urho3D::StringHash type, Urho3D::VariantMap& data);
    void HandleKeyDown(Urho3D::StringHash type, Urho3D::VariantMap& data);
};
