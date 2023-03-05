using System.Windows;

namespace memoryGame {
	/// <summary>
	/// Interaction logic for StartGameWindow.xaml
	/// </summary>
	public partial class StartGameWindow : Window {
		public StartGameWindow() {
			InitializeComponent();
		}

		private void startNewGame_Click(object sender, RoutedEventArgs e) {
			// for now dont hide this window until you implement a button to go back to the game menu
			GameWindow gameWindow = new GameWindow();
			gameWindow.Show();
		}
	}
}
