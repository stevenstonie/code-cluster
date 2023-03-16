using System;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Media.Imaging;

namespace MemoryTilesGame {
	public partial class ChooseUserWindow : Window {
		string[] usersFoldersPaths;
		int userIndex;

		public ChooseUserWindow() {
			InitializeComponent();

			string folderPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Assets", "Users");
			usersFoldersPaths = Directory.GetDirectories(folderPath);
			userIndex = 0;
		}

		private void nextWindow_Click(object sender, RoutedEventArgs e) {
			if(userImage.Source != null) {
				this.Hide();
				StartGameWindow startGameWindow = new StartGameWindow(usersFoldersPaths[userIndex]);
				startGameWindow.Show();
			}
			else {
				MessageBox.Show("no user has been assigned yet.");
			}
		}

		private void exitApp(object sender, RoutedEventArgs e) {
			Application.Current.Shutdown();
		}

		private void back_Click(object sender, RoutedEventArgs e) {
			this.Hide();
			MainWindow mainWindow = new MainWindow();
			mainWindow.Show();
		}

		private void nextUser_Click(object sender, RoutedEventArgs e) {
			userIndex++;
			if(userIndex >= usersFoldersPaths.Length)
				userIndex = 0;

			assignUserToWindow();
		}

		private void prevUser_Click(object sender, RoutedEventArgs e) {
			userIndex--;
			if(userIndex < 0)
				userIndex = usersFoldersPaths.Length - 1;

			assignUserToWindow();
		}

		private void assignUserToWindow() {
			userImage.Source = new BitmapImage(new Uri(Directory.GetFiles(usersFoldersPaths[userIndex], "*.png").FirstOrDefault()));
			userName.Text = System.IO.Path.GetFileName(usersFoldersPaths[userIndex]);
		}
	}
}
