
/**
 * @author Allan Deutsch
 * @version 0.5
 * @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
 *
 * @brief The Engine class is the core of the game engine.
 *
 */


#pragma once
#include <memory> // Shared pointers for automatic memory management
#include <vector>
#include <unordered_map>
#include "System.h"
#include "Entity.h"
#include "Space.h"
#include "ArchetypeFactory.h"
#include "Message.h"

namespace AlJeEngine
{

  struct Engine
  {
    Engine();
    /**
    * @brief Initializes the Engine
    * @detail This is where the startup operations happen.
    *   Systems are added and initialized, variables are set, and the initial space is created.
    */
    void Init();

    void Shutdown();

    void Update(float dt);

    void mainLoop();

    float FrameTime();

    SpacePtr CreateSpace(std::string name);

    SpacePtr GetSpace(std::string name);

    SpacePtr SetActiveSpace(std::string name);

    SpacePtr GetActiveSpace();

    ArchetypeFactory& Factory();

    void SendMsg(EntityPtr, EntityPtr, Message::Message);

    float Getdt() { return dt; }

    // Don't use this directly! Do GETSYS(sysType) instead, it's much cleaner looking.
    template<typename T>
    std::shared_ptr<T> GetSystem(EnumeratedSystem sysType);

    void Stop(void) { _running = false;  }

  private:

    bool _running = true;

    float dt;

    std::string _activeSpace;

    typedef std::unordered_map<std::string, SpacePtr> SpaceMap;

     SpaceMap _spaces;

    SystemVec _systems;

    ArchetypeFactory _archetypeFactory;

  };

#define GETSYS( systype ) \
ENGINE->GetSystem<systype>(ES_##systype)

  template <typename T>
  std::shared_ptr<T> Engine::GetSystem(EnumeratedSystem sysType)
  {
    for (auto &it : _systems)
    {
      if (it->_type == sysType)
        return std::static_pointer_cast<T>(it);
    }

    // Throw an error if the system doesn't exist in the engine.
    throw std::range_error("The specified system does not exist.");

  }



}; // AlJeEngine
