#pragma once
#include <string>
#include "Core/Object.h"


namespace gp {


	struct VisibilityQuery {
		bool hasKey{ false };
		bool isOpen{ false };
		bool isLocked{ false };
		// can be expanded later (distance, stance ? ?.?.)
	};


	class EntityActionManager; // fwd


	class EntityAction : public Object {
	public:
		using Object::Object; // inherit ctor (takes Entity&)
		virtual ~EntityAction() = default;


		virtual std::string Name() const = 0;
		virtual bool CanBeVisible(const VisibilityQuery& q) const { (void)q; return true; }
		virtual void Execute() { /* default: no-op for demo */ }


		// We connect to the manager in specific actions (ctor/dtor Register/Unregister)
	};


} // namespace gp