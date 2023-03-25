using Newtonsoft.Json.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Imaging;

namespace MatchingTilesGame {
	public partial class StartGameWindow : Window {
		private int rows;
		private int cols;
		private readonly int standardCols = 6;
		private readonly int standardRows = 5;
		JToken user;
		JArray usersArray;
		string usersJsonFile;

		public StartGameWindow(JToken user) {
			InitializeComponent();

			initializeMembers(user);

			usersStatsGrid.Visibility = Visibility.Hidden;
			initializeUsersStats();
		}

		private void startNewGame_Click(object sender, RoutedEventArgs e) {

			try {
				cols = int.Parse(tbGridSizeY.Text);
				rows = int.Parse(tbGridSizeX.Text);
			}
			catch {
				MessageBox.Show("the input is either null or contains invalid symbols. \nthe game will start with the standard dimensions: " + standardCols + "x" + standardRows);
				cols = standardCols;
				rows = standardRows;
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

					updateUserStatsInArrayAndJsonFile();

					initializeUsersStats();
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

		private void popupButton_Click(object sender, RoutedEventArgs e) {
			MyPopup.IsOpen = true;
		}


		private void initializeMembers(JToken user) {
			this.user = user;
			userName.Text = user.Value<string>("Name");
			userImage.Source = new System.Windows.Media.Imaging.BitmapImage(new System.Uri(user.Value<string>("ImagePath")));

			usersJsonFile = "users.json";
			initializeJArrayFromJsonFile();
		}

		private void initializeUsersStats() {
			usersStatsStackPanel.Children.Clear();

			foreach(JToken user in usersArray) {
				Grid userStatsGrid = new Grid();

				ColumnDefinition column1 = new ColumnDefinition();
				column1.Width = new GridLength(50);
				ColumnDefinition column2 = new ColumnDefinition();
				column2.Width = new GridLength(380);
				userStatsGrid.ColumnDefinitions.Add(column1);
				userStatsGrid.ColumnDefinitions.Add(column2);

				Image userImage = new Image();
				userImage.Source = new BitmapImage(new System.Uri(user.Value<string>("ImagePath")));
				userImage.Height = userImage.Width = 25;
				userStatsGrid.Children.Add(userImage);

				TextBlock userName = new TextBlock();
				userName.Text = user.Value<string>("Name");
				userName.FontSize = 20;
				Grid.SetColumn(userName, 1);
				userStatsGrid.Children.Add(userName);

				usersStatsStackPanel.Children.Add(userStatsGrid);

				TextBlock roundsPlayed = new TextBlock();
				roundsPlayed.Text = "rounds played: " + user.Value<int>("RoundsPlayed").ToString();
				roundsPlayed.FontSize = 10;
				usersStatsStackPanel.Children.Add(roundsPlayed);

				TextBlock roundsWon = new TextBlock();
				roundsWon.Text = "rounds won: " + user.Value<int>("RoundsWon").ToString();
				roundsWon.FontSize = 10;
				usersStatsStackPanel.Children.Add(roundsWon);

				usersStatsStackPanel.Children.Add(new Separator());
			}
		}

		private void initializeJArrayFromJsonFile() {
			string jsonData = System.IO.File.ReadAllText(usersJsonFile);
			usersArray = JArray.Parse(jsonData);
		}

		private void updateUserStatsInArrayAndJsonFile() {
			foreach(JObject userObj in usersArray.Children<JObject>()) {
				if(userObj.Value<string>("Name") == user.Value<string>("Name")) {
					userObj["RoundsPlayed"] = user.Value<int>("RoundsPlayed");
					userObj["RoundsWon"] = user.Value<int>("RoundsWon");
				}
			}

			System.IO.File.WriteAllText(usersJsonFile, usersArray.ToString());
		}

		private void toggleUsersStatsButton_Click(object sender, RoutedEventArgs e) {
			if(usersStatsGrid.Visibility == Visibility.Hidden) {
				usersStatsGrid.Visibility = Visibility.Visible;
			}
			else {
				usersStatsGrid.Visibility = Visibility.Hidden;
			}
		}
	}
}
