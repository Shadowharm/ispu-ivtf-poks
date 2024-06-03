document.addEventListener("DOMContentLoaded", function (event) {
    init();
  });
  function init() {
    var head = document.getElementById("zagolovok");
    head.innerHTML += " 12";
    head.addEventListener("mouseover", function () {
      zagolovok.className = "zag";
    });
    head.addEventListener("mouseout", function () {
      zagolovok.className = "zag";
    });
  
    var d = new Date(); 
    var hour = d.getHours();
    var min = d.getMinutes();
    var day = d.getDay();
    var mon = d.getMonth();
    var year = d.getFullYear();
    var dstr = day + "-" + ++mon + "-" + year + " " + ++hour + ":" + min;
    head.innerHTML += " Дата: " + dstr;
  
    var rr = document.getElementsByTagName("input");
    console.log(rr.length);
  
    var l = document.getElementsByTagName("label");
    for (var i = 0; i < l.length; i++) {
      l[i].style.fontWeight = "bold";
      l[i].style.color = "blue";
    }
  
    var parent = document.getElementById("kurs");
    var child = document.getElementById("kurs1");
    parent.removeChild(child);
  
    var s = document.getElementById("sel");
    var opt = document.createElement("option");
    var text = document.createTextNode("Очно-заочная");
    opt.appendChild(text);
    s.appendChild(opt);
    opt.value = "Очно-заочная";
  
    var form = document.getElementById("forma");
    parent = form.parentNode;
    var p = document.createElement("p");
    text = document.createTextNode(
      "Бег-один из основных дисциплин в легкой атлетике."
    );
    p.appendChild(text);
    parent.insertBefore(p, form);
  
    var inputData = document.getElementById("data");
    inputData.addEventListener("input", function () {
      var minData = "1912-01-01";
      if (inputData.value < minData) {
        alert("Неверная дата рождения!");
      }
    });
    var newCheckBox = document.createElement("input");
    newCheckBox.type = "checkbox";
    form.appendChild(newCheckBox);
    var newTextArea = document.createElement("input");
    form.appendChild(newTextArea);
    newTextArea.style.display = "none";
    newCheckBox.addEventListener("change", function () {
      if (newCheckBox.checked) {
        newTextArea.style.display = "block";
      } else {
        newTextArea.style.display = "none";
      }
    });
  
    var pol = document.getElementsByName("gender");
    var dat = {
      fN: document.getElementsByName("FirstName").value,
      sN: document.getElementsByName("SecondName").value,
      polM: pol[0].checked,
      polF: pol[1].checked,
      bD: inputData.value,
      form: document.getElementById("sel").value,
      test1: document.getElementsByName("fav").value,
      test2: document.getElementById("fi").value,
      test3: document.getElementById("fil").value,
      comment: document.getElementsByName("comments").value,
    };
    console.log(dat);
  }
  