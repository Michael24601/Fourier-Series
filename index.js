
const express = require('express');
const multer = require("multer");
const bodyParser = require('body-parser');
require('dotenv').config();

/*
    The addon is always in build/Release, 
    and its name is set by the binding file
*/
const cppAddon = require('./build/Release/addon');
let parser = require('./Parser/Parser');
const path = require('path');
const app = express();
app.set('json spaces', 4);
app.use(bodyParser.urlencoded({extended: true}));


let Member = require("./Models/Member.js");

const PORT = process.env.PORT;


app.get('/login', (req, res)=>{
    res.sendFile(path.join(__dirname, 'Public/HTML/loginAl.html'));
});

app.get('/signup', (req, res)=>{
    res.sendFile(path.join(__dirname, 'Public/HTML/signup.html'));
});

app.get('/landing', (req, res)=>{
    res.sendFile(path.join(__dirname, 'Public/HTML/landing.html'));
});

app.post('/login', async (req, res) => {
    const {username, password} = req.body;

    await Member.findOne({ 
        where: { member_username: username } 
    }).then(async function (member) {
        if (!member) {
            res.status(401).send("Username or password is incorrect.");
        } else if (!await member.validPassword(password)) {
            res.status(401).send("Username or password is incorrect.");
        } else {
            res.status(200);
        }
    }).catch((error) => {
        console.log(error);
        res.status(500).send("Internal server error.");
    });
});


app.post('/signup', async (req, res) => {
    const {username, password} = req.body;

    await Member.findOne({ 
        where: { member_username: username } 
    }).then(async function (member) {
        if(member)
            res.status(409).send('Username already exists.');
        else{
            let user = {member_username: username, member_password: password};
            await Member.create(user);
            res.status(200);
        }
    }).catch((error) => {
        console.log(error);
        res.status(500).send("Internal server error.");
    });
});



app.listen(PORT, () => {
    console.log(`App listening at http://localhost: ${PORT}`);
});

app.use(express.static('Public'));



/*
let getComplexNumbers = (string, n, dt) => {
    return addon.generateFourrier(string, `${n}`, `${dt}`);
}

let getVectors = (string, n, dt) => {
    return addon.generateVectors(string, `${n}`, `${dt}`);
}

let getBezierCurves = (string) => {
    return addon.generateBezier(string);
}

app.get('/home', (req, res) => {
    res.sendFile(path.join(__dirname, 'Public/HTML/home.html'));
});

app.get('/draw', (req, res) => {
    res.sendFile(path.join(__dirname, 'Public/HTML/draw.html'));
});

//Used for image upload
var imageStorage = multer.diskStorage({   
    //Where uploaded file is placed
    destination: path.join(__dirname, 'Public/SVG'), 
    //Filename (randomized with date to ensure no conflicts)
    filename: (req, file, cb) => {
        cb(null, file.fieldname + '_' + Date.now() 
           + path.extname(file.originalname))
    }
 });

//Image configuration
const imageUpload = multer({
    //Size limit
    storage: imageStorage,
    limits: {
      fileSize: 1000000
    },
    //Picks what files are accepted and shown
    fileFilter(req, file, cb) {
        if (!file.originalname.match(/\.(svg)$/)) { 
            return cb(new Error('Please upload a Image'))
        }
        cb(undefined, true)
    }
});
  

app.post('/postImage', imageUpload.single('image'), (req, res) => {

    const image = parser.uploadImage(req.file.filename);

    let svg = parser.getSVGPath(image);
    console.log(svg);
    let array = parser.parseSVGPath(svg.path);
    let string = parser.arrayToString(array);
    let complexNumbers = getComplexNumbers(string, 500, 0.0001);
    let bezierCurves = getBezierCurves(string);
    let vectors = getVectors(string, 500, 0.0001);

    let json = {
        "SVG path" : path.join(`SVG/${req.file.filename}`),
        "Width" : svg.width,
        "Height": svg.height,
        "SVG" : svg.path,
        "Path as sent to addon" : string,
        "Bezier Curves": bezierCurves,
        "Vectors" : complexNumbers,
        "Fourier Series" : vectors
    };
    res.send(json);
}, (error, req, res, next) => {
    console.log({ error: error.message });
    res.send('error uploading image');
});

*/