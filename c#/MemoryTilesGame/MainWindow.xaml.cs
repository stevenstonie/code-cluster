using System.Windows;

namespace MemoryTilesGame {
	public partial class MainWindow : Window {
		public MainWindow() {
			InitializeComponent();


		}

		private void start_Click(object sender, RoutedEventArgs e) {
			// hide this window
			this.Hide();
			ChooseUserWindow chooseUserWindow = new ChooseUserWindow();
			chooseUserWindow.ShowDialog();
		}

		private void exit_Click(object sender, RoutedEventArgs e) {
			Application.Current.Shutdown();
		}
	}
}
