using MaterialDesignThemes.Wpf;
using System.Windows;

namespace MemoryTilesGame {
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

		private void toggleTheme(object sender, RoutedEventArgs e) {
			ITheme theme = paletteHelper.GetTheme();
			if(IsDarkTheme = theme.GetBaseTheme() == BaseTheme.Dark) {
				IsDarkTheme = false;
				theme.SetBaseTheme(Theme.Light);
			}
			else {
				IsDarkTheme = true;
				theme.SetBaseTheme(Theme.Dark);
			}
			paletteHelper.SetTheme(theme);
		}
		public bool IsDarkTheme {
			get; set;
		}
		private readonly PaletteHelper paletteHelper = new PaletteHelper();

		private void exitApp(object sender, RoutedEventArgs e) {
			Application.Current.Shutdown();
		}
	}
}
