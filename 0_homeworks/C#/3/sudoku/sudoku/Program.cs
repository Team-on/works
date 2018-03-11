using System;

namespace sudoku
{

    class Game
    {
        bool[,] mask = new bool[9,9];
        byte[,] field = new byte[9,9];

        void SwapRow(byte[,] arr,int r1, int r2)
        {
            if (r1 == r2)
                return;
            byte tmp;
            for(byte i = 0; i < arr.GetLength(0); ++i)
            {
                tmp = arr[r1, i];
                arr[r1, i] = arr[r2, i];
                arr[r2, i] = tmp;
            }
        }

        void SwapCol(byte[,] arr, int c1, int c2)
        {
            if (c1 == c2)
                return;
            byte tmp;
            for (byte i = 0; i < arr.GetLength(1); ++i)
            {
                tmp = arr[i, c1];
                arr[i, c1] = arr[i, c2];
                arr[i, c2] = tmp;
            }
        }

        public Game()
        {
            for (int i = 0; i < field.GetLength(0); ++i)
                    for (int j = 0; j < field.GetLength(1); ++j)
                    {
                        mask[i, j] = true;
                        field[i, j] = 0;
                    }
        }

        public void Fill()
        {
            Random rnd = new Random();
            byte[,] arr = new byte[9,9];
            byte[] nums = new byte[9] { 1,2,3,4,5,6,7,8,9};
            byte numPos = (byte)(rnd.Next(0, nums.GetLength(0) - 1));

            for (int i = 0; i < arr.GetLength(0); ++i)
            {
                for (int j = 0; j < arr.GetLength(0); ++j)
                {
                    if (numPos >= nums.Length)
                        numPos = (byte)(numPos - nums.Length);
                    arr[i, j] = nums[numPos++];
                }
                numPos += 3;
                if (i == 2 || i == 5)
                    ++numPos;
            }

            byte currSqr, index1, index2;
            byte[] pos = new byte[3] {0, 3, 6 };
            for (int i = 0; i < 5; ++i)
            {
                for (int j = 0; j < 5; ++j)
                {
                    currSqr = pos[rnd.Next(0, 3)];
                    index1 = (byte)(rnd.Next(0, 3));
                    do
                        index2 = (byte)(rnd.Next(0, 3));
                    while (index2 == index1);

                    if (rnd.Next(0, 2) == 1)
                        SwapRow(arr, index1 + currSqr, index2 + currSqr);
                    else
                        SwapCol(arr, index1 + currSqr, index2 + currSqr);
                }
            }

            
            for (int i = 0; i < nums.GetLength(0); ++i)
                for (int j = 0; j < nums.GetLength(0); ++j) 
                    if(rnd.Next(0,2) == 1 && i != j)
                    {
                        byte tmp = nums[i];
                        nums[i] = nums[j];
                        nums[j] = tmp;
                    }

            for (int i = 0; i < field.GetLength(0); ++i)
                for (int j = 0; j < arr.GetLength(1); ++j)
                    field[i, j] = nums[arr[i, j] - 1];
        }

        public void Print()
        {
            for (int i = 0; i < field.GetLength(0); ++i)
            {
                for (int j = 0; j < field.GetLength(1); ++j)
                {
                    if (mask[i, j] == true)
                        Console.Write($"[{field[i, j]}] ");
                    else
                        Console.Write("[ ] ");
                    if (j == 2 || j == 5)
                        Console.Write(' ');
                }
                Console.Write('\n');
                if(i == 2 || i == 5)
                    Console.Write('\n');
            }
                    
           }

    }

    class Program
    {
        static void Main(string[] args)
        {
            Game game = new Game();
            game.Fill();
            game.Print();
        }
    }
}
