#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#define OLC_SOUNDWAVE
#include "olcSoundWaveEngine.h"

#include <algorithm>
#include <cstdint>
#include <array>
#include <time.h>
#include <stdio.h>

class Game : public olc::PixelGameEngine
{

public:

	Game()
	{
		sAppName = "Asher Bear's SPACE ADVENTURE v1.0";
	}

	

	olc::Sprite* spritePlayer = nullptr;
	olc::Sprite* spriteEnemy[3];
	olc::Sprite* spriteBoss;
	olc::Sprite* kibble[1];
	olc::Sprite* kibbleS;
	olc::Sprite* spriteDrop;
	olc::Sprite* spriteTitle;
	olc::Sprite* background;
	olc::Sprite* menu;
	olc::Sprite* pupSprite[1];
	olc::Sprite* StagS;

	olc::Pixel healthBar[2] = { olc::GREEN, olc::RED };


protected:
	olc::sound::WaveEngine waveEngine;
	olc::sound::Wave music;
	olc::sound::Wave woof = olc::sound::Wave(1, sizeof(uint32_t), 44100, 44100);
	olc::sound::Wave pop_01 = olc::sound::Wave(1, sizeof(uint32_t), 44100, 44100);
	olc::sound::Wave pop_02 = olc::sound::Wave(1, sizeof(uint32_t), 44100, 44100);
	olc::sound::Wave fart_01 = olc::sound::Wave(1, sizeof(uint32_t), 44100, 44100);
	olc::sound::Wave fart_02 = olc::sound::Wave(1, sizeof(uint32_t), 44100, 44100);
	olc::sound::Wave fart_03 = olc::sound::Wave(1, sizeof(uint32_t), 44100, 44100);

public:
	olc::vf2d vPlayerPos;

	float fPlayerSpeed = 100.0f;
	float fScrollSpeed = 45.0f;
	float fShipRad = 24 * 24;
	float fPlayerHealth = 1000.0f;
	float fGunTemp = 0.0f;
	float fGunReload = 0.2f;
	float fGunReloadTime = 0.0f;
	float fShitTemp = 0.0f;
	float fShitReload = 0.0f;
	float fShitReloadTime = 0.2f;

	double dWorldPos = 0.0f;

	uint32_t GO_TOKEN = 0;
	uint32_t D_TOKEN = 0;
	uint32_t NG_TOKEN = 0;
	uint32_t LVL_TOKEN = 1;
	uint32_t nLives = 3;
	uint32_t nFartNoise = 0;
	uint32_t nTagS = 0;
	uint32_t nTagG = 0;

	int score;
	int m_nGameMode = MODE_TITLE;
	int m_nTitleConfirm = 0;
	int m_nMenuItem = 0;


	std::string printScore = std::to_string(score);
	std::string printLatestScore;

	bool retry = false;
	bool bLevelPlus = false;
	bool bLevelClear = false;

	bool bHasPUP = false;

	std::array<olc::vf2d, 1100>aryStars;
	std::array<olc::vf2d, 1100>titleStars;

	std::array<int, 3>aryFarts;
	std::array<olc::sound::Wave, 3>aryFartSamples;

	enum
	{
		MODE_TITLE,
		MODE_GAME,
		MODE_GAME_OVER
	};


	enum _menu_item
	{
		MODE_START,
		MODE_0,
		MODE_1,
		QUIT,
	};
	std::array<std::string, 2>menuItem;

	enum _sound_control
	{
		STOP,
		START,
		VOLUME_UP,
		VOLUME_DOWN
	};

	

	bool UpdateTitle(float fElapsedTime)
	{
		Clear(olc::BLACK);
		DrawSprite(5, 5, spriteTitle, 2U);

		//More star programming//
		for (size_t i = 0; i < titleStars.size(); i++)
		{
			auto& t = titleStars[i];
			auto& t2 = titleStars[i];
			auto& s = aryStars[i];

			t.y += ((fScrollSpeed / 0.33) * (fElapsedTime / 2.33) * ((i < titleStars.size() >> 3) ? 0.0f : 1.0f));
			t.y -= ((fScrollSpeed / 0.33) * (fElapsedTime / 2.33) * ((i < titleStars.size() >> 2) ? 0.0f : 1.0f));

			if (t.y >= ((float)ScreenHeight()) && (t.y != ((float)ScreenHeight() * (float)ScreenWidth())))
			{
				t.y = { (float)(rand() % ScreenHeight()) };
				if (t.y >= (float)ScreenWidth())
					t.y = (float)ScreenWidth();
			}

			t.x += ((fScrollSpeed / 0.33) * (fElapsedTime / 2.33) * ((i < titleStars.size() >> 2) ? 0.0f : 1.0f));
			t.x -= ((fScrollSpeed / 0.33) * (fElapsedTime / 2.33) * ((i < titleStars.size() >> 2) ? 0.0f : 1.0f));

			if (t.x >= ((float)ScreenWidth()) && (t.x != ((float)ScreenWidth() * (float)ScreenHeight())))
			{
				t.x = { (float)(rand() % ScreenWidth()) };
				if (t.x >= (float)ScreenWidth())
					t.x = (float)ScreenWidth();
			}

			t2.y += ((fScrollSpeed / 0.33) * (fElapsedTime / 2.99) * ((i < titleStars.size() >> 4) ? 0.0f : 1.0f));


			if (t2.y >= (float)ScreenHeight() && t2.y != (float)ScreenHeight() * 1.50)
			{
				t2.y = { (float)(rand() % ScreenHeight()) };
			}
			if (t2.y < 0.0f) t.y = t2.y + (float)ScreenHeight();
			if (t2.y > (float)ScreenHeight()) t.y = t2.y - (float)ScreenHeight();

			t2.x += ((fScrollSpeed / 0.99) * fElapsedTime / 2.99) * ((i < titleStars.size() >> 2) ? 0.0f : 1.0f);
			t2.x -= ((fScrollSpeed / 0.99) * fElapsedTime / 2.99) * ((i < titleStars.size() >> 2) ? 0.0f : 1.0f);


			if (t2.x >= ((float)ScreenWidth()) && (t2.x != ((float)ScreenWidth())))
			{
				t2.x = { (float)(rand() % ScreenWidth()) };
				if (t2.x >= (float)ScreenWidth())
					t2.x = (float)ScreenWidth();
			}
			if (t2.x < 0.0f) t.x = t2.x + (float)ScreenWidth();
			if (t2.x > (float)ScreenWidth()) t.x = t2.x - (float)ScreenWidth();

			Draw(t, (i < titleStars.size() >> 1) ? olc::WHITE : olc::DARK_GREY);
			Draw(s, (i < aryStars.size() >> 1) ? olc::WHITE : olc::DARK_GREY);
			Draw(t2, (i < titleStars.size() >> 1) ? olc::WHITE : olc::DARK_GREY);

			SetPixelMode(olc::Pixel::MASK);
		}
	
		SetPixelMode(olc::Pixel::MASK);

		DrawString(olc::vf2d(225.0f, (float)ScreenHeight() / 2), "PRESS START", olc::WHITE, 2U);

		if (GetKey(olc::Key::SPACE).bPressed && GO_TOKEN <= this->GO_TOKEN)
		{
			GO_TOKEN = this->GO_TOKEN;
			nLives = this->nLives;
			dWorldPos = this->dWorldPos;
			fScrollSpeed = this->fScrollSpeed;
			fElapsedTime = 0.0f;

			m_nGameMode = MODE_GAME;
			return OnUserUpdate(fElapsedTime);
		}
		if (GetKey(olc::Key::ESCAPE).bHeld)
			return 0;



		return true;
	}


