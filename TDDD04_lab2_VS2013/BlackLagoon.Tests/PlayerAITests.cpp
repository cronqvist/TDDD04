#include "stdafx.h"
#include "CppUnitTest.h"

#include "PlayerAI.h"
#include "IInputDevice.h"
#include "Player.h"

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

	TEST_CLASS(PlayerAITests){

		PlayerAI* _playerAI;
		TestInputDevice* _inputDevice;
		Player* player;

	public:

		TEST_METHOD_INITIALIZE(setUp) {
			_inputDevice = new TestInputDevice();
			_playerAI = new PlayerAI(_inputDevice);
			player = new Player();
		}

		TEST_METHOD_CLEANUP(tearDown) {
			delete player;
			delete _playerAI;
			delete _inputDevice;
		}

		TEST_METHOD(testPlayerAITickUp) {
			_inputDevice->_up = true;

			_playerAI->tick(player, 0, NULL);

			Assert::AreEqual(-PLAYER_ACCELERATION, player->getVelocity().y, L"Up velocity did not update correctly");				
		}

		TEST_METHOD(testPlayerAITickDown) {
			_inputDevice->_down = true;

			_playerAI->tick(player, 0, NULL);
		
			Assert::AreEqual(PLAYER_ACCELERATION, player->getVelocity().y, L"Down velocity did not update correctly");
		}

		TEST_METHOD(testPlayerAITickRight) {
			_inputDevice->_right = true;

			_playerAI->tick(player, 0, NULL);

			Assert::AreEqual(PLAYER_ACCELERATION, player->getVelocity().x, L"Right velocity did not update correctly");
		}

		TEST_METHOD(testPlayerAITickLeft) {
			_inputDevice->_left = true;

			_playerAI->tick(player, 0, NULL);

			Assert::AreEqual(-PLAYER_ACCELERATION, player->getVelocity().x, L"Left velocity did not update correctly");
		}
	};
}