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


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackLagoontests
{
	class TestInputDevice
		: public IInputDevice
	{
	public:
		bool left() { return _left; }
		bool right() { return _right; }
		bool up() { return _up; }
		bool down() { return _down; }

		bool turnLeft() { return false; }
		bool turnRight() { return false; }
		bool fire() { return false; }

		bool left2() { return false; }
		bool right2() { return false; }
		bool up2() { return false; }
		bool down2() { return false; }

		bool select() { return false; }
		bool next() { return false; }
		bool previously() { return false; }
		bool pause() { return false; }
		bool displayInfo() { return false; }
		bool exit() { return false; }

		bool _left = false;
		bool _right = false;
		bool _up = false;
		bool _down = false;

	};

	class GameWordEventTest : public IGameWorldEvent
	{
	public:
		void run()
		{ 
			_eventRunned = true;
		}

		bool _eventRunned = false;
	};

	TEST_CLASS(GameWorldTests)
	{

		GameWordEventTest* playerDeadEvent;
		GameWorld* world;
		IGameObjectManager* manager;

	public:

		TEST_METHOD_INITIALIZE(setUp)
		{
			playerDeadEvent = new GameWordEventTest();

			IGameObjectFactory* factory = new GameObjectFactory(NULL);
			IScoreComponent* component = new ScoreComponent(NULL, NULL);
			manager = new GameObjectManager(factory);

			IPhysicsComponent* physics = new PhysicsComponent();

			ITileSprites* sprites = new TileSprites(0, 1, 1, 1, 1);
			ITerrainTileTypes* tiles = new TerrainTileTypes(sprites);
			ITerrainManager* terrain = new TerrainManager(tiles);

			world = new GameWorld(playerDeadEvent, NULL, manager, physics, component, terrain, NULL, Rect());
		}

		TEST_METHOD_CLEANUP(tearDown)
		{
		}

		TEST_METHOD(physicsSimulationRaiseDeadEventTest)
		{
			IInputDevice* input = new TestInputDevice();

			manager->addPlayer(input);
			manager->getPlayer()->Health = -1;

			world->tick(1);

			Assert::AreEqual(true, playerDeadEvent->_eventRunned, L"Event did not run");
		}

		TEST_METHOD(physicsSimulationNotRaiseDeadEventTest)
		{
			IInputDevice* input = new TestInputDevice();

			manager->addPlayer(input);
			manager->getPlayer()->Health = 0;

			world->tick(1);

			Assert::AreEqual(false, playerDeadEvent->_eventRunned, L"Event did run when it should not");
		}
	};
}