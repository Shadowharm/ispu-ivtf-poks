from enum import Enum
from typing import Any


class Token(Enum):
    # keywords
    PRINT = 0
    ELSE = 1
    FALSE = 2
    FUNCTION = 3
    IF = 4
    VAR = 5
    TRUE = 6
    FOR = 7

    # operators
    AND = 115
    ASSIGN = 100
    DIVISION = 104
    EQUAL = 111
    GREATER = 107
    GREATER_OR_EQUAL = 109
    LESS = 108
    LESS_OR_EQUAL = 110
    MINUS = 102
    MOD = 106
    MULTIPLICATION = 103
    NOT = 113
    NOT_EQUAL = 112
    OR = 114
    PLUS = 101
    POW = 105

    # delimiters
    BRACE_LEFT = 203
    BRACE_RIGHT = 204
    BRACKET_LEFT = 201
    BRACKET_RIGHT = 202
    COMMA = 205
    SEMICOLON = 200

    # constants
    FLOAT = 301
    INTEGER = 300
    STRING = 302

    IDENTIFIER = 400


class Scanner:
    code: str
    cur_line: int
    cur_char_idx: int
    tokens: list[tuple[Token, Any]]

    def __init__(self, code: str) -> None:
        self.code = code

    def _get_next_chars(self, count = 1) -> str | None:
        if self.cur_char_idx + count > len(self.code):
            return None
        return self.code[self.cur_char_idx : self.cur_char_idx + count]

    def _has_more_code(self) -> bool:
        return self.cur_char_idx < len(self.code)

    def _scan_non_significant_chars(self) -> bool:
        if self._get_next_chars() in [' ', '\t']:
            self.cur_char_idx += 1
            return True

        elif self._get_next_chars() == '\n':
            self.cur_line += 1
            self.cur_char_idx += 1
            return True

        elif self._get_next_chars(2) == '/*':
            self.cur_char_idx += 2
            while self._has_more_code():
                if self._get_next_chars(2) == '*/':
                    self.cur_char_idx += 2
                    return True
                elif self._get_next_chars() == '\n':
                    self.cur_line += 1
                self.cur_char_idx += 1
            raise Exception(f"[NanoScript] Comment wasn't closed in line {self.cur_line}")

        return False

    def _scan_keywords(self) -> bool:
        if self._get_next_chars(5) == 'print':
            self.cur_char_idx += 5
            self.tokens.append((Token.PRINT, 'print'))
            return True
        elif self._get_next_chars(4) == 'else':
            self.cur_char_idx += 4
            self.tokens.append((Token.ELSE, 'else'))
            return True
        elif self._get_next_chars(5) == 'false':
            self.cur_char_idx += 5
            self.tokens.append((Token.FALSE, 'false'))
            return True
        elif self._get_next_chars(8) == 'function':
            self.cur_char_idx += 8
            self.tokens.append((Token.FUNCTION, 'function'))
            return True
        elif self._get_next_chars(2) == 'if':
            self.cur_char_idx += 2
            self.tokens.append((Token.IF, 'if'))
            return True
        elif self._get_next_chars(3) == 'var':
            self.cur_char_idx += 3
            self.tokens.append((Token.VAR, 'var'))
            return True
        elif self._get_next_chars(4) == 'true':
            self.cur_char_idx += 4
            self.tokens.append((Token.TRUE, 'true'))
            return True
        elif self._get_next_chars(3) == 'for':
            self.cur_char_idx += 3
            self.tokens.append((Token.FOR, 'for'))
            return True
        return False
    def _scan_operators(self) -> bool:
        if self._get_next_chars(2) == '&&':
            self.cur_char_idx += 2
            self.tokens.append((Token.AND, '&&'))
            return True
        elif self._get_next_chars(2) == '==':
            self.cur_char_idx += 2
            self.tokens.append((Token.EQUAL, '=='))
            return True
        elif self._get_next_chars() == '=':
            self.cur_char_idx += 1
            self.tokens.append((Token.ASSIGN, '='))
            return True
        elif self._get_next_chars() == '/':
            self.cur_char_idx += 1
            self.tokens.append((Token.DIVISION, '/'))
            return True
        elif self._get_next_chars() == '>':
            self.cur_char_idx += 1
            self.tokens.append((Token.GREATER, '>'))
            return True
        elif self._get_next_chars(2) == '>=':
            self.cur_char_idx += 2
            self.tokens.append((Token.GREATER_OR_EQUAL, '>='))
            return True
        elif self._get_next_chars() == '<':
            self.cur_char_idx += 1
            self.tokens.append((Token.LESS, '<'))
            return True
        elif self._get_next_chars(2) == '<=':
            self.cur_char_idx += 2
            self.tokens.append((Token.LESS_OR_EQUAL, '<='))
            return True
        elif self._get_next_chars() == '-':
            self.cur_char_idx += 1
            self.tokens.append((Token.MINUS, '-'))
            return True
        elif self._get_next_chars() == '%':
            self.cur_char_idx += 1
            self.tokens.append((Token.MOD, '%'))
            return True
        elif self._get_next_chars(2) == '**':
            self.cur_char_idx += 2
            self.tokens.append((Token.POW, '**'))
            return True
        elif self._get_next_chars() == '*':
            self.cur_char_idx += 1
            self.tokens.append((Token.MULTIPLICATION, '*'))
            return True
        elif self._get_next_chars() == '!':
            self.cur_char_idx += 1
            self.tokens.append((Token.NOT, '!'))
            return True
        elif self._get_next_chars(2) == '!=':
            self.cur_char_idx += 2
            self.tokens.append((Token.NOT_EQUAL, '!='))
            return True
        elif self._get_next_chars(2) == '||':
            self.cur_char_idx += 2
            self.tokens.append((Token.OR, '||'))
            return True
        elif self._get_next_chars() == '+':
            self.cur_char_idx += 1
            self.tokens.append((Token.PLUS, '+'))
            return True
        return False

    def _scan_delimiters(self) -> bool:
        if self._get_next_chars() == '{':
            self.cur_char_idx += 1
            self.tokens.append((Token.BRACE_LEFT, '{'))
            return True
        elif self._get_next_chars() == '}':
            self.cur_char_idx += 1
            self.tokens.append((Token.BRACE_RIGHT, '}'))
            return True
        elif self._get_next_chars() == '(':
            self.cur_char_idx += 1
            self.tokens.append((Token.BRACKET_LEFT, '('))
            return True
        elif self._get_next_chars() == ')':
            self.cur_char_idx += 1
            self.tokens.append((Token.BRACKET_RIGHT, ')'))
            return True
        elif self._get_next_chars() == ',':
            self.cur_char_idx += 1
            self.tokens.append((Token.COMMA, ','))
            return True
        elif self._get_next_chars() == ';':
            self.cur_char_idx += 1
            self.tokens.append((Token.SEMICOLON, ';'))
            return True
        return False

    def _scan_constants(self) -> bool:
        char = self._get_next_chars()
        if char and char.isdigit():
            val: str = char
            self.cur_char_idx += 1
            is_float = False
            while self._has_more_code():
                char = self._get_next_chars()
                if char == '.' and not is_float:
                    is_float = True
                elif not (char and char.isdigit()):
                    break
                val += char
                self.cur_char_idx += 1
            if is_float:
                self.tokens.append((Token.FLOAT, float(val)))
            else:
                self.tokens.append((Token.INTEGER, int(val)))
            return True

        elif char == '"':
            val: str = ""
            is_success = False
            is_screening = False
            self.cur_char_idx += 1
            while self._has_more_code():
                char = self._get_next_chars()
                if char == '"' and not is_screening:
                    is_success = True
                    self.cur_char_idx += 1
                    break
                elif char == '\\':
                    print('fff')
                    is_screening = True
                    self.cur_char_idx += 1
                    continue
                elif char == '\n' or not char:
                    break
                if is_screening:
                    is_screening = False
                val += char
                self.cur_char_idx += 1
            if not is_success:
                raise Exception(f"[NanoScript]: String wasn't closed in line " + str(self.cur_line))
            self.tokens.append((Token.STRING, val))
            return True

        return False

    def _scan_identifier(self) -> bool:
        char = self._get_next_chars()

        if char and (char.isalpha() or char == '_'):
            val: str = char
            self.cur_char_idx += 1
            while self._has_more_code():
                char = self._get_next_chars()
                if not (char and (char.isalnum() or char == '_')):
                    break
                val += char
                self.cur_char_idx += 1
            self.tokens.append((Token.IDENTIFIER, val))
            return True

        return False

    def scan(self):
        self.cur_line = 0
        self.cur_char_idx = 0
        self.tokens = []

        while self._has_more_code():
            if not (self._scan_non_significant_chars() or \
                    self._scan_keywords() or \
                    self._scan_operators() or \
                    self._scan_delimiters() or \
                    self._scan_constants() or \
                    self._scan_identifier()):
                raise Exception(f"[NanoScript] Unexpected character in line {self.cur_line}: {self._get_next_chars()}")

        return self.tokens


source_code = """
function main() {
	var number = (8 * (6 - 2)) + 1;
	print("number: ", number);
	
	var boolean = !(number > 5 && true);
	print("boolean: ", boolean);

	if (number == boolean) {
		print("vars are the same");
	} else {
		print("vars are different");
	}

	var factorial = 1;

	for (var count = 0; count < 10;) {
		factorial = factorial * count;
	}

	print("10! = ", factorial);
}
"""

if __name__ == '__main__':
    scanner = Scanner(source_code)
    tokens = scanner.scan()

    for token in tokens:
        print(f'{token[0]}: {token[1]}')
