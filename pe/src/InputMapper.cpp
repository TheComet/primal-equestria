#include "pe/InputMapper.h"
#include "pe/InputMapperEvents.h"

#include <Urho3D/Input/Input.h>

using namespace Urho3D;

// ----------------------------------------------------------------------------
InputMapper::InputMapper(Urho3D::Context* context) :
    Object(context)
{
    Input* input = GetSubsystem<Input>();
    SubscribeToEvent(input, E_KEYDOWN, URHO3D_HANDLER(InputMapper, HandleKeyDown));
    SubscribeToEvent(input, E_KEYUP, URHO3D_HANDLER(InputMapper, HandleKeyUp));
}

// ----------------------------------------------------------------------------
void InputMapper::HandleKeyDown(StringHash type, VariantMap& data)
{
    using namespace KeyDown;
    int key = data[P_KEY].GetInt();

    if (key == KEY_C)
    {
        VariantMap& map = GetEventDataMap();
        SendEvent(E_TOGGLESPELLCRAFTER, map);
    }
}

// ----------------------------------------------------------------------------
void InputMapper::HandleKeyUp(StringHash type, VariantMap& data)
{
}