	olc::vf2d GetMiddle(olc::Sprite* s)
	{
		return { (float)s->width / 2.0f,(float)s->height / 2.0f };
	}




	//STRUCTS//

	struct sBullet
	{
		olc::vf2d Pos;
		olc::vf2d Vol;
		bool remove = false;
	};


	struct sEnemy;
	struct sPUP;
	struct sPUPDef 
	{
		double dTriggerTime;
		uint32_t nSpriteID = 0;
		uint32_t nSpawnID = 0;
		float fOffset;
		std::function<void(sPUP&, float, float)>funcMove;
	};
	struct sPUP
	{
		olc::vf2d pos;
		sPUPDef def;
		bool remove = false;
		std::array<float, 4>DataMove{ 0 };

		void Update(float fElapsedTime, float fScrollSpeed, bool bRetrieved, std::list<sPUPDef>&pup)
		{
			def.funcMove(*this, fElapsedTime, fScrollSpeed);
		}
	
	};

	struct sTags;
	struct sTagsDefinition
	{
		uint32_t nSpriteID = 0;
		uint32_t nSpawnID = 0;
		float fOffset;
		std::function<void(sTags&, float, float)>funcMove;
	};
	struct sTags
	{
		olc::vf2d pos;
		sTagsDefinition def;
		bool remove = false;
		std::array<float, 4>DataMove{ 0 };

		void Update(float fElapsedTime, float fScrollSpeed, std::list<sTagsDefinition>& tags)
		{
			def.funcMove(*this, fElapsedTime, fScrollSpeed);
		}
	};

	struct sEnemyDefinition
	{
		double dTriggerTime;
		uint32_t nSpriteID = 0;
		float fHealth = 0.0f;
		std::function<void(sEnemy&, float, float)>funcMove;
		std::function<void(sEnemy&, float, float, std::list<sBullet>& bullets)>funcFire;
		float offset = 0.0f;
		bool bDestroyed = false;
		bool bHasDrop = false;
	};

	struct sEnemy
	{
		olc::vf2d pos;
		sEnemyDefinition def;
		bool isDestroyed = false;
		bool bHasDrop = false;

		std::array<float, 4>DataMove{ 0 };
		std::array<float, 4>DataFire{ 0 };

		void Update(float fElapsedTime, float fScrollSpeed, bool destroyed, std::list<sBullet>& bullets)
		{
			def.funcMove(*this, fElapsedTime, fScrollSpeed);
			def.funcFire(*this, fElapsedTime, fScrollSpeed, bullets);
		}

	};

	//LISTS//
	std::list<sTags>listTagsS;
	std::list<sTags>listTagsG;
	std::list<sTagsDefinition>listTagsDefS;
	std::list<sTagsDefinition>listTagsDefG;
	std::list<sPUP>listPowerup;
	std::list<sPUPDef>listDrop;
	std::list<sEnemyDefinition>listSpawns;
	std::list<sEnemyDefinition>listSpawns2;
	std::list<sEnemyDefinition>listBoss;
	std::list<sEnemy>listEnemies;
	std::list<sBullet>listEnemyBullets;
	std::list<sBullet>listPlayerBullets;
	std::list<sBullet>listPlayerShit;
	std::list<olc::vf2d>listStars;
	std::list<olc::vf2d>listTitleStars;
	std::list<sBullet>listFragments;



	bool GetCharacters()
	{
		spritePlayer = new olc::Sprite("gfx/BearPlayer.png");
		spriteEnemy[0] = new olc::Sprite("gfx/Pit.png");
		spriteEnemy[1] = new olc::Sprite("gfx/bEnemy1.png");
		spriteEnemy[2] = new olc::Sprite("gfx/bEnemy1.png");
		spriteBoss = new olc::Sprite("gfx/Pit_Boss.png");
		kibble[0] = new olc::Sprite("gfx/kibble.png");
		kibbleS = new olc::Sprite("gfx/kibble+.png");
		spriteDrop = new olc::Sprite("gfx/upgrade_01.png");
		spriteTitle = new olc::Sprite("gfx/title02.png");
		background = new olc::Sprite("gfx/background_stars2.png");
		menu = new olc::Sprite("gfx/RetroMenu.png");
		pupSprite[0] = new olc::Sprite("gfx/upgrade_01.png");
		StagS = new olc::Sprite("gfx/tags_silver.png");

		return true;
	}

	bool GetStars()
	{
		//Star Array Generation//
		for (auto& s : aryStars) s = { (float)(rand() % ScreenWidth()),
			(float)(rand() % ScreenHeight()) };
		//Title//
		for (auto& t : titleStars) t =
		{ (float)(rand() % ScreenWidth() * 2),
			(float)(rand() % ScreenHeight() * 2) };

		return true;
	}

