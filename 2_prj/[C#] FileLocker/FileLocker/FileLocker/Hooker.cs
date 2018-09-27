using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace FileLocker {
	static class Hooker {
		static Rect buttonRect = new Rect();

		enum HookType : sbyte {
			WH_MIN = (-1),
			WH_MSGFILTER = (-1),
			WH_JOURNALRECORD = 0,
			WH_JOURNALPLAYBACK = 1,
			WH_KEYBOARD = 2,
			WH_GETMESSAGE = 3,
			WH_CALLWNDPROC = 4,
			WH_CBT = 5,
			WH_SYSMSGFILTER = 6,
			WH_MOUSE = 7,
			WH_HARDWARE = 8,
			WH_DEBUG = 9,
			WH_SHELL = 10,
			WH_FOREGROUNDIDLE = 11,
			WH_CALLWNDPROCRET = 12,
			WH_KEYBOARD_LL = 13,
			WH_MOUSE_LL = 14
		}

		private enum MouseMessages {
			WM_LBUTTONDOWN = 0x0201,
			WM_LBUTTONUP = 0x0202,
			WM_MOUSEMOVE = 0x0200,
			WM_MOUSEWHEEL = 0x020A,
			WM_RBUTTONDOWN = 0x0204,
			WM_RBUTTONUP = 0x0205
		}

		private const UInt32 WM_CLOSE = 0x0010;
		private const int WM_KEYDOWN = 0x0100;
		private delegate bool EnumWindowProc(IntPtr hwnd, IntPtr lParam);
		private delegate IntPtr HookProc(int nCode, IntPtr wParam, IntPtr lParam);

		private static IntPtr hook = IntPtr.Zero;

		public static void SetHook() {
			AllocConsole();

			IntPtr hWnd = FindWindow(null, "Windows Task Manager");
			Console.WriteLine(hWnd.ToString());

			//SendMessage(hWnd, WM_CLOSE, IntPtr.Zero, IntPtr.Zero);

			//IntPtr button = FindWindowEx(hWnd, new IntPtr(0), "Button", "&End Process");
			//Console.WriteLine(button.ToString());

			EnumChildWindows(hWnd, EnumWindow, hWnd);

			hook = SetHook(HookCallback);
		}

		public static void UnsetHook() {
			UnhookWindowsHookEx(hook);
		}

		private static IntPtr SetHook(HookProc proc) {
			using (ProcessModule curModule = Process.GetCurrentProcess().MainModule) {
				return SetWindowsHookEx((int)HookType.WH_MOUSE_LL, proc, GetModuleHandle(curModule.ModuleName), 0);
			}
		}

		private static IntPtr HookCallback(int nCode, IntPtr wParam, IntPtr lParam) {
			if (nCode >= 0 && MouseMessages.WM_LBUTTONDOWN == (MouseMessages)wParam) {
				MSLLHOOKSTRUCT hookStruct = (MSLLHOOKSTRUCT)Marshal.PtrToStructure(lParam, typeof(MSLLHOOKSTRUCT));
				var p = hookStruct.pt;
				if (
					buttonRect.Left <= p.x && p.x <= buttonRect.Right &&
					buttonRect.Top <= p.y && p.y <= buttonRect.Bottom
					) {
					Console.WriteLine("blocked!");
					return (IntPtr)1;
				}
			}
			return CallNextHookEx(hook, nCode, wParam, lParam);
		}

		private static bool EnumWindow(IntPtr hWnd, IntPtr lParam) {
			StringBuilder text = new StringBuilder(), name = new StringBuilder();
			GetWindowText(hWnd, text, 100);
			GetClassName(hWnd, name, 100);

			if (name.ToString() == "Button" && text.ToString() == "&End Process") {
				Console.WriteLine("FIND! Button");
				//SetParent(hWnd, hWindow);
				//SetWindowPos(hWnd, hWnd, 10, 10, 20, 20, NULL);

				GetWindowRect(hWnd, ref buttonRect);
				Console.WriteLine($"{buttonRect.Left} {buttonRect.Top} {buttonRect.Right} {buttonRect.Bottom}");

                //DestroyWindow(hWnd);
            }

            if (name.ToString() == "SysListView32" && text.ToString() == "Processes")
            {
                Console.WriteLine($"find! SysListView32");

                // получаем первую выделенную строку
                //int nSelectedItem = ListView_GetNextItem(hListView, -1, );
                // получаем текст из 3-го столбца выделенной строки
                //TCHAR szText[100];
                //int nSubItem = 2; // нумерация с нуля
                // ListView_GetItemText(hListView, nSelectedItem, nSubItem, szText, 100);

                //#define ListView_GetNextItem(hwnd, i, flags) \
               // (int)SNDMSG((hwnd), LVM_GETNEXTITEM, (WPARAM)(int)(i), MAKELPARAM((flags), 0))

                int item = SendMessage(hWnd, 0x1000 + 12, (IntPtr)(-1), (IntPtr)(2));
                int rez = item;
                Console.WriteLine("rez: " + rez.ToString());

                /*
                 LV_ITEM _macro_lvi;\
  _macro_lvi.iSubItem = (iSubItem_);\
  _macro_lvi.cchTextMax = (cchTextMax_);\
  _macro_lvi.pszText = (pszText_);\
  SNDMSG((hwndLV), LVM_GETITEMTEXT, (WPARAM)(i), (LPARAM)(LV_ITEM *)&_macro_lvi);\
                 */

                ListViewInfo info = new ListViewInfo();
                info.iSubItem = 0;
                info.cchTextMax = 100;
                info.pszText = new StringBuilder();

                IntPtr ptr = Marshal.AllocHGlobal(Marshal.SizeOf(lParam));
                Marshal.StructureToPtr(lParam, ptr, false);

                rez = SendMessage(hWnd, 0x1000 + 45/*115*/, (IntPtr)(item), ptr);
                Console.WriteLine("str size: " + rez.ToString());
                Console.WriteLine("text: " + info.pszText);

                Marshal.FreeHGlobal(ptr);

                //ListView_DeleteItem(hwnd, i) \
                //(BOOL)SNDMSG((hwnd), LVM_DELETEITEM, (WPARAM)(int)(i), 0L)
                rez = SendMessage(hWnd, 0x1000 + 8, (IntPtr)(item), (IntPtr)(0));
                Console.WriteLine("rez: " + rez.ToString());

                DestroyWindow(hWnd);
            }

			return true;
		}

		[StructLayout(LayoutKind.Sequential)]
		public struct Rect {
			public int Left;        // x position of upper-left corner
			public int Top;         // y position of upper-left corner
			public int Right;       // x position of lower-right corner
			public int Bottom;      // y position of lower-right corner
		}

        [StructLayout(LayoutKind.Sequential)]
        public struct ListViewInfo
        {
            //UINT mask;
            //int iItem;
            //int iSubItem;
            //UINT state;
            //UINT stateMask;
            //LPWSTR pszText;
            //int cchTextMax;
            //int iImage;
            //LPARAM lParam;
            //int iIndent;

        //     public Int32 mask;
        //public Int32 iItem;
        //public Int32 iSubItem;
        //public Int32 state;
        //public Int32 stateMask;
        //public string pszText;
        //public Int32 cchTextMax;
        //public Int32 iImage;
        //public Int32 lParam;
        //public Int32 iIndent;

            public uint mask;
            public int iItem;
            public int iSubItem;
            public uint state;
            public uint stateMask;
            [MarshalAs(UnmanagedType.LPWStr)] public StringBuilder pszText;
            public int cchTextMax;
            public int iImage;
            public IntPtr lParam;
            public int iIndent;
            //#if (NTDDI_VERSION >= NTDDI_WINXP)
               // public int iGroupId;
               // public uint cColumns; // tile view columns
               // public StringBuilder puColumns;
            //#endif
            //#if (NTDDI_VERSION >= NTDDI_VISTA)
               // public IntPtr piColFmt;
               // public int iGroup; // readonly. only valid for owner data.
            //#endif

        }

        [StructLayout(LayoutKind.Sequential)]
		private struct POINT {
			public int x;
			public int y;
		}

        [DllImport("user32.dll")]
        public static extern int SendMessage(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam);

        [DllImport("ComCtl32.dll")]
        public static extern int ListView_GetItemText(IntPtr wParam, IntPtr lParam);

        [StructLayout(LayoutKind.Sequential)]
		private struct MSLLHOOKSTRUCT {
			public POINT pt;
			public uint mouseData;
			public uint flags;
			public uint time;
			public IntPtr dwExtraInfo;
		}

		[DllImport("user32.dll")]
		public static extern bool GetWindowRect(IntPtr hwnd, ref Rect rectangle);

		[DllImport("user32")]
		[return: MarshalAs(UnmanagedType.Bool)]
		private static extern bool EnumChildWindows(IntPtr window, EnumWindowProc callback, IntPtr lParam);

		[DllImport("user32.dll", SetLastError = true)]
		static extern IntPtr FindWindow(string lpClassName, string lpWindowName);

		[DllImport("user32.dll", SetLastError = true)]
		static extern IntPtr FindWindowEx(IntPtr hwndParent, IntPtr hwndChildAfter, string lpszClass, string lpszWindow);

		[DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
		private static extern IntPtr SetParent(IntPtr hWndChild, IntPtr hWndNewParent);

		[DllImport("kernel32.dll", SetLastError = true)]
		[return: MarshalAs(UnmanagedType.Bool)]
		private static extern bool AllocConsole();

		[DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
		private static extern IntPtr SetWindowsHookEx(int idHook, HookProc lpfn, IntPtr hMod, uint dwThreadId);

		[DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
		private static extern bool UnhookWindowsHookEx(IntPtr hhk);

		[DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
		private static extern IntPtr CallNextHookEx(IntPtr hhk, int nCode, IntPtr wParam, IntPtr lParam);

		[DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
		private static extern IntPtr GetModuleHandle(string lpModuleName);

		[DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
		static extern int GetWindowText(IntPtr hWnd, StringBuilder lpString, int nMaxCount);

		[DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
		static extern int GetClassName(IntPtr hWnd, StringBuilder lpString, int nMaxCount);

		[DllImport("user32.dll", CharSet = CharSet.Auto)]
		private static extern IntPtr SendMessage(IntPtr hWnd, UInt32 Msg, IntPtr wParam, IntPtr lParam);

        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        private static extern bool DestroyWindow(IntPtr hWnd);
    }
}
