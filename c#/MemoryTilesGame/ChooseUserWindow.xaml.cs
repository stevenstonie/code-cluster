using System;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Media.Imaging;


namespace MemoryTilesGame {
	public partial class ChooseUserWindow : Window {
		private string[] usersFoldersPaths;
		private int userIndex;

		public ChooseUserWindow() {
			InitializeComponent();

			string folderPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Users");
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

		private void deleteUser_Click(object sender, RoutedEventArgs e) {

			if(userImage.Source != null) {
				var userPathToDelete = usersFoldersPaths[userIndex];
				var filesToDelete = Directory.GetFiles(userPathToDelete);

				nextUser_Click(sender, e);

				foreach(var fileToDelete in filesToDelete) {
					using(var stream = new FileStream(fileToDelete, FileMode.Open, FileAccess.ReadWrite, FileShare.None)) {
						File.Delete(fileToDelete);
					}
				}
				Directory.Delete(userPathToDelete);
			}
			else {
				MessageBox.Show("no user has been selected");
			}
		}
	}
}
