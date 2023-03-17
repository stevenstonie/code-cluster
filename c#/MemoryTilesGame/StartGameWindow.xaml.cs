using System.Windows;

namespace MemoryTilesGame {
	public partial class StartGameWindow : Window {
		private int rows;
		private int cols;
		private readonly int standardRows;
		private readonly int standardCols;

		public StartGameWindow() {
			InitializeComponent();

			standardRows = 5;
			standardCols = 6;
		}

		private void startNewGame_Click(object sender, RoutedEventArgs e) {
			// for now dont hide this window until you implement a button to go back to the game menu

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
					GameWindow gameWindow = new GameWindow(cols, rows);
					gameWindow.Show();
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
	}
}
