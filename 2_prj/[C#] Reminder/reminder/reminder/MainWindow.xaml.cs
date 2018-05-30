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
using System.Windows.Navigation;
using System.IO;
using System.Windows.Shapes;

namespace reminder {
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window {
		public MainWindow() {
			InitializeComponent();
			taskController = new TaskController();
			PickDate.SelectedDate = DateTime.Now;
		}

		public void FillWithTasksButton() {
			TaskPanel.Children.Clear();
			taskController.SortByTime();
			foreach (var i in taskController.GetTasksEnumerator()) {
				Button currTask = new Button();

				Grid mainGrid = new Grid();
				mainGrid.RowDefinitions.Add(new RowDefinition());
				mainGrid.RowDefinitions.Add(new RowDefinition());
				mainGrid.ColumnDefinitions.Add(new ColumnDefinition());
				mainGrid.ColumnDefinitions.Add(new ColumnDefinition());
				mainGrid.ColumnDefinitions.Add(new ColumnDefinition());

				Label currLabel = new Label() { Content=i.name };
				currLabel.HorizontalAlignment = HorizontalAlignment.Center;
				currLabel.VerticalAlignment = VerticalAlignment.Center;
				Grid.SetColumn(currLabel, 1);
				Grid.SetRowSpan(currLabel, 2);
				mainGrid.Children.Add(currLabel);

				currLabel.HorizontalAlignment = HorizontalAlignment.Right;
				currLabel.HorizontalContentAlignment = HorizontalAlignment.Right;
				currLabel.VerticalContentAlignment = VerticalAlignment.Center;

				currLabel = new Label() { Content = i.dateTime.ToShortDateString() };
				Grid.SetColumn(currLabel, 2);
				mainGrid.Children.Add(currLabel);

				currLabel = new Label() { Content = i.dateTime.ToShortTimeString() };
				Grid.SetRow(currLabel, 1);
				Grid.SetColumn(currLabel, 2);
				mainGrid.Children.Add(currLabel);

				Image img = null;

				if (i.image != null) 
					img = new Image() { Source = i.image.Source };
				else
					img = new Image() { Source = TaskController.defaultImage.Source };

				img.Margin = new Thickness(5, 5, 5, 5);
				img.VerticalAlignment = VerticalAlignment.Center;
				img.HorizontalAlignment = HorizontalAlignment.Left;
				Grid.SetRowSpan(img, 2);
				mainGrid.Children.Add(img);

				currTask.Click += DisplayTaskInfo;

				currTask.Tag = i;
				currTask.Content = mainGrid;
				TaskPanel.Children.Add(currTask);
			}
		}

		private void CreateNewTask(object sender, RoutedEventArgs e) {
			if (PickName.Text == "" ||
				PickName.Text == "Task name"
				)
				return;
			if (PickDescription.Text == "Description")
				PickDescription.Text = "";
			if (PickTheme.Text == "Pick theme")
				PickTheme.Text = "Default";

			Image img = new Image();
			img.Source = null;
			if (File.Exists(PickImage.Text)) 
				img.Source = new BitmapImage(new Uri(PickImage.Text));

			if(img.Source != null)
				taskController.AddTask(new Task(PickDate.SelectedDate.Value.AddHours(byte.Parse(PickHours.Text)).AddMinutes(byte.Parse(PickMinutes.Text)), PickName.Text, PickTheme.Text, PickDescription.Text, img));
			else
				taskController.AddTask(new Task(PickDate.SelectedDate.Value.AddHours(byte.Parse(PickHours.Text)).AddMinutes(byte.Parse(PickMinutes.Text)), PickName.Text, PickTheme.Text, PickDescription.Text, null));

			PickTheme.Text = "Pick theme";
			PickName.Text = "Task name";
			PickDescription.Text = "Description";
			PickImage.Text = "Select image(optional)";
			PickMinutes.Text = "30";
			PickHours.Text = "12";
			PickDate.SelectedDate = DateTime.Now;
			PickDate.SelectedDate = PickDate.SelectedDate.Value.AddHours(-PickDate.SelectedDate.Value.Hour).AddMinutes(-PickDate.SelectedDate.Value.Minute);

			PickTheme.Focus();

			FillWithTasksButton();
		}

		private void ClearDefaultValueTextBox(object sender, RoutedEventArgs e) {
			var a = sender as TextBox;
			if (a == null)
				return;
			if (a.Text == "Description" || a.Text == "Task name")
				a.Text = "";
		}

		private void SelectImage(object sender, RoutedEventArgs e) {
			if (openFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
				PickImage.Text = openFileDialog.FileName;
		}

		void DisplayTaskInfo(object sender, RoutedEventArgs e) {
			Task task = (sender as Button).Tag as Task;

			PickTheme.Text = task.theme;
			PickName.Text = task.name;
			PickDescription.Text = task.description;
			PickMinutes.Text = task.dateTime.Minute.ToString();
			PickHours.Text = task.dateTime.Hour.ToString();
			PickDate.SelectedDate = task.dateTime;
			PickDate.SelectedDate = PickDate.SelectedDate.Value.AddHours(-PickDate.SelectedDate.Value.Hour).AddMinutes(-PickDate.SelectedDate.Value.Minute);
			//PickImage.Text = task.image.Source.;
		}

		TaskController taskController;
		System.Windows.Forms.OpenFileDialog openFileDialog = new System.Windows.Forms.OpenFileDialog() { Multiselect = false, Filter= "images|*.jpg; *.jpeg; *.png; *.jpe; *.ico; *.bmp" };

		private void Button_Click(object sender, RoutedEventArgs e) {
			byte n = byte.Parse(PickHours.Text);
			if (n != 23)
				++n;
			else
				n = 0;
			PickHours.Text = n.ToString();
		}

		private void Button_Click_1(object sender, RoutedEventArgs e) {
			byte n = byte.Parse(PickHours.Text);
			if (n != 0)
				--n;
			else
				n = 23;
			PickHours.Text = n.ToString();
		}

		private void Button_Click_2(object sender, RoutedEventArgs e) {
			byte n = byte.Parse(PickMinutes.Text);
			if (n != 55)
				n+=5;
			else
				n = 0;
			PickMinutes.Text = n.ToString();
		}

		private void Button_Click_3(object sender, RoutedEventArgs e) {
			byte n = byte.Parse(PickMinutes.Text);
			if (n != 0)
				n-=5;
			else
				n = 55;
			PickMinutes.Text = n.ToString();
		}
	}
}
