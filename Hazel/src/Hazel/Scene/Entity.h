#pragma once

#include "SceneContext.h"

namespace Hazel
{
	class Entity
	{
	private:
		entt::entity entity = entt::null;
		SceneContext *context = nullptr;

	public:
		Entity() = default;

		Entity(entt::entity entity, SceneContext &context)
			: entity(entity),
			context(&context)
		{
		}

		bool IsValid() const
		{
			return context && context->GetRegistry().valid(entity);
		}

		SceneContext &GetSceneContext() const
		{
			return *context;
		}

		template<typename ComponentType>
		bool HasComponent() const
		{
			return context->GetRegistry().has<ComponentType>(entity);
		}

		template<typename ComponentType>
		ComponentType &GetComponent()
		{
			return context->GetRegistry().get<ComponentType>(entity);
		}

		template<typename ComponentType>
		ComponentType *TryGetComponent()
		{
			return context->GetRegistry().try_get<ComponentType>(entity);
		}

		template<typename ComponentType, typename ...Args>
		ComponentType &AddComponent(Args &&...args)
		{
			auto &component = context->GetRegistry().emplace<ComponentType>(entity, std::forward<Args>(args)...);
			EntityEvents::OnAddComponent<ComponentType>(*this, component);
			return component;
		}

		template<typename ComponentType>
		void RemoveComponent()
		{
			EntityEvents::OnRemoveComponent<ComponentType>(*this);
			context->GetRegistry().remove<ComponentType>(entity);
		}

		operator entt::entity() const
		{
			return entity;
		}
	};

	class EntityEvents
	{
	public:
		template<typename ComponentType>
		static void OnAddComponent(Entity entity, ComponentType &component)
		{
		}

		template<typename ComponentType>
		static void OnRemoveComponent(Entity entity)
		{
		}
	};
}