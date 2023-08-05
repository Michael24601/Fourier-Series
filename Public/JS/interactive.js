

import Interactive from "https://vectorjs.org/interactive.js";

let MAX = 500;

let loadInteractive = () =>{
    // Construct an interactive within the HTML element with the id "my-interactive"
    let myInteractive = new Interactive("my-interactive");
    myInteractive.border = true;

    myInteractive.height = 1000;
    myInteractive.width = 1000;

    // Sets the center as (0, 0)
    myInteractive.originX = myInteractive.width / 2;
    myInteractive.originY = myInteractive.height / 2;
    
    let string = $('#output').text();
    let points = convertStringtoPoints(string);
    let circles = loadCircles(myInteractive, points);
    let vectors = loadVectors(myInteractive, points);

    let fourierSeries = [];
    for(let i = 0; i < circles.length && i < MAX; i++){
        let radius = circles[i].r;
        let speed;
        if(i % 2 === 1){
            speed = Math.floor((i+1)/2);
        }
        else{
            speed = Math.floor(-i/2);
        }
        fourierSeries.push({circle : circles[i], vector: {line: vectors[i], length: radius, originalX1: vectors[i].x1,
            originalX2: vectors[i].x2, originalY1: vectors[i].y1, originalY2: vectors[i].y2}, 
            speed: speed});
    }

    // Time in milliseconds
    setTimeout(()=>{    animation(myInteractive, fourierSeries, 10000);}, 3000)
}

window.onload =  () => {
    document.querySelector('#buttonLoad').addEventListener('click', loadInteractive);
};

let convertStringtoPoints = (string) =>{
    let array = string.split(' ');
    let output = [];
    for(let i = 0; i < array.length - 1; i+=2){
        output.push({x: parseFloat(array[i]), y: parseFloat(array[i+1])});
    }
    return output;
} 

let loadCircles = (myInteractive, points) => {
    // All circles
    let circles = [];
    let sum = {x : 0, y : 0};
    for(let i = 0; i < points.length && i < MAX; i++){
        let radius = Math.pow((points[i].x * points[i].x) + (points[i].y * points[i].y), 0.5);
        let c = myInteractive.circle(sum.x, sum.y, radius);
        c.classList.add('default');
        circles.push(c);
        sum.x += points[i].x;
        sum.y += points[i].y;
    }

    return circles;
}

let loadVectors = (myInteractive, points) => {
    // All circles
    let vectors = [];
    let sum = {x : 0, y : 0};
    for(let i = 0; i < points.length && i < MAX; i++){
        let l = myInteractive.line(sum.x, sum.y, sum.x + points[i].x, sum.y + points[i].y);
        l.style.stroke = 'blue';
        vectors.push(l);
        sum.x += points[i].x;
        sum.y += points[i].y;
    }

    return vectors;
}

let animation = (myInteractive, fourierSeries, totalTime) => {
    // let scrubber = myInteractive.scrubber(-400, 400, {});
    // scrubber.min = 0;
    // scrubber.width = 100;
    // scrubber.max = 1000;
    // console.log(scrubber.width);

    let fps = 60;
    let intervalLength = 1000/fps;

    // Since the fourier series takes place from 0 to 1
    // For every frame, instead of sending the frame length
    // as a time parameter, we increment by totalTime/frameLength 
    // That way, we are done at 1. 

    let deltaT = (1000*intervalLength)/totalTime;

    console.log(deltaT);

    let startTime = Date.now();

    let sum =0, j = 0;

    let lastVector = fourierSeries[fourierSeries.length - 1].vector.line;
    let lineX = lastVector.x2, lineY = lastVector.y2;

    // time in in milliseconds
    let moveControl = () => {


        let time = Date.now();

        // temp = Date.now();

        if(sum >= 1000)
            return;
    
        let shift = {x: 0, y: 0};

        for(let i = 0; i < fourierSeries.length; i++){
            let s = rotateVector(fourierSeries[i].vector, fourierSeries[i].speed, deltaT, totalTime);

            fourierSeries[i].circle.cx =  fourierSeries[i].circle.cx + shift.x;
            fourierSeries[i].circle.cy =  fourierSeries[i].circle.cy +  shift.y;

            fourierSeries[i].vector.line.x1 = fourierSeries[i].vector.line.x1 + shift.x;
            fourierSeries[i].vector.line.y1 = fourierSeries[i].vector.line.y1 + shift.y;

            shift.x = shift.x + s.x;
            shift.y = shift.y + s.y;

            fourierSeries[i].vector.line.x2 +=  shift.x;
            fourierSeries[i].vector.line.y2 +=  shift.y;

            // Adds a line
            if(i === fourierSeries.length -1){
                let x = fourierSeries[i].vector.line.x2;
                let y = fourierSeries[i].vector.line.y2;
                let line = myInteractive.line(lineX, lineY, x, y);
                lineX = x;
                lineY = y;
                line.style.stroke = 'red';
            }
        }

        // wait so that the frames remain constant
        let interval = Date.now() - time;

        sum += deltaT;
        j++;

        if(intervalLength - interval > 0){
            setTimeout(() => {
                requestAnimationFrame(moveControl);
                }, (intervalLength - interval));
        }
        else{
            requestAnimationFrame(moveControl);
        }
    }
    requestAnimationFrame(moveControl);
}

// function that calculates how far the second point of a line
// travels when rotated at a certain speed in a time interval
// where one rotation at a speed of 1 occurs every time unit
let rotateVector = (vector, speed, deltaT, totalTime) => {

    let theta = 2 * Math.PI * speed * (deltaT / 1000);

    let cs = Math.cos(theta);
    let sn = Math.sin(theta);

    let x = vector.line.x2 - vector.line.x1;
    let y = vector.line.y2 - vector.line.y1;

    let newX = x * cs - y * sn;
    let newY = x * sn + y * cs;

    let shift = {x : newX - x, y : newY - y};

    return shift;
}

let rotateVectorFromStart = (vector, speed, fullT, totalTime) => {

    let theta = 2 * Math.PI * speed * (fullT / 1000);

    let cs = Math.cos(theta);
    let sn = Math.sin(theta);

    let x = vector.originalX2 - vector.originalX1;
    let y = vector.originalY2 - vector.originalX2;

    let newX = x * cs - y * sn;
    let newY = x * sn + y * cs;

    let shift = {x : newX - x, y : newY - y};

    return shift;
}