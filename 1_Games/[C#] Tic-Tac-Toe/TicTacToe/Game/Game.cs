using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameLib {
	public class Game {
		Stack<PlayerType> playersPool = new Stack<PlayerType>();
		PlayerType currPlayer;
		FieldState[] field;

		public Game() {
			field = new FieldState[9];
			playersPool = new Stack<PlayerType>(2);
		}

		public void StartNewGame() {
			currPlayer = PlayerType.PlayerX;

			if(DateTime.Now.Ticks % 2 == 0) {
				playersPool.Push(PlayerType.Player0);
				playersPool.Push(PlayerType.PlayerX);
			}
			else {
				playersPool.Push(PlayerType.PlayerX);
				playersPool.Push(PlayerType.Player0);
			}

			for(byte i = 0; i < field.Length; ++i)
				field[i] = FieldState.Empty;
		}

		public PlayerType GetNextPlayer() {
			if(playersPool.Count == 0)
				return PlayerType.PlayerNone;
			return playersPool.Pop();
		}

		public GameState MakeTurn(byte id, PlayerType player) {
			if(player != currPlayer || field[id] != FieldState.Empty)
				return GameState.CantMakeTurn;

			field[id] = (FieldState)player;
			currPlayer = (currPlayer == PlayerType.Player0 ? PlayerType.PlayerX : PlayerType.Player0);

			if(
				(field[0] == field[1] && field[1] == field[2] && field[2] == (FieldState)player) ||
				(field[3] == field[4] && field[4] == field[5] && field[5] == (FieldState)player) ||
				(field[6] == field[7] && field[7] == field[8] && field[8] == (FieldState)player) ||

				(field[0] == field[3] && field[3] == field[6] && field[6] == (FieldState)player) ||
				(field[1] == field[4] && field[4] == field[7] && field[7] == (FieldState)player) ||
				(field[2] == field[5] && field[5] == field[8] && field[8] == (FieldState)player) ||

				(field[0] == field[4] && field[4] == field[8] && field[8] == (FieldState)player) ||
				(field[2] == field[4] && field[4] == field[6] && field[6] == (FieldState)player)
			)
				return (GameState)(player + 2);

			for(byte i = 0; i < 9; ++i) {
				if(field[i] == FieldState.Empty) {
					return GameState.Continue;
				}
			}

			return GameState.Draw;
		}
	}
}
