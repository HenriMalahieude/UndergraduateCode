let username = undefined;
let roomId = document.getElementsByTagName('h2')[0].innerHTML.substring(4);

function clearMessages() {
	document.getElementsByClassName('chats-container')[0].innerHTML = '';
}

function addMessage(author, time, contents) {
	document.getElementsByClassName('chats-container')[0].innerHTML += `\
    <div class="message">
        <div class="msg-meta">
            <div class="mm-author">
                ${author}
            </div>
            <div class="mm-date">
                ${time}
            </div>
        </div>
        <div class="msg-contents">
            ${contents}
        </div>
    </div>`
}

async function updateMessages() {
	let response = await fetch(window.location.href + "/messages");
	if (response.status != 200) {
		console.log(`Error (${response.status}) when getting messages!`);
		console.log(response);
		return;
	}

	clearMessages();
	let msgs = await response.json();
	for (let i = 0; i < msgs.length; i++) {
		addMessage(msgs[i].author, msgs[i].time, msgs[i].content);
	}
}

async function sendMessage() {
	let contents = document.getElementById("msgtext").value;
	while (username == undefined || username == "") {
		username = prompt("Please input a username:");
	}

	let res = await fetch(window.location.href + '/newMessage', {
		method: "POST",
		headers: {"Content-Type": "application/json"},
		body: JSON.stringify({author: username, content: contents})
	})

	if (res.status != 200) {
		console.log(`Error (${res.status}) when sending message!`);
		console.log(res);
	} else {
		document.getElemebyById("msgtext").value = "";
		updateMessages();
	}
}

setInterval(updateMessages, 3000);