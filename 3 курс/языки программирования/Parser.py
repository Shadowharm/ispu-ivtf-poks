from Analyze import Token

from typing import Any


type TokenData = tuple[Token, Any]


class TreeNode:
    type: str
    token: TokenData | None
    children: list['TreeNode']

    def __init__(self, type: str, token: TokenData | None = None) -> None:
        self.type = type
        self.token = token
        self.children = []

    def print_tree(self, level = 0):
        if self.type == 'token':
            print(f'{" " * (level * 4)}{self.token[0]}: {self.token[1]}')
        else:
            print(f'{" " * (level * 4)}{self.type}')
            

        for child in self.children:
            child.print_tree(level + 1)


class ParseException(Exception):
    pass


class Parser:
    tokens: list[TokenData]
    cur_token_idx = -1
    tree: list[TreeNode]

    def __init__(self, tokens: list[TokenData]) -> None:
        self.tokens = tokens
        self.tree = []

    @property
    def next_token(self) -> TokenData:
        # handle stack overflow
        self.cur_token_idx += 1
        return self.tokens[self.cur_token_idx]

    @property
    def prev_token(self) -> TokenData:
        # handle stack overflow
        return self.tokens[self.cur_token_idx - 1]

    def parseProg(self) -> bool:
        if self.next_token[0] == Token.FUNCTION and \
                self.next_token[0] == Token.IDENTIFIER and \
                self.next_token[0] == Token.BRACKET_LEFT and \
                self.next_token[0] == Token.BRACKET_RIGHT and \
                self.next_token[0] == Token.BRACE_LEFT:
            while self.next_token[0] != Token.BRACE_RIGHT:
                self.cur_token_idx -= 1
                self.tree.append(self.parseStmt())
            return True
        return False

    def parseStmt(self) -> TreeNode:
        token = self.next_token
        self.cur_token_idx -= 1

        if token[0] == Token.IF:
            return self.parseIfStmt()
        elif token[0] == Token.FOR:
            return self.parseForStmt()
        elif token[0] == Token.PRINT:
            return self.parsePrintStmt()
        else:
            return self.parseAssign()

    def parseAssign(self) -> TreeNode:
        node = TreeNode('assign')
        token = self.next_token

        if token[0] == Token.VAR:
            node.children.append(TreeNode('token', token))
        else:
            self.cur_token_idx -= 1

        token = self.next_token

        if token[0] == Token.IDENTIFIER:
            node.children.append(TreeNode('token', token))
            token = self.next_token
            if token[0] == Token.ASSIGN:
                node.children.append(TreeNode('token', token))
                node.children.append(self.parseExpr())
                token = self.next_token
                if token[0] == Token.SEMICOLON:
                    node.children.append(TreeNode('token', token))
                    return node

        raise ParseException(f"Error in assign statement. Unexpected \"{token[1]}\"/")

    def parseExpr(self) -> TreeNode:
        node = TreeNode('expr')
        node.children.append(self.parseAndExpr())

        token = self.next_token
        while token[0] == Token.OR:
            node.children.append(TreeNode('token', token))
            node.children.append(self.parseAndExpr())
            token = self.next_token

        self.cur_token_idx -= 1
        return node

    def parseAndExpr(self) -> TreeNode:
        node = TreeNode('and_expr')
        node.children.append(self.parseEqualExpr())

        token = self.next_token
        while token[0] == Token.AND:
            node.children.append(TreeNode('token', token))
            node.children.append(self.parseEqualExpr())
            token = self.next_token

        self.cur_token_idx -= 1
        return node

    def parseEqualExpr(self) -> TreeNode:
        node = TreeNode('equal_expr')
        node.children.append(self.parseCompareExpr())

        token = self.next_token
        if token[0] in [Token.EQUAL, Token.NOT_EQUAL]:
            node.children.append(TreeNode('token', token))
            node.children.append(self.parseCompareExpr())
        else:
            self.cur_token_idx -= 1

        return node

    def parseCompareExpr(self) -> TreeNode:
        node = TreeNode('compare_expr')
        node.children.append(self.parseArithmExpr())

        token = self.next_token
        if token[0] in [Token.LESS, Token.LESS_OR_EQUAL, Token.GREATER, Token.GREATER_OR_EQUAL]:
            node.children.append(TreeNode('token', token))
            node.children.append(self.parseArithmExpr())
        else:
            self.cur_token_idx -= 1

        return node

    def parseArithmExpr(self) -> TreeNode:
        node = TreeNode('arithm_expr')
        node.children.append(self.parseTerm())

        token = self.next_token
        while token[0] in [Token.PLUS, Token.MINUS]:
            node.children.append(TreeNode('token', token))
            node.children.append(self.parseTerm())
            token = self.next_token

        self.cur_token_idx -= 1
        return node

    def parseTerm(self) -> TreeNode:
        node = TreeNode('term')
        node.children.append(self.parsePowerTerm())

        token = self.next_token
        while token[0] in [Token.MULTIPLICATION, Token.DIVISION, Token.MOD]:
            node.children.append(TreeNode('token', token))
            node.children.append(self.parsePowerTerm())
            token = self.next_token

        self.cur_token_idx -= 1
        return node

    def parsePowerTerm(self) -> TreeNode:
        node =  TreeNode('power_term')
        node.children.append(self.parseFactor())

        token = self.next_token
        while token[0] == Token.POW:
            node.children.append(TreeNode('token', token))
            node.children.append(self.parseFactor())
            token = self.next_token

        self.cur_token_idx -= 1
        return node

    def parseFactor(self) -> TreeNode:
        node = TreeNode('factor')
        token = self.next_token

        if token[0] in [Token.MINUS, Token.NOT]:
            node.children.append(TreeNode('token', token))
            token = self.next_token

        if token[0] in [Token.IDENTIFIER, Token.INTEGER, Token.FLOAT, Token.TRUE, Token.FALSE, Token.STRING]:
            node.children.append(TreeNode('token', token))
            return node
        elif token[0] == Token.BRACKET_LEFT:
            node.children.append(TreeNode('token', token))
            node.children.append(self.parseExpr())
            token = self.next_token
            if token[0] == Token.BRACKET_RIGHT:
                node.children.append(TreeNode('token', token))
                return node

        raise ParseException(f"Error in factor. Unexpected \"{token[1]}\"")

    def parseIfStmt(self) -> TreeNode:
        node = TreeNode("if_stmt")

        token = self.next_token
        if token[0] == Token.IF:
            node.children.append(TreeNode('token', token))
            token = self.next_token
            if token[0] == Token.BRACKET_LEFT:
                node.children.append(TreeNode('token', token))
                node.children.append(self.parseExpr())
                token = self.next_token
                if token[0] == Token.BRACKET_RIGHT:
                    node.children.append(TreeNode('token', token))
                    token = self.next_token
                    if token[0] == Token.BRACE_LEFT:
                        node.children.append(TreeNode('token', token))
                        token = self.next_token
                        while token[0] != Token.BRACE_RIGHT:
                            self.cur_token_idx -= 1
                            node.children.append(self.parseStmt())
                            token = self.next_token
                        node.children.append(TreeNode('token', token))
                        token = self.next_token
                        if token[0] == Token.ELSE:
                            node.children.append(TreeNode('token', token))
                            token = self.next_token
                            if token[0] == Token.BRACE_LEFT:
                                node.children.append(TreeNode('token', token))
                                token = self.next_token
                                while token[0] != Token.BRACE_RIGHT:
                                    self.cur_token_idx -= 1
                                    node.children.append(self.parseStmt())
                                    token = self.next_token
                                node.children.append(TreeNode('token', token))
                                return node
                        else:
                            self.cur_token_idx -= 1
                            return node

        raise ParseException(f"Error in if statement. Unexptected \"{token[1]}\"")

    def parseForStmt(self) -> TreeNode:
        node = TreeNode("for_stmt")

        token = self.next_token
        if token[0] == Token.FOR:
            node.children.append(TreeNode('token', token))
            token = self.next_token
            if token[0] == Token.BRACKET_LEFT:
                node.children.append(TreeNode('token', token))
                node.children.append(self.parseAssign())
                node.children.append(self.parseExpr())
                token = self.next_token
                if token[0] == Token.SEMICOLON:
                    token = self.next_token
                    if token[0] == Token.BRACKET_RIGHT:
                        node.children.append(TreeNode('token', token))
                        token = self.next_token
                        if token[0] == Token.BRACE_LEFT:
                            node.children.append(TreeNode('token', token))
                            token = self.next_token
                            while token[0] != Token.BRACE_RIGHT:
                                self.cur_token_idx -= 1
                                node.children.append(self.parseStmt())
                                token = self.next_token
                            node.children.append(TreeNode('token', token))
                            return node

        raise ParseException(f"Error in for statement. Unexpected {token[0]}: \"{token[1]}\"")

    def parsePrintStmt(self) -> TreeNode:
        node = TreeNode("print_stmt")

        token = self.next_token
        if token[0] == Token.PRINT:
            node.children.append(TreeNode('token', token))
            token = self.next_token
            if token[0] == Token.BRACKET_LEFT:
                node.children.append(TreeNode('token', token))
                node.children.append(self.parseExpr())
                token = self.next_token
                while token[0] == Token.COMMA:
                    node.children.append(TreeNode('token', token))
                    node.children.append(self.parseExpr())
                    token = self.next_token
                if token[0] == Token.BRACKET_RIGHT:
                    node.children.append(TreeNode('token', token))
                    token = self.next_token
                    if token[0] == Token.SEMICOLON:
                        node.children.append(TreeNode('token', token))
                        return node

        raise ParseException(f"Error in print statement. Unexpected \"{token[1]}\"")

    def parse(self):
        self.parseProg()
        return self.tree
