// Controller handler to handle functionality in home page
const chatroomHandler = require('../roomHandler.js');
// Example for handle a get request at '/' endpoint.

function getHome(request, response){
  let roomInfo = chatroomHandler.GetRoomsInfo();
  if (roomInfo.length <= 0) {
    roomInfo.push({id: "00000", name: "None Exist", visible:"invisible"});
  }

  response.render('home', {title: 'Home', rooms: roomInfo});
}

module.exports = {
    getHome
};