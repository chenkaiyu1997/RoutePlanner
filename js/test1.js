$.ajax({
    url: 'toshow.json',
    dataType: 'json',
}).done(successFunction);

function successFunction(data) {
    var markers = [];
    for(var i = 0; i < data.markers.length; i++){
        markers[i] = new BMap.Point(data.markers[i][0], data.markers[i][1]);
    }
    //地图初始化
    var bm = new BMap.Map("allmap");
    bm.enableScrollWheelZoom(true);
    bm.centerAndZoom(markers[0], 15);
    for (var i = 0; i < markers.length; i++) {
        bm.addOverlay(new BMap.Marker(markers[i]));
    }

    if(data.points !== undefined){
        var points = [];
        for(i = 0; i < data.points.length; i++){
            points[i] = new BMap.Point(data.points[i][0], data.points[i][1]);
        }
        for (var i = 0; i < points.length; i++) {
            bm.addOverlay(new BMap.Circle(points[i],1));
        }
    }
    
    if(data.lines !== undefined){
        var lines = [], p1, p2;
        for(i = 0; i < data.lines.length; i+=2){
            p1 = new BMap.Point(data.lines[i][0], data.lines[i][1]);
            p2 = new BMap.Point(data.lines[i+1][0], data.lines[i+1][1]);
            bm.addOverlay(new BMap.Polyline([p1, p2], {strokeColor:"blue", strokeWeight:3, strokeOpacity:0.5}));
        }
    }
}