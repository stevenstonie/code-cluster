using System;
using System.Collections.Generic;
using System.IO;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Threading;

namespace MemoryTilesGame {
	public partial class GameWindow : Window {
		DispatcherTimer _timer;
		TimeSpan _time;
		private string button1Tag;
		private Button button1;

		public GameWindow() {
			InitializeComponent();

			initAllVariables();

			int cols = 6;
			int rows = 5;

			createGrid(cols, rows);

			addImagesToGrid(cols, rows);

			placeTimer();
		}

		private void initAllVariables() {
			button1Tag = "";
			button1 = null;
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

					button.Click += Button_Click; // add event handler

					Grid.SetRow(button, i);
					Grid.SetColumn(button, j);
					GameGrid.Children.Add(button);
				}
			}

			GameGrid.VerticalAlignment = VerticalAlignment.Top;
			GameGrid.HorizontalAlignment = HorizontalAlignment.Left;
			GameGrid.Margin = new Thickness(0, 40, 0, 50);
		}

		private void addImagesToGrid(int cols, int rows) {
			// specify the folder path where your images are stored
			string folderPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Assets", "Images");

			// get the file names of all the images in the folder
			string[] images = Directory.GetFiles(folderPath, "*.png");

			// put images in a list
			List<KeyValuePair<string, ImageBrush>> imagesList = new List<KeyValuePair<string, ImageBrush>>(); // 1 param - tag, 2 param - image
			for(int i = 0; i < cols * rows / 2; i++) {
				imagesList.Add(new KeyValuePair<string, ImageBrush>(i.ToString(), new ImageBrush { ImageSource = new BitmapImage(new Uri(images[i], UriKind.Relative)) }));
				imagesList.Add(new KeyValuePair<string, ImageBrush>(i.ToString(), new ImageBrush { ImageSource = new BitmapImage(new Uri(images[i], UriKind.Relative)) }));
			}

			//shuffle the list
			Random random = new Random();
			imagesList.Sort((a, b) => random.Next(2) == 0 ? -1 : 1);


			// Loop through each button and assign an image and a tag to it
			int listIndex = 0;
			foreach(var child in GameGrid.Children) {
				if(child is Button button) {
					button.Background = imagesList[listIndex].Value;
					button.Tag = imagesList[listIndex].Key;

					listIndex++;
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

		private void placeTimer() {
			_time = TimeSpan.FromSeconds(10);
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

		private async void Button_Click(object sender, RoutedEventArgs e) {
			Console.WriteLine("tag: " + ((Button)sender).Tag);

			// disable the mouse for the entire grid
			IsHitTestVisible = false;
			// Wait some time
			await Task.Delay(1000);

			// first flipped image
			if(button1Tag == "") {
				button1Tag = ((Button)sender).Tag.ToString();
				button1 = (Button)sender;
			}
			// second flipped image
			else {
				// are the same image but different button
				if(((Button)sender).Tag.ToString() == button1Tag && ((Button)sender) != button1) {
					button1.Opacity = 0;
					button1.IsEnabled = false;
					((Button)sender).Opacity = 0;
					((Button)sender).IsEnabled = false;
					button1 = null;
					button1Tag = "";
				}
				else {
					button1 = null;
					button1Tag = "";
				}
			}

			// reenable the mouse for the entire grid
			IsHitTestVisible = true;
		}
	}
}

// notes here:
// - add images like this: take cols*rows/2 images from the folder and put them in the images array.
// shuffle the array and for each image insert one in an random empty place and the other one in another random empty place.
// (note: the same images have the same tag)
// - make the images initially grey (idk turn the brightness on full or something. when a button gets clicked change the setting accordingly)
// - add more images
// - get parameter of how many cols and rows should the grid have. (also limit the cols and rows to a maximum and also make sure one is even)
// - redo the timer and the lose case.