	bool GetSpawns()
	{
		//Movement Pattern Functions//
		auto Move_None = [&](sEnemy& e, float fElapsedTime, float fScrollSpeed)
		{
			e.pos.y += fScrollSpeed * fElapsedTime;
		};

		auto Move_NoneP = [&](sPUP& p, float fElapsedTime, float fScrollSpeed)
		{
			p.pos.y += fScrollSpeed * fElapsedTime;
		};

		auto Move_NoneTS = [&](sTags& t, float fElapsedTime, float fScrollSpeed)
		{
			t.pos.y += fScrollSpeed * fElapsedTime / 2;
		};

		auto Move_NoneTG = [&](sTags& t, float fElapsedTime, float fScrollSpeed)
		{
			t.pos.y += fScrollSpeed * fElapsedTime / 1;
		};

		auto Move_StraightFast = [&](sEnemy& e, float fElapsedTime, float fScrollSpeed)
		{
			e.pos.y += 3.0f * (fScrollSpeed / 2.50) * fElapsedTime;
		};
		
		auto Move_Straight_Fast = [&](sPUP& p, float fElapsedTime, float fScrollSpeed)
		{
			p.pos.y += 2.0f * (fScrollSpeed / 2.50) * fElapsedTime;
		};

		auto Move_StraightSlow = [&](sEnemy& e, float fElapsedTime, float fScrollSpeed)
		{
			e.pos.y += 0.5f * fScrollSpeed * fElapsedTime;
		};

		auto Move_StraightSlowP = [&](sPUP& p, float fElapsedTime, float fScrollSpeed)
		{
			p.pos.y += 0.7f * fScrollSpeed * fElapsedTime;
		};

		auto Move_SinusoidNarrow = [&](sEnemy& e, float fElapsedTime, float fScrollSpeed)
		{
			e.DataMove[0] += fElapsedTime;
			e.pos.y += 0.5f * fScrollSpeed * fElapsedTime;
			e.pos.x += 50.0f * cosf(e.DataMove[0]) * fElapsedTime;
		};

		auto Move_SinusoidNarrowP = [&](sPUP& p, float fElapsedTime, float fScrollSpeed)
		{
			p.DataMove[0] += fElapsedTime * 1.70;
			p.pos.y += 0.3f * fScrollSpeed * fElapsedTime;
			p.pos.x += 125.0f * cosf(p.DataMove[0]) * fElapsedTime / 2;
		};

		auto Move_SinusoidWide = [&](sEnemy& e, float fElapsedTime, float fScrollSpeed)
		{
			e.DataMove[0] += fElapsedTime;
			e.pos.y += 0.5f * fScrollSpeed * fElapsedTime;
			e.pos.x += 150.0f * cosf(e.DataMove[0]) * fElapsedTime;
		};

		auto Move_SinusoidWide_2 = [&](sEnemy& e, float fElapsedTime, float fScrollSpeed)
		{
			e.DataMove[0] += fElapsedTime * 1.5;
			e.pos.y += 0.2f * fScrollSpeed * fElapsedTime;
			e.pos.x += 450.0f * cosf(e.DataMove[0]) * fElapsedTime;
			if (e.pos.y > (float)ScreenHeight() / 3.33) e.pos.y = (float)ScreenHeight() / 3.33;
		};

		auto Move_SinusoidWide_2P = [&](sPUP& p, float fElapsedTime, float fScrollSpeed)
		{
			p.DataMove[0] += fElapsedTime * 1.5;
			p.pos.y += 0.2f * fScrollSpeed * fElapsedTime;
			p.pos.x += 225.0f * cosf(p.DataMove[0]) * fElapsedTime / 2;
		};

		//FIRING PATTERN FUNCTIONS//

		auto Fire_None = [&](sEnemy& e, float fElapsedTime, float fScrollSpeed)
		{

		};

		auto Fire_StraightDelay2 = [&](sEnemy& e, float fElapsedTime, float fScrollSpeed, std::list<sBullet>& bullets)
		{
			constexpr float fDelay = 0.2f;
			constexpr float nBullets = 10;
			e.DataFire[0] += fElapsedTime;
			if (e.DataFire[0] >= fDelay)
			{
				e.DataFire[0] -= fDelay;
				sBullet b;
				b.Pos = e.pos + olc::vf2d((float)spriteEnemy[e.def.nSpriteID]->width / 2.0f,
					(float)spriteEnemy[e.def.nSpriteID]->height / 2.0f);
				b.Vol = { 0.0f, 100.0f };
				bullets.push_back(b);
			}
		};

		auto Fire_Straight_Delay2_2 = [&](sEnemy& e, float fElapsedTime, float fScrollSpeed, std::list<sBullet>& bullet)
		{
			constexpr float fDelay = 0.2f;
			constexpr int nBullets = 10;

			e.DataFire[0] += fElapsedTime;
			if (e.DataFire[0] >= fDelay)
			{
				e.DataFire[0] -= fDelay;
				sBullet b;
				b.Pos = e.pos + olc::vf2d((float)spriteBoss->width / 2.0f,
					(float)spriteBoss->height / 2.0f);
				b.Vol = { 0.0f,100.0f };
				bullet.push_back(b);
			}
		};

		auto Fire_CirclePulse2 = [&](sEnemy& e, float fElapsedTime, float fScrollSpeed, std::list<sBullet>& bullets)
		{
			constexpr float fDelay = 0.9f;
			constexpr float nBullets = 10;
			constexpr float fTheta = 2.0f * 3.14159f / (float)nBullets;
			e.DataFire[0] += fElapsedTime;
			if (e.DataFire[0] >= fDelay)
			{
				e.DataFire[0] -= fDelay;
				for (int i = 0; i < nBullets; i++)
				{
					sBullet b;
					b.Pos = e.pos + GetMiddle(spriteEnemy[e.def.nSpriteID]);
					b.Vol = { 100.0f * cosf(fTheta * i), 100.0f * sinf(fTheta * i) };
					bullets.push_back(b);
				}
			}
		};

		auto Fire_CirclePulse2_2 = [&](sEnemy& e, float fElapsedTime, float fScrollSpeed, std::list<sBullet>& bullet)
		{
			constexpr float fDelay = 0.9f;
			constexpr int nBullets = 10;
			constexpr float fTheta = 2.0f * 3.141597 / (float)nBullets;

			e.DataFire[0] += fElapsedTime;
			if (e.DataFire[0] >= fDelay)
			{
				e.DataFire[0] -= fDelay;
				for (int i = 0; i < nBullets; i++)
				{
					sBullet b;
					b.Pos = e.pos + GetMiddle(spriteBoss);
					b.Vol = { 100.0f * cosf(fTheta * i), 100.0f * sinf(fTheta * i) };

					bullet.push_back(b);
				}
			}
		};

		auto Fire_DeathSpiral = [&](sEnemy& e, float fElapsedTime, float fScrollSpeed, std::list<sBullet>& bullets)
		{
			constexpr float fDelay = 0.8f;
			e.DataFire[0] += fElapsedTime;
			if (e.DataFire[0] >= fDelay)
			{
				e.DataFire[1] += 0.1f;
				e.DataFire[0] -= fDelay;
				sBullet b;
				b.Pos = e.pos + GetMiddle(spriteEnemy[e.def.nSpriteID]);
				b.Vol = { 100.0f * cosf(e.DataFire[1]), 100.0f * sinf(e.DataFire[1]) };
				bullets.push_back(b);
			}
		};

		auto Fire_DeathSpiralCircle = [&](sEnemy& e, float fElapsedTime, float fScrollSpeed, std::list<sBullet>& bullets)
		{
			constexpr float fDelay = 1.0f;
			constexpr int nBullets = 10;
			constexpr float fTheta = 2.0f * 3.14159f / (float)nBullets;
			e.DataFire[0] += fElapsedTime;
			if (e.DataFire[0] >= fDelay)
			{
				e.DataFire[0] -= fDelay;
				e.DataFire[1] += 0.1f;
				for (int i = 0; i < nBullets; i++)
				{
					sBullet b;
					b.Pos = e.pos + GetMiddle(spriteEnemy[e.def.nSpriteID]);
					b.Vol = { 100.0f * cosf(fTheta * i + e.DataFire[1]),100.0f
						* sinf(fTheta * i + e.DataFire[1]) };
					bullets.push_back(b);
				}
			}
		};

		auto Boss_Fire_DeathCircle1 = [&](sEnemy& e, float fElapsedTime, float fScrollSpeed, std::list<sBullet>& bullets)
		{
			constexpr float fDelay = 0.2f;
			constexpr int nBullets = 10;
			constexpr float fTheta = 2 * 3.141579 / (float)nBullets;
			e.DataFire[0] += fElapsedTime;
			if (e.DataFire[0] >= fDelay)
			{
				e.DataFire[0] -= fDelay;
				e.DataFire[1] += 0.2f;

				for (int i = 0; i < nBullets; i++)
				{
					sBullet b;
					b.Pos = e.pos + GetMiddle(spriteBoss);
					b.Vol =
					{
						100.0f * cosf(fTheta * i + e.DataFire[1]), 100.0f *
						sinf(fTheta * i + e.DataFire[1])
					};
					bullets.push_back(b);
				}
			}
		};

		//Construct level//
		listSpawns =
		{
			{100.0, 0, 3.0f, Move_None,           Fire_StraightDelay2, 0.6f,true},
			{100.0, 0, 3.0f, Move_StraightFast,   Fire_DeathSpiral,  0.45f, true},
			{120.0, 1, 3.0f, Move_SinusoidNarrow, Fire_CirclePulse2, 0.2f, true},

			{200.0, 2, 3.0f, Move_SinusoidWide, Fire_CirclePulse2, 0.35f},
			{200.0, 2, 3.0f, Move_SinusoidWide, Fire_CirclePulse2, 0.70f},

			{500.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2,  0.25f},
			{500.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2,  0.48f},
			{500.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2,  0.62f},
			{500.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2,  0.81f},

			{550.0, 0, 3.0f, Move_StraightFast,   Fire_DeathSpiral,  0.3f},
			{550.0, 0, 3.0f, Move_StraightFast,   Fire_DeathSpiral,  0.6f},
			{550.0, 0, 3.0f, Move_StraightSlow,   Fire_DeathSpiralCircle,  0.5f},
			{550.0, 0, 3.0f, Move_StraightFast,   Fire_DeathSpiral,  0.6f},
			{550.0, 0, 3.0f, Move_StraightFast,   Fire_DeathSpiral,  0.9f},

			{600.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2,  0.25f},
			{600.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2,  0.46f},
			{600.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2,  0.67f},
			{600.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2,  0.82f},

			{1100.0, 0, 3.0f, Move_None,           Fire_CirclePulse2, 0.25f},
			{1100.0, 0, 3.0f, Move_StraightFast,   Fire_DeathSpiral,  0.75f},
			{1120.0, 1, 3.0f, Move_SinusoidNarrow, Fire_CirclePulse2, 0.50f},

			{1200.0, 2, 3.0f, Move_SinusoidWide, Fire_CirclePulse2, 0.30f},
			{1200.0, 2, 3.0f, Move_SinusoidWide, Fire_CirclePulse2, 0.70f},

			{1500.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2,  0.2f},
			{1500.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2,  0.4f},
			{1500.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2,  0.6f},
			{1500.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2,  0.8f},

			{1550.0, 0, 3.0f, Move_StraightFast,   Fire_DeathSpiral,  0.1f},
			{1550.0, 0, 3.0f, Move_StraightFast,   Fire_DeathSpiral,  0.3f},
			{1550.0, 0, 3.0f, Move_StraightSlow,   Fire_DeathSpiralCircle,  0.5f},
			{1550.0, 0, 3.0f, Move_StraightFast,   Fire_DeathSpiral,  0.7f},
			{1550.0, 0, 3.0f, Move_StraightFast,   Fire_DeathSpiral,  0.9f},

			{1600.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2,  0.2f},
			{1600.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2,  0.4f},
			{1600.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2,  0.6f},
			{1600.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2,  0.8f},

		};

		listBoss =
		{
			{1700.0, 3, 10.0f, Move_SinusoidWide_2, Boss_Fire_DeathCircle1, 0.15f},
		};

		listSpawns2 =
		{
				{300.0, 0, 5.0f, Move_SinusoidWide_2, Fire_DeathSpiral, 0.7f},
				{300.0, 1, 5.0f, Move_None, Fire_StraightDelay2, 1.0f},
				{300.0, 2, 5.0f, Move_None, Fire_StraightDelay2, 0.6f},
				{300.0, 0, 5.0f, Move_SinusoidWide, Fire_StraightDelay2, 0.9f},
				{400.0, 3, 6.0f, Move_StraightSlow, Fire_StraightDelay2, 0.4f},

				{500.0, 0, 5.0f, Move_SinusoidWide, Fire_DeathSpiral, 0.9f},
				{500.0, 1, 5.0f, Move_None, Fire_StraightDelay2, 0.4f},
				{520.0, 2, 5.0f, Move_None, Fire_StraightDelay2, 0.6f},
				{530.0, 0, 5.0f, Move_SinusoidWide, Fire_StraightDelay2, 0.5f},
				{600.0, 3, 6.0f, Move_StraightSlow, Fire_StraightDelay2, 0.5f},
				{650.0, 3, 10.0f, Move_StraightSlow, Fire_CirclePulse2, 1.0f},

		};

		listDrop =
		{
			{500.0, 0, 0, 0.6f, Move_Straight_Fast},
			{1000.0, 1, 1, 0.5f, Move_SinusoidNarrowP},
			{1250.0, 0, 2, 0.25f, Move_NoneP},
			{1400.0, 1, 3, 0.33f, Move_SinusoidWide_2P},
		};

		listTagsDefS =
		{
			{0,0,0.0f, Move_NoneTS},
		};
	
		return true;
	}

