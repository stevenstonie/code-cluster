using System.Windows;

namespace memoryGame {
	/// <summary>
	/// Interaction logic for ChooseUserWindow.xaml
	/// </summary>
	public partial class ChooseUserWindow : Window {
		public ChooseUserWindow() {
			InitializeComponent();
		}

		private void nextWindow_Click(object sender, RoutedEventArgs e) {
			this.Hide();
			StartGameWindow startGameWindow = new StartGameWindow();
			startGameWindow.Show();
		}
	}
}
