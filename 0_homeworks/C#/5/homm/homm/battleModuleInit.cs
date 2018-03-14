using System;

namespace homm {
	partial class BattleModule {
		public BattleModule(BattleMap.LandscapeTypes type) {
			mapPrintPos.x = 37;
			mapPrintPos.y = 1;
			map = new BattleMap();
			map.GenerateLandscape(type);
			arrow = new ArrowBattle();
			currPlayer = pl;
		}

		public void SetLeftArmy(ref Army left) {
			pl = left;
			pl.SetUnitsPosX(0);
		}
		public void SetRightArmy(ref Army right) {
			pr = right;
			pr.SetUnitsPosX(14);
		}

		void BeforeExit() {
			pr.SetUnitsPosX(-1);
			pl.SetUnitsPosX(-1);
		}
	}
}
