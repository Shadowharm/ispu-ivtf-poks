import Lexer from "./Lexer";
import Parser from "./Parser";

const code =
    `
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

	for (var count = 0; count < 10; count = count + 1) {
		factorial = factorial * count;
	}

	print("10! = ", factorial);
}`

const lexer = new Lexer(code);

lexer.lexAnalysis()
// console.log(lexer.tokenList.map(i => i.text).join('\n'));


const parser = new Parser(lexer.tokenList);


// console.log(parser);

const rootNode = parser.parseCode()

// parser.run(rootNode);
