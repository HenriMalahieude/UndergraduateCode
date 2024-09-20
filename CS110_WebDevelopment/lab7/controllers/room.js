// Controller handler to handle functionality in room page
const chatroomHandler = require('../roomHandler.js');

// Example for handle a get request at '/:roomName' endpoint.
function getRoom(request, response){
    let room = chatroomHandler.GetRoomInfo(request.params.roomId);

    response.render('room', {title: 'Chatroom \''+room.name+'\'', roomName: room.name, roomId: room.id});
}

module.exports = {
    getRoom
};