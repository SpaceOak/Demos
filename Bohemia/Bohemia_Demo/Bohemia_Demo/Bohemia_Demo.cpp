#include <iostream>
#include "Core/Entity.h"
#include "Actions/OpenAction.h"
#include "Actions/InspectAction.h"
#include "Actions/LockpickAction.h"

using namespace gp;

static void PrintVisible(const char* tag, Entity& e, const VisibilityQuery& q)
{
    std::cout << "--- " << tag << " ---\n";
    auto visible = e.Actions().Visible(q);
    for (auto* a : visible)
    {
        std::cout << " * " << a->Name() << "\n";
    }
}

int main()
{
    Entity door;

    // Chest entity with Open + Lockpick + Inspect
    Entity chest;
    chest.AddAction<OpenAction>();
    chest.AddAction<LockpickAction>();
    chest.AddAction<InspectAction>();

    // Chest scenarios (same flags, but includes Inspect always)
    PrintVisible("CHEST: locked, no key", chest, { false, false, true });
    PrintVisible("CHEST: closed + key", chest, { true, false, false });
    PrintVisible("CHEST: already open", chest, { false, true, false });

    // Demo execute: run all visible actions for chest in "closed + key" state
    auto vis = chest.Actions().Visible({ true, false, false });
    for (auto* a : vis) a->Execute();


    return 0;
}
