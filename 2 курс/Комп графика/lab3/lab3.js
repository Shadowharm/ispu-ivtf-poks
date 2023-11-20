const NUM_SEGMENTS = 50;
const CIRCLE_RADIUS = 10;
const SIZE = 600;

let points = [];
let selectedPoint = null;

let needLinearSpline = true;
let needQuadraticSpline = true;
let needCubicSpline = true;

let context;

document.addEventListener('DOMContentLoaded', setup);


function setup(){
    const inputX = document.getElementById('inputX')
    const inputY = document.getElementById('inputY')

    const addButton = document.getElementById('addButton');
    addButton.addEventListener('click', () => {
        mousePressed({offsetX: +inputX.value, offsetY: +inputY.value});
        mouseReleased()
        inputX.value=''
        inputY.value=''
    })

    const linearSplineCheckbox = document.getElementById('linearSpline')
    const quadrtaticSplineCheckbox = document.getElementById('quadraticSpline')
    const cubicSplineCheckbox = document.getElementById('cubicSpline')

    linearSplineCheckbox.checked = needLinearSpline
    quadrtaticSplineCheckbox.checked = needQuadraticSpline
    cubicSplineCheckbox.checked = needCubicSpline
    linearSplineCheckbox.addEventListener('change', () => {
        needLinearSpline = !needLinearSpline
        draw()
    })
    quadrtaticSplineCheckbox.addEventListener('change', () => {
        needQuadraticSpline = !needQuadraticSpline
        draw()
    })
    cubicSplineCheckbox.addEventListener('change', () => {
        needCubicSpline = !needCubicSpline
        draw()
    })


    const canvas = document.getElementById('canvas');
    canvas.width = SIZE;
    canvas.height = SIZE;

    context = canvas.getContext('2d');
    canvas.onmousedown = mousePressed;
    canvas.onmousemove = mouseDragged;
    canvas.onmouseup = mouseReleased;
    clear();
}

function clear(){
    context.fillStyle = 'white';
    context.fillRect(0, 0, SIZE, SIZE);
}

function line(x1, y1, x2, y2){
    context.beginPath()
    context.moveTo(x1, y1);
    context.lineTo(x2, y2)
    context.stroke();
}

function circle(x, y, r){
    context.beginPath();
    context.arc(x, y, r, 0, 2*Math.PI);
    context.stroke();
}

function linearSpline(points){
    for(let i = 0; i < points.length - 1; i++){
        const point = points[i];
        const nextPoint = points[i+1];
        line(point.x, point.y, nextPoint.x, nextPoint.y);
    }
}

function sortPoints(a, b){
    return (a.x < b.x) ? -1 :
           (a.x > b.x) ? 1 : 0
}


function mouseDragged(e){
    const mouseX = e.offsetX;
    const mouseY = e.offsetY;

    if(selectedPoint){
        points.sort(sortPoints);
        selectedPoint.x = mouseX;
        selectedPoint.y = mouseY;
        draw();
    }

    return false;
}

function mouseReleased(){
    selectedPoint = null;
    return false;
}

function draw(){
    clear();
    context.strokeStyle = 'black';
    for(point of points){
        circle(point.x, point.y, CIRCLE_RADIUS);
    }
    
    // linearSpline(points);
    if(needLinearSpline){
        context.strokeStyle = 'red';
        linearSpline(points);
    }
    
    if(needQuadraticSpline){
        context.strokeStyle = 'green';
        let quadrtaticSpline = [];
        if(points.length >= 3){
            const spline = new QuadraticSpline(points);
            for(let i = 0; i < SIZE; i+=1){
                quadrtaticSpline.push({x: i, y: spline.getY(i)});
            }
        }
        linearSpline(quadrtaticSpline);
    }
    
    if(needCubicSpline){
        context.strokeStyle = 'blue';
        let cubicSpline = [];
        if(points.length >= 3){
            const spline = new CubicSpline(points);
            for(let i = 0; i < SIZE; i+=1){
                cubicSpline.push({x: i, y: spline.getY(i)});
            }
        }
        linearSpline(cubicSpline);
    }
    
}

const sq = x => x*x;

function mousePressed(e){
    const mouseX = e.offsetX;
    const mouseY = e.offsetY;
    

    if(mouseX < 0 || mouseX > 600 || mouseY < 0 || mouseY > 600) return;

    for(let point of points){
        if(Math.sqrt(sq(mouseX - point.x) + sq(mouseY - point.y)) < (CIRCLE_RADIUS*4)){
            selectedPoint = point;
            return false;
        } 
    }
    points = points.concat({x: mouseX, y: mouseY}).sort(sortPoints);
    draw();
}