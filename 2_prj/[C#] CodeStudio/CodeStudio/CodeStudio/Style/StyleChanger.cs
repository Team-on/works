using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CodeStudio {
	static class StyleChanger {

		static public void SetMenuStripStyle(MenuStrip contextMenu) {
			foreach (ToolStripItem i in contextMenu.Items) {
				i.BackColor = Singletones.settings.DefaultBackground;
				i.ForeColor = Singletones.settings.DefaultForeground;

				SetColorToDefault(i);
			}

			void SetColorToDefault(ToolStripItem item) {
				if (item as ToolStripMenuItem != null) {
					(item as ToolStripMenuItem).DropDown.ForeColor = Singletones.settings.DefaultForeground;
					(item as ToolStripMenuItem).DropDown.BackColor = Singletones.settings.DefaultBackground;
					foreach (ToolStripItem j in (item as ToolStripMenuItem).DropDownItems) {
						j.ForeColor = Singletones.settings.DefaultForeground;
						j.BackColor = Singletones.settings.DefaultBackground;
						SetColorToDefault(j);
					}
				}
			}
		}

		static public void SetContexMenuStripStyle(ContextMenuStrip contextMenu) {
			foreach (ToolStripMenuItem i in contextMenu.Items) {
				i.BackColor = Singletones.settings.DefaultBackground;
				i.ForeColor = Singletones.settings.DefaultForeground;

				SetColorToDefault(i);
			}

			void SetColorToDefault(ToolStripItem item) {
				if (item as ToolStripMenuItem != null) {
					(item as ToolStripMenuItem).DropDown.ForeColor = Singletones.settings.DefaultForeground;
					(item as ToolStripMenuItem).DropDown.BackColor = Singletones.settings.DefaultBackground;
					foreach (ToolStripItem j in (item as ToolStripMenuItem).DropDownItems) {
						j.ForeColor = Singletones.settings.DefaultForeground;
						j.BackColor = Singletones.settings.DefaultBackground;
						SetColorToDefault(j);
					}
				}
			}
		}
	}
}
