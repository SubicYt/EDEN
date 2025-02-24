import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.List;
import java.util.Scanner;

enum TokenType {
    KEYWORD, IDENTIFIER, LITERAL, OPERATOR, PUNCTUATION, WHITESPACE, COMMENT, UNKNOWN
}

class Token {
    private TokenType type;
    private String value;

    public Token(TokenType type, String value) {
        this.type = type;
        this.value = value;
    }

    public TokenType getType() {
        return type;
    }

    public String getValue() {
        return value;
    }

    @Override
    public String toString() {
        return "Token{" + "type=" + type + ", value='" + value + '\'' + '}';
    }
}

public class lexer {
    private String input;
    private int currentPosition;

    public lexer(String input) {
        this.input = input;
        this.currentPosition = 0;
    }

    public List<Token> tokenize() {
        List<Token> tokens = new ArrayList<>();

        while (currentPosition < input.length()) {
            char currentChar = input.charAt(currentPosition);

            if (Character.isWhitespace(currentChar)) {
                currentPosition++;
                continue;
            }

            Token token = nextToken();
            if (token != null) {
                tokens.add(token);
            } else {
                throw new RuntimeException("Unknown character: " + currentChar);
            }
        }

        return tokens;
    }

    private Token nextToken() {
        if (currentPosition >= input.length()) {
            return null;
        }

        String[] tokenPatterns = {
            "if|else|while|for",         // Keywords
		"let",			 // Assignment
            "[a-zA-Z_][a-zA-Z0-9_]*",    // Identifiers
            "\\d+",                      // Literals
            "[+-/*=<>!]",                // Operators
            "[.,;(){}]",                 // Punctuation
        };

        TokenType[] tokenTypes = {
            TokenType.KEYWORD,
            TokenType.IDENTIFIER,
            TokenType.LITERAL,
            TokenType.OPERATOR,
            TokenType.PUNCTUATION,
        };

        for (int i = 0; i < tokenPatterns.length; i++) {
            Pattern pattern = Pattern.compile("^" + tokenPatterns[i]);
            Matcher matcher = pattern.matcher(input.substring(currentPosition));

            if (matcher.find()) {
                String value = matcher.group();
                currentPosition += value.length();
                return new Token(tokenTypes[i], value);
          }
        }

        return null;
    }
}


class Main {
    public static void main(String[] args) {
	Scanner scan = new Scanner(System.in);
	System.out.println("Code here");

        String code = scan.next();

        lexer lexer = new lexer(code);
        List<Token> tokens = lexer.tokenize();

        for (Token token : tokens) {
            System.out.println(token);
        }
    }
}
