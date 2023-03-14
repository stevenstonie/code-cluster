def crc(message, key):
    if crcVerification(message, key) is False:
        print('the parameters do not meet the requirements')
        return

    print('orig message')
    print(message)
    print('\ncoded message\n')

    degreeOfPolynome = len(key)-1
    remainder = message + '0' * degreeOfPolynome

    while len(remainder) > degreeOfPolynome:
        partOfMessage = remainder[:degreeOfPolynome+1]
        partOfMessage = xor(partOfMessage, key)
        remainder = remainder[degreeOfPolynome+1:]
        remainder = partOfMessage + remainder
        while len(remainder) > 0 and remainder[0] == '0':
            remainder = remainder[1:]

    if remainder == '':
        remainder = '0' * degreeOfPolynome

    message += xor(remainder, '0' * degreeOfPolynome)

    print(message)
    return message


def twoDimensionalParity(input):
    if isBinary(input) is False or isMultipleOf7(input) is False:
        print('does not meet the requirements..')
    else:
        printTheParityMatrix(input)


def main():
    print('~~~~~~TWO-DIMENSIONAL PARITY CHECKER~~~~~~')
    twoDimensionalParity('100101100100111100101')

    print('\n~~~~~~CRC~~~~~~')
    encodedMessage = crc('1011111', '101')

    print('\n~~~~~~CRC VERIFICATION~~~~~~')


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


def crcVerification(message, key):
    if key[0] != '1':
        while key[0] != '1':
            print('the binary polinome has to be binary and start with 1!!')
            key = input("input another key: ")
    if isBinary(message) is False or isBinary(key) is False:
        return False
    else:
        return True


def xor(a, b):
    result = ""

    for i in range(len(a)):
        result += '0' if a[i] == b[i] else '1'
    return result


if __name__ == '__main__':
    main()
