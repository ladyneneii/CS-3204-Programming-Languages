# Constants
MAX_LEXEME = 100
EOF = -1
# Character classes
LETTER = 0
DIGIT = 1
UNKNOWN = 99
# Token codes
INT_LIT = 10
IDENT = 11
ASSIGN_OP = 20
ADD_OP = 21
SUB_OP = 22
MULT_OP = 23
DIV_OP = 24
LEFT_PAREN = 25
RIGHT_PAREN = 26
# Global variables
file_content = None
idx = 0
charClass = None
lexeme = None
nextChar = None
nextToken = None


def getChar():
    global idx, nextChar, charClass
    if (idx < len(file_content)):
        nextChar = file_content[idx]
        if nextChar.isalpha():
            charClass = LETTER
        elif nextChar.isdigit():
            charClass = DIGIT
        else:
            charClass = UNKNOWN
        idx += 1
    else:
        nextChar = '-'
        charClass = EOF

    # print(idx)


def addChar():
    global lexeme, nextChar
    if (len(lexeme) <= MAX_LEXEME - 2): # max 99
        lexeme += nextChar
    else:
        print("Error - lexeme is too long");


def lookup(ch):
    nextToken = {
        '(': LEFT_PAREN,
        ')': RIGHT_PAREN,
        '+': ADD_OP,
        '-': SUB_OP,
        '*': MULT_OP,
        '/': DIV_OP,
    }

    return nextToken.get(ch, EOF)


def lex():
    global lexeme, nextChar, charClass, nextToken
    lexeme = ""

    while (nextChar.isspace()):
        getChar()

    if (charClass == LETTER):
        # Parse identifiers 
        while (charClass == LETTER or charClass == DIGIT):
            addChar();
            getChar();
            nextToken = IDENT;
    elif (charClass == DIGIT): 
        # Parse integer literals 
        while (charClass == DIGIT):
            addChar();
            getChar();
            nextToken = INT_LIT;
    elif (charClass == UNKNOWN):
        # Parentheses and operators 
        nextToken = lookup(nextChar);
        addChar();
        getChar();
    else:
        # EOF 
        nextToken = EOF;
        lexeme = "EOF"
    print(f"Next token is: {nextToken}, Next lexeme is {lexeme}");

    return nextToken;
    

try:
    with open("front.in", 'r') as file:
        file_content = file.read()
        getChar()
        while(lex() != EOF):
            pass
except FileNotFoundError:
    print(f"ERROR - cannot open front.in")
except Exception as e:
    print(f"An error occurred: {e}")