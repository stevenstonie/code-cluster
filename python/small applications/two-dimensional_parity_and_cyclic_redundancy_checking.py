def crc(input):
    None


def twoDimensionalParity(input):
    if isBinary(input) is False or isMultipleOf7(input) is False:
        print('does not meet the requirements..')
    else:
        printTheParityMatrix(input)


def main():
    print("~~~~~~TWO-DIMENSIONAL PARITY CHECKER~~~~~~")
    twoDimensionalParity('100101100100111100101')

    print("\n~~~~~~CRC~~~~~~")
    crc('100101100100111100101')


def isBinary(input):
    return False if any(char != '0' and char != '1' for char in input) else True


def isMultipleOf7(input):
    return True if len(input) % 7 == 0 else False


def printTheParityMatrix(input):
    nbOfLines = len(input) // 7

    parityMatrix = [input[i:i+7] + ('  1' if input[i:i+7].count('1') %
                                    2 == 0 else '  0') for i in range(0, len(input), 7)]

    newRow = ''.join(['1' if sum(1 for i in range(
        nbOfLines) if parityMatrix[i][j] == '1') % 2 == 0 else '0' for j in range(7)])
    parityMatrix += ['', newRow]

    print('\n'.join(parityMatrix))


if __name__ == '__main__':
    main()
