#include "pe/UISpellCrafter.h"
#include "pe/InputMapper.h"
#include "pe/InputMapperEvents.h"

#include <Urho3D/UI/UI.h>
#include <Urho3D/IO/Log.h>

using namespace Urho3D;

// ----------------------------------------------------------------------------
UISpellCrafter::UISpellCrafter(Context* context) :
    UIElement(context),
    isOpen_(false)
{
    InputMapper* mapper = GetSubsystem<InputMapper>();
    assert(mapper != NULL);

    SubscribeToEvent(mapper, E_TOGGLESPELLCRAFTER, URHO3D_HANDLER(UISpellCrafter, HandleToggleSpellCrafter));
}

// ----------------------------------------------------------------------------
UISpellCrafter::~UISpellCrafter()
{
    CloseCrafter();
}

// ----------------------------------------------------------------------------
void UISpellCrafter::OpenCrafter()
{
    if (isOpen_ == true)
        return;

    URHO3D_LOGDEBUG("Opening spell crafter");
    GetSubsystem<UI>()->GetRoot()->AddChild(this);
    isOpen_ = true;
}

// ----------------------------------------------------------------------------
void UISpellCrafter::CloseCrafter()
{
    if (isOpen_ == false)
        return;

    URHO3D_LOGDEBUG("Closing spell crafter");
    // UI subsystem might not exist during shutdown
    UI* ui = GetSubsystem<UI>();
    if (ui == NULL)
        return;

    ui->GetRoot()->RemoveChild(this);
    isOpen_ = false;
}

// ----------------------------------------------------------------------------
void UISpellCrafter::ToggleCrafter()
{
    if (isOpen_)
        CloseCrafter();
    else
        OpenCrafter();
}

// ----------------------------------------------------------------------------
void UISpellCrafter::HandleToggleSpellCrafter(StringHash eventType, VariantMap& data)
{
    using namespace ToggleSpellCrafter;

    ToggleCrafter();
}
