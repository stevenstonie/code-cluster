using System.Windows;

namespace MemoryTilesGame {
	public partial class MainWindow : Window {
		public MainWindow() {
			InitializeComponent();
		}

		private void start_Click(object sender, RoutedEventArgs e) {
			ChooseUserWindow chooseUserWindow = new ChooseUserWindow();
			chooseUserWindow.Show();
			Close();
		}

		private void exit_Click(object sender, RoutedEventArgs e) {
			Application.Current.Shutdown();
		}
	}
}
