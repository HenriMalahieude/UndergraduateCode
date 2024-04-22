var turn = "X";
var wins_x = 0;
var wins_o = 0;
var can_play = true
var two_player = true

function update_turn() {
	if (turn == "X") {
		turn = "O";
	} else {
		turn = "X";
	}

	var turn_display = document.getElementById("display_turn");
	turn_display.innerHTML = "It's " + turn + "'s Turn.";
}

function winner_tell(person) {
	var turn_display = document.getElementById("display_turn");
	turn_display.innerHTML = person + " Wins!";
}

function update_score() {
	var score_display = document.getElementById("display_score");
	score_display.innerHTML = "X: " + wins_x + ", O: " + wins_o;
}

function reset_board() {
	var board = document.getElementsByClassName("xo");
	for (var i = 0; i < board.length; i++) {
		board[i].innerHTML = ""
	}

	turn = "O";
	update_turn();
	can_play = true;
}

function reset_all() {
	reset_board();

	wins_o = 0;
	wins_x = 0;
	update_score();
}

function who_won() {
	var board = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"];
	var set = ['', '', '', '', '', '', '', '', ''];
	var filled = 0
	for (var i = 0; i < 9; i++) {
		var parent = document.getElementsByClassName(board[i]);
		var xo = parent[0].firstElementChild;
		if (xo.innerHTML.length > 0) {
			set[i] = xo.innerHTML;
			filled += 1;
		}
	}

	var pass = '';

	//Horizontal
	if (set[0].length > 0 && set[0] == set[1] && set[1] == set[2]) pass = set[0];
	if (set[3].length > 0 && set[3] == set[4] && set[4] == set[5]) pass = set[3];
	if (set[6].length > 0 && set[6] == set[7] && set[7] == set[8]) pass = set[6];
	
	//Vertical
	if (set[0].length > 0 && set[0] == set[3] && set[3] == set[6]) pass = set[0];
	if (set[1].length > 0 && set[1] == set[4] && set[4] == set[7]) pass = set[1];
	if (set[2].length > 0 && set[2] == set[5] && set[5] == set[8]) pass = set[2];

	//Diagonal
	if (set[0].length > 0 && set[0] == set[4] && set[4] == set[8]) pass = set[0];
	if (set[2].length > 0 && set[2] == set[4] && set[4] == set[6]) pass = set[2];

	if (pass != '') {
		if (pass == "X") {
			wins_x += 1;
			winner_tell("X");
		} else {
			wins_o += 1;
			winner_tell("O");
		}
		can_play = false;
		update_score();
	} else if (filled >= 9) {
		can_play = false;
	}
}

function robo_time() {
	reset_all();
	if (document.getElementById("robocheck").checked) { //robo time
		two_player = true;
	} else {
		two_player = false;
	}
}

function robo() {
	if (!can_play || two_player) return;

	var board = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"];
	//find marked
	for (var i = 0; i < board.length; i++) {
		var parent = document.getElementsByClassName(board[i]);
		var xo = parent[0].firstElementChild;
		if (xo.innerHTML.length > 0) {
			board.splice(i, 1);
			i = -1;
		}
	}

	var rando = Math.floor(Math.random() * board.length);
	document.getElementsByClassName(board[rando])[0].firstElementChild.innerHTML = "O";
	update_turn();
	who_won();
}

function mark_square(square) {
	if (!can_play) return;

	var board = document.getElementsByClassName(square);
	var xo = board[0].firstElementChild;

	xo.innerHTML = turn;

	update_turn();
	who_won();

	robo();
}

reset_all();