#pragma once
#include <utility>


namespace gp {


	class Entity; // fwd


	class Object {
	public:
		explicit Object(Entity& owner) : owner_(owner) {}
		virtual ~Object() = default;


		Entity& Owner() const { return owner_; }


		// No copy/move to avoid dangling registrations.
		Object(const Object&) = delete;
		Object& operator=(const Object&) = delete;
		Object(Object&&) = delete;
		Object& operator=(Object&&) = delete;


	protected:
		Entity& owner_;
	};


} // namespace gp