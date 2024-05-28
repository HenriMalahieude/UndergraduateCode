const moment = require('moment');

let rooms = [];

function generateRoomIdentifier() {
    const chars = 'ABCDEFGHJKLMNPQRSTUVWXYZ23456789';

    let result = '';
    for (let i = 0; i < 6; i++)
        result += chars[(Math.floor(Math.random() * chars.length))];

    return result;
}

function CreateRoom(name) {
	let id = generateRoomIdentifier();

	rooms.push({id: id, name: name, msgs: []});

	return id;
}

function GetRoomsInfo() {
	return rooms.map((room) => { return {id: room.id, name: room.name} });
}

function GetRoomInfo(id) {
	for (let i = 0; i < rooms.length; i++) {
		if (rooms[i].id == id) {
			return rooms[i];
		}
	}

	return {};
}

function GetMessages(id) {
	for (let i = 0; i < rooms.length; i++) {
		if (rooms[i].id == id) {
			return rooms[i].msgs;
		}
	}

	return [];
}

function AddMessage(msg, id) {
	msg.time = moment().format("MMMM Do YYYY [@] h:mm:ss a");

	for (let i = 0; i < rooms.length; i++) {
		if (rooms[i].id == id) {
			rooms[i].msgs.push(msg);
		}
	}
}

module.exports = {
	GetRoomInfo,
	GetMessages,
	GetRoomsInfo,
	CreateRoom,
	AddMessage,
}