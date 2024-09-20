// import dependencies
const express = require('express');
const cookieParser = require('cookie-parser');
const hbs = require('express-handlebars');
const path = require('path');

// import handlers
const chatroomHandler = require('./roomHandler.js');
const homeHandler = require('./controllers/home.js');
const roomHandler = require('./controllers/room.js');

const app = express();
const port = 8080;

app.use(express.json());
app.use(express.urlencoded({extended: true}));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

// If you choose not to use handlebars as template engine, you can safely delete the following part and use your own way to render content
// view engine setup
app.engine('hbs', hbs({extname: 'hbs', defaultLayout: 'layout', layoutsDir: __dirname + '/views/layouts/'}));
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'hbs');

//API Calls
app.post('/create/:name', (req, res) => {
	try {
		let id = chatroomHandler.CreateRoom(req.params.name);
		res.status(200).json({id: id});
	} catch (e) {
		res.status(500).send(e);
	}
})

app.use(express.json());
app.post('/:roomId/newMessage', (req, res) => {
	try {
		chatroomHandler.AddMessage(req.body, req.params.roomId);
		res.status(200).send();
	} catch (err) {
		res.send(500).send(err);
		console.log(err);
	}	
})

app.get('/:roomId/messages', (req, res) => {
	try {
		let msgs = chatroomHandler.GetMessages(req.params.roomId);
		res.status(200).json(msgs);
	} catch (err) {
		res.status(500).send(err);
	}
})

//Renders/HTML
app.get('/', homeHandler.getHome);
app.get('/:roomId', roomHandler.getRoom);

app.listen(port, () => console.log(`Server listening on http://localhost:${port}`));