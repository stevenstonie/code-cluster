using Newtonsoft.Json;
using System;
using System.IO;
using System.Windows;

namespace MemoryTilesGame {
	class User {
		private string name;
		private string profileImagePath;
		private int matchesPlayed;
		private int matchesWon;

		public User() {
			Random random = new Random();
			name = "user" + random.Next(1000, 10000).ToString();
			profileImagePath = "../../Assets/greysquare.png";
			matchesPlayed = 0;
			matchesWon = 0;
		}

		public string Name {
			get {
				return name;
			}
			set {
				name = value;
			}
		}

		public string ProfileImagePath {
			get {
				return profileImagePath;
			}
			set {
				profileImagePath = value;
			}
		}

		public int MatchesPlayed {
			get {
				return matchesPlayed;
			}
			set {
				matchesPlayed = value;
			}
		}

		public int MatchesWon {
			get {
				return matchesWon;
			}
			set {
				matchesWon = value;
			}
		}
	}

	public partial class ChooseUserWindow : Window {
		public ChooseUserWindow() {
			InitializeComponent();

			string folderPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Users");
		}

		private void nextWindow_Click(object sender, RoutedEventArgs e) {
			if(userImage.Source != null) {
				this.Hide();
				StartGameWindow startGameWindow = new StartGameWindow();
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
			/*userIndex++;
			if(userIndex >= usersFoldersPaths.Length)
				userIndex = 0;*/

			updateUserOnWindow();
		}

		private void prevUser_Click(object sender, RoutedEventArgs e) {
			/*userIndex--;
			if(userIndex < 0)
				userIndex = usersFoldersPaths.Length - 1;*/

			updateUserOnWindow();
		}

		private void updateUserOnWindow() {
			/*userImage.Source = new BitmapImage(new Uri(Directory.GetFiles(usersFoldersPaths[userIndex], "*.png").FirstOrDefault()));
			userName.Text = System.IO.Path.GetFileName(usersFoldersPaths[userIndex]);*/
		}

		private void newUser_Click(object sender, RoutedEventArgs e) {
			User newUser = new User();

			CreateNewUserWindow createNewUserWindow = new CreateNewUserWindow();
			createNewUserWindow.ShowDialog();

			newUser.Name = createNewUserWindow.NewUserName;
			newUser.ProfileImagePath = createNewUserWindow.NewUserImagePath;

			if(newUser.Name != "" && newUser.ProfileImagePath != "") {
				appendToUsersJsonFile(newUser);
			}
		}

		private void appendToUsersJsonFile(User newUser) {
			string filePath = Path.Combine(Directory.GetCurrentDirectory(), "users.json");

			((Action)(() => { if(!File.Exists(filePath)) { File.Create(filePath).Dispose(); } }))();

			using(StreamWriter sw = new StreamWriter(filePath, append: true)) {
				using(JsonTextWriter jtw = new JsonTextWriter(sw)) {
					JsonSerializer serializer = new JsonSerializer();
					serializer.Formatting = Formatting.Indented;

					serializer.Serialize(jtw, newUser);
					jtw.WriteRaw("\n");
				}
			}
		}

		private void deleteUser_Click(object sender, RoutedEventArgs e) {

		}
	}
}
