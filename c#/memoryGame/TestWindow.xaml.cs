using System;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace memoryGame {
	public partial class TestWindow : Window {
		public TestWindow() {
			InitializeComponent();

			// specify the folder path where your images are stored
			string folderPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Assets", "GridImages");

			// create a new WrapPanel and set its properties
			var wrapPanel = new WrapPanel {
				Orientation = Orientation.Horizontal,
				HorizontalAlignment = HorizontalAlignment.Center,
				VerticalAlignment = VerticalAlignment.Center,
				Margin = new Thickness(5)
			};

			// get the file names of all the images in the folder
			string[] fileNames = Directory.GetFiles(folderPath, "*.png");

			// loop through the file names and create an Image control for each one
			int row = 0;
			int column = 0;
			foreach(string fileName in fileNames) {
				// create a new Image control and set its properties
				var image = new Image {
					Source = new BitmapImage(new Uri(fileName)),
					Width = 100,
					Height = 100,
					Margin = new Thickness(5),
					Stretch = Stretch.Fill
				};

				// add the Image control to the WrapPanel
				wrapPanel.Children.Add(image);

				// increment the row and column counters
				column++;
				if(column > 2) {
					row++;
					column = 0;
				}
			}

			// add the WrapPanel to the grid
			Grid.SetRow(wrapPanel, 0);
			Grid.SetColumn(wrapPanel, 0);
			ImageGrid.Children.Add(wrapPanel);
		}
	}
	/*
		public partial class TestWindow : Window {
		public ObservableCollection<string> StringItems {
			get; set;
		}

		public TestWindow() {
			InitializeComponent();

			// initialize the StringItems collection
			StringItems = new ObservableCollection<string> { "something", "else", "Button 3", "Button 4", "Button 5" };

			// set the data context of the window to this instance
			DataContext = this;

			// specify the folder path where your images are stored
			string folderPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Assets", "GridImages");

			// create a new list to store the image paths
			List<string> imagePaths = new List<string>();

			// get the file names of all the images in the folder and add them to the list
			string[] fileNames = Directory.GetFiles(folderPath, "*.png");
			foreach(string fileName in fileNames) {
				var image = new Image {
					Source = new BitmapImage(new Uri(fileName)),
					Width = 100,
					Height = 100,
					Margin = new Thickness(5),
					Stretch = Stretch.Uniform
				};

				ImageGrid.Children.Add(image);
			}


			// set the data context of the window to the list of image paths
			DataContext = imagePaths;


			// specify the folder path where your images are stored
			string folderPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Assets", "GridImages");

			// create a new WrapPanel and set its properties
			var wrapPanel = new WrapPanel {
				Orientation = Orientation.Horizontal,
				HorizontalAlignment = HorizontalAlignment.Center,
				VerticalAlignment = VerticalAlignment.Center,
				Margin = new Thickness(10)
			};

			// get the file names of all the images in the folder
			string[] fileNames = Directory.GetFiles(folderPath, "*.png");

			// loop through the file names and create an Image control for each one
			foreach(string fileName in fileNames) {
				// create a new Image control and set its properties
				var image = new Image {
					Source = new BitmapImage(new Uri(fileName)),
					Width = 100,
					Height = 100,
					Margin = new Thickness(5)
				};

				// add the Image control to the WrapPanel
				wrapPanel.Children.Add(image);
			}

			// add the WrapPanel to the grid
			Grid.SetRow(wrapPanel, 0);
			Grid.SetColumn(wrapPanel, 0);
			ImageGrid.Children.Add(wrapPanel);
}
	}
*/
}
