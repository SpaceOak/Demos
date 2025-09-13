#include <iostream>
#include "Core/Entity.h"
#include "Actions/OpenAction.h"
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

    // attach actions to the entity
    door.AddAction<OpenAction>();
    door.AddAction<LockpickAction>();

    // try different visibility states
    VisibilityQuery q1{ false, false, true };   // locked, no key
    VisibilityQuery q2{ true, false, false };   // closed, has key, unlocked
    VisibilityQuery q3{ false, true, false };   // already open

    PrintVisible("locked, no key", door, q1);
    PrintVisible("closed + key", door, q2);
    PrintVisible("already open", door, q3);

    // demo execution of available actions
    auto visible = door.Actions().Visible(q2);
    for (auto* a : visible)
        a->Execute();

    return 0;
}
