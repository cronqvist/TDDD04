#include "stdafx.h"
#include "CppUnitTest.h"

#include "Player.h"
#include "Shot.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackLagoontests
{		
	TEST_CLASS(PlayerTests)
	{
		Player* _player;

	public:

		TEST_METHOD_INITIALIZE(setUp)
		{
			_player = new Player();
		}
		TEST_METHOD_CLEANUP(tearDown)
		{
			delete _player;
		}
		
		TEST_METHOD(testAmmoDecreaseWhenFire)
		{
			HTEXTURE texture = 0;
			hgeSprite* sprite = new hgeSprite(texture, 0, 0, 0, 0);
			Shot* shot = new Shot(sprite);

			_player->Ammo = 100;

			_player->setNewShot(shot);

			Assert::AreEqual(99, _player->Ammo, L"Ammo count did not decrease");
		}

	};
}