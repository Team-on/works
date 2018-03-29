using System;
using System.IO;

namespace TeamCommander
{
    class Program
    {
        static void Main(string[] args)
        {
           

			Commander commander = new Commander();
			commander.Launch();
			System.Threading.Thread.Sleep(10000);
			Console.SetCursorPosition(0, 0);

			/*DriveInfo[] drives = DriveInfo.GetDrives();
            foreach (DriveInfo drive in drives)
            {
                Console.WriteLine("Название: {0}", drive.Name);
                Console.WriteLine("Тип: {0}", drive.DriveType);
                if (drive.IsReady)
                {
                    Console.WriteLine("Объем диска: {0}", drive.TotalSize);
                    Console.WriteLine("Свободное пространство: {0}", drive.TotalFreeSpace);
                    Console.WriteLine("Метка: {0}", drive.VolumeLabel);
                }
                Console.WriteLine();
            }
            Console.ReadLine();
            */
		}
    }
}
