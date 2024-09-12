#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#define OLC_SOUNDWAVE
#include "olcSoundWaveEngine.h"

#define OLC_PGEX_POPUPMENU
#include "olcPGEX_PopUpMenu.h"


class Game : public olc::PixelGameEngine
{

public:

	Game()
	{
		sAppName = "Asher Bear's SPACE ADVENTURE v1.0";
	}

	olc::popup::Menu menu;
	olc::popup::Manager man;


	olc::Sprite* spriteEnemy[3];
	olc::Sprite* spriteBoss;
	olc::Sprite* kibble[2];
	olc::Sprite* kibbleS;
	olc::Sprite* spriteDrop[3];
	olc::Sprite* spriteTitle;
	olc::Sprite* background;
	olc::Sprite* sprMenu;
	olc::Sprite* pupSprite[1];
	olc::Sprite* StagS;
	olc::Sprite* StagG;
	olc::Sprite* spritePlayer = nullptr;
	olc::Sprite* splashScreen;

	olc::Pixel healthBar[2] = { olc::GREEN, olc::RED };
	olc::Pixel player;

	olc::sound::WaveEngine waveEngine;
	olc::sound::Wave music;
	olc::sound::Wave woof = olc::sound::Wave(1, sizeof(uint32_t), 44100, 44100);
	olc::sound::Wave pop_01 = olc::sound::Wave(1, sizeof(uint32_t), 44100, 44100);
	olc::sound::Wave pop_02 = olc::sound::Wave(1, sizeof(uint32_t), 44100, 44100);
	olc::sound::Wave fart_01 = olc::sound::Wave(1, sizeof(uint32_t), 44100, 44100);
	olc::sound::Wave fart_02 = olc::sound::Wave(1, sizeof(uint32_t), 44100, 44100);
	olc::sound::Wave fart_03 = olc::sound::Wave(1, sizeof(uint32_t), 44100, 44100);
	olc::sound::Wave fart_04 = olc::sound::Wave(1, sizeof(uint32_t), 44100, 44100);
	olc::sound::Wave death_01 = olc::sound::Wave(1, sizeof(uint32_t), 44100, 44100);
	olc::sound::Wave death_02 = olc::sound::Wave(1, sizeof(uint32_t), 44100, 44100);
	olc::sound::Wave death_03 = olc::sound::Wave(1, sizeof(uint32_t), 44100, 44100);
	olc::sound::Wave shit_empty = olc::sound::Wave(1, sizeof(uint32_t), 44100, 44100);
	olc::sound::Wave gameOver_01 = olc::sound::Wave(1, sizeof(uint32_t), 44100, 44100);
	olc::sound::Wave upgradeSound = olc::sound::Wave(1, sizeof(uint32_t), 44100, 44100);
	olc::sound::Wave downgradeSound = olc::sound::Wave(1, sizeof(uint32_t), 44100, 44100);
	olc::sound::WaveInstance* deathNoise;

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
	double dWorldEnd = 2800.0;

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
	int m_nPauseMode = MODE_UNPAUSE;
	int m_nTitleConfirm = 0;
	int m_nMenuMode = OFF;
	int fartSound = 0;

	std::string printScore = std::to_string(score);
	std::string printLatestScore;

	bool retry = false;
	bool bLevelPlus = false;
	bool bLevelClear = false;
	bool bUpgraded = false;
	bool bDead = false;
	bool bPaused = false;


	std::chrono::steady_clock::time_point upgradeTimeEnd;
	std::chrono::steady_clock::time_point gradeBegin, gradeEnd;


	std::array<olc::vf2d, 1100>aryStars;
	std::array<olc::vf2d, 1100>titleStars;


	enum
	{
		MODE_SPLASH,
		MODE_TITLE,
		MODE_NEWGAME,
		MODE_GAME,
		MODE_GRADE,
		MODE_GAME_OVER,
	};

	enum MENU_
	{
		OFF,
		ON,
	};


	enum _pause
	{
		MODE_PAUSE,
		MODE_UNPAUSE,
	};


	enum _sound_control
	{
		STOP,
		START,
		VOLUME_UP,
		VOLUME_DOWN
	};

	void autoFade(olc::Sprite* splash)
	{
		

	}

	void autoScrollBackground(float fElapsedTime)
	{
		float posX = 0.0f;
		float posY = 0.0f;
		olc::vf2d pos = { posX, posY };

		posX = GetMiddle(background).x;
		posY = GetMiddle(background).y;

		DrawSprite(pos, background, 2U);
	}

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

		DrawString(olc::vf2d(225.0f, (float)ScreenHeight() / 2), "PRESS START", olc::WHITE, 2U);



		if (GetKey(olc::Key::SPACE).bPressed && GO_TOKEN <= this->GO_TOKEN
			|| GetKey(olc::Key::SPACE).bPressed && GO_TOKEN <= this->GO_TOKEN && m_nGameMode == MODE_NEWGAME)
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

