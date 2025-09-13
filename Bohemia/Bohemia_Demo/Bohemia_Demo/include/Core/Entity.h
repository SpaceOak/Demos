// ================================================
// File: include/Core/Entity.h
// ================================================

#pragma once
#include <vector>
#include <memory>
#include <type_traits>
#include "Core/EntityActionManager.h"


namespace gp {


	class Entity {
	public:
		Entity() : actions_(*this) {}
		~Entity() = default;


		// No copying/moving to keep registration lifecycle straightforward
		Entity(const Entity&) = delete;
		Entity& operator=(const Entity&) = delete;
		Entity(Entity&&) = delete;
		Entity& operator=(Entity&&) = delete;


		// Factory to create and own actions. The Action type must derive from EntityAction
		// and expose a constructor like Action(Entity&, EntityActionManager& [, ...args]).
		template <class TAction, class... Args>
		TAction& AddAction(Args&&... args) {
			static_assert(std::is_base_of_v<EntityAction, TAction>, "TAction must derive from EntityAction");
			auto up = std::make_unique<TAction>(*this, actions_, std::forward<Args>(args)...);
			auto& ref = *up;
			actionsOwner_.push_back(std::move(up));
			return ref;
		}


		EntityActionManager& Actions() { return actions_; }
		const EntityActionManager& Actions() const { return actions_; }


	private:
		// Owner-side storage to guarantee dtor order: action dtor → Unregister → manager clean
		EntityActionManager actions_;
		std::vector<std::unique_ptr<EntityAction>> actionsOwner_{};
	};


} // namespace gp