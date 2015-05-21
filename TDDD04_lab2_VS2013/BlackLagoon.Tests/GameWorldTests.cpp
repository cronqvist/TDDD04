#include "stdafx.h"
#include "CppUnitTest.h"

#include "GameWorld.h"
#include "IGameWorldEvent.h"
#include "ScoreComponent.h"
#include "GameObjectManager.h"
#include "GameObjectFactory.h"
#include "IInputDevice.h"
#include "PhysicsComponent.h"
#include "TerrainManager.h"
#include "TerrainTileTypes.h"
#include "TileSprites.h"

#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackLagoontests {

	class TestInputDevice final : public IInputDevice {
	public:
		bool left() override { return _left; }
		bool right() override { return _right; }
		bool up() override { return _up; }
		bool down() override { return _down; }

		bool turnLeft() override { return false; }
		bool turnRight() override { return false; }
		bool fire() override { return false; }

		bool left2() override { return false; }
		bool right2() override { return false; }
		bool up2() override { return false; }
		bool down2() override { return false; }

		bool select() override { return false; }
		bool next() override { return false; }
		bool previously() override { return false; }
		bool pause() override { return false; }
		bool displayInfo() override { return false; }
		bool exit() override { return false; }

		bool _left = false;
		bool _right = false;
		bool _up = false;
		bool _down = false;
	};

	class BasicGameWorldEvent final : public IGameWorldEvent {
	public:
		void run() override { _eventDidRun = true; }
		const bool eventDidRun() const { return _eventDidRun; }
	private:
		bool _eventDidRun = false;
	};

	TEST_CLASS(GameWorldTests) {

		BasicGameWorldEvent* playerDeadEvent;
		IGameWorld* world;
		IGameObjectManager* manager;

	public:

		TEST_METHOD_INITIALIZE(setUp) {
			playerDeadEvent = new BasicGameWorldEvent();
			
			IGameObjectFactory* factory = new GameObjectFactory(NULL);
			IScoreComponent* component = new ScoreComponent(NULL, NULL);
			manager = new GameObjectManager(factory);

			IPhysicsComponent* physics = new PhysicsComponent();

			ITileSprites* sprites = new TileSprites(0, 1, 1, 1, 1);
			ITerrainTileTypes* tiles = new TerrainTileTypes(sprites);
			ITerrainManager* terrain = new TerrainManager(tiles);
			
			world = new GameWorld(playerDeadEvent, NULL, manager, physics, component, terrain, NULL, Rect());
		}

		TEST_METHOD_CLEANUP(tearDown) {
			delete world;
			delete manager;
			delete playerDeadEvent;
		}

		TEST_METHOD(physicsSimulationDidRaiseDeadEvent) {
			IInputDevice* input = new TestInputDevice();

			manager->addPlayer(input);
			manager->getPlayer()->Health = -1;

			world->tick(1);

			Assert::IsTrue(playerDeadEvent->eventDidRun(), L"Event did not run");
			
			delete input;
		}

		TEST_METHOD(physicsSimulationDidNotRaiseDeadEvent) {
			IInputDevice* input = new TestInputDevice();

			manager->addPlayer(input);
			manager->getPlayer()->Health = 0;

			world->tick(1);

			Assert::IsFalse(playerDeadEvent->eventDidRun(), L"Event did run when it should not");
		
			delete input;
		}
	};
}