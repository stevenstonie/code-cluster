using Newtonsoft.Json.Linq;
using System.Windows;

namespace MemoryTilesGame {
	public partial class StartGameWindow : Window {
		private int rows;
		private int cols;
		private readonly int standardRows;
		private readonly int standardCols;
		JToken user;

		public StartGameWindow(JToken user) {
			InitializeComponent();

			standardRows = 5;
			standardCols = 6;

			this.user = user;
			userName.Text = user.Value<string>("Name");
			userImage.Source = new System.Windows.Media.Imaging.BitmapImage(new System.Uri(user.Value<string>("ImagePath")));
		}

		private void startNewGame_Click(object sender, RoutedEventArgs e) {

			try {
				cols = int.Parse(tbGridSizeX.Text);
				rows = int.Parse(tbGridSizeY.Text);
			}
			catch {
				MessageBox.Show("the input is either null or contains invalid symbols. \nthe game will start with the standard dimensions: " + standardRows + "x" + standardCols);
				rows = standardRows;
				cols = standardCols;
			}
			if(cols < 2 || cols > 12 || rows < 2 || rows > 12) {
				MessageBox.Show("the dimensions are out of bounds. the accepted limits are from 2 to 12");
			}
			else {
				if(cols % 2 != 0 && rows % 2 != 0) {
					MessageBox.Show("at least dimension has to be even");
				}
				else {
					user["RoundsPlayed"] = user.Value<int>("RoundsPlayed") + 1;

					GameWindow gameWindow = new GameWindow(user, cols, rows);
					gameWindow.ShowDialog();

					if(gameWindow.RoundWon == true) {
						user["RoundsWon"] = user.Value<int>("RoundsWon") + 1;
					}

					updateUserStatsInJsonFile();
				}
			}

		}

		private void exit_Click(object sender, RoutedEventArgs e) {
			Application.Current.Shutdown();
		}

		private void back_Click(object sender, RoutedEventArgs e) {
			this.Hide();
			ChooseUserWindow chooseUserWindow = new ChooseUserWindow();
			chooseUserWindow.Show();
		}

		private void updateUserStatsInJsonFile() {
			string usersFile = "users.json";

			string jsonData = System.IO.File.ReadAllText(usersFile);
			JArray usersArray = JArray.Parse(jsonData);

			foreach(JObject userObj in usersArray.Children<JObject>()) {
				if(userObj.Value<string>("Name") == user.Value<string>("Name")) {
					userObj["RoundsPlayed"] = user.Value<int>("RoundsPlayed");
					userObj["RoundsWon"] = user.Value<int>("RoundsWon");
				}
			}

			System.IO.File.WriteAllText(usersFile, usersArray.ToString());
		}
	}
}
