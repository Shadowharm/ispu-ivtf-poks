export default class TokenType {
    name: string;
    regex: string;


    constructor(name: string, regex: string) {
        this.name = name;
        this.regex = regex;
    }
}

export const tokenTypesList = {
    'NUMBER': new TokenType('NUMBER', '\\b\\d+(\\.\\d+)?\\b'), // Числа
    'STRING': new TokenType('STRING', `"(?:[^"\\\\]|\\\\.)*"|'(?:[^'\\\\]|\\\\.)*'`), // Строки в кавычках
    'VARIABLE': new TokenType('VARIABLE', '\\b[a-zA-Z_$][a-zA-Z0-9_$]*\\b'), // Имена переменных
    'SEMICOLON': new TokenType('SEMICOLON', ';'), // Точка с запятой
    'SPACE': new TokenType('SPACE', '[ \\n\\t\\r]+'), // Пробелы и символы переноса строки
    'ASSIGN': new TokenType('ASSIGN', '='), // Присваивание
    'PLUS': new TokenType('PLUS', '\\+'), // Сложение
    'MINUS': new TokenType('MINUS', '-'), // Вычитание
    'MULTIPLY': new TokenType('MULTIPLY', '\\*'), // Умножение
    'DIVIDE': new TokenType('DIVIDE', '/'), // Деление
    'LPAR': new TokenType('LPAR', '\\('), // Левая скобка
    'RPAR': new TokenType('RPAR', '\\)'), // Правая скобка
    'LBRACE': new TokenType('LBRACE', '\\{'), // Левая фигурная скобка
    'RBRACE': new TokenType('RBRACE', '\\}'), // Правая фигурная скобка
    'COMMA': new TokenType('COMMA', ','), // Запятая
    'AND': new TokenType('AND', '&&'), // Логическое И
    'OR': new TokenType('OR', '\\|\\|'), // Логическое ИЛИ
    'NOT': new TokenType('NOT', '!'), // Логическое НЕ
    'EQUALS': new TokenType('EQUALS', '=='), // Сравнение равенства
    'LESS_THAN': new TokenType('LESS_THAN', '<'), // Меньше
    'GREATER_THAN': new TokenType('GREATER_THAN', '>'), // Больше
    'PRINT': new TokenType('PRINT', '\\bprint\\b'), // Встроенная функция print
    'TRUE': new TokenType('TRUE', '\\btrue\\b'), // Логическое значение true
    'FALSE': new TokenType('FALSE', '\\bfalse\\b'), // Логическое значение false
    'IF': new TokenType('IF', '\\bif\\b'), // Условие if
    'ELSE': new TokenType('ELSE', '\\belse\\b'), // Альтернативное условие else
    'FOR': new TokenType('FOR', '\\bfor\\b'), // Цикл for
    'VAR': new TokenType('VAR', '\\bvar\\b'), // Объявление переменной var
    'FUNCTION': new TokenType('FUNCTION', '\\bfunction\\b'), // Объявление функции
}
