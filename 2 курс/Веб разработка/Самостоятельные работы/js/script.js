function javascript() {
  // 1. Объявить две числовых переменных. Одна из переменных с номером варианта. Вторая переменная равна шести.
  let variantNumber = 12;
  let numberSix = 6;

  // 2. Добавить восемь разных условий, которые сравнивают эти переменные и выводят результат в консоль браузера.
  if (variantNumber > numberSix) {
    console.log("variantNumber больше numberSix");
  } else {
    console.log("variantNumber не больше numberSix");
  }

  if (variantNumber < numberSix) {
    console.log("variantNumber меньше numberSix");
  }

  if (variantNumber >= numberSix) {
    console.log("variantNumber больше или равен numberSix");
  } else {
    console.log("variantNumber не больше и не равен numberSix");
  }

  if (variantNumber <= numberSix) {
    console.log("variantNumber меньше или равен numberSix");
  }

  if (variantNumber === numberSix) {
    console.log("variantNumber равен numberSix");
  } else {
    console.log("variantNumber не равен numberSix");
  }

  if (variantNumber !== numberSix) {
    console.log("variantNumber не равен numberSix");
  }

  if (variantNumber + numberSix > 10) {
    console.log("Сумма variantNumber и numberSix больше 10");
  } else {
    console.log("Сумма variantNumber и numberSix не больше 10");
  }

  if (variantNumber * numberSix < 10) {
    console.log("Произведение variantNumber и numberSix меньше 10");
  } else {
    console.log("Произведение variantNumber и numberSix не меньше 10");
  }

  // 3. Добавить условный (тернарный) оператор с выводом сообщения в консоль.
  let message =
    variantNumber > numberSix
      ? "variantNumber больше numberSix"
      : "variantNumber не больше numberSix";
  console.log(message);

  // 4. Сложить две переменных и вывести результата в консоль.
  let sum = variantNumber + numberSix;
  console.log("Сумма:", sum);

  // 5. Используя краткую форму прибавить получившемуся значению единицу и вывести результат в консоль.
  sum += 1;
  console.log("Сумма + 1:", sum);

  // 6. Объявить массив строк из шести элементов.
  let stringArray = ["apple", "banana", "cherry", "date", "elderberry", "fig"];

  // 7. Используя цикл вывести все элементы в консоль.
  for (let i = 0; i < stringArray.length; i++) {
    console.log(stringArray[i]);

    // 8. В цикл добавить проверку по поиску подстроки, и если условие выполняется, то вывести его в консоль со знаком восклицания.
    if (stringArray[i].includes("a")) {
      console.log(stringArray[i] + "!");
    }
  }

  // 9. Удалить второй и пятый элементы массива. Вывести результат в консоль.
  stringArray.splice(1, 1); // Удаляет элемент с индексом 1 (второй элемент)
  stringArray.splice(3, 1); // Удаляет элемент с индексом 3 (пятый элемент после предыдущего удаления)
  console.log("Массив после удаления:", stringArray);

  // 10. Объявить функцию с темой варианта.
  function showTopic() {
    // 11. При вызове функции должно показываться окно alert с названием темы.
    alert("Тема: Пример выполнения задания");
  }

  // 12. Создать глобальную переменную для хранения значения типа данных Boolean со значением false.
  let confirmationFlag = false;

  // 13. Добавить функцию, которая запрашивает у пользователя подтверждение. В случае подтверждения, назначить глобальной переменной значение true и вывести результат в консоль.
  function askConfirmation() {
    if (confirm("Вы подтверждаете?")) {
      confirmationFlag = true;
    }
    console.log("Подтверждение:", confirmationFlag);
  }

  // 14. Преобразовать строку в число и вывести результат в консоль.
  let stringToNumber = parseInt("123", 10);
  console.log("Преобразованное число:", stringToNumber);

  // 15. Создать объект с использованием инициализатора объекта или любым другим способом:
  let topicObject = {
    // a. Задать название объекта, как название темы.
    // i. Первая пара имени свойства и значения строкового типа - предложение с переносом строки (New line).
    description: "Это объект\nс новой строкой",
    // ii. Вторая пара имени свойства и значения - числового типа с номером варианта.
    variant: variantNumber,
    // iii. Третья пара имени свойства и значений - массив строк.
    stringArray: ["apple", "banana", "cherry"],
    // iv. Четвертая пара имени свойства и значений - произвольный массив чисел.
    numbers: [1, 2, 3, 4, 5],
    // v. Пятая пара имени свойства и значения - объект.
    nestedObject: {
      nestedKey: "nestedValue",
    },
  };

  // b. Вывести объект в консоль.
  console.log("Объект:", topicObject);

  // c. Обратиться к первому элементу массива свойства объекта и заменить его на название темы и вывести в консоль.
  topicObject.stringArray[0] = "Пример выполнения задания";
  console.log("Измененный массив строк:", topicObject.stringArray);

  // d. Найти и вывести в консоль максимальное значение из массива чисел.
  let maxNumber = Math.max(...topicObject.numbers);
  console.log("Максимальное значение:", maxNumber);

  // 16. Добавить функцию, которая преобразует входную строку в верхний регистр.
  function toUpperCase(str) {
    return str.toUpperCase();
  }

  // 17. Вызвать функцию и вывести результат в консоль.
  console.log("Преобразованная строка:", toUpperCase("example string"));

  // 18. Добавить в ранее созданный объект новое свойство со значением даты.
  topicObject.currentDate = new Date();

  // 19. Вывести свойство объекта типа дата в консоль.
  console.log("Текущая дата:", topicObject.currentDate);
}
