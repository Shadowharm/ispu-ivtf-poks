from Parser import TreeNode
from Analyze import Token

from typing import Any, cast


class Expr:
    node: TreeNode

    def __init__(self, node: TreeNode):
        self.node = node


class AssignStmt:
    var_name: str
    expr: Expr

    def __init__(self, node: TreeNode):
        offset = 0
        if node.children[0].token and node.children[0].token[0] == Token.VAR:
            offset = 1
        self.var_name = node.children[0 + offset].token[1]
        self.expr = Expr(node.children[2 + offset])


class IfStmt:
    condition: Expr
    success: list
    fail: list

    def __init__(self, node: TreeNode):
        self.condition = Expr(node.children[2])
        self.success = []
        self.fail = []

        if len(node.children) >= 6:
            node_idx = 5
            while node_idx < len(node.children):
                child = node.children[node_idx]
                if child.token and child.token[0] == Token.BRACE_RIGHT:
                    break
                if child.type == "assign":
                    self.success.append(AssignStmt(child))
                elif child.type == "if_stmt":
                    self.success.append(IfStmt(child))
                elif child.type == "for_stmt":
                    self.success.append(ForStmt(child))
                elif child.type == "print_stmt":
                    self.success.append(PrintStmt(child))
                else:
                    raise Exception(f"Неожиданный тип узла: {child.type}")
                node_idx += 1

            if len(node.children) >= node_idx + 3:
                node_idx += 3
                while node_idx < len(node.children):
                    child = node.children[node_idx]
                    if child.token and child.token[0] == Token.BRACE_RIGHT:
                        break
                    if child.type == "assign":
                        self.fail.append(AssignStmt(child))
                    elif child.type == "if_stmt":
                        self.fail.append(IfStmt(child))
                    elif child.type == "for_stmt":
                        self.fail.append(ForStmt(child))
                    elif child.type == "print_stmt":
                        self.fail.append(PrintStmt(child))
                    else:
                        raise Exception(f"Неожиданный тип узла: {node.type}")
                    node_idx += 1


class ForStmt:
    condition: Expr
    assign: AssignStmt
    body: list

    def __init__(self, node: TreeNode):
        self.body = []
        self.assign = AssignStmt(node.children[2])
        
        self.condition = Expr(node.children[3])

        node_idx = 6
        while node_idx < len(node.children):
            child = node.children[node_idx]
            if child.token and child.token[0] == Token.BRACE_RIGHT:
                break
            if child.type == "assign":
                self.body.append(AssignStmt(child))
            elif child.type == "if_stmt":
                self.body.append(IfStmt(child))
            elif child.type == "for_stmt":
                self.body.append(ForStmt(child))
            elif child.type == "print_stmt":
                self.body.append(PrintStmt(child))
            else:
                raise Exception(f"Неожиданный тип узла: {child.type}")
            node_idx += 1


class PrintStmt:
    exprs: list[Expr]

    def __init__(self, node: TreeNode):
        self.exprs = []
        for node in node.children[2 : len(node.children) - 2]:
            if node.type == "expr":
                self.exprs.append(Expr(node))


