let db
const createDatabase = () => {
  db = openDatabase("javascriptDB", "1.0", "javascriptDB", 65535);
  db.transaction((transaction) => {
    const sql =
      "CREATE TABLE items (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, item VARCHAR(2500) NOT NULL)";
    transaction.executeSql(sql, undefined, () => {
      alert("Таблица успешно создана");
    });
  });
};

const insert = () => {
  let item = document.getElementById("text").innerHTML;

  db.transaction((transaction) => {
    var sql = "INSERT INTO items(item) VALUES(?)";
    transaction.executeSql(sql, [item], () => {
      alert("Новая сущность успешно добавлена");
    });
  });
};
const result = () => {
  db.transaction(function (transaction) {
    const sql = "SELECT * FROM items ORDER BY id DESC";
    transaction.executeSql(sql, undefined, (transaction, result) => {
      const row = result.rows.item(0);
      texx = row.item;
      calculate(row.item);
    });
  });
};

const resultData = {
  countPredl: 0,
  countTypes: 0,
  countOperat: 0,
  countOperln: 0,
  countOperOut: 0
}

function calculate(text){
  const data = text.split('\\n');
  console.log(data);
  resultData.countPredl = data.length
  data.map(line => {
      const [key, value] = line.split('::=')
      if (/Простой тип переменной/i.test(key)) {
          resultData.countTypes = value.split('|').length
      } else if (/Оператор/i.test(key)) {
          resultData.countOperat += value.split('|').length
      }
      if (/Оператор ввода/i.test(key)) {
          resultData.countOperln = value.split('|').length
      }
      if (/Оператор вывода/i.test(key)) {
          resultData.countOperOut = value.split('|').length
      }
  })
  const outResult = text + '<br><br>' + `Количество предложений: ${resultData.countPredl}<br>
  Количество типов: ${resultData.countTypes}<br>
  Количество операторов: ${resultData.countOperat}<br>
  Количество операторов ввода: ${resultData.countOperln}<br>
  Количество операторов вывода: ${resultData.countOperOut}
  `

  document.getElementById('text').innerHTML = outResult
}


document.addEventListener('DOMContentLoaded', createDatabase)