	bool GetMusic()
	{
		waveEngine.InitialiseAudio(44100, 1);
		music = olc::sound::Wave(1, sizeof(uint16_t), 44100, 44100);
		music.LoadAudioWaveform("AsheTheme.wav");

		waveEngine.PlayWaveform(&music, true);


		return true;
	}

	bool GetSplash(float fElapsedTime)
	{
		olc::Sprite* splash = new olc::Sprite("gfx/background.png");
		splash->width = 400;
		splash->height = 300;


		if (fElapsedTime < 10.0f)
		{
			DrawSprite(splash->width, splash->height, splash);
		}

		return true;
	}

	bool OnUserCreate() override
	{
		GetCharacters();
		GetStars();
		GetSpawns();
		GetMusic();
		woof.LoadAudioWaveform("woof.wav");
		pop_01.LoadAudioWaveform("gfx/pop_01.wav");
		pop_02.LoadAudioWaveform("pop_02.wav");
		fart_01.LoadAudioWaveform("Fart_0.wav"); 
		fart_02.LoadAudioWaveform("Fart_1.wav");
		fart_03.LoadAudioWaveform("Fart_2.wav");
	

		vPlayerPos = { (float)ScreenWidth() / 2,(float)ScreenHeight() / 2 };


		return true;
	}


