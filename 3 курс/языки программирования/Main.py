from Analyze import Scanner
from Parser import Parser
from interpretator import Interpretator

source_code = """
function main() {

	var source = 7;
    
    var factorial = 1;

	for (var count = 1; count < source + 1;) {
		factorial = factorial * count;
        count = count + 1;
	}

	print(source, "! = ", factorial);
    
    
    
    var firstValue = 8 * (6 - 2 ** 3 ** 4) + 1;
	print(firstValue, " <----- firstValue");
	
	var secondValue = !(firstValue > 5 && true);
	print(secondValue, " <----- secondValue");

	if (firstValue == secondValue) {
		print("Результат одинаковый");
	} else {
		print("Переменные разные!!!");
	}
}
"""

if __name__ == '__main__':
    scanner = Scanner(source_code)
    tokens = scanner.scan()
    
    parser = Parser(tokens)
    stmts = parser.parse()   
     
    # for node in parser.tree:
    #     node.print_tree()
    #     print('\n')
    
    
    interpretator = Interpretator(stmts)
    interpretator.interpret()
