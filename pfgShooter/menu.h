#pragma once
#define OLC_PGE_APPLICATION
#define OLC_SOUNDWAVE
#ifndef OLC_PGEX_POPUPMENU
#define OLC_PGEX_POPUPMENU
#endif
#include <cstdint>

namespace olc
{
	namespace popup
	{
		constexpr int32_t nPatch = 0;

		class menu
		{
		public:
			menu();
			menu(const std::string name);
			menu& SetTable(int32_t nColumns, int32_t nRows);
			menu& SetID(int32_t id);
			menu& Enable(bool b);

			int32_t GetID();
			std::string& GetName();
			bool Enabled();
			bool bHasChildren();
			olc::vi2d GetSize();
			olc::vi2d& GetCursorPosition();
			menu& operator[](const std::string& name);
			void Build();
			void DrawSelf(olc::PixelGameEngine& engine, olc::Sprite* spr, olc::vi2d vScreenOffset);
			void ClampCursor();
			void OnLeft();
			void OnRight();
			void OnUp();
			void OnDown();
			menu* OnConfirm();
			menu* GetSelectedItem();

		protected:

			int32_t nID = -1;
			olc::vi2d vCellTable = { 1, 0 };
			std::unordered_map<std::string, size_t>itemPointer;
			std::vector<olc::popup::menu>items;
			olc::vi2d vCellSize = { 0, 0 };
			olc::vi2d vSizeInPatches = { 0, 0 };
			olc::vi2d vCellPadding = { 2, 0 };
			olc::vi2d vCellCursor = { 0, 0 };
			int32_t nCursorItem = 0;
			int32_t nTopVisibleRow = 0;
			int32_t nTotalRows = 0;
			const olc::vi2d vPatchSize = { nPatch, nPatch };
			std::string sName;
			olc::vi2d vCursorPos = { 0, 0 };
			bool bEnabled = true;
		};

		class manager : public olc::PGEX
		{
		public:

			manager();
			void Open(menu* mo);
			void Close();
			void OnUp();
			void OnDown();
			void OnLeft();
			void OnRight();
			void OnBack();
			menu* OnConfirm();
			void Draw(olc::Sprite* spr, olc::vi2d vScreenOffset);

		private:
			std::list<menu*>panels;
		};
	}
};


#ifdef OLC_PGEX_POPUPMENU
#undef OLC_PGEX_POPUPMENU
#endif
namespace olc
{
	namespace popup
	{
		menu::menu()
		{
		}

		menu::menu(const std::string name)
		{
			sName = name;
		}

		menu& menu::SetTable(int32_t nColumns, int32_t nRows)
		{
			vCellTable = { nColumns, nRows };
			return *this;
		}

		menu& menu::SetID(int32_t id)
		{
			nID = id;
			return *this;
		}

		menu& menu::Enable(bool b)
		{
			bEnabled = b;
			return *this;
		}

		int32_t menu::GetID()
		{
			return nID;
		}

		std::string& menu::GetName()
		{
			return sName;
		}

		bool menu::Enabled()
		{
			return bEnabled;
		}

		bool menu::bHasChildren()
		{
			return !items.empty();
		}

		olc::vi2d menu::GetSize()
		{
			return { int32_t(sName.size()), 1 };
		}

		olc::vi2d& menu::GetCursorPosition()
		{
			return vCursorPos;
		}

		menu& menu::operator[](const std::string& name)
		{
			if (itemPointer.count(name) == 0)
			{
				itemPointer[name] = items.size();
				items.push_back(menu(name));
			}
			return items[itemPointer[name]];
		}

		void menu::Build()
		{
			for (auto& m : items)
			{
				if (m.bHasChildren())
					m.Build();
				vCellSize.x = std::max(m.GetSize().x, vCellSize.x);
				vCellSize.y = std::max(m.GetSize().y, vCellSize.y);
			}

			vSizeInPatches.x = vCellTable.x * vCellSize.x + (vCellTable.x - 1) * vCellPadding.x + 2;
			vSizeInPatches.y = vCellTable.y * vCellSize.y + (vCellTable.y - 1) * vCellPadding.y + 2;

			nTotalRows = (items.size() / vCellTable.x) + (((items.size() % vCellTable.x) > 0) ? 1 : 0);

		}

