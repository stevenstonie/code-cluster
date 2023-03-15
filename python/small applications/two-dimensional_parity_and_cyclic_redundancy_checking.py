import random


def encodedMessageVerification(encodedMessage, key):
    remainder = modulo2Division(encodedMessage, key)

    return True if remainder == '' else False


def crc(message, key):
    if keyVerification(message, key) is False:
        return 'the parameters do not meet the requirements'

    degreeOfPolynome = len(key)-1
    # remainder also == extendedMessage and also == currentMessage
    remainder = message + '0' * degreeOfPolynome

    remainder = modulo2Division(remainder, key)

    if remainder == '':
        remainder = '0' * degreeOfPolynome

    message += xor(remainder, '0' * degreeOfPolynome)

    return message


def twoDimensionalParity(input):
    if isBinary(input) is False or isMultipleOf7(input) is False:
        return 'does not meet the requirements..'
    else:
        return printTheParityMatrix(input)


def main():
    initMessage = '100101100100111100101'
    print('~~~~~~TWO-DIMENSIONAL PARITY CHECKER~~~~~~')
    parityMatrix = twoDimensionalParity(initMessage)
    print(parityMatrix)

    ###

    initMessage = '11010011101100'
    key = '1011'
    print('\n~~~~~~CRC~~~~~~')
    encodedMessage = crc(initMessage, key)
    print('orig message')
    print(initMessage)
    print('\ncoded message')
    print(encodedMessage)

    ###

    print('\n~~~~~~CRC VERIFICATION~~~~~~')
    if encodedMessageVerification(encodedMessage, key) == True:
        print('message contains no errors')
    else:
        print('message contains errors!')

    bitIndex = random.randint(0, len(encodedMessage))
    # flip the bit at the index bitIndex
    encodedMessage = encodedMessage[:bitIndex] + \
        ('0' if encodedMessage[bitIndex] ==
         '1' else '1') + encodedMessage[bitIndex+1:]

    if encodedMessageVerification(encodedMessage, key) == True:
        print('message contains no errors')
    else:
        print('message contains errors!')


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

    return '\n'.join(parityMatrix)


def keyVerification(message, key):
    if key[0] != '1':
        while key[0] != '1':
            print('the binary polinome has to be binary and start with 1!!')
            key = input("input another key: ")
    if isBinary(message) is False or isBinary(key) is False:
        return False
    else:
        return True


def xor(a, b):  # len(a) == len(b)
    result = ''

    for i in range(len(a)):
        result += '0' if a[i] == b[i] else '1'
    return result


def modulo2Division(remainder, key):
    while len(remainder) > len(key) - 1:
        partOfMessage = remainder[:len(key)]
        remainder = remainder[len(key):]
        partOfMessage = xor(partOfMessage, key)
        remainder = partOfMessage + remainder
        while len(remainder) > 0 and remainder[0] == '0':
            remainder = remainder[1:]
    return remainder


if __name__ == '__main__':
    main()
