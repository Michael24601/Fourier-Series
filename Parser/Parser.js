/******************************************************************************
 * This file takes as input an SVG file. It then checks wether or not it is
 * a single path file or a multiple path file. 
******************************************************************************/

const parse = require("svg-parser");
var fs = require('fs');
var parsePath = require('parse-svg-path')

let uploadImage = (imageName) => {
    return fs.readFileSync(`./Public/SVG/${imageName}`, "utf8");
};

let getSVGPath = (svg) =>{
    return {
        width: parse.parse(svg).children[0].properties.width,
        height: parse.parse(svg).children[0].properties.height,
        path: parse.parse(svg).children[0].children[2].children[0].properties.d
    }
}

let parseSVGPath = (path) => {
    return parsePath(path);
}

let arrayToString = (array) => {
    let string = "";
    let lastX, lastY;
    for(a of array){
        switch(a[0]){
            case 'M':
                lastX = a[1]; 
                lastY = a[2];
                break;
            case 'L':
                string += `${lastX} ${lastY} ${a[1]} ${a[2]},`
                lastX = a[1]; 
                lastY = a[2];
                ;break;
            case 'Q':
                string += `${lastX} ${lastY} ${a[1]} ${a[2]} ${a[3]} ${a[4]},`
                lastX = a[3]; 
                lastY = a[4];
                break;
            case 'C':
                string += `${lastX} ${lastY} ${a[1]} ${a[2]} ${a[3]} ${a[4]} ${a[5]} ${a[6]},`
                lastX = a[5]; 
                lastY = a[6];
                break;
            case 'Z' : case 'z' :
                break;
        }
    }
    return string;
}
 

module.exports = {
    uploadImage : uploadImage,
    getSVGPath: getSVGPath,
    parseSVGPath : parseSVGPath,
    arrayToString: arrayToString

}