//Load HTTP module
const http = require("http");
const hostname = '127.0.0.1';
const port = 3000;

const DARWIN_TOKEN = '4311f837-5f84-41c6-b309-13dcdf625541'
const Rail = require('national-rail-darwin')
const rail = new Rail(DARWIN_TOKEN)

const server = http.createServer((req, res) => {

  res.statusCode = 200;
  res.setHeader('Content-Type', 'text/plain');
  res.end('hw');
  //   const now = new Date()
  //   rail.getNextDeparture('BUG', 'BTN', {}, (err, resp) => {
  //   //   if (resp) {
  //   //     res.end(resp.trainServices[0].std.replace(':', ''));
  //   //   }
  //   //   res.end(
  //   //     now.getHours().toString().padStart(2, '0') + 
  //   //     now.getMinutes().toString().padStart(2, '0'))
  //   // })
});

//listen for request on port 3000, and as a callback function have the port listened on logged
server.listen(port, hostname, () => {
  console.log(`Server running at http://${hostname}:${port}/`);
});