	bool OnUserUpdate(float fElapsedTime) override
	{

		switch (m_nGameMode)
		{
		case (MODE_TITLE):
			return this->UpdateTitle(fElapsedTime); break;
		case (MODE_GAME_OVER):
			return this->GameOver(fElapsedTime); break;
		}

		double dWorldEnd = 2800.0;
		uint32_t nEnemies = (uint32_t)listSpawns.size();
		if (nEnemies != 0 && listSpawns.front().fHealth == 0.0f) nEnemies--;
		else {}
		if (listSpawns.size() == 0)
			nEnemies = 0;
		uint32_t nBoss = (uint32_t)listBoss.size();
		if (nBoss != 0)
		{

			if (listBoss.front().fHealth == 0.0f)
				if (dWorldPos < dWorldEnd)
				{
					bLevelClear = true;
				}
				else { bLevelClear = false; }
		}
		if (nBoss <= 0 && !bLevelClear)
		{

			if (dWorldPos >= dWorldEnd)
			{
				dWorldPos = 0.0;
				bLevelClear = true;
				LVL_TOKEN++;
			}
			else { bLevelClear = false; }
		}


		//Conditions for cheats//
		if (fPlayerHealth > 0.0f)
		{
			//Cheats
			if (GetKey(olc::Key::P).bHeld)
				fPlayerHealth += 20.0f;

			if (GetKey(olc::Key::Q).bHeld)
			{
				fPlayerHealth = 0.0f;
			}
			if (GetKey(olc::Key::Z).bHeld)
			{
				listEnemies.clear();
				spriteEnemy[listSpawns.front().nSpriteID]->
					GetPixel({ spriteEnemy[listSpawns.front().nSpriteID]->width,spriteEnemy[listSpawns.front().nSpriteID]->height })
					= 0;
				listEnemyBullets.clear();

				dWorldPos = 1500.0;

			}

			if (GetKey(olc::Key::UP).bPressed)
			{
				sEnemy e;
				listEnemies.clear();
				listEnemyBullets.clear();
				listPlayerBullets.clear();
				listPlayerShit.clear();
				listPowerup.clear();
				listTagsS.clear();

				
				while (LVL_TOKEN == 0 && dWorldPos <= 1600.0)
				{
					e.def = listSpawns.front();
					spriteEnemy[listSpawns.front().nSpriteID]->
						GetPixel({ spriteEnemy[listSpawns.front().nSpriteID]->width,
									spriteEnemy[listSpawns.front().nSpriteID]->height
							}) = 0;
					break;
				}
				while (LVL_TOKEN == 0 && dWorldPos <= 2800.0)
				{
					e.def = listBoss.front();
					spriteEnemy[listBoss.front().nSpriteID]->
						GetPixel({ spriteEnemy[listBoss.front().nSpriteID]->width,
							spriteEnemy[listBoss.front().nSpriteID]->height }) = 0;
					break;
				}
				while (LVL_TOKEN == 1 && dWorldPos < 650.0)
				{
					e.def = listSpawns2.front();
					spriteEnemy[listSpawns2.front().nSpriteID]->GetPixel({ spriteEnemy[listSpawns2.front().nSpriteID]->width,
						spriteEnemy[listSpawns2.front().nSpriteID]->height }) = 0;
					break;
				}

				dWorldPos++;
				listEnemies.push_back(e);
			}

			if (GetKey(olc::Key::DOWN).bHeld)
			{
				sEnemy e;

				listEnemies.clear();
				listEnemyBullets.clear();
				listPowerup.clear();
				
				while ((LVL_TOKEN == 0 || LVL_TOKEN == 1) || ((dWorldPos > 0) || (dWorldPos < dWorldEnd )))
				{
					e.def = listSpawns.back();

					spriteEnemy[listSpawns.front().nSpriteID]->GetPixel({ spriteEnemy[listSpawns.front().nSpriteID]->width,
						spriteEnemy[listSpawns.front().nSpriteID]->height }) = 0;

					break;
				}
				--dWorldPos;
				listEnemies.push_front(e);
			} 


		} 
		else if (fPlayerHealth <= 0.0f && nLives < 0)
		{
			if (GetKey(olc::Key::P).bHeld)
				fPlayerHealth = 0.0f;
			if (GetKey(olc::Key::UP).bHeld)
				dWorldPos = this->dWorldPos;

			m_nGameMode = MODE_GAME_OVER;
		}

		if (fPlayerHealth > 1000.0f)
			fPlayerHealth = 1000.0f;


		//Draw score
		DrawString(37, 80, std::to_string(score));

		//AutoScroll world//
		dWorldPos += fScrollSpeed * fElapsedTime;

		//Scroll Player Object//
		vPlayerPos.y += fScrollSpeed * fElapsedTime;



		//Handke input//
		if (GetKey(olc::W).bHeld && fScrollSpeed > 0) vPlayerPos.y -= (fPlayerSpeed + fScrollSpeed) * fElapsedTime;
		if (GetKey(olc::S).bHeld && fScrollSpeed > 0) vPlayerPos.y += (fPlayerSpeed - fScrollSpeed) * fElapsedTime;
		if (GetKey(olc::A).bHeld && fScrollSpeed > 0) vPlayerPos.x -= fPlayerSpeed * fElapsedTime * 2.0f;
		if (GetKey(olc::D).bHeld && fScrollSpeed > 0) vPlayerPos.x += fPlayerSpeed * fElapsedTime * 2.0f;

		if (GetKey(olc::ESCAPE).bPressed) return 0;

		//"Clamps" player to screen//
		if (vPlayerPos.x <= 0) vPlayerPos.x = 0;
		if (vPlayerPos.x + (float)spritePlayer->width >= ScreenWidth()) vPlayerPos.x = (float)ScreenWidth() - spritePlayer->width;
		if (vPlayerPos.y <= 0) vPlayerPos.y = 0;

		//Screen Limits
		if (vPlayerPos.y + (float)spritePlayer->height >= ScreenHeight())
			vPlayerPos.y = (float)ScreenHeight() - spritePlayer->height;

		if (vPlayerPos.y + (float)spritePlayer->height > (float)ScreenHeight() - 30)
			vPlayerPos.y = ((float)ScreenHeight() - spritePlayer->height - 30);



		//Player Fire//
		bool bCanFire = false;
		bool bCanShit = false;
		fGunReloadTime -= fElapsedTime;
		fShitReloadTime -= fElapsedTime;
		if (fGunReloadTime <= 0.0f)
		{
			bCanFire = true;
		}
		if (fShitReloadTime <= 0.0f)
		{
			bCanShit = true;
		}


		fGunTemp -= fElapsedTime * 13.5f;
		if (fGunTemp < 0.0f) fGunTemp = 0.0f;
		if (GetMouse(0).bHeld && fPlayerHealth > 0.0f)
		{
			if (bCanFire && fGunTemp < 100.0f)
			{
				fGunReloadTime = fGunReload;
				fGunTemp += 5.0f;
				if (fGunTemp > 100.0f) fGunTemp = 100.0f;
				
				listPlayerBullets.push_back({
					vPlayerPos + olc::vf2d((float)spritePlayer->width / 2.0f,0.0f),{0.0f,-200.0f} });
				waveEngine.PlayWaveform(&woof);
			}
					

			if (fPlayerHealth <= 0.0f)
			{
				bCanFire = false;
				fGunReload = fElapsedTime * 10;
			}
		}

		fShitTemp -= fElapsedTime * 10.0f;
		if (fShitTemp < 0.0f) fShitTemp = 0.0f;

		if (GetMouse(1).bHeld && fPlayerHealth > 0.0f)
		{
			float fTimeHeld = 0;
			fTimeHeld += fElapsedTime;

			if (bCanShit && fShitTemp < 50.0f)
			{
				fShitReload = (float)0.01;
				fShitReloadTime = fShitReload / 0.33;
				fShitTemp += (float)2.66;

				listPlayerShit.push_back
				({
					vPlayerPos +
					olc::vf2d((float)spritePlayer->width / 4.72, 36.0f), {10.0f,200.0f}

					});
			}

		}

		//Update Shit
		for (auto& s : listPlayerShit)
		{
			//Position Shit
			s.Pos += (s.Vol + olc::vf2d(0.0f, fScrollSpeed / 2)) * fElapsedTime;

			for (auto& e : listEnemies)
			{
				if ((s.Pos - (e.pos + olc::vf2d(15.0f, 12.0f))).mag2() < fShipRad)
				{
					e.def.fHealth -= 1.0f;
					s.remove = true;

					//"Trigger Death Explosion"//
					if (e.def.fHealth <= 0.0f)
					{
						for (int i = 0; i < 30; i++)
						{
							float angle = ((float)rand() / RAND_MAX * 2.0f * 3.1459f);
							float speed = ((float)rand() / RAND_MAX * 200.0f + 50.0f);
							listFragments.push_back({
								e.pos + GetMiddle(spriteEnemy[e.def.nSpriteID]),
								{ cosf(angle) * speed, sinf(angle) * speed } });
						}
						if (e.def.nSpriteID == 0) waveEngine.PlayWaveform(&pop_01);
						if (e.def.nSpriteID > 0) waveEngine.PlayWaveform(&pop_02);
					}

				}
			}
		}

		//Update Player Bullets//
		for (auto& b : listPlayerBullets)
		{
			//Position Bullets//
			b.Pos += (b.Vol + olc::vf2d(0.0f, fScrollSpeed)) * fElapsedTime;

			for (auto& e : listEnemies)
			{
					if ((b.Pos - (e.pos + olc::vf2d(12.0f, 12.0f))).mag2() < fShipRad)
					{
						//Enemy has been hit//
						e.def.fHealth -= 1.0f;
						b.remove = true;

						//"Trigger Death Explosion"//
						if (e.def.fHealth <= 0.0f)
						{
							nEnemies--;
							waveEngine.PlayWaveform(&pop_01);

							for (int i = 0; i < 30; i++)
							{
								float angle = ((float)rand() / RAND_MAX * 2.0f * 3.1459f);
								float speed = ((float)rand() / RAND_MAX * 200.0f + 50.0f);
								listFragments.push_back({
									e.pos + GetMiddle(spriteEnemy[e.def.nSpriteID]),
									{ cosf(angle) * speed, sinf(angle) * speed } });
							}
						}
					} 
			}
		}

		for (auto& p : listPowerup)
		{
			if (p.pos.x >= vPlayerPos.x && p.pos.y >= vPlayerPos.y)
			{
				fPlayerHealth += 200.0f;
				p.remove = true;
			}
		}

		for (auto& ts : listTagsS)
		{
			
				if (ts.pos.x >= vPlayerPos.x && ts.pos.y >= vPlayerPos.y)
				{
					nTagS++;
					ts.remove = true;
				}
		}

		for (auto& tg : listTagsG)
		{
			if (tg.pos.x >= vPlayerPos.x && tg.pos.y >= vPlayerPos.y)
			{
				nTagG++;
				tg.remove = true;
			}

			
		}

		//Spawn Control//
		while (!listSpawns.empty() && dWorldPos >= listSpawns.front().dTriggerTime)
		{
			LVL_TOKEN = 1;
			sEnemy e;

			e.def = listSpawns.front();
			e.pos =
			{
				listSpawns.front().offset * (float)(ScreenWidth() -
				spriteEnemy[e.def.nSpriteID]->width),
				0.0f - spriteEnemy[e.def.nSpriteID]->height
			};

			if (listSpawns.size() < 1)
			{
				break;
			}


			listSpawns.pop_front();
			listEnemies.push_back(e);

		}

		while (!listBoss.empty() && dWorldPos >= listBoss.front().dTriggerTime)
		{
			sEnemy e;
	
			e.def = listBoss.front();
			e.pos =
			{
				listBoss.front().offset * (float)(ScreenWidth() - spriteEnemy[e.def.nSpriteID]->width),
				0.0f - spriteEnemy[e.def.nSpriteID]->height
			};


			listBoss.pop_front();
			listEnemies.push_back(e);

			break;
		}
		

		if (bLevelClear)
		{
			dWorldPos += fScrollSpeed * fElapsedTime;
			const double dWorldEnd = 2800.0;
			nEnemies = listSpawns2.size();

			while (LVL_TOKEN == 2 && !listSpawns2.empty() && dWorldPos >= listSpawns2.front().dTriggerTime)
			{
				bLevelPlus = false;
				sEnemy e;

				e.def = listSpawns2.front();
				e.pos =
				{
					listSpawns2.front().offset * (float)(ScreenWidth() -
					spriteEnemy[e.def.nSpriteID]->width),
					0.0f - spriteEnemy[e.def.nSpriteID]->height
				};


				listSpawns2.pop_front();
				listEnemies.push_back(e);

				break;
			}

			while (listSpawns2.empty())
			{
				if (dWorldPos == dWorldEnd)
				{
					bLevelClear = true;
					LVL_TOKEN++;
					m_nGameMode = MODE_GAME_OVER;
					dWorldPos = this->dWorldPos;
				}
				break;
			}
		}

		while (!listDrop.empty() && dWorldPos >= listDrop.front().dTriggerTime)
		{
			sPUP p;
			p.def = listDrop.front();
			p.pos =
			{
				listDrop.front().fOffset * (float)(ScreenWidth() - pupSprite[p.def.nSpriteID]->width),
				0.0f - pupSprite[p.def.nSpriteID]->height
			};
			listDrop.pop_front();
			listPowerup.push_back(p);

		}


		//Update Enemy//
		for (auto& e : listEnemies)
			e.Update(fElapsedTime, fScrollSpeed, true, listEnemyBullets);


		//Update Drops//
		for (auto& p : listPowerup)
		{
			p.Update(fElapsedTime, fScrollSpeed, bHasPUP, listDrop);
		}

		//Update Silver Tags//
		for (auto& ts : listTagsS)
		{
			ts.Update(fElapsedTime, fScrollSpeed, listTagsDefS);
		}

		//Update Score//
		for (auto& e : listEnemies)
		{
			//Count score
			if (e.def.fHealth <= 0.0f)
				printScore = std::to_string(++score);
		}


		//Update Enemy Bullets//
		for (auto& b : listEnemyBullets)
		{
			//Position Bullet//
			b.Pos += (b.Vol + olc::vf2d(0.0f, fScrollSpeed)) * fElapsedTime;

			//Check Player Bullets Against Enemy Bullets//
			if ((b.Pos - (vPlayerPos + olc::vf2d(24.0f, 24.0f))).mag2() < fShipRad)
			{
				b.remove = true;
				fPlayerHealth -= 30.0f;
			}

			if (fPlayerHealth <= 0.0f)
				b.remove = false;
		}


		//Update Fragments//
		for (auto& f : listFragments) f.Pos += (f.Vol + olc::vf2d(0.0f, fScrollSpeed)) * fElapsedTime * 2;

		//Remove Offscreen Enemies//
		listEnemies.remove_if([&](const sEnemy& e) {return (e.pos.y >= (float)ScreenHeight()) || e.def.fHealth <= 0.0f; });

		//Remove Finished Enemy Bullets//
		listEnemyBullets.remove_if([&](const sBullet& b) {return (b.Pos.x<0 || b.Pos.x > ScreenWidth() || b.Pos.y<0 || b.Pos.y>ScreenHeight() || b.remove); });

		//Remove Finished Fragments//
		listFragments.remove_if
		(
			[&](const sBullet& b)
			{return b.Pos.x < 0 || b.Pos.x > ScreenWidth() || b.Pos.y < 0 || b.Pos.y > ScreenHeight() || b.remove; }
		);
		//Remove collected and off-screen PUPS//
		listPowerup.remove_if
		(
			[&](const sPUP& p)
			{return ((p.pos.y > ScreenHeight() || (bHasPUP && D_TOKEN > 0) || (p.remove))); }
		);

		//Remove collected and off-screen Silver Tags//
		listTagsS.remove_if
		(
			[&](const sTags& t)
			{return ((t.pos.y > ScreenHeight() || (t.remove))); }
		);

		//Remove player bullets//
		listPlayerBullets.remove_if
		(
			[&](const sBullet& b)
			{return b.remove; }
		);

		//Remove player shit//
		listPlayerShit.remove_if
		(
			[&](const sBullet& s)
			{return (s.remove || s.Pos.x < 0 || s.Pos.x > ScreenWidth() || s.Pos.y < 0 || s.Pos.y > ScreenHeight()); }
		);

	gameOver:
		if (fPlayerHealth <= 0.0f)
		{
			GO_TOKEN = 1;
			fPlayerHealth = 0.0f;
			fScrollSpeed = 0;

			SetPixelMode(olc::Pixel::NORMAL);
			DrawString((float)ScreenHeight() / 2, ScreenHeight() / 2, "PRESS SPACE TO RETRY");



			if (fPlayerHealth <= 0.0f && nLives > 0)
			{
				if (GetKey(olc::SPACE).bHeld)
				{
					GO_TOKEN--;
					nLives--;
					printLatestScore = printScore;
					score = 0;
					printScore = score;
					dWorldPos -= 200.0;
					if (dWorldPos < 0.0) dWorldPos = 0.0;
					listEnemies.front().pos.y = listEnemies.front().pos.y - 300.0f;
					listEnemies.back().pos.y = listEnemies.back().pos.y - 300.0f;


					vPlayerPos.y = vPlayerPos.y + 100.0f;
					fPlayerHealth = 1000.0f;
					fPlayerSpeed = 100.0f;
					fScrollSpeed = 45.0f;

					fGunTemp = 0.0f;
					fShitTemp = 0.0f;
					listEnemyBullets.clear();
					listPlayerBullets.clear();
				}
			}

			if (nLives == 0 && GO_TOKEN == 0)
			{
				if (GetKey(olc::Key::SPACE).bReleased)
				{
					m_nGameMode = MODE_GAME_OVER;
				}
			}
		}
		if (nLives == 0 && GO_TOKEN != 0)
		{
			if (GetKey(olc::Key::SPACE).bPressed)
			{
				spriteEnemy[listSpawns.front().nSpriteID]->
					GetPixel({ spriteEnemy[listSpawns.front().nSpriteID]->width,
								spriteEnemy[listSpawns.front().nSpriteID]->height }) = 0;

				spritePlayer->GetPixel({ spritePlayer->width, spritePlayer->height }) = 0;
				background->GetPixel({ background->width, background->height }) = 0;

				listEnemies.clear();
				listEnemyBullets.clear();
				listPlayerBullets.clear();
				listPlayerShit.clear();
				listPowerup.clear();
				listTagsS.clear();
				listTagsG.clear();

				retry = true;

			}
		}

		if (m_nGameMode == MODE_TITLE && GetKey(olc::Key::SPACE).bReleased)
		{
			while (retry)
			{

				fScrollSpeed = 45.0f;
				dWorldPos = 0.0;
				nLives = 3;
				fPlayerHealth = 1000.0f;

				//Handke input//
				if (GetKey(olc::W).bHeld && fScrollSpeed > 0) vPlayerPos.y -= (fPlayerSpeed + fScrollSpeed) * fElapsedTime;
				if (GetKey(olc::S).bHeld && fScrollSpeed > 0) vPlayerPos.y += (fPlayerSpeed - fScrollSpeed) * fElapsedTime;
				if (GetKey(olc::A).bHeld && fScrollSpeed > 0) vPlayerPos.x -= fPlayerSpeed * fElapsedTime * 2.0f;
				if (GetKey(olc::D).bHeld && fScrollSpeed > 0) vPlayerPos.x += fPlayerSpeed * fElapsedTime * 2.0f;



				return OnUserCreate();
				return OnUserUpdate(fElapsedTime);

				break;
			}
		}



		//GRAPHICS//
		Clear(olc::BLACK);
		
		//BACKGROUND//
		DrawSprite({ 5, 5 }, background, 1U);

		//Draw Player//
		DrawSprite({ vPlayerPos }, spritePlayer);
		SetPixelMode(spritePlayer->GetPixel({ spritePlayer->width, spritePlayer->height }).ALPHA);

		//More star programming//
		for (size_t i = 0; i < aryStars.size(); i++)
		{
			auto& s = aryStars[i];
			auto& s2 = aryStars[i];

			s.y += ((fScrollSpeed / 2.50) * fElapsedTime) * ((i < aryStars.size() >> 2) ? 0.0f : 1.0f);
			if (s.y >= (float)ScreenHeight())
				s.y = { (float)(rand() % ScreenHeight()) };

			s.x += ((fScrollSpeed / 0.33) * fElapsedTime / 2.99) * ((i < aryStars.size() >> 2) ? 0.0f : 1.0f);
			if (s.x >= (float)ScreenWidth())
				s.x = { (float)(rand() % ScreenWidth()) };

			s2.y += ((fScrollSpeed / 0.33) * fElapsedTime / 2.33) * ((i < aryStars.size() >> 2) ? 0.0f : 1.0f);
			s2.y -= ((fScrollSpeed / 0.33) * fElapsedTime / 2.33) * ((i < aryStars.size() >> 2) ? 0.0f : 1.0f);

			if (s2.y >= (float)ScreenHeight())
				s2.y = { (float)(rand() % ScreenHeight()) };
			if (s2.y >= (float)ScreenHeight())
				s2.y = s.y - ScreenHeight();
			if (s2.y < 0.0f)
				s2.y = s.y + ScreenHeight();

			s2.x += ((fScrollSpeed / 0.99) * fElapsedTime / 2.99) * ((i < aryStars.size() >> 2) ? 0.0f : 1.0f);
			s2.x -= ((fScrollSpeed / 0.99) * fElapsedTime / 2.99) * ((i < aryStars.size() >> 2) ? 0.0f : 1.0f);

			if (s2.x >= (float)ScreenWidth())
				s2.x = { (float)(rand() % ScreenWidth()) };
			if (s2.x > (float)ScreenWidth())
				s2.x = s.x - ScreenWidth();
			if (s2.x < 0.0f)
				s2.x = s.x + ScreenWidth();

			Draw(s, (i < aryStars.size() >> 2) ? olc::DARK_GREY : olc::WHITE);
			Draw(s2, (i < aryStars.size() >> 2) ? olc::DARK_GREY : olc::WHITE);

			SetPixelMode(olc::Pixel::NORMAL);
		}

		//Draw Enemies//
		for (auto& e : listEnemies)
		{
			DrawSprite(e.pos, spriteEnemy[e.def.nSpriteID]);
		}

		//Draw PUPS//
		for (auto& p : listPowerup)
		{
			DrawSprite({ p.pos }, pupSprite[p.def.nSpriteID], 1U);
		}

		//Draw Silver Tags//
		for (auto& ts : listTagsS)
		{
			DrawSprite({ ts.pos }, StagS, 1U);
		}

		//Draw Bullets//
		for (auto& b : listEnemyBullets)
		{
			FillCircle(b.Pos, 3, olc::RED);
		}

		//Draw Player Bullets//
		for (auto& b : listPlayerBullets)
		{
			DrawSprite(b.Pos, kibble[0]);
		}

		//Draw Fragments//
		for (auto& f : listFragments)
		{
			DrawSprite(f.Pos, kibbleS);
		}

		//Draw Shit//
		for (auto& s : listPlayerShit)
		{
			DrawSprite(s.Pos, kibbleS);
		}

		

		//Draw Player Health Bar//
		DrawString(4, 4, "HEALTH: ");
		FillRect(60, 16, (fPlayerHealth / 1000.0f * 576.0f), 8, healthBar[1]);
		


		//WEAPON//
		DrawString(4, 16, "WEAPON: ");
		DrawString(4, 32, "TEMP: ");
		DrawString(48, 32, std::to_string(fGunTemp));
		FillRect(60, 16, (fGunTemp), 8, olc::YELLOW); 
		FillRect(60, 16, (fGunTemp), 8, olc::RED); 

		//SHIT//
		DrawString(4, 48, "SHIT: ");
		FillRect(48, 48, (fShitTemp / 100.0f * 120.0f), 8, olc::BROWN);

		//Draw Score
		DrawString(20, 80, "SCORE: ", olc::YELLOW);
		DrawString(34, 100, std::to_string(score));
		DrawString(20, 120, "LATEST: ");
		DrawString(34, 140, printLatestScore);

		//Draw Lives
		DrawString(34, 360, std::to_string(nLives));
		DrawString(25, 320, "LIVES: ");

		//Draw level #
		DrawString(8, 80, std::to_string(LVL_TOKEN));

		//Draw Enemy Count
		DrawString(54, 100, std::to_string(nEnemies));

		//Instructions//
		if (dWorldPos < 380.0)
		{
			DrawString(120, 360, "CLICK TO SHOOT");
		}
		else if (dWorldPos >= 380.0)
		{
			DrawString(120, 360, " ");
		}

		if (dWorldPos < 380.0)
		{
			DrawString(480, 360, "WASD to move");
		}
		else if (dWorldPos >= 380.0)
		{
			DrawString(480, 360, " ");
		}

		//Draw world pos
		DrawString(80, 80, std::to_string((short)(int)dWorldPos));


		return true;
	}


