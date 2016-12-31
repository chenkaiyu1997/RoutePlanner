var Papa = require("babyparse");

var fs = require("fs");
var coordtransform = require('coordtransform');
// 异步读取
fs.readFile('../data/toshow.txt', function (err, data) {
   if (err) {
       return console.error(err);
   }
   data = data.toString();
   lines = data.split("\n");
   var linnum = 0;
   var x, y;
   var a = [];
   //lines
   var m = parseInt(lines[linnum]);
   linnum++;
   var segs = [];
   for(var i = 0; i < m; i++) {
      x = parseInt(lines[linnum].split(' ')[0]);
      y = parseInt(lines[linnum].split(' ')[1]);
      x /= 1e5; y /= 1e5;
      a = [x,y];
      a = coordtransform.wgs84togcj02(a[0], a[1]);
      a = coordtransform.gcj02tobd09(a[0], a[1]);

      x = parseInt(lines[linnum].split(' ')[2]);
      y = parseInt(lines[linnum].split(' ')[3]);
      x /= 1e5; y /= 1e5;
      b = [x,y];
      b = coordtransform.wgs84togcj02(b[0], b[1]);
      b = coordtransform.gcj02tobd09(b[0], b[1]);

      segs[2*i] = [a[0], a[1]];
      segs[2*i + 1] = [b[0], b[1]];
      linnum++;
   }

   n = parseInt(lines[linnum]);
   linnum++;
   var markers = [];
   for(i = 0; i < n; i++) {
      x = parseInt(lines[linnum].split(' ')[0]);
      y = parseInt(lines[linnum].split(' ')[1]);
      x /= 1e5; y /= 1e5;
      a = [x,y];
      a = coordtransform.wgs84togcj02(a[0], a[1]);
      a = coordtransform.gcj02tobd09(a[0], a[1]);
      linnum++;
      markers[i] = [a[0], a[1]];
   }


   n = parseInt(lines[linnum]);
   linnum++;
   var points = [];
   for(i = 0; i < n; i++) {
      x = parseInt(lines[linnum].split(' ')[0]);
      y = parseInt(lines[linnum].split(' ')[1]);
      x /= 1e5; y /= 1e5;
      a = [x,y];
      a = coordtransform.wgs84togcj02(a[0], a[1]);
      a = coordtransform.gcj02tobd09(a[0], a[1]);
      linnum++;
      points[i] = [a[0], a[1]];
   }

   var myexport = {
      "lines": segs,
      "markers": markers,
      "points" : points
   }
   console.log(myexport);
   fs.writeFile('toshow.json', JSON.stringify(myexport));
});

