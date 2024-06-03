document.addEventListener("DOMContentLoaded", function (event) {
    init();
});
function init() {
    let uri = "https://api.ipify.org/?format=json";
    let request = new XMLHttpRequest();
    request.open("GET", uri);
    request.onload = function () {

        let obj = JSON.parse(request.responseText);

        document.getElementById('111').innerHTML = obj.ip;
        console.log(obj.ip);
    };
    request.send();

    let ur = "https://restcountries.com/v2/name/deutschland";
    let reques = new XMLHttpRequest();
    reques.open("GET", ur);
    reques.onload = function () {
        let ob = JSON.parse(reques.responseText);
        document.getElementById('11').innerHTML = ob[0].name;
        document.getElementById('12').innerHTML = ob[0].capital;
        document.getElementById('13').innerHTML = ob[0].region;
        document.getElementById('14').innerHTML = ob[0].nativeName;
        document.getElementById('16').innerHTML = ob[0].translations.es;
        console.log(ob[0].name);
        console.log(ob[0].capital);
        console.log(ob[0].region);
        console.log(ob[0].nativeName);
        console.log(ob[0].languages.nativeName);
        console.log(ob[0].translations.es);

        let pc = document.getElementById("222");
        pc.innerHTML = `<img style="width: 300px" src='${ob[0].flag}'>`;
    };
    reques.send();

    let u = "http://numbersapi.com/random/trivia?json";
    let reque = new XMLHttpRequest();
    reque.open("GET", u);
    reque.onload = function () {
        let obb = JSON.parse(reque.responseText);

        document.getElementById('44').innerHTML = obb.text;
        console.log(obb.text);
    };
    reque.send();

    
}


function geocoder (event) {
    let ppe = `https://geocode-maps.yandex.ru/1.x/?apikey=7b9fb346-cd33-469e-aa8e-746121e5f942&format=json&geocode=${event.target.value}`;
    let requez = new XMLHttpRequest();
    requez.open("GET", ppe);
    requez.onload = function () {

        let obj = JSON.parse(requez.responseText);

        console.log(obj);

        document.getElementById('result').innerHTML = obj?.response?.GeoObjectCollection?.featureMember.map(item => item.GeoObject.name).join('<br>') || ''
    };
    requez.send();
}