	void ResetScore()
	{
		if (this->score != 0)
			this->score = 0;
		DrawString(37, 80, std::to_string(0));
	}

	bool GameOver(float fElapsedTime)
	{
		Clear(olc::BLACK);
		DrawString({ (ScreenWidth() / 2), (ScreenHeight() / 2) }, "GAME OVER", 2U);

		for (size_t t = 0; t < aryStars.size() || titleStars.size(); t++)
		{
			auto& s0 = aryStars[t];
			auto& t0 = titleStars[t];

			s0.x += ((fScrollSpeed / 0.33) * (fElapsedTime / 2.33) * ((t < aryStars.size() >> 2 ? 1 : 0)));
			t0.x += ((fScrollSpeed / 0.33) * (fElapsedTime / 2) * ((t < titleStars.size() >> 2 ? 1 : 0)));

			Draw(s0, (t < aryStars.size() ? olc::WHITE : olc::DARK_GREY));
			Draw(t0, (t < titleStars.size() ? olc::WHITE : olc::DARK_GREY));
		}

		if (GetKey(olc::ENTER).bReleased)
			m_nGameMode = MODE_TITLE;



		return true;
	}

	bool OnUserDestroy() override
	{
		waveEngine.DestroyAudio();
		exit(0);
		return true;
	}


};



int main()
{
	Game g;
	

	if (g.Construct(640, 480, 4, 4, true))
	{	
		g.Start();
	}
	return 0;
}