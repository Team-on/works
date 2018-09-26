using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace FileLocker {
	class Hooker {
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

		private const UInt32 WM_CLOSE = 0x0010;
		private const int WM_KEYDOWN = 0x0100;
		private delegate bool EnumWindowProc(IntPtr hwnd, IntPtr lParam);
		private delegate IntPtr HookProc(int nCode, IntPtr wParam, IntPtr lParam);

		private static IntPtr hook = IntPtr.Zero;

		public static void SetHook() {
			AllocConsole();

			IntPtr hWnd = FindWindow(null, "Windows Task Manager");
			Console.WriteLine(hWnd.ToString());

			SendMessage(hWnd, WM_CLOSE, IntPtr.Zero, IntPtr.Zero);

			//IntPtr button = FindWindowEx(hWnd, new IntPtr(0), "Button", "&End Process");
			//Console.WriteLine(button.ToString());

			//EnumChildWindows(hWnd, EnumWindow, hWnd);

			//hook = SetHook(HookCallback);
		}

		public static void UnsetHook() {
			UnhookWindowsHookEx(hook);
		}

		private static IntPtr SetHook(HookProc proc) {
			using (ProcessModule curModule = Process.GetCurrentProcess().MainModule) {
				return SetWindowsHookEx((int)HookType.WH_KEYBOARD_LL, proc, GetModuleHandle(curModule.ModuleName), 0);
			}
		}

		private static IntPtr HookCallback(int nCode, IntPtr wParam, IntPtr lParam) {
			//if ((nCode >= 0) && (wParam == (IntPtr)WM_KEYDOWN)) {
			Console.WriteLine("blocked!");
			return (IntPtr)1;
			//}
			return CallNextHookEx(hook, nCode, wParam, lParam);
		}

		private static bool EnumWindow(IntPtr hWnd, IntPtr lParam) {
			StringBuilder text = new StringBuilder(), name = new StringBuilder();
			GetWindowText(hWnd, text, 100);
			GetClassName(hWnd, name, 100);

				Console.WriteLine("TRY TO FIND!");
			if (text.ToString() == "Button" && name.ToString() == "&End Process") {
				Console.WriteLine("IND!");
				//SetParent(hWnd, hWindow);
				//SetWindowPos(hWnd, hWnd, 10, 10, 20, 20, NULL);
			}

			return true;
		}

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
	}
}
