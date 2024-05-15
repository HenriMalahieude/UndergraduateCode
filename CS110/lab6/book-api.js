const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');

const app = express();
const port = 3000;

// Where we will keep books
let books = [];

app.use(cors());

app.use(bodyParser.urlencoded({extended: false}));
app.use(bodyParser.json());

//All POSTs
app.post('/book', (req, res) => {
	const book = req.body;

	console.log(book);
	books.push(book);
});

app.post('/book/:isbn', (req, res) => {
	const isbn = req.params.isbn;
	const newBook = req.body;

	console.log(isbn, newBook);

	for (let i = 0; i < books.length; i++) {
		let book = books[i];

		if (book.isbn === isbn) {
			books[i] = newBook;
			return;
		}
	}

	res.status(404).send("Did not exist?");
});

//All GETs
app.get('/delete/:isbn', (req, res) => {
	const isbn = req.params.isbn;

	for (let i = 0; i < books.length; i++) {
		if (books[i].isbn === isbn) {
			books.splice(i, 1);
			res.status(200).send("Success");
			return;
		}
	}

	res.status(404).send("Did not exist?");
})

app.get('/book', (req, res) => {
	res.status(200).json(books);
});

app.get('/book/:isbn', (req, res) => {
	const isbn = req.params.isbn;

	for (let i = 0; i < books.length; i++) {
		if (books[i].isbn === isbn) {
			res.status(200).json(books[i]);
			return;
		}
	}

	res.status(404).send('Did not exist?');
})

app.listen(port, () => console.log(`Hello world app listening on port ${port}`));