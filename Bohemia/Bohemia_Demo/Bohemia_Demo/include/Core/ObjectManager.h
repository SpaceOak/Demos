// ================================================
// File: include/Core/ObjectManager.h
// ================================================

#pragma once
#include <unordered_map>
#include "Core/SlotMap.h"


namespace gp {


	class Entity; // fwd


	// Generic non-owning registry for objects of type T.
	// Objects are expected to call Register/Unregister themselves (RAII style).
	template <typename T>
	class ObjectManager {
	public:
		explicit ObjectManager(Entity& owner) : owner_(owner) {}
		virtual ~ObjectManager() = default;


		void Register(T& obj) {
			auto h = storage_.insert(&obj);
			handles_[&obj] = h;
		}


		void Unregister(T& obj) {
			auto it = handles_.find(&obj);
			if (it != handles_.end()) {
				storage_.erase(it->second);
				handles_.erase(it);
			}
		}


		template <class Fn>
		void ForEach(Fn&& fn) {
			storage_.for_each([&](T& t) { fn(t); });
		}


		template <typename Method, typename... Args>
		void CallAll(Method memfn, Args&&... args) {
			ForEach([&](T& t) { (t.*memfn)(std::forward<Args>(args)...); });
		}


		Entity& Owner() const { return owner_; }


	protected:
		Entity& owner_;
		SlotMap<T> storage_{}; // stores T*
		std::unordered_map<T*, typename SlotMap<T>::Handle> handles_{};
	};


} // namespace gp