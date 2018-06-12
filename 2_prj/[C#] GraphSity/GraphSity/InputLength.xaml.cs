using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace GraphSity
{
    /// <summary>
    /// Interaction logic for InputLength.xaml
    /// </summary>
    public partial class InputLength : Window
    {
        public InputLength()
        {
            InitializeComponent();
        }

		private void Button_Click(object sender, RoutedEventArgs e) {
			if(uint.TryParse(textBox.Text, out length) && length != 0)
				this.Close();
		}

		public uint length = 0;

		private void textBox_KeyDown(object sender, KeyEventArgs e) {
			if(e.Key != Key.D0 &&
				e.Key != Key.D1 &&
				e.Key != Key.D2 &&
				e.Key != Key.D3 &&
				e.Key != Key.D4 &&
				e.Key != Key.D5 &&
				e.Key != Key.D6 &&
				e.Key != Key.D7 &&
				e.Key != Key.D8 &&
				e.Key != Key.D9
				)
				e.Handled = true;
		}

		private void textBox_GotFocus(object sender, RoutedEventArgs e) {
			if (textBox.Text == "Введіть довжину дуги") {
				textBox.SelectionStart = 0;
				textBox.SelectionLength = textBox.Text.Length;
				textBox.SelectedText = "";
			}
		}
	}
}