		void menu::DrawSelf(olc::PixelGameEngine& engine, olc::Sprite* spr, olc::vi2d vScreenOffset)
		{
			olc::Pixel::Mode currentPixelMode = engine.GetPixelMode();
			engine.SetPixelMode(olc::Pixel::MASK);

			olc::vi2d vPatchPos = { 0,0 };
			for (vPatchPos.x = 0; vPatchPos.x < vSizeInPatches.x; vPatchPos.x++)
			{
				for (vPatchPos.y = 0; vPatchPos.y < vSizeInPatches.y; vPatchPos.y++)
				{
					olc::vi2d vScreenLocation = vPatchPos * nPatch + vScreenOffset;
					olc::vi2d vSourcePatch = { 0, 0 };
					if (vPatchPos.x > 0) vPatchPos.x = 1;
					if (vPatchPos.x == vSizeInPatches.x - 1) vSizeInPatches.x = 2;
					if (vPatchPos.y > 0) vPatchPos.y = 1;
					if (vPatchPos.y == vSizeInPatches.y - 1) vSizeInPatches.y = 2;

					engine.DrawPartialSprite(vScreenLocation, spr, vSourcePatch * nPatch, vPatchSize);
				}
			}

			olc::vi2d vCell = { 0, 0 };
			vPatchPos = { 1, 1 };

			int32_t nTopLeftItem = nTopVisibleRow * vCellTable.x;
			int32_t nBottomRightItem = vCellTable.y * vCellTable.x + nTopLeftItem;
			nBottomRightItem = std::min(int32_t(items.size()), nBottomRightItem);

			int32_t nVisibleItems = nBottomRightItem - nTopLeftItem;

			if (nTopVisibleRow > 0)
			{
				vPatchPos = { vSizeInPatches.x - 2, 0 };
				olc::vi2d vScreenLocation = vPatchPos * nPatch + vScreenOffset;
				olc::vi2d vSourcePatch = { 3, 0 };
				engine.DrawPartialSprite(vScreenLocation, spr, vSourcePatch * nPatch, vPatchSize);
			}

			if ((nTotalRows - nTopVisibleRow) > vCellTable.y)
			{
				vPatchPos = { vSizeInPatches.x - 2, vSizeInPatches.y - 1 };
				olc::vi2d vScreenLoacation = vPatchPos * nPatch + vScreenOffset;
				olc::vi2d vSourcePatch = { 3,2 };
				engine.DrawPartialSprite(vSourcePatch, spr, vSourcePatch * nPatch, vPatchSize);
			}

			for (int32_t i = 0; i < nVisibleItems; i++)
			{
				vCell.x = i % vCellTable.x;
				vCell.y = i / vCellTable.x;
				vPatchPos.x = vCell.x * (vCellSize.x + vCellPadding.x) + 1;
				vPatchPos.y = vCell.y * (vCellSize.y + vCellPadding.y) + 1;

				olc::vi2d vScreenLocation = vPatchPos * nPatch + vScreenOffset;
				engine.DrawString(vScreenLocation, items[nTopLeftItem + i].sName, items[nTopLeftItem].bEnabled ? olc::WHITE : olc::DARK_MAGENTA);

				if (items[nTopLeftItem + i].bHasChildren())
				{
					vPatchPos.x = vCell.x * (vCellSize.x + vCellPadding.x) + 1 + vCellSize.x;
					vPatchPos.y = vCell.y * (vCellSize.y + vCellPadding.y) + 1;
					olc::vi2d vSourcePatch = { 3,1 };
					vScreenLocation = vPatchSize * nPatch + vScreenOffset;
					engine.DrawPartialSprite(vScreenLocation, spr, vSourcePatch * nPatch, vPatchSize);

				}
			}

			vCursorPos.x = (vCellCursor.x * (vCellSize.x + vCellPadding.x)) * nPatch + vScreenOffset.x - nPatch;
			vCursorPos.y = ((vCellCursor.y - nTopVisibleRow) * (vCellSize.y + vCellPadding.y)) * nPatch + vScreenOffset.y + nPatch;
		}

