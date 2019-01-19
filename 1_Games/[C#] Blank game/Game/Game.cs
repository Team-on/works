using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace Game {
    public class Game {
        GameContext gameContext = GameContext.GetGCState();
        Thread gameThread;

        public void StartGame() {
            gameThread = new Thread(() => {
                gameContext.StartGame();
            });
            gameThread.Start();
        }

        public void StopGame() {
            gameContext.StopGame();
            while (gameThread.IsAlive)
                Thread.Sleep(250);
        }
    }
}
