using System;

namespace homm {
	partial class BattleModule {
		void ChangePlayer() {
			if (currPlayer == pl)
				currPlayer = pr;
			else if (currPlayer == pr)
				currPlayer = pl;
		}

		ref Army GetEnemyPlayer() {
			if (currPlayer == pl)
				return ref pr;
			else if (currPlayer == pr)
				return ref pl;
			throw new ArgumentException("No curr Player");
		}
	}
}
