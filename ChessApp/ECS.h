#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentId = std::size_t;

inline ComponentId GetComponentTypeId()
{
  static ComponentId lastId = 0;
  return lastId++;
}

template<typename T>
inline ComponentId GetComponentTypeId() noexcept
{
  static ComponentId typeId = GetComponentTypeId();
  return typeId;
}

constexpr std::size_t maxComponents = 64;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
  Component() {}
  virtual ~Component() {}

  Entity* GetEntity() const
  {
    return _entity;
  }

  void SetEntity(Entity* entity)
  {
    _entity = entity;
  }

  virtual void Init() {}
  virtual void Update() {}
  virtual void Draw() {}

private:
  Entity* _entity;
};

class Entity
{
public:
  bool GetIsActive() const
  {
    return _isActive;
  }

  void Update()
  {
    for (auto& component : _components)
    {
      component->Update();
    }

    for (auto& component : _components)
    {
      component->Draw();
    }
  }

  void Draw() {}
  void Destroy()
  {
    _isActive = false;
  }

  template<typename T>
  bool HasComponent() const
  {
    return _componentBitSet[GetComponentTypeId<T>()];
  }

  template<typename T, typename... TArgs>
  T& AddComponent(TArgs&&... mArgs)
  {
    T* c(new T(std::forward<TArgs>(mArgs)...));
    c->SetEntity(this);
    std::unique_ptr<Component> uPtr{ c };
    _components.emplace_back(std::move(uPtr));

    _componentArray[GetComponentTypeId<T>()] = c;
    _componentBitSet[GetComponentTypeId<T>()] = true;

    c->Init();
    return *c;
  }

  template<typename T>
  T& GetComponent() const
  {
    auto ptr(_componentArray[GetComponentTypeId<T>()]);
    return *static_cast<T*>(ptr);
  }

private:
  bool _isActive = true;
  std::vector<std::unique_ptr<Component>> _components;

  ComponentArray _componentArray;
  ComponentBitSet _componentBitSet;
};

class Manager
{
public:
  void Update()
  {
    for (auto& entity : _entities)
    {
      entity->Update();
    }
  }

  void Draw()
  {
    for (auto& entity : _entities)
    {
      entity->Draw();
    }
  }

  void Refresh()
  {
    _entities.erase(std::remove_if(std::begin(_entities), std::end(_entities), [](const std::unique_ptr<Entity>& mEntity)
      {
        return !mEntity->GetIsActive();
      }), std::end(_entities));
  }

  Entity& AddEntity()
  {
    auto entity = new Entity();
    std::unique_ptr<Entity> uPtr{ entity };
    _entities.emplace_back(std::move(uPtr));
    return *entity;
  }

private:
  std::vector<std::unique_ptr<Entity>> _entities;
};
