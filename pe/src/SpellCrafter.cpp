#include "pe/SpellCrafter.h"
#include "pe/InputMapper.h"
#include "pe/InputMapperEvents.h"

#include <Urho3D/Core/Context.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/Window.h>

using namespace Urho3D;

// ----------------------------------------------------------------------------
SpellCrafter::SpellCrafter(Context* context) :
    Object(context)
{
    const int padding = 20;
    UI* ui = GetSubsystem<UI>();
    IntVector2 screenSize = ui->GetRoot()->GetSize();
    window_ = ui->GetRoot()->CreateChild<Window>();
    window_->SetSize(screenSize.x_ - padding * 2, screenSize.y_ - padding * 2);
    window_->SetPosition(padding, padding);
    window_->SetOpacity(0.9);
    window_->SetStyle("Window");
    window_->SetVisible(false);
}

// ----------------------------------------------------------------------------
SpellCrafter::~SpellCrafter()
{
    CloseCrafter();
}

// ----------------------------------------------------------------------------
void SpellCrafter::RegisterObject(Context* context)
{
    context->RegisterFactory<SpellCrafter>("UI");
}

// ----------------------------------------------------------------------------
void SpellCrafter::OpenCrafter()
{
    URHO3D_LOGDEBUG("Opening spell crafter");
    window_->SetVisible(true);
}

// ----------------------------------------------------------------------------
void SpellCrafter::CloseCrafter()
{
    URHO3D_LOGDEBUG("Closing spell crafter");
    window_->SetVisible(false);
}

// ----------------------------------------------------------------------------
bool SpellCrafter::IsOpen()
{
    return window_->IsVisible();
}