	void UpdateGrade(float fElapsedTime, bool bLevelFinished, int nSilver, int nGold)
	{
		double dWorldPos = this->dWorldPos;
		double dWorldEnd = this->dWorldEnd;

		std::string totalS, totalG;


		if (dWorldPos == dWorldEnd)
		{
			while (fElapsedTime < 180.0f)
			{
				if ((nSilver == 0) || (nSilver > 1 && nSilver < 8))
				{
					++fElapsedTime;
					DrawString(200, 300, std::to_string(nSilver));
					DrawRect(160, 360, 260, 100);
					DrawString(240, 380, "F");
					DrawString(180, 420, std::to_string(nTagS) + ": " + std::to_string(nTagG) + ": ");
				}
				break;
			}
		}
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
		uint32_t nSpawnID;
		float fOffset;
		std::function<void(sPUP&, float, float)>funcMove;
	};
	struct sPUP
	{
		olc::vf2d pos;
		sPUPDef def;
		bool remove = false;
		std::array<float, 4>DataMove{ 0 };

		void Update(float fElapsedTime, float fScrollSpeed, bool bRetrieved, std::list<sPUPDef>& pup)
		{
			def.funcMove(*this, fElapsedTime, fScrollSpeed);
		}

	};

	struct sTags;
	struct sTagsDefinition
	{
		std::function<void(sTags&, float, float)>funcMove;
	};

