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
			int cols = 4;
			int rows = 5;

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
					button.MinHeight = 50;
					button.MinWidth = 50;
					button.Margin = new Thickness(5); // Set the margin to 5 pixels
					Grid.SetRow(button, i);
					Grid.SetColumn(button, j);
					grid.Children.Add(button);
				}
			}

			// Add some margin to the right of the grid
			grid.Margin = new Thickness(0, 0, 50, 0);

			// Add the grid to your WPF window
			this.Content = grid;

			// specify the folder path where your images are stored
			string folderPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Assets", "GridImages");

			// get the file names of all the images in the folder
			string[] images = Directory.GetFiles(folderPath, "*.png");

			// Loop through each button and assign an image to it
			int imageIndex = 0;
			foreach(Button button in grid.Children) {
				// Set the background of the button to an image
				ImageBrush imageBrush = new ImageBrush();
				imageBrush.ImageSource = new BitmapImage(new Uri(images[imageIndex], UriKind.Relative));
				imageBrush.Stretch = Stretch.Uniform;
				button.Background = imageBrush;

				// Increment the image index
				imageIndex++;

				// If we've assigned all the images, start again from the beginning
				if(imageIndex == images.Length) {
					imageIndex = 0;
				}
			}

			// Add a SizeChanged event handler for the window
			this.SizeChanged += (sender, e) => {
				// Calculate the new button size based on the window size
				double size = Math.Min((this.ActualWidth - grid.Margin.Right) / cols, this.ActualHeight / rows);

				// Update the button sizes
				foreach(Button button in grid.Children) {
					button.Width = size;
					button.Height = size;
				}
			};
		}
	}
}
