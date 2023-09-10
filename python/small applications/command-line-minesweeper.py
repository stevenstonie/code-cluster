from random import sample
import re

class Board:
    # initialize the board and all attributes
    def __init__(self, dim_size, nb_bombs):
        self.dim_size = dim_size
        self.nb_bombs = nb_bombs
        # create the board and insert the bombs
        self.board = self.make_new_board()
        self.assign_values_to_board()
        # 'dug' is a set of already dug squares
        self.dug = set()
    
    def make_new_board(self):
        board = [[None for _ in range(self.dim_size)] for _ in range(self.dim_size)]
        # create an array of random indexes where bombs will be placed
        bombs_arr = sample(range(self.dim_size**2), self.nb_bombs)
        for idx in bombs_arr:
            row = idx // self.dim_size
            col = idx % self.dim_size
            board[row][col] = '*'
        return board
    
    def assign_values_to_board(self):
        # go through each square. if the square is bomb skip 1 loop. if not assign its value as nb of neighouring bombs
        for i_row in range(self.dim_size):
            for i_col in range(self.dim_size):
                if self.board[i_row][i_col] == '*':
                    continue
                # assign the current element's value as how many neighbouring bombs it has
                self.board[i_row][i_col] = self.get_nb_of_neighbouring_bombs(i_row, i_col)
    
    def get_nb_of_neighbouring_bombs(self, i_row, i_col):
        nb_neighb_bombs = 0
        # go through all neighbours. use min and max so it doesnt overflow
        for i_r in range(max(0, i_row - 1), min(self.dim_size - 1, (i_row + 1)) + 1):
            for i_c in range(max(0, i_col - 1), min(self.dim_size - 1, (i_col + 1)) + 1):
                # skip the currently dug element
                if i_r == i_row and i_c == i_col:
                    continue
                # if neighbour is bomb increment nb of neighbouring bombs
                if self.board[i_r][i_c] == '*':
                    nb_neighb_bombs+=1;
        return nb_neighb_bombs
        
    # called every time a square is dug
    def dig(self, i_row, i_col):
        # add the just dug element into the 'dug' set.
        self.dug.add((i_row, i_col))
        # return false if the element just dug is a bomb
        if self.board[i_row][i_col] == '*':
            return False
        # return true if element has at least 1 neighbouring bomb
        elif self.board[i_row][i_col] > 0:
            return True
        # recursively go through each neighbour while the current one doesnt have any neighbouring bombs
        for i_r in range(max(0, i_row - 1), min(self.dim_size - 1, (i_row + 1)) + 1):
            for i_c in range(max(0, i_col - 1), min(self.dim_size - 1, (i_col + 1)) + 1):
                # skip the squares that have been dug
                if (i_r, i_c) in self.dug:
                    continue
                self.dig(i_r, i_c)
        return True
    
    # magic method that prints a string representation of the instance of the class rather than its memory location
    def __str__(self):
        # there are two boards: the real one, 'board', and the one that the player sees, 'visible_board'
        # at every call of the print(object), when iterating through the real board, 
        # if the value has been dug before --> place its value into the visible one
        visible_board = [[None for _ in range(self.dim_size)] for _ in range(self.dim_size)]
        for i_row in range(self.dim_size):
            for i_col in range(self.dim_size):
                if(i_row, i_col) in self.dug:
                    visible_board[i_row][i_col] = str(self.board[i_row][i_col])
                else:
                    visible_board[i_row][i_col] = ' '
        
        # "beautifying" the output using 'str_rep' as a table representation
        str_rep = ''
        widths = []
        for idx in range(self.dim_size):
            columns = map(lambda x: x[idx], visible_board)
            widths.append(
				len(max(columns, key = len))
			)
        indices = [i for i in range(self.dim_size)]
        indices_row = '    '
        cells = []
        for idx, col in enumerate(indices):
            format = '%-' + str(widths[idx]) + "s" # print indexes above
            cells.append(format % (col))
        indices_row += '  '.join(cells)
        indices_row += '  \n'
        
        
        for i in range(len(visible_board)):     # for every row
            row = visible_board[i]
            str_rep += f'{i}  |'
            cells = []
            for idx, col in enumerate(row):
                format = '%-' + str(widths[idx]) + "s"  # print indexes to the left
                cells.append(format % (col))
            str_rep += ' |'.join(cells)
            str_rep += ' |\n'
        
        str_len = int(len(str_rep) / self.dim_size)
        str_rep = indices_row + '-'*str_len + '\n' + str_rep + '-'*str_len
        
        return str_rep
        
       

def play(dim_size = 10, nb_bombs=10):
    # create the board and plant the bombs
    board = Board(dim_size, nb_bombs)
    
    is_safe = True
    # repeat the loop as long as the number of the dug squares is smaller than the squares that are safe
    while len(board.dug) < board.dim_size ** 2 - nb_bombs:
    	# show the board and ask for a place to dig
        print(board)
        # the re.split() below takes input as 
        user_input = re.split(', *| (\\s)*', input("input a place to dig (as either \"i,j\" or \"i j\"): "))
        print('\n\n')
        
        # skip iteration if input is not a number
        try:
            i_row, i_col = int(user_input[0]), int(user_input[-1])
        except ValueError:
            print("invalid input. try again")
            continue
        # skip iteration if input is not correct
        if i_row < 0 or i_row >= board.dim_size or i_col < 0 or i_col >= dim_size:
            print("invalid location. try again.")
            continue
    	# dig the square. if returned value is true then the square is not a bomb
        is_safe = board.dig(i_row, i_col);
    	# if location is a bomb, game over
        if not is_safe:
            break
    
    if is_safe:
        print("congratulations!! you won!")
        board.dug = [(i_r, i_c) for i_r in range(board.dim_size) for i_c in range(board.dim_size)]
        print(board)
    else:
        print("you just dug a bomb. game over..")
        board.dug = [(i_r, i_c) for i_r in range(board.dim_size) for i_c in range(board.dim_size)]
        print(board)


if __name__ == '__main__':
    play()