using System;
using System.Diagnostics;
using System.Windows.Forms;
using System.Runtime.InteropServices;
class BlockWindows
{
	private const int WH_KEYBOARD_LL = 13;

	private const int WM_KEYDOWN = 0x0100;

	private delegate IntPtr HookProc(int nCode, IntPtr wParam, IntPtr lParam);

	//private static HookProc proc = HookCallback;

	private static IntPtr hook = IntPtr.Zero;
	public static void Main()
	{
		hook = SetHook(HookCallback);
		Application.Run();
		UnhookWindowsHookEx(hook);
	}
	private static IntPtr SetHook(HookProc proc)
	{
		

		using (ProcessModule curModule = Process.GetCurrentProcess().MainModule)
		{
			return SetWindowsHookEx(WH_KEYBOARD_LL, proc, GetModuleHandle(curModule.ModuleName), 0);
		}
	}
	
	private static IntPtr HookCallback(int nCode, 	IntPtr wParam, 	IntPtr lParam)

	{
		if ((nCode >= 0) && (wParam == (IntPtr)WM_KEYDOWN))
{
			int vkCode = Marshal.ReadInt32(lParam);

			///if (((Keys)vkCode == Keys.LWin) || ((Keys)vkCode == Keys.RWin))
			{
				Console.WriteLine("{0} blocked!", (Keys)vkCode);
				return (IntPtr)0;
			}
		}
		return CallNextHookEx(hook, nCode, wParam,lParam);
	}



	[DllImport("user32.dll", CharSet = CharSet.Auto,SetLastError = true)]
	private static extern IntPtr SetWindowsHookEx (int idHook,	HookProc lpfn,	IntPtr hMod,uint dwThreadId);

	[DllImport("user32.dll", CharSet = CharSet.Auto,SetLastError = true)]
	private static extern bool UnhookWindowsHookEx(IntPtr hhk);

	[DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
	private static extern IntPtr CallNextHookEx	(IntPtr hhk, int nCode, IntPtr wParam, IntPtr lParam);

	[DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
	private static extern IntPtr GetModuleHandle(string lpModuleName);
}