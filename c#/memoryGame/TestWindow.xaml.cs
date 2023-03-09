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

			// Define the dimensions of the matrix
			int cols = 3;
			int rows = 4;

			// Create a Grid to hold the buttons
			Grid grid = new Grid();

			// Create the rows of the grid
			for(int i = 0; i < rows; i++) {
				RowDefinition rowDef = new RowDefinition();
				grid.RowDefinitions.Add(rowDef);
			}

			// Create the columns of the grid
			for(int i = 0; i < cols; i++) {
				ColumnDefinition colDef = new ColumnDefinition();
				grid.ColumnDefinitions.Add(colDef);
			}

			// Create the buttons and add them to the grid
			for(int i = 0; i < rows; i++) {
				for(int j = 0; j < cols; j++) {
					Button button = new Button();
					button.Content = string.Format("Button {0},{1}", i, j);
					button.Height = 50;
					button.Width = 50;
					Grid.SetRow(button, i);
					Grid.SetColumn(button, j);
					grid.Children.Add(button);
				}
			}

			// Add some margin to the right of the grid
			grid.Margin = new Thickness(0, 0, 50, 0);

			// Add the grid to your WPF window
			this.Content = grid;

			//////

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
			string[] images = Directory.GetFiles(folderPath, "*.png");

			// Create the buttons and add them to the grid
			for(int i = 0; i < rows; i++) {
				for(int j = 0; j < cols; j++) {
					Button button = new Button();

					// Set the background of the button to an image
					ImageBrush imageBrush = new ImageBrush();
					imageBrush.ImageSource = new BitmapImage(new Uri(images[i * cols + j], UriKind.Relative));
					imageBrush.Stretch = Stretch.Uniform;
					button.Background = imageBrush;

					Grid.SetRow(button, i);
					Grid.SetColumn(button, j);
					grid.Children.Add(button);
				}
			}
		}
	}
}
