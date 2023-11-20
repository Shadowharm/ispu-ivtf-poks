// https://www.cs.trinity.edu/~jhowland/cs2322/2d/2d/

document.addEventListener('DOMContentLoaded', setup);

let ui = null;
let context;
let gridStep = 50;

const startPoints = [
        {x: 15, y: 15},
        {x: 80, y: 15},
        {x: 45, y: 55},
        {x: 15, y: 55},
]

const figure = {
    src: startPoints,
    points: startPoints,
}

const SIZE = 600;
let debug = false
function setup(){
    ui = new UI((transforms) => {
        clear();
        applyTransforms(transforms)
        drawFigure(figure);
    })

    const canvas = document.getElementById('canvas');
    canvas.width = SIZE;
    canvas.height = SIZE;

    context = canvas.getContext('2d');

    clear();
    drawFigure(figure);
    // space from -w/2 to w/2 so 0,0 will be center;
    // translate(width/2, height/2);
    const debugButton = document.getElementById('debug')
    debugButton.addEventListener('click', () => {
        debug = !debug;
        ui.updateViewBox()
    })
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

function clear(){
    context.fillStyle = 'white';
    context.fillRect(0, 0, SIZE, SIZE);    

    context.strokeStyle = 'rgb(230, 230, 230)';
    for(let i = 0; i <= SIZE; i += gridStep){
        line(0, i, SIZE, i);
        line(i, 0, i, SIZE);
    }
}

function debugRotate(points, newPoints, t){
    for(let i = 0; i < points.length; i++){
        const p1 = points[i];
        const dx = p1.x - t.x;
        const dy = p1.y - t.y;
        const r = Math.sqrt(dx*dx + dy*dy);
        circle(t.x, t.y, r);
    }
}

function debugTranslate(points, newPoints){
    context.strokeStyle = 'black';
    for(let i = 0; i < points.length; i++){
        line(points[i].x, points[i].y, newPoints[i].x, newPoints[i].y);
    }
}

function debugScale(points, newPoints){
    context.strokeStyle = 'black';
    for(let i = 0; i < points.length; i++){
        line(points[i].x, points[i].y, newPoints[i].x, newPoints[i].y);
    }
} 
function debugSkew(points, newPoints){
    context.strokeStyle = 'black';
    for(let i = 0; i < points.length; i++){
        line(points[i].x, points[i].y, newPoints[i].x, newPoints[i].y);
    }
} 

function debugTransform(points, newPoints, transformation){
    context.strokeStyle = 'black';
    switch(transformation.type){
        case 'rotate': return debugRotate(points, newPoints, transformation);
        case 'translate': return debugTranslate(points, newPoints, transformation);
        case 'scale': return debugScale(points, newPoints, transformation);
        case 'skew': return debugSkew(points, newPoints, transformation);
    }
}


function applyTransform(points, transformation){
    let newPoints;
    if(transformation.type === 'translate'){
        newPoints = points.map(point => ({x: point.x + transformation.x,
                                     y: point.y + transformation.y}));

    }else if(transformation.type === 'rotate'){
        const angle =  Math.PI * transformation.angle / 180;
        const cosa = Math.cos(angle);       
        const sina = Math.sin(angle);       
        newPoints = points.map(point => { 
            const dx = point.x - transformation.x;
            const dy = point.y - transformation.y;
            return {
                x:  (dx*cosa - dy*sina) + transformation.x,
                y:  (dx*sina + dy*cosa) + transformation.y
            }
        });
    }else if(transformation.type === 'scale'){
        newPoints = points.map(point => ({x: point.x * transformation.x,
                                     y: point.y * transformation.y}));
    }else if(transformation.type === 'skew'){
        newPoints = points.map(point => ({x: point.x * transformation.a + point.y * transformation.c,
                                     y: point.x * transformation.b + point.y * transformation.d}));
    }

    if (debug) {
        debugTransform(points, newPoints, transformation);
    }
    return newPoints;
}

function applyTransforms(transformations){
    clear();
    let points = figure.src;
    figure.points = points;
    drawFigure(figure);
    for(let transformation of transformations){
        points = applyTransform(points, transformation);
        figure.points = points;
        drawFigure(figure);
    } 
}

function drawFigure(figure) {
    const rc = () => Math.round(255*Math.random());
    context.strokeStyle = `rgb(${rc()}, ${rc()}, ${rc()})`
    context.beginPath();
    context.moveTo(figure.points[0].x, figure.points[0].y);
    for(let i = 1; i < figure.points.length; i++){
        const point = figure.points[i];
        context.lineTo(point.x, point.y);
    }
    
    context.closePath();
    context.stroke();
}

