import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

class LexicalAnalyzerJava {
    // Constants
    public static final int MAX_LEXEME = 100;
    public static final int EOF = -1;
    // Character classes
    public static final int LETTER = 0;
    public static final int DIGIT = 1;
    public static final int UNKNOWN = 99;
    // Token codes
    public static final int INT_LIT = 10;
    public static final int IDENT = 11;
    public static final int ASSIGN_OP = 20;
    public static final int ADD_OP = 21;
    public static final int SUB_OP = 22;
    public static final int MULT_OP = 23;
    public static final int DIV_OP = 24;
    public static final int LEFT_PAREN = 25;
    public static final int RIGHT_PAREN = 26;
    // Global variables
    private static String file_content;
    private static int idx = 0;
    private static int charClass;
    private static String lexeme = "";
    private static char nextChar;
    private static int nextToken;

    public static void getChar() {
        if (idx < file_content.length()) {
            nextChar = file_content.charAt(idx);
            if (Character.isLetter(nextChar)) 
                charClass = LETTER;
            else if (Character.isDigit(nextChar)) 
                charClass = DIGIT;
            else 
                charClass = UNKNOWN;
            // charClass = Character.isLetter(nextChar) ? LETTER :
            //             Character.isDigit(nextChar) ? DIGIT : UNKNOWN;
            idx++;
        } else {
            nextChar = '-';
            charClass = EOF;
        }
    }

    public static void addChar() {
        if (lexeme.length() <= MAX_LEXEME - 2) // max 99
            lexeme += nextChar;
        else
            System.out.println("Error - lexeme is too long");
    }

    public static int lookup(char ch) {
        switch (ch) {
            case '(': return LEFT_PAREN;
            case ')': return RIGHT_PAREN;
            case '+': return ADD_OP;
            case '-': return SUB_OP;
            case '*': return MULT_OP;
            case '/': return DIV_OP;
            default: return EOF;
        }
    }

    public static int lex() {
        lexeme = "";

        while (Character.isWhitespace(nextChar)) 
            getChar();

        if (charClass == LETTER) {
            // Parse identifiers 
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
                nextToken = IDENT;
            }
        } else if (charClass == DIGIT) { 
            /* Parse integer literals */
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
        } else if (charClass == UNKNOWN) {
            /* Parentheses and operators */
            nextToken = lookup(nextChar);
            addChar();
            getChar();
        } else {
            /* EOF */
            nextToken = EOF;
            lexeme = "EOF";
        }
        System.out.printf("Next token is: %d, Next lexeme is %s%n", nextToken, lexeme);

        return nextToken;
    }

    public static void main(String[] args) {
        try {
            Path path = Paths.get("front.in");
            file_content = Files.readString(path);
            getChar();
            while (lex() != EOF){}
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

