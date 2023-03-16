using System.Windows;

namespace MemoryTilesGame {
	/// <summary>
	/// Interaction logic for StartGameWindow.xaml
	/// </summary>
	public partial class StartGameWindow : Window {
		public StartGameWindow(string userFolderPath) {
			InitializeComponent();
		}

		private void startNewGame_Click(object sender, RoutedEventArgs e) {
			// for now dont hide this window until you implement a button to go back to the game menu
			GameWindow gameWindow = new GameWindow();
			gameWindow.Show();
		}

		private void exitApp(object sender, RoutedEventArgs e) {
			Application.Current.Shutdown();
		}

		private void back_Click(object sender, RoutedEventArgs e) {
			this.Hide();
			ChooseUserWindow chooseUserWindow = new ChooseUserWindow();
			chooseUserWindow.Show();
		}
	}
}
