#include "stdafx.h"
#include "CppUnitTest.h"

#include "PlayerAI.h"
#include "IInputDevice.h"
#include "Player.h"

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

	TEST_CLASS(PlayerAITests)
	{
		PlayerAI* _playerAI;
		TestInputDevice* _inputDevice;

	public:

		TEST_METHOD_INITIALIZE(setUp)
		{
			_inputDevice = new TestInputDevice();
			_playerAI = new PlayerAI(_inputDevice);
		}

		TEST_METHOD_CLEANUP(tearDown)
		{
			delete _playerAI;
		}

		TEST_METHOD(testPlayerAITickUp)
		{
			_inputDevice->_up = true;

			Player* player = new Player();

			_playerAI->tick(player, 0, NULL);

			Assert::AreEqual(-PLAYER_ACCELERATION, player->getVelocity().y, L"Up velocity did not update correctly");
		}

		TEST_METHOD(testPlayerAITickDown)
		{
			_inputDevice->_down = true;

			Player* player = new Player();

			_playerAI->tick(player, 0, NULL);

			Assert::AreEqual(PLAYER_ACCELERATION, player->getVelocity().y, L"Down velocity did not update correctly");
		}

		TEST_METHOD(testPlayerAITickRight)
		{
			_inputDevice->_right = true;

			Player* player = new Player();

			_playerAI->tick(player, 0, NULL);

			Assert::AreEqual(PLAYER_ACCELERATION, player->getVelocity().x, L"Right velocity did not update correctly");
		}

		TEST_METHOD(testPlayerAITickLeft)
		{
			_inputDevice->_left = true;

			Player* player = new Player();

			_playerAI->tick(player, 0, NULL);

			Assert::AreEqual(-PLAYER_ACCELERATION, player->getVelocity().x, L"Left velocity did not update correctly");
		}

	};
}