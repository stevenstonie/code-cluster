using System;
using System.IO;
using System.Windows;
using System.Windows.Media.Imaging;

namespace MemoryTilesGame {
	public partial class CreateNewUserWindow : Window {
		private string[] imagesPathsArray;
		private int imageIndex;
		public string NewUserName {
			get; set;
		}
		public string NewUserImagePath {
			get; set;
		}

		public CreateNewUserWindow() {
			InitializeComponent();
			this.WindowStartupLocation = WindowStartupLocation.CenterScreen;

			string folderPath = Path.Combine(Environment.CurrentDirectory, "Assets", "Images");
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
			if(newUserNameBox.Text == "" || newUserNameBox.Text.Length > 20) {
				MessageBox.Show("the name either is null or over the limit of 20 characters");
			}
			else {
				if(newUserImageBox.Source == null) {
					MessageBox.Show("no image has been assigned yet.");
				}
				else {
					NewUserName = newUserNameBox.Text;
					NewUserImagePath = imagesPathsArray[imageIndex];

					Close();
				}
			}
		}

		private void cancel_Click(object sender, RoutedEventArgs e) {
			NewUserName = "";
			NewUserImagePath = "";
			Close();
		}

		private void updateUserImageOnScreen() {
			newUserImageBox.Source = new BitmapImage(new Uri(imagesPathsArray[imageIndex]));
		}
	}
}