class Interpretator:
    vars: dict[str, Any]
    stmts: list[AssignStmt | IfStmt | ForStmt | PrintStmt]

    def __init__(self, nodes: list[TreeNode]) -> None:
        self.vars = {}
        self.stmts = []

        for node in nodes:
            if node.type == "assign":
                self.stmts.append(AssignStmt(node))
            elif node.type == "if_stmt":
                self.stmts.append(IfStmt(node))
            elif node.type == "for_stmt":
                self.stmts.append(ForStmt(node))
            elif node.type == "print_stmt":
                self.stmts.append(PrintStmt(node))
            else:
                raise Exception(f"Неожиданный тип узла: {node.type}")

    def interpret(self):
        for stmt in self.stmts:
            self.interpretatorStmt(stmt)

    def interpretatorStmt(self, stmt: AssignStmt | IfStmt | ForStmt | PrintStmt):
        if stmt.__class__ == AssignStmt:
            self.evalAssignStmt(cast(AssignStmt, stmt))
        elif stmt.__class__ == IfStmt:
            self.evalIfStmt(cast(IfStmt, stmt))
        elif stmt.__class__ == ForStmt:
            self.evalForStmt(cast(ForStmt, stmt))
        elif stmt.__class__ == PrintStmt:
            self.evalPrintStmt(cast(PrintStmt, stmt))
        else:
            raise Exception(f"Неожиданный тип выражения: {stmt.__class__}")

    def evalAssignStmt(self, stmt: AssignStmt):
        self.vars[stmt.var_name] = self.evalExpression(stmt.expr.node)

    def evalIfStmt(self, stmt: IfStmt):
        if (self.evalExpression(stmt.condition.node)):
            for stmt in stmt.success:
                self.interpretatorStmt(stmt)
        else:
            for stmt in stmt.fail:
                self.interpretatorStmt(stmt)

    def evalForStmt(self, stmt: ForStmt):
        # self.stmts.append(stmt.assign)
        self.evalAssignStmt(stmt.assign)
        while self.evalExpression(stmt.condition.node):
            for i in stmt.body:
                self.interpretatorStmt(i)

    def evalPrintStmt(self, stmt: PrintStmt):
        print(''.join(map(lambda expr: str(self.evalExpression(expr.node)), stmt.exprs)))

    def evalExpression(self, node: TreeNode):
        res_exists = False
        res = None

        for child in node.children:
            if child.type == 'and_expr':
                child_res = self.evalAndExpression(child)
                if res_exists:
                    res = res or child_res
                else:
                    res = child_res
                    res_exists = True

        return res

    def evalAndExpression(self, node: TreeNode):
        res_exists = False
        res = None

        for child in node.children:
            if child.type == 'equal_expr':
                child_res = self.evalEqualExpression(child)
                if res_exists:
                    res = res and child_res
                else:
                    res = child_res
                    res_exists = True

        return res

    def evalEqualExpression(self, node: TreeNode):
        if len(node.children) == 1:
            return self.evalCompareExpression(node.children[0])

        args = []
        for child in node.children:
            if child.type == 'compare_expr':
                args.append(self.evalCompareExpression(child))
            else:
                args.append(child.token[1])

        return eval(''.join(str(i) for i in args))

    def evalCompareExpression(self, node: TreeNode):
        if len(node.children) == 1:
            return self.evalArithmExpression(node.children[0])

        args = []
        for child in node.children:
            if child.type == 'arithm_expr':
                args.append(self.evalArithmExpression(child))
            else:
                args.append(child.token[1])

        return eval(''.join(str(i) for i in args))

    def evalArithmExpression(self, node: TreeNode):
        args = []

        for child in node.children:
            if child.type == 'term':
                args.append(self.evalTermExpression(child))
            elif child.type == 'token':
                args.append(child.token[1])

        if (len(args) == 1):
            return args[0]
        return eval(''.join(str(i) for i in args))

    def evalTermExpression(self, node: TreeNode):
        args = []

        for child in node.children:
            if child.type == 'power_term':
                args.append(self.evalPowerTermExpression(child))
            elif child.type == 'token':
                args.append(child.token[1])

        if (len(args) == 1):
            return args[0]
        return eval(''.join(str(i) for i in args))

    def evalPowerTermExpression(self, node: TreeNode):
        args = []

        for child in node.children:
            if child.type == 'factor':
                args.append(self.evalFactorExpression(child))

        if (len(args) == 1):
            return args[0]

        return eval('**'.join(map(lambda i: str(i), args)))

    def evalFactorExpression(self, node: TreeNode):
        offset = 0
        has_minus = False
        has_not = False
        res = None

        if node.children[0].type == 'token' and node.children[0].token[0] == Token.MINUS:
            offset = 1
            has_minus = True
        elif node.children[0].type == 'token' and node.children[0].token[0] == Token.NOT:
            offset = 1
            has_not = True

        if node.children[0 + offset].type == 'token' and node.children[0 + offset].token[0] == Token.IDENTIFIER:
            var_name = node.children[0 + offset].token[1]
            if var_name in self.vars:
                res = self.vars[node.children[0 + offset].token[1]]
            else:
                raise Exception(f"Переменная не найдена: {var_name}")
            # print(res, '<---')
        elif node.children[0 + offset].type == 'token' and node.children[0 + offset].token[0] == Token.INTEGER:
            res = node.children[0 + offset].token[1]
        elif node.children[0 + offset].type == 'token' and node.children[0 + offset].token[0] == Token.FLOAT:
            res = node.children[0 + offset].token[1]
        elif node.children[0 + offset].type == 'token' and node.children[0 + offset].token[0] == Token.STRING:
            res = node.children[0 + offset].token[1]
        elif node.children[0 + offset].type == 'token' and node.children[0 + offset].token[0] == Token.TRUE:
            res = True
        elif node.children[0 + offset].type == 'token' and node.children[0 + offset].token[0] == Token.FALSE:
            res = False
        elif node.children[0 + offset].type == 'token' and node.children[0 + offset].token[0] == Token.BRACKET_LEFT:
            res = self.evalExpression(node.children[1 + offset])
        else:
            raise Exception(f'Неожиданный символ: {node.children[0 + offset].token}')

        if has_minus:
            return -res
        elif has_not:
            return not res
        return res
