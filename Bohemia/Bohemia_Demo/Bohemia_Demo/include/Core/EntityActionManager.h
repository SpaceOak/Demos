// ================================================
// File: include/Core/EntityActionManager.h
// ================================================

#pragma once
#include <vector>
#include "Core/ObjectManager.h"
#include "Core/EntityAction.h"


namespace gp {


	class EntityActionManager : public ObjectManager<EntityAction> {
	public:
		using ObjectManager::ObjectManager; // reuse ctor(Entity&)


		std::vector<EntityAction*> Visible(const VisibilityQuery& q) {
			std::vector<EntityAction*> out;
			this->ForEach([&](EntityAction& a) { if (a.CanBeVisible(q)) out.push_back(&a); });
			return out;
		}
	};


} // namespace gp