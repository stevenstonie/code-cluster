using System;
using System.IO;
using System.Windows;
using System.Windows.Media.Imaging;

namespace MemoryTilesGame {
	public partial class CreateNewUserWindow : Window {
		private string[] imagesPathsArray;
		private int imageIndex;
		private string currentUserImagePath;

		public CreateNewUserWindow(string newUserName, string newUserImagePath) {
			InitializeComponent();
			this.WindowStartupLocation = WindowStartupLocation.CenterScreen;

			string folderPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Assets", "Images");
			imagesPathsArray = Directory.GetFiles(folderPath, "*.png");
			imageIndex = -1;
		}

		private void next_Click(object sender, RoutedEventArgs e) {
			imageIndex++;
			if(imageIndex > imagesPathsArray.Length - 1) {
				imageIndex = 0;
			}

			updateUserImageOnScreen();
		}

		private void prev_Click(object sender, RoutedEventArgs e) {
			imageIndex--;
			if(imageIndex < 0) {
				imageIndex = imagesPathsArray.Length - 1;
			}

			updateUserImageOnScreen();
		}

		private void add_Click(object sender, RoutedEventArgs e) {

		}

		private void cancel_Click(object sender, RoutedEventArgs e) {

		}

		private void updateUserImageOnScreen() {
			newUserImage.Source = new BitmapImage(new Uri(imagesPathsArray[imageIndex]));


		}
	}
}
