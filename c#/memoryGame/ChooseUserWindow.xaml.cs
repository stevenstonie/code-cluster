using MaterialDesignThemes.Wpf;
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
