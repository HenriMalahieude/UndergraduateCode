async function createRoom() {
	let roomName = prompt("Please enter the room name:", "Chatroom");

	if (roomName == undefined || roomName == "") return;

	let response = await fetch(`http://localhost:8080/create/${roomName}`, {method: 'POST'})
	if (response.status != 200) {
		console.log(`Error (${response.status}) when creating room!`);
		console.log(response);
		return;
	}

	let json = await response.json();
	window.location.href += `${json.id}`;
}