

using System;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Threading;

namespace memoryGame {
	public partial class GameWindow : Window {
		DispatcherTimer _timer;
		TimeSpan _time;

		public GameWindow() {
			InitializeComponent();

			int cols = 6;
			int rows = 5;

			createGrid(cols, rows);

			addImagesToGrid(cols, rows);

			_time = TimeSpan.FromSeconds(4);
			tbTime.Margin = new Thickness(0, 0, GameGrid.ActualWidth - tbTime.ActualWidth, 0);

			_timer = new DispatcherTimer(new TimeSpan(0, 0, 1), DispatcherPriority.Normal, delegate {
				tbTime.Text = _time.ToString("c");
				if(_time == TimeSpan.Zero) {
					_timer.Stop();
					youLostMessage.Text = "the time is up. you lost..";
				}
				_time = _time.Add(TimeSpan.FromSeconds(-1));
			}, System.Windows.Application.Current.Dispatcher);


			_timer.Start();


		}

		private void createGrid(int cols, int rows) {
			// Create the rows of the grid
			for(int i = 0; i < rows; i++) {
				RowDefinition rowDef = new RowDefinition();
				GameGrid.RowDefinitions.Add(rowDef);
			}

			// Create the columns of the grid
			for(int i = 0; i < cols; i++) {
				ColumnDefinition colDef = new ColumnDefinition();
				GameGrid.ColumnDefinitions.Add(colDef);
			}

			// Create the buttons and add them to the grid
			for(int i = 0; i < rows; i++) {
				for(int j = 0; j < cols; j++) {
					Button button = new Button();
					button.MinHeight = 50;
					button.MinWidth = 50;
					button.Margin = new Thickness(3);
					Grid.SetZIndex(button, -1); // Set the Panel.ZIndex to -1 to make the button behind any other elements
					Grid.SetRow(button, i);
					Grid.SetColumn(button, j);
					GameGrid.Children.Add(button);
				}
			}

			GameGrid.VerticalAlignment = VerticalAlignment.Top;
			GameGrid.Margin = new Thickness(0, 40, 0, 50);
		}

		private void addImagesToGrid(int cols, int rows) {
			// specify the folder path where your images are stored
			string folderPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Assets", "Images");

			// get the file names of all the images in the folder
			string[] images = Directory.GetFiles(folderPath, "*.png");

			// Loop through each button and assign an image to it
			int imageIndex = 0;
			foreach(var child in GameGrid.Children) {
				if(child is Button button) {
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
			}

			// Add a SizeChanged event handler for the window
			this.SizeChanged += (sender, e) => {
				// Calculate the new button size based on the window size
				double size = Math.Min((this.ActualWidth - GameGrid.Margin.Right) / cols, this.ActualHeight / rows);

				// Update the button sizes
				foreach(var child in GameGrid.Children) {
					if(child is Button button) {
						button.Width = size;
						button.Height = size;
					}
				}
			};
		}
	}
}