	struct sTags : sBullet
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

	};

	struct sEnemy
	{
		olc::vf2d pos;
		sEnemyDefinition def;
		bool isDestroyed = false;

		std::array<float, 4>DataMove{ 0 };
		std::array<float, 4>DataFire{ 0 };

		void Update(float fElapsedTime, float fScrollSpeed, bool destroyed, bool bHasPUP, std::list<sBullet>& bullets)
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
	std::list<sTagsDefinition>listBurst;
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
	std::list<olc::sound::Wave*>listFarts;
	std::list<olc::sound::PlayingWave>listPlayingFartSound;

	void timeBuffer()
	{
		std::chrono::steady_clock::time_point a =
			std::chrono::steady_clock::now() + std::chrono::seconds(8);
		std::chrono::steady_clock::time_point b =
			std::chrono::steady_clock::now();
		/*if (a < b) {....}*/

	}

	void approximateTags(sTags& tag, olc::vf2d& player)
	{
		player = vPlayerPos;
		
		if (tag.pos.x >= ((player.y * player.x) * 2) && tag.pos.y > player.y + 30.0f)
		{
			if ((tag.pos.x >= player.x) || (tag.pos.y >= player.y))
				tag.remove;

		}
	}

	bool Pause(float fElapsedTime)
	{
		//Draw Pause//
		if (bPaused == true)
		{
			std::string s = "PAUSED";
			DrawString({ ScreenWidth() / 2 - 10, ScreenHeight() / 2 }, s, olc::WHITE, 2U);
			GetMenu(0);
			if (GetKey(olc::ENTER).bPressed)
			{
				dWorldPos += fScrollSpeed * fElapsedTime;
				s.clear();
				bPaused = false;
			}
		}

		return true;
	}

	bool GetMenu(int id)
	{	
		olc::popup::Menu* command = nullptr;

		if (id == 0)
		{

			menu.SetTable(1, 5);
			menu["main"].SetTable(1, 3);
			menu["main"]["new game"].SetID(1);
			menu["main"]["options"].SetID(2);
			menu["main"]["exit"].SetID(3);


			if (GetKey(olc::UP).bPressed) { man.OnUp(); man.Close(); }
			if (GetKey(olc::DOWN).bPressed) { man.OnDown(); man.Close(); }
			if (GetKey(olc::LEFT).bPressed) { man.OnLeft(); man.Close(); }
			if (GetKey(olc::RIGHT).bPressed) { man.OnRight(); man.Close(); }
			if (GetKey(olc::X).bPressed) command = man.OnConfirm(); man.Close();
			menu.Build();

			if (command != nullptr)
			{
				std::string sLastAction =
					"Selected: " + command->GetName() + " ID: " +
					std::to_string(command->GetID());
				if (command->GetID() == 1)
				{
					listEnemyBullets.clear();
					listFragments.clear();
					listPlayerBullets.clear();
					listPowerup.clear();
					listPlayerShit.clear();

					if (dWorldPos >= dWorldEnd) dWorldPos = 0.0;
					dWorldPos = 0.0;	
					GO_TOKEN = 0;
					LVL_TOKEN = 0;
					bUpgraded = false;
					listTagsS.clear();
					listTagsG.clear();

					bPaused = false;
					bDead = false;
					fPlayerHealth = 1000.0f;
					fGunTemp = 0.0f;
					fShitTemp = 0.0f;
					vPlayerPos = { (float)ScreenWidth() / 2, (float)ScreenHeight() / 2 };
					m_nGameMode = MODE_NEWGAME;
					man.Close();
				}
				if (command->GetID() == 2)
				{
					menu["options"].SetTable(1, 3);
					menu["options"].Enable(true);
					menu["options"]["MUTE"].SetID(210);
					man.Open(&menu["options"]);
					if (command->GetID() == 210)
					{
						waveEngine.StopAll();

						if (command->GetID() == 210)
						{
							waveEngine.PlayWaveform(&music);
						}
					}
					man.Close();
				}
				if (command->GetID() == 3)
				{
					return OnUserDestroy();
				}

				man.Close();
			}

			man.Open(&menu["main"]);
			man.Draw(sprMenu, { 30, 30 });
			
		}

		return true;
	}

	bool GetCharacters()
	{
		spritePlayer = new olc::Sprite("gfx/BearPlayer.png");
		spriteEnemy[0] = new olc::Sprite("gfx/Pit.png");
		spriteEnemy[1] = new olc::Sprite("gfx/bEnemy1.png");
		spriteEnemy[2] = new olc::Sprite("gfx/bEnemy1.png");
		spriteBoss = new olc::Sprite("gfx/Pit_Boss.png");
		kibble[0] = new olc::Sprite("gfx/kibble.png");
		kibble[1] = new olc::Sprite("gfx/kibble1.png");
		kibbleS = new olc::Sprite("gfx/kibble+.png");
		spriteDrop[0] = new olc::Sprite("gfx/upgrade_01.png");
		spriteDrop[1] = new olc::Sprite("gfx/upgrade_02.png");
		spriteTitle = new olc::Sprite("gfx/title02.png");
		background = new olc::Sprite("gfx/background_stars2.png");
		sprMenu = new olc::Sprite("gfx/RetroMenu.png");
		StagS = new olc::Sprite("gfx/tags_silver.png");
		StagG = new olc::Sprite("gfx/tags_gold.png");

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

		auto Move_Straight_FastTS = [&](sTags& t, float fElapsedTime, float fScrollSpeed)
		{
			t.pos.y += 2.3f * (fScrollSpeed / 2.50) * fElapsedTime;
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

		auto Move_Gold_Tag_1 = [&](sTags& t, float fElapsedTime, float fScrollSpeed)
		{
			t.DataMove[0] += fElapsedTime;
			t.pos.y += 0.4f * fScrollSpeed * fElapsedTime;
			t.pos.x += 225.0f * cosf(t.DataMove[0]) * fElapsedTime;
		};
		
		auto Burst_Gold_Tag_1 = [&](sTags& t, float fElapsedTime, float fScrollSpeed)
		{
				t.def = listTagsDefG.back();

				constexpr float fDelay = 0.9f;
				constexpr float nBullets = 10;
				constexpr float fTheta = 2.0f * 3.14159f / (float)nBullets;
				t.DataMove[0] += fElapsedTime;
				if (t.DataMove[0] >= fDelay)
				{
					t.DataMove[0] -= fDelay;
					for (int i = 0; i < 10; i++)
					{
						t.pos = GetMiddle(spriteEnemy[2]);
						t.Vol = { 100.0f * cosf(fTheta * i), 100.0f * sinf(fTheta * i) };
						listTagsG.push_back(t);
					}
				}
				
		};

		//FIRING PATTERN FUNCTIONS//

		auto Fire_None = [&](sEnemy& e, float fElapsedTime, float fScrollSpeed, std::list<sBullet>& bullets)
		{
				e.pos.y += fScrollSpeed * fElapsedTime;
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
			{100.0, 0, 3.0f, Move_None,           Fire_StraightDelay2, 0.6f},
			{100.0, 0, 3.0f, Move_StraightFast,   Fire_DeathSpiral, 0.45f},
			{120.0, 1, 3.0f, Move_SinusoidNarrow, Fire_CirclePulse2, 0.2f},

			{200.0, 2, 3.0f, Move_SinusoidWide, Fire_CirclePulse2, 0.35f},
			{200.0, 2, 3.0f, Move_SinusoidWide, Fire_CirclePulse2, 0.70f},

			{500.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2, 0.25f},
			{500.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2, 0.48f},
			{500.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2, 0.62f},
			{500.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2, 0.81f},

			{550.0, 0, 3.0f, Move_StraightFast,   Fire_DeathSpiral, 0.3f},
			{550.0, 0, 3.0f, Move_StraightFast,   Fire_DeathSpiral, 0.6f},
			{550.0, 0, 3.0f, Move_StraightSlow,   Fire_DeathSpiralCircle, 0.5f},
			{550.0, 0, 3.0f, Move_StraightFast,   Fire_DeathSpiral, 0.6f},
			{550.0, 0, 3.0f, Move_StraightFast,   Fire_DeathSpiral, 0.9f},

			{600.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2, 0.25f},
			{600.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2, 0.46f},
			{600.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2, 0.67f},
			{600.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2, 0.82f},

			{1100.0, 0, 3.0f, Move_None,           Fire_CirclePulse2, 0.25f},
			{1100.0, 0, 3.0f, Move_StraightFast,   Fire_DeathSpiral, 0.75f},
			{1120.0, 1, 3.0f, Move_SinusoidNarrow, Fire_CirclePulse2, 0.50f},

			{1200.0, 2, 3.0f, Move_SinusoidWide, Fire_CirclePulse2, 0.30f},
			{1200.0, 2, 3.0f, Move_SinusoidWide, Fire_CirclePulse2, 0.70f},

			{1500.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2, 0.2f},
			{1500.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2, 0.4f},
			{1500.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2, 0.6f},
			{1500.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2, 0.8f},

			{1550.0, 0, 3.0f, Move_StraightFast,   Fire_DeathSpiral, 0.1f},
			{1550.0, 0, 3.0f, Move_StraightFast,   Fire_DeathSpiral, 0.3f},
			{1550.0, 0, 3.0f, Move_StraightSlow,   Fire_DeathSpiralCircle, 0.5f},
			{1550.0, 0, 3.0f, Move_StraightFast,   Fire_DeathSpiral, 0.7f},
			{1550.0, 0, 3.0f, Move_StraightFast,   Fire_DeathSpiral, 0.9f},

			{1600.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2, 0.2f},
			{1600.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2, 0.4f},
			{1600.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2, 0.6f},
			{1600.0, 0, 3.0f, Move_StraightFast,   Fire_StraightDelay2, 0.8f},

		};

		listBoss =
		{
			{1700.0, 3, 10.0f, Move_SinusoidWide_2, Boss_Fire_DeathCircle1, 0.15f},
		};

		listSpawns2 =
		{		
				{900.0, 0, 5.0f, Move_SinusoidWide, Fire_DeathSpiral, 0.2f},
				{900.0, 1, 5.0f, Move_None, Fire_StraightDelay2, 0.2f},
				{940.0, 2, 5.0f, Move_None, Fire_StraightDelay2, 0.6f},
				{960.0, 0, 5.0f, Move_SinusoidWide, Fire_StraightDelay2, 0.9f},

				{1200.0, 3, 6.0f, Move_StraightSlow, Fire_StraightDelay2, 0.4f},
				{1220.0, 2, 5.0f, Move_SinusoidNarrow, Fire_DeathSpiral, 0.6f},
				{1225.0, 0, 5.0f, Move_SinusoidWide, Fire_DeathSpiral, 0.9f},
				{1500.0, 1, 5.0f, Move_None, Fire_StraightDelay2, 0.4f},

				{1520.0, 2, 5.0f, Move_None, Fire_StraightDelay2, 0.6f},
				{1530.0, 0, 5.0f, Move_SinusoidWide, Fire_StraightDelay2, 1.0f},
				{1800.0, 3, 6.0f, Move_StraightSlow, Fire_StraightDelay2, 0.5f},
				{1821.0, 1, 4.0f, Move_None, Fire_CirclePulse2, 0.8f},

				{1850.0, 3, 10.0f, Move_StraightSlow, Fire_CirclePulse2, 1.0f},
				{1860.0, 3, 10.0f, Move_SinusoidWide, Fire_DeathSpiralCircle, 0.4f},
				{2100.0, 0, 5.0f, Move_SinusoidNarrow, Fire_CirclePulse2, 0.3f},
				{2118.0, 0, 7.0f, Move_StraightSlow, Fire_DeathSpiralCircle, 0.2f},

				{2118.0, 1, 7.0f, Move_StraightSlow, Fire_DeathSpiral, 0.8f},
				{2200.0, 2, 7.0f, Move_None, Fire_DeathSpiralCircle, 1.0f},
				{2220.0, 3, 10.0f, Move_None, Fire_None, 0.5f},
				{2220.0, 3, 10.0f, Move_None, Fire_None, 1.5f},
		};

		listDrop =
		{
			{500.0, 0, 0.6f, Move_Straight_Fast},
			{1000.0, 1, 0.5f, Move_SinusoidNarrowP},
			{1620.0, 0, 0.25f, Move_NoneP},
			{1880.0, 0, 0.33f, Move_SinusoidWide_2P},
			{2000.0, 1, 0.25f, Move_StraightSlowP},
			{2800.0, 0, 0.36f, Move_NoneP},
		};

		listTagsDefS =
		{
			{ Move_Straight_FastTS },
		};

		listTagsDefG =
		{
			{ Move_Gold_Tag_1 },
		};



		listFarts =
		{
			{&fart_01},
			{&fart_02},
			{&fart_03},
			{&fart_04},

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
		fart_02.LoadAudioWaveform("Fart_2.wav");
		fart_03.LoadAudioWaveform("Fart_3.wav");
		death_01.LoadAudioWaveform("death_01.wav");
		death_02.LoadAudioWaveform("death_02.wav");
		death_03.LoadAudioWaveform("death_03.wav");
		shit_empty.LoadAudioWaveform("shit_empty.wav");
		upgradeSound.LoadAudioWaveform("POWERUP.wav");
		downgradeSound.LoadAudioWaveform("POWERDOWN.wav");
		gameOver_01.LoadAudioWaveform("Game_Over_01.wav");

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
		case (MODE_NEWGAME):
			return this->UpdateTitle(fElapsedTime); break;
		}

		switch (bPaused)
		{
		case true: 
			return this->Pause(fElapsedTime); break;
		case false:
			 break;
		}

	
		double dWorldEnd = 2800.0;
		if (this->dWorldPos > dWorldEnd)
		{
			if (bLevelClear)
				dWorldPos = 0;
			else if (!bLevelClear)
				dWorldPos = dWorldEnd;
		}
		

		//Conditions for cheats//
		if (bDead == false)
		{
			//Cheats
			if (GetKey(olc::Key::P).bHeld)
				fPlayerHealth += 20.0f;

			if (GetKey(olc::Key::Q).bHeld)
			{
				fPlayerHealth = 0.0f;
				nLives -= 1;
				waveEngine.PlayWaveform(&death_02);
			}
		
			//Fast-Forward to first boss//
			if (GetKey(olc::Key::Z).bHeld)
			{
				listEnemies.clear();
				spriteEnemy[listSpawns.front().nSpriteID]->
					GetPixel({ spriteEnemy[listSpawns.front().nSpriteID]->width,spriteEnemy[listSpawns.front().nSpriteID]->height })
					= 0;
				listEnemyBullets.clear();
				listPowerup.clear();
				
				
				dWorldPos = 1500.0;
			}
			if (dWorldPos > 1500.0 && LVL_TOKEN == 0 && GetKey(olc::Key::Z).bHeld)
			{
				listEnemies.clear();
				spriteEnemy[listSpawns.front().nSpriteID]->GetPixel({ spriteEnemy[listSpawns.front().nSpriteID]->width,
					spriteEnemy[listSpawns.front().nSpriteID]->height }) = 0;
				listEnemyBullets.clear();
			
				dWorldPos = 1500.0;
			}

			if (GetKey(olc::Key::UP).bPressed)
			{
				sEnemy e;
				listEnemies.clear();
				listEnemyBullets.clear();
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
				listTagsS.clear();

				while ((LVL_TOKEN == 0) || ((dWorldPos > 0) || (dWorldPos < dWorldEnd)))
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

		if (bDead == true)
		{
			if (GetKey(olc::Key::P).bHeld)
				fPlayerHealth += 0.0f;
			if (GetKey(olc::Key::UP).bHeld)
				dWorldPos += 0.00;
			if (GetKey(olc::Key::Z).bHeld)
				dWorldPos += 0.00;

			fPlayerHealth = 0.0f;
			bUpgraded = false;
			fScrollSpeed = 0;

			if (vPlayerPos.y > ScreenHeight() + spritePlayer->height - 30)
				vPlayerPos.y = ScreenHeight() + spritePlayer->height - 30;
			DrawString((float)(ScreenWidth() / 2), (float)(ScreenHeight() / 2), "PRESS SPACE TO RETRY");


			if (GetKey(olc::SPACE).bPressed)
			{
				printLatestScore = printScore;
				score -= 20; if (score < 20) score = this->score; if (score <= 0) { score = 0; }
				printScore = score;
				dWorldPos -= 200.0;
				if (dWorldPos < 0.0) dWorldPos = 0.0;

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


		if (fPlayerHealth > 1000.0f)
			fPlayerHealth = 1000.0f;
		if (fPlayerHealth <= 0.0f)
			bDead = true;
		else
			bDead = false;
		

		//Audio Controls//

		//Mute / Unmute //
		if (GetKey(olc::M).bPressed)
		{
			waveEngine.SetOutputVolume(0);
			if (GetKey(olc::M).bPressed)
			{
				for (int i = 0; i <= 100; ++i)
					waveEngine.SetOutputVolume(i);
			}
		}

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
		if (GetKey(olc::ENTER).bPressed)
		{
			bPaused = true;
			GetMenu(0);
		}

		//"Clamps" player to screen//
		if (vPlayerPos.x <= 0) vPlayerPos.x = 0;
		if (vPlayerPos.x + (float)spritePlayer->width >= ScreenWidth()) vPlayerPos.x = (float)ScreenWidth() - spritePlayer->width;
		if (vPlayerPos.y <= 0) vPlayerPos.y = 0;
		if (vPlayerPos.y + (float)spritePlayer->height >= ScreenHeight()) vPlayerPos.y = (float)ScreenHeight() - spritePlayer->height;

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
		if (GetMouse(0).bPressed && fPlayerHealth > 0.0f)
		{
			if (bCanFire && fGunTemp < 80.0f)
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

		
		
		if (GetMouse(1).bHeld && fPlayerHealth > 0.0f)
		{
			bCanShit = true;
			if (fShitTemp < 0.0f) fShitTemp = 0.0f;
		
			if (bCanShit)
			{

				if (bCanShit)
				{
					fShitReload = (float)0.1f;
					fShitReloadTime = fShitReload;
					fShitTemp += (float)1.66;

					listPlayerShit.push_back
					({
						vPlayerPos +
						olc::vf2d((float)spritePlayer->width / 4.72, 36.0f), {10.0f,200.0f}
						});
					waveEngine.PlayWaveform(listFarts.front());
					if (fShitTemp > 60.0f)
					{
						bCanShit = false;
					}

				}
				else if (!bCanShit)
				{
					waveEngine.PlayWaveform(&shit_empty);
					if (fShitTemp > 0)
						fShitTemp -= 1.66;
				}
				
				 
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
						
						if (e.def.nSpriteID == 0) {
							waveEngine.PlayWaveform(&pop_02);
							waveEngine.PlayWaveform(&death_02);
						}
						if (e.def.nSpriteID > 0)
						{
							waveEngine.PlayWaveform(&pop_01); 
							waveEngine.PlayWaveform(&death_01);
						}

						if (e.def.nSpriteID == 0 || e.def.nSpriteID == 1 || e.def.nSpriteID == 2)
						{
							sTags tag;
							tag.def = listTagsDefS.front();
							tag.pos = e.pos;
							listTagsS.push_back(tag);
						}
						if (e.def.nSpriteID == 3)
						{
							sTags tag;
							tag.def = listTagsDefG.front();
							tag.pos = e.pos;
							listTagsG.push_back(tag);
						}
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
					if (!bUpgraded)
					{
						//Enemy has been hit//
						e.def.fHealth -= 1.0f;
						b.remove = true;
					}
					else if (bUpgraded)
					{
						e.def.fHealth -= 3.0f;
						b.remove = true;
					}
					//"Trigger Death Explosion"//
					if (e.def.fHealth <= 0.0f)
					{
						if (e.def.nSpriteID == 0)
						{
							waveEngine.PlayWaveform(&pop_01);
							waveEngine.PlayWaveform(&death_02);
						}
						if (e.def.nSpriteID > 0)
						{
							waveEngine.PlayWaveform(&pop_02);
							waveEngine.PlayWaveform(&death_01);
						}

						for (int i = 0; i < 30; i++)
						{
							float angle = ((float)rand() / RAND_MAX * 2.0f * 3.1459f);
							float speed = ((float)rand() / RAND_MAX * 200.0f + 50.0f);
							listFragments.push_back({
								e.pos + GetMiddle(spriteEnemy[e.def.nSpriteID]),
								{ cosf(angle) * speed, sinf(angle) * speed } });
						}
						if (e.def.nSpriteID == 0 || e.def.nSpriteID == 1 || e.def.nSpriteID == 2)
						{
							sTags tag;
							tag.def = listTagsDefS.front();
							tag.pos = e.pos;
							listTagsS.push_back(tag);
						}
						if (e.def.nSpriteID == 3)
						{
							sTags tag;
							tag.def = listBurst.front();
							tag.pos = e.pos;
							listTagsG.push_back(tag);

							
						}
						if (e.def.nSpriteID == 3 && dWorldPos < dWorldEnd)
						{										
							dWorldPos = dWorldEnd;
							bLevelClear = true;
							LVL_TOKEN += 1;
						}
					
					}
					if (e.def.nSpriteID == 3)
					{
						sTags tag;
						tag.def = listTagsDefG.front();
						tag.pos = { e.pos };
						listTagsG.push_back(tag);

					}
				}
			}
		}

	
		//Spawn Control//
		while (!listSpawns.empty() && dWorldPos >= listSpawns.front().dTriggerTime)
		{
			sEnemy e;

			e.def = listSpawns.front();
			e.pos =
			{
				listSpawns.front().offset * (float)(ScreenWidth() -
				spriteEnemy[e.def.nSpriteID]->width),
				0.0f - spriteEnemy[e.def.nSpriteID]->height
			};

		
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

		}

		//Health Drop spawn//
		while (!listDrop.empty() && dWorldPos >= listDrop.front().dTriggerTime)
		{
			sPUP p;
			p.def = listDrop.front();
     		p.pos =
			{
				listDrop.front().fOffset * (float)(ScreenWidth() - spriteDrop[p.def.nSpawnID]->width),
				0.0f - spriteDrop[p.def.nSpawnID]->height
			};
			listDrop.pop_front();
			listPowerup.push_back(p);
		}

	
		if (bLevelClear && dWorldPos >= dWorldEnd)
		{
			LVL_TOKEN += 1;
			dWorldPos = this->dWorldPos;
			dWorldEnd = this->dWorldEnd;
			UpdateGrade(fElapsedTime, bLevelClear, nTagS, nTagG);

			while (LVL_TOKEN == 1 && !listSpawns2.empty() && dWorldPos >= listSpawns2.front().dTriggerTime)
			{
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
		}

		//Update Enemy//
		for (auto& e : listEnemies)
			e.Update(fElapsedTime, fScrollSpeed, true, true, listEnemyBullets);
		

		//Update Drops//
		for (auto& p : listPowerup)
		{
			p.Update(fElapsedTime, fScrollSpeed, true, listDrop);
			if (p.def.nSpawnID == 0 && (p.pos - (vPlayerPos + olc::vf2d(2.0f, 4.0f))).mag2() < fShipRad)
			{
				fPlayerHealth += 200.0f;
				p.remove = true;
			}
			if (p.def.nSpawnID == 1 && (p.pos - (vPlayerPos + olc::vf2d(2.0f, 4.0f))).mag2() < fShipRad)
			{
				bUpgraded = true;
				waveEngine.PlayWaveform(&upgradeSound);
				p.remove = true;
				upgradeTimeEnd = std::chrono::steady_clock::now() + std::chrono::seconds(10);
			}
			if (bUpgraded == true && std::chrono::steady_clock::now() > upgradeTimeEnd)
			{
				bUpgraded = false;
				waveEngine.PlayWaveform(&downgradeSound);
			}
		}

		//Update Silver Tags// 
		for (auto& t : listTagsS)
		{
			t.Update(fElapsedTime, fScrollSpeed, listTagsDefS);
			t.pos += (olc::vf2d(0.0f, fScrollSpeed)) * fElapsedTime / 1.5f;
			if ((t.pos - (vPlayerPos + olc::vf2d(4.0f, 4.0f))).mag2() < fShipRad)
			{
				nTagS++;
				t.remove = true;
			}
		}


		//Update Gold Tags//
		for (auto& t : listTagsG)
		{
			t.Update(fElapsedTime, fScrollSpeed, listTagsDefG);
			t.pos += (olc::vf2d(0.0f, fScrollSpeed)) * fElapsedTime;
			if ((t.pos - (vPlayerPos + olc::vf2d(4.0f, 4.0f))).mag2() < fShipRad)
			{
				nTagG++;
				t.remove = true;
			}
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
				fPlayerHealth -= 10.0f;
			}

			if (fPlayerHealth <= 0.0f)
			{
				b.remove = true;
			}
		}

		//Ship Collision//
		for (auto& e : listEnemies)
		{
			if ((e.pos - (vPlayerPos + olc::vf2d(4.0f, 2.0f))).mag2() < fShipRad)
			{
				fPlayerHealth -= 50.0f;
			}
		}


		//Update Fragments//
		for (auto& f : listFragments)
		{
			f.Pos += (f.Vol + olc::vf2d(0.0f, fScrollSpeed)) * fElapsedTime * 2;
		}


		//Remove Offscreen Enemies//
		listEnemies.remove_if([&](const sEnemy& e) {return (e.pos.y >= (float)ScreenHeight()) || e.def.fHealth <= 0.0f; });
		listBoss.remove_if([&](const sEnemyDefinition& def) {return (def.fHealth <= 0.0f); });

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
			{return ((p.pos.y > ScreenHeight() || (p.remove))); }
		);

		//Remove collected and off-screen Silver Tags//
		listTagsS.remove_if
		(
			[&](const sTags& t)
			{return ((t.pos.y > ScreenHeight()) || (t.remove)); }
		);
	

		//Remove collected and off-screen Gold Tags//
		listTagsG.remove_if
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


			if (fPlayerHealth <= 0.0f && nLives == 0)
			{
				waveEngine.PlayWaveform(&gameOver_01);
				GO_TOKEN += 1;
				fScrollSpeed = 0;

				if (nLives == 0 && GO_TOKEN == 1)
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
						listTagsS.clear();
						listTagsG.clear();
						listPowerup.clear();


						retry = true;

						if (retry)
						{
							GO_TOKEN -= 1;
							m_nGameMode = MODE_GAME;
						}
						else
						{
							GO_TOKEN = 1;
							m_nGameMode = MODE_GAME_OVER;
						}
					}
				}
			}


		//GRAPHICS//
		Clear(olc::BLANK);
		

		//BACKGROUND//
		background->CLAMP;
		DrawSprite({ 0, 0 }, background, 1U);

		//Draw Player//
		if (bUpgraded == true)
		{
			olc::Pixel player = spritePlayer->GetPixel({ vPlayerPos });
			SetPixelMode(spritePlayer->GetPixel({ vPlayerPos }).ALPHA);
			player.a = 0;
			DrawSprite({ vPlayerPos }, spritePlayer);
		}
		if (bUpgraded == false)
		{
			olc::Pixel player = spritePlayer->GetPixel({ vPlayerPos });
			SetPixelMode(spritePlayer->GetPixel({ vPlayerPos }).MASK);
			player.g = 66;
			DrawSprite({ vPlayerPos }, spritePlayer);
		}
		

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
			olc::Pixel enemy = spriteEnemy[e.def.nSpriteID]->GetPixel({ e.pos });
			SetPixelMode(spriteEnemy[e.def.nSpriteID]->GetPixel({ e.pos }).ALPHA);
			enemy.a = 0;
			DrawSprite(e.pos, spriteEnemy[e.def.nSpriteID]);
		}

		//Draw Boss//
		for (auto& b : listBoss)
		{
			sEnemy e;
			e.def = b;
			olc::Pixel boss = spriteBoss->GetPixel({ spriteBoss->width, spriteBoss->height });
			SetPixelMode(spriteBoss->GetPixel({ spriteBoss->width, spriteBoss->height }).ALPHA);
			boss.a = 0;
			e.pos = { listBoss.front().offset * (float)(ScreenWidth() - spriteEnemy[e.def.nSpriteID]->width),
				0.0f - spriteEnemy[e.def.nSpriteID]->height };
		}

		//Draw PUPS//
		for (auto& p : listPowerup)
		{
			if (p.def.nSpawnID == 0)
			{
				olc::Pixel pup0 = spriteDrop[p.def.nSpawnID]->GetPixel({ p.pos });
				SetPixelMode(spriteDrop[p.def.nSpawnID]->GetPixel({ p.pos }).ALPHA);
				pup0.a = 0;
				DrawSprite({ p.pos }, spriteDrop[p.def.nSpawnID], 1U);
			}
			if (p.def.nSpawnID == 1)
			{
				olc::Pixel pup1 = spriteDrop[p.def.nSpawnID]->GetPixel({ p.pos });
				SetPixelMode(spriteDrop[p.def.nSpawnID]->GetPixel({ p.pos }).ALPHA);
				pup1.a = 0;
				DrawSprite({ p.pos }, spriteDrop[p.def.nSpawnID], 1U);
			}
		}

		//Draw Silver Tags//
		for (auto& st : listTagsS)
		{
			olc::Pixel tag = StagS->GetPixel({ st.pos });
			SetPixelMode(StagS->GetPixel({ st.pos }).ALPHA);
			tag.a = 0;
			DrawSprite({ st.pos }, StagS);
		}

		//Draw Gold Tags//
		for (auto& gt : listTagsG)
		{
			olc::Pixel tag = StagG->GetPixel({ gt.pos });
			SetPixelMode(StagG->GetPixel({ gt.pos }).ALPHA);
			tag.a = 0;
			DrawSprite({ gt.pos }, StagG);
		}

		//Draw Bullets//
		for (auto& b : listEnemyBullets)
		{
			FillCircle(b.Pos, 3, olc::RED);
		}

		//Draw Player Bullets//
		for (auto& b : listPlayerBullets)
		{

			if (!bUpgraded)
			{
				olc::Pixel bullet = kibble[0]->GetPixel({ b.Pos });
				SetPixelMode(kibble[0]->GetPixel({ b.Pos }).ALPHA);
				bullet.a = 0;
				DrawSprite(b.Pos, kibble[0]);
			}
			if (bUpgraded)
			{

				olc::Pixel bullet = kibble[1]->GetPixel({ b.Pos });
				SetPixelMode(kibble[1]->GetPixel({ b.Pos }).ALPHA);
				bullet.a = 0;
				DrawSprite(b.Pos, kibble[1]);
			}
			
		}

		//Draw Fragments//
		for (auto& f : listFragments)
		{
			olc::Pixel frag = kibbleS->GetPixel({ f.Pos });
			SetPixelMode(kibbleS->GetPixel({ f.Pos }).ALPHA);
			frag.a = 0;
			DrawSprite(f.Pos, kibbleS);
		}

		//Draw Shit//
		for (auto& s : listPlayerShit)
		{
			olc::Pixel shit = kibbleS->GetPixel({ s.Pos });
			SetPixelMode(kibbleS->GetPixel({ s.Pos }).ALPHA);
			shit.a = 0;
			DrawSprite(s.Pos, kibbleS);
		}

		


		//Draw Player Health Bar//
		DrawString(4, 4, "HEALTH: ");
		FillRect(64, 4, (fPlayerHealth / 1000.0f * 576.0f), 8, olc::GREEN);
		
		//WEAPON//
		DrawString(4, 16, "WEAPON: ");
		DrawString(4, 32, "TEMP: ");
		DrawString(48, 32, std::to_string(fGunTemp));
		FillRect(60, 16, (fGunTemp / 100.0f * 576.0f), 8, olc::YELLOW);

		//SHIT//
		DrawString(4, 48, "SHIT: ");
		FillRect(48, 48, (fShitTemp), 8, olc::BROWN);

		//Draw Score
		DrawString(20, 80, "SCORE: ", olc::YELLOW);
		DrawString(34, 100, std::to_string(score));
		DrawString(20, 120, "LATEST: ");
		DrawString(34, 140, printLatestScore);

		//Draw Lives
		DrawString(84, 240, std::to_string(nLives));
		DrawString(25, 240, "LIVES: ");
		

		//Draw level #
		DrawString(8, 80, std::to_string(LVL_TOKEN));


		//Draw Silver Tag Count
		DrawString(34, 320, std::to_string(nTagS));
		DrawSprite({ 25, 280 }, StagS, 1U);

		//Draw Gold Tag Count
		DrawString(70, 320, std::to_string(nTagG));
		DrawSprite({ 60, 280 }, StagG, 1U);

		//Draw RETRY status//
		DrawString({(ScreenWidth() / 2), (ScreenHeight() / 20)}, std::to_string((int)retry));

		//Instructions//
		if (nLives >= 3 && LVL_TOKEN == 1)
		{
			if (dWorldPos < 380.0)
			{
				DrawRect(160, 360, 260, 100);
				DrawString(240, 380, "CLICK TO SHOOT");
				DrawString(180, 420, "RIGHT-CLICK TO TAKE A SHIT!");
			}
			else if (dWorldPos >= 380.0)
			{
				DrawString(120, 360, " ");
				DrawString(70, 270, " ");
			}

			if (dWorldPos > 380.0 && dWorldPos < 520.0)
			{
				DrawRect(160, 360, 260, 100);
				DrawString(240, 380, "WASD to move");
			}
			else if (dWorldPos >= 520.0)
			{
				DrawString(480, 360, " ");
			}
		}
		else if (nLives < 3)
		{
			if (dWorldPos < 380.0)
			{
				DrawString(240, 388, " ");
			}
			if (dWorldPos < 520.0)
			{
				DrawString(240, 388, " ");
			}
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
		fScrollSpeed = 0;
		ClearBuffer(aryStars.size());
		listEnemies.clear();
		listEnemyBullets.clear();
		listPlayerBullets.clear();
		listPlayerShit.clear();
		listPowerup.clear();
		listTagsS.clear();
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

		if (GetKey(olc::SPACE).bPressed)
		{
			m_nGameMode = MODE_TITLE;
		}



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