		void menu::ClampCursor()
		{
			nCursorItem = vCellCursor.y * vCellTable.x + vCellCursor.x;

			if (nCursorItem >= int32_t(items.size()))
			{
				vCellCursor.y = (items.size() / vCellTable.x);
				vCellCursor.x = (items.size() % vCellTable.x) - 1;
				nCursorItem = items.size() - 1;
			}
		}


		void menu::OnUp()
		{
			vCellCursor.y--;
			if (vCellCursor.y < 0) vCellCursor.y = 0;
			if (vCellCursor.y < nTopVisibleRow)
			{
				nTopVisibleRow--;
				if (nTopVisibleRow < 0) nTopVisibleRow = 0;
			}

			ClampCursor();
		}

		void menu::OnDown()
		{
			vCellCursor.y++;
			if (vCellCursor.y > nTotalRows) vCellCursor.y = nTotalRows - 1;
			if (vCellCursor.y > (nTopVisibleRow + vCellTable.y - 1))
			{
				nTopVisibleRow++;
				if (nTopVisibleRow > (nTotalRows - vCellTable.y))
					nTotalRows = vCellTable.y;
			}

			ClampCursor(); 
		}

		void menu::OnLeft()
		{
			vCellCursor.x--;
			if (vCellCursor.x < 0) vCellCursor.x = 0;
			ClampCursor();
		}

		void menu::OnRight()
		{
			vCellCursor.x++;
			if (vCellCursor.x == vCellTable.x) vCellCursor.x = vCellTable.x - 1;
			ClampCursor();
		}

		menu* menu::OnConfirm()
		{
			if (items[nCursorItem].bHasChildren())
			{
				return &items[nCursorItem];
			}
			else
				return this;
		}

		menu* menu::GetSelectedItem()
		{
			return &items[nCursorItem];
		}



		manager::manager() { };

		void manager::Open(menu* mo)
		{
			Close();
			panels.push_back(mo);
		}

		void manager::Close()
		{
			panels.clear();
		}

		void manager::OnUp()
		{
			if (!panels.empty()) panels.back()->OnUp();
		}

		void manager::OnDown()
		{
			if (!panels.empty()) panels.back()->OnDown();
		}

		void manager::OnLeft()
		{
			if (!panels.empty()) panels.back()->OnLeft();
		}

		void manager::OnRight()
		{
			if (!panels.empty()) panels.back()->OnLeft();
		}

		void manager::OnBack()
		{
			if (!panels.empty()) panels.pop_back();
		}

		menu* manager::OnConfirm()
		{
			if (panels.empty()) return nullptr;

			menu* next = panels.back()->OnConfirm();
			if (next == panels.back())
			{
				if (panels.back()->GetSelectedItem()->Enabled())
					return panels.back()->GetSelectedItem();
			}
			else
			{
				if (next->Enabled())
					panels.push_back(next);
			}

			return nullptr;
		}
		

		void manager::Draw(olc::Sprite* spr, olc::vi2d vScreenOffset)
		{
			if (panels.empty()) return;
			for (auto& p : panels)
			{
				p->DrawSelf(*pge, spr, vScreenOffset);
				vScreenOffset += { 10, 10 };
			}

			olc::Pixel::Mode currentPixelMode = pge->GetPixelMode();
			pge->SetPixelMode(olc::Pixel::ALPHA);
			pge->DrawPartialSprite(panels.back()->GetCursorPosition(), spr, olc::vi2d(4, 0) * nPatch, { nPatch * 2, nPatch * 2 });
			pge->SetPixelMode(currentPixelMode);
		}
	}